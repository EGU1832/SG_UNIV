#include <stdio.h>
#include <stdlib.h>

typedef struct Listnode *listPointer;
typedef struct Listnode {
    listPointer prev;
    int data;
    listPointer next;
} listnode;

void insert_(listPointer list, int item, int *HEADNODE) {
    listPointer newNode, currNode, prevNode;

    // Create a new node
    newNode = (listPointer) malloc(sizeof(listnode));
    newNode->data = item;

    // Find the proper position to insert the new node
    prevNode = list;
    currNode = list->next;

    if (*HEADNODE == 1) {
        list->data = item;
        free(newNode);
        *HEADNODE = 0;
        return;
    }

    if (list->data > item) {
    // Insert the new node
        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = currNode;
        currNode->prev = newNode;
        newNode->data = list->data;
        list->data = item;
        return;
    }
    else if (list->data < item ){ }
    else { free(newNode); return; }
	
    while (currNode != list && currNode->data < item) {
        prevNode = currNode;
        currNode = currNode->next;
    }

    // Do not insert if the node already exists
    if (currNode != list && currNode->data == item) {
        free(newNode);
        return;
    }

    // Insert the new node
    prevNode->next = newNode;
    newNode->prev = prevNode;
    newNode->next = currNode;
    currNode->prev = newNode;
}

void print_forward(listPointer list) {
	listPointer curr;
	FILE *outfile;
	outfile = fopen("hw2_result.txt", "a");
	if(list) {
		curr = list;
		while(1) {
			fprintf(outfile, "%d ", curr->data);
			 printf("%d ", curr->data);
			 curr = curr->next;
			 if(curr == list) break;
		}
	}
	fprintf(outfile, "\n");
	printf("\n");
	fclose(outfile);
}

int main() {
    int HEADNODE = 1;
    // Create the head node
    listPointer list = (listPointer) malloc(sizeof(listnode));
    list->prev = list;
    list->next = list;
	list->data = 0;

    // Insert nodes in ascending order
    insert_(list, 5, &HEADNODE);
    insert_(list, 3, &HEADNODE);
    insert_(list, 7, &HEADNODE);
    insert_(list, 1, &HEADNODE);

	print_forward(list);

    // Print the list in ascending order
    printf("Ascending order: ");
    listPointer currNode = list->next;
    while (currNode != list) {
        printf("%d ", currNode->data);
        currNode = currNode->next;
    }
    printf("\n");

    // Insert a node that already exists
    insert_(list, 5, &HEADNODE);

    // Print the list in ascending order again
    printf("Ascending order: ");
    currNode = list->next;
    while (currNode != list) {
        printf("%d ", currNode->data);
        currNode = currNode->next;
    }
    printf("\n");

    // Free the memory allocated for the list
    currNode = list->next;
    while (currNode != list) {
        listPointer temp = currNode;
        currNode = currNode->next;
        free(temp);
    }
    free(list);

    return 0;
}
