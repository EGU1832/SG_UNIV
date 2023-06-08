#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// functions for Min Heap
//{{{
// Data Structure - Min Heap
typedef struct {
    int* weight;
	int** edge;
    int size;
} MinHeap;

MinHeap mallocHeap(int edges){
	MinHeap heap;
	heap.size = 0;
	heap.weight = (int*)malloc(sizeof(int) * edges);
	heap.edge = (int**)malloc(sizeof(int*) * edges);
	for(int i = 0; i < edges; i++){
		heap.edge[i] = (int*)malloc(sizeof(int) * 2);
	}
	return heap;
}

int parent(int index) {
    return (index - 1) / 2;
}

int leftChild(int index) {
    return (2 * index) + 1;
}

int rightChild(int index) {
    return (2 * index) + 2;
}

void swap(int* curr, int* parrent) {
    int temp = *curr;
    *curr = *parrent;
    *parrent = temp;
}

void insert(MinHeap* heap, int value, int edge1, int edge2) {

    heap->weight[heap->size] = value;
	heap->edge[heap->size][0] = edge1;
	heap->edge[heap->size][1] = edge2;
    int current = heap->size;
    int parentIndex = parent(current);

    while (current > 0 && heap->weight[current] < heap->weight[parentIndex]) {
        swap(&heap->weight[current], &heap->weight[parentIndex]);
		swap(&heap->edge[current][0], &heap->edge[parentIndex][0]);
        swap(&heap->edge[current][1], &heap->edge[parentIndex][1]);
		current = parentIndex;
        parentIndex = parent(current);
    }

    heap->size++;
}

int findMinIndex(MinHeap* heap, int index){
	return (heap->weight[leftChild(index)] < heap->weight[rightChild(index)]) ? leftChild(index) : rightChild(index);
}

void heapify(MinHeap* heap, int index) {
    int smallest = index;
    int L = leftChild(index);
    int R = rightChild(index);

    if (L < heap->size && heap->weight[L] < heap->weight[smallest]) {
        smallest = L;
    }
    if (R < heap->size && heap->weight[R] < heap->weight[smallest]) {
        smallest = R;
    }
    if (smallest != index) {
        swap(&heap->weight[index], &heap->weight[smallest]);
		swap(&heap->edge[index][0], &heap->edge[smallest][0]);
        swap(&heap->edge[index][1], &heap->edge[smallest][1]);
        heapify(heap, smallest);
    }
}

void extractMin(MinHeap* heap){
	if (heap->size == 0){
		return;
	}

	heap->weight[0] = heap->weight[heap->size - 1];
	heap->edge[0][0] = heap->edge[heap->size - 1][0];
	heap->edge[0][1] = heap->edge[heap->size - 1][1];
	heap->size--;
	heapify(heap, 0);
}
//}}}

// functions for Parent
//{{{
int* mallocParent(int vertices) {
	int* parent = (int*)malloc(sizeof(int) * vertices);
	for (int i = 0; i < vertices; i++){
		parent[i] = i;
	}
	return parent;
}

int findRoot(int i, int* parent){
	if(parent[i] != i) {
		parent[i] = findRoot(parent[i], parent);
	}
	return parent[i];
}

void unionSets(int* parent, int u, int v) {
	int rootX = findRoot(u, parent);
	int rootY = findRoot(v, parent);

	if (rootX == rootY) {
		return;
	}

	else { parent[rootY] = rootX; }
}

int cycle(int*parent, int x, int y) {
    int rootX = findRoot(x, parent);
    int rootY = findRoot(y, parent);
    if (rootX == rootY)
        return 1;
    else
        return 0;
}
//}}}

//funtions for Connected & free
//{{{
int connected(int* parent, int first, int vertices){
	int root = findRoot(first, parent);
    for (int i = 0; i < vertices; i++) {
        if (i != first && findRoot(i, parent) != root) {
            return 0;
        }
    }
    return 1;
}

void freeMalloc(MinHeap* heap, int edges, int* parent){
	free(heap->weight);
	for(int i = 0; i < edges; i++){
		free(heap->edge[i]);
	}
	free(heap->edge);
	free(parent);
}
//}}}

// Usage funtion
void usage(char *program_name) {
    fprintf(stderr, "usage: %s input_filename\n", program_name);
    exit(1);
}

int main(int argc, char *argv[]) {

	// checking running time start
	clock_t start_time, end_time;
    double execution_time;
	start_time = clock();

	FILE *infile;
	FILE *outfile;
	char *filename;

	// open file
    if (argc != 2) {
        usage(argv[0]);
    }

	filename = argv[1];
	infile = fopen(filename, "r");
	if (infile == NULL) {
		printf("The input file does not exist\n");
		exit(1);
	}

	outfile = fopen("fp1_result.txt", "w+");

	//TODO : main function of hw3
	MinHeap heap;
	int* parent;
	int vertices, edges;
	int edge1, edge2, weight;	// (edge1, edge2) : weight

	// initialize or malloc the variables
	fscanf(infile, "%d", &vertices);
	fscanf(infile, "%d", &edges);
	heap = mallocHeap(edges);
	parent = mallocParent(vertices);

	while(fscanf(infile, "%d %d %d", &edge1, &edge2, &weight) > 0){
		insert(&heap, weight, edge1, edge2);
	}

	// Kruskal's algorithm start
	int T_index = 0;
	int total_cost = 0;
	int first = heap.edge[0][1];
	while(T_index < vertices - 1 && heap.size >= 0){
		if (!cycle(parent, heap.edge[0][0], heap.edge[0][1])){
			unionSets(parent, heap.edge[0][0], heap.edge[0][1]);
			T_index++;
			total_cost += heap.weight[0];
			fprintf(outfile, "%d %d %d\n", heap.edge[0][0], heap.edge[0][1], heap.weight[0]);
		}
		extractMin(&heap);
	}
	fprintf(outfile, "%d\n", total_cost);

	// check if Disjoin Set is connected
	if(connected(parent, first, vertices)) { fprintf(outfile, "CONNECTED\n"); }
	else { fprintf(outfile, "DISCONNECTED\n"); }

	// free malloc memories
	freeMalloc(&heap, edges, parent);

	// close file
	fclose(infile);
	fclose(outfile);
	printf("output written to fp1_result.txt\n");

	// checking running time end
	end_time = clock();
	execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("running time: %f seconds\n", execution_time);

	return 0;
}
