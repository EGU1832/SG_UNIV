#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100


enum {INSERT, DELETE, ASCEND, DESCEND};

typedef struct Listnode *listPointer;
typedef struct Listnode{
 	listPointer prev;
	int data;
	listPointer next;
} listnode;

int r_command(char* command_str);

void insert_(listPointer list, int item, int *HEADNODE);
listPointer delete_(listPointer list, int item);
void print_forward(listPointer list);
void print_reverse(listPointer list);

void usage(char *program_name) {
    fprintf(stderr, "usage: %s input_filename\n", program_name);
    exit(1);
}


int main(int argc, char *argv[]) {

	listPointer list;
	int HEADNODE = 1;
	
	list = (listPointer) malloc(sizeof(listnode));
	list->next = list;
	list->prev = list;

	FILE *infile;
	char *filename;
	char line[MAX_LINE_LENGTH];

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

	// execute command
	while(fgets(line, MAX_LINE_LENGTH, infile) != NULL) {

		line[strcspn(line, "\n")] = '\0';
		
		char command_str[MAX_LINE_LENGTH];
		int command = 0, item = 0;

		if (sscanf(line, "%s %d", command_str, &item) == 0) {
			fprintf(stderr, "Invalid command: %s\n", line);
			exit(1);
		}
		
		command = r_command(command_str);
		switch(command){
			case INSERT:
				insert_(list, item, &HEADNODE);
                // printf("insert %d %d %d %d\n", list->data, list->next->data, list->next->next->data, list->next->next->next->data);
				continue;
 			case DELETE:
 				list = delete_(list, item);
                // printf("delete %d %d %d %d\n", list->data, list->next->data, list->next->next->data, list->next->next->next->data);
				continue;
 			case ASCEND:
				print_forward(list);
				continue;
			case DESCEND:
				print_reverse(list);
				continue;
		}
	}

	fclose(infile);

	return 0;
}

int r_command(char* command_str) {
	if (strcmp(command_str, "INSERT") == 0) { return INSERT; }
	else if (strcmp(command_str, "DELETE") == 0) { return DELETE; }
	else if (strcmp(command_str, "ASCEND") == 0) { return ASCEND; }
	else if (strcmp(command_str, "DESCEND") == 0) { return DESCEND; }
	else { fprintf(stderr, "Invalid command: %s\n", command_str); }
}

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

listPointer delete_(listPointer list, int item) {
    listPointer currNode, prevNode, nextNode;
    // printf("0\n");
    // Find the node to be deleted
    currNode = list;
    if (list->data == item) {
        // Remove the head node and make the next node the new head
        // printf("1\n");
        prevNode = list->prev;
        nextNode = list->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        // printf("next->data %d\n", nextNode->data);
        free(list);
        list = nextNode;
        // printf("list->data %d, list->next->data %d, list->prev->data %d\n", list->data, list->next->data, list->prev->data);
        return nextNode;
    }

    currNode = list->next;
    while (currNode != list && currNode->data != item) {
        currNode = currNode->next;
    }

    // Node not found
    if (currNode == list) {
        return list;
    }

    // Delete the node
    prevNode = currNode->prev;
    nextNode = currNode->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    free(currNode);
    return list;
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

void print_reverse(listPointer list) {
	listPointer curr;
	FILE *outfile;

	outfile = fopen("hw2_result.txt", "a");
	if(list) {
		curr = list->prev;

		while(curr != list) {
			fprintf(outfile, "%d ", curr->data);
			printf("%d ", curr->data);
			curr = curr->prev;
		}
		fprintf(outfile, "%d ", curr->data);
		printf("%d ", curr->data);
	}
	fprintf(outfile, "\n");
	printf("\n");
	fclose(outfile);
}
