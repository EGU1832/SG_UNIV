#include "maze.h"

int main() {
	srand(time(NULL));
    FILE *file;

    //open file
    file = fopen("maze.maz", "w");

	//if file does not exist in current directory, make a new file "maze.maz"
    if (file == NULL) {
		file = fopen("maze.maz", "w+");
	}

	//user code

	//make field[M][N] M: HEIGHT, N: WIDTH
	scanf("%d", &N);
	scanf("%d", &M);

	makeBasicMaze(&field, &set);
	makeMaze();

	print();

	//free allocated memory at field
	for (int i = 0; i < HEIGHT; i++) {
        free(field[i]);
    }
    free(field);

	for (int i = 0; i < M; i++) {
        free(set[i]);
    }
    free(set);

    //close file
    fclose(file);

    return 0;
}

void makeBasicMaze(char*** field, int*** set) {

	HEIGHT = M * 2 + 1;
	WIDTH = N * 2 + 1;

	*field = (char**)malloc(HEIGHT * sizeof(char*));
    /*
	if (*field == NULL) {
        prcharf("memory allocation error!");
        return 1;
    }
	*/
    for (char i = 0; i < HEIGHT; i++) {
        (*field)[i] = (char*)malloc(WIDTH * sizeof(char));
		/*
        if ((*field)[i] == NULL) {
            prcharf("memory allocation error!");
            return 1;
        }
		*/
    }

	*set = (int**)malloc(M * sizeof(int*));
    /*
	if (*set == NULL) {
        printf("memory allocation error!");
        return 1;
    }
	*/
    for (int i = 0; i < M; i++) {
        (*set)[i] = (int*)malloc(N * sizeof(int));
		/*
        if ((*set)[i] == NULL) {
            printf("memory allocation error!");
            return 1;
        }
		*/
    }
	setNum = 1;

	//make maze field with form
	for (int i = 0; i < HEIGHT; i++) {
		if (i % 2 == 0) {
			for (int j = 0; j < WIDTH; j++) {
				if (j % 2 == 0) { (*field)[i][j] = '+'; }
				else { (*field)[i][j] = '-'; }
			}
		}
		else{
			for (int j = 0; j < WIDTH; j++) {
				if (j % 2 == 0) { (*field)[i][j] = '|'; }
				else { (*field)[i][j] = ' '; }
			}
		}
	}

}

void makeMaze() {
	
	for (int i = 0; i < HEIGHT; i++) {
		if (i == 1) { determineSet(i); }
		if (i % 2 == 1 && i != HEIGHT - 2){
			determineRow(i);
			determineColumn(i+1);
			determineSet(i + 2);
		}
		else if (i == HEIGHT - 2) {
			determineLastRow(i);
		}
	}

}

void determineRow(int currHEIGHT) {

	int setM = currHEIGHT / 2;

	for (int setN = 1; setN < N; setN++) {
		int currWIDTH = setN * 2 + 1;
		//if two adjacent rooms belong to a different set
		if (set[setM][setN] != set[setM][setN - 1]) {
			//choose rather delete '|' or not
			int choice = rand() % 2;
			if (choice == 0) { 
				//delete '|'
				field[currHEIGHT][currWIDTH - 1] = ' ';

				//putting all connected rooms together in the same set
				int min = findMin(set[setM][setN] , set[setM][setN - 1]);
				int max = findMax(set[setM][setN] , set[setM][setN - 1]);

				for (int j = 0; j < M; j++) {
					for (int k = 0; k < N; k++) {
						if (set[j][k] == max) { set[j][k] = min; }
					}
				}
			}
		}
	}

}

void determineLastRow(int currHEIGHT) {

	int setM = currHEIGHT / 2;

	for (int setN = 1; setN < N; setN++) {
		if (field[currHEIGHT][setN * 2 + 1 - 1] == '|' && set[setM][setN] != set[setM][setN - 1]) {
			field[currHEIGHT][setN * 2 + 1 - 1] = ' ';

			int min = findMin(set[setM][setN], set[setM][setN - 1]);
			int max = findMax(set[setM][setN], set[setM][setN - 1]);

			for (int j = 0; j < M; j++) {
				for (int k = 0; k < N; k++) {
					if (set[j][k] == max) { set[j][k] = min; }
				}
			}
		}
	}

}

void determineColumn(int currHEIGHT) {

	int flag = 0;
	int setM = currHEIGHT / 2;

	for (int i = 0; i < N; i++) {
		//if two adjacent rooms belong to a same set
		if (set[setM - 1][i] == set[setM - 1][i + 1]) {
			//choose rather delete '-' or not
			int choice = rand() % 2;
			if (choice == 0) {
				field[currHEIGHT][i * 2 + 1] = ' ';
				set[setM][i] = set[setM - 1][i];
				flag = 1;
			}
		}

		//if two adjacent rooms belongs to a defferent set
		else { 
			//if field didn't changed until
			if (flag == 0) {
				field[currHEIGHT][i * 2 + 1] = ' ';
				set[setM][i] = set[setM - 1][i];
			}
			//if field changed until
			flag = 0;
		}
	}

}

void determineSet(int currM) {

	for (int i = 0; i < N; i++) {
		if (set[currM / 2][i] == 0) {
			set[currM / 2][i] = setNum++;
		}
	}

}

void print() {

	//print maze
	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH; j++) {
			printf("%c", field[i][j]);
		}
		printf("\n");
	}

	//print set
	/*
	for (int i = 0; i < M; i++){
		for (int j = 0; j < N; j++) {
			printf("%d ", set[i][j]);
		}
		printf("\n");
	}
	*/

}

int findMin(int a, int b) {
	return (a < b) ? a : b;
}

int findMax(int a, int b) {
    return (a > b) ? a : b;
}
