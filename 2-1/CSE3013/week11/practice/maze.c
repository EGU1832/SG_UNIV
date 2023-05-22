#include "maze.h"

int main() {
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

	makeMaze(N, M, &field);

	//print maze
	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH; j++) {
			printf("%c", field[i][j]);
		}
		printf("\n");
	}

	//free allocated memory at field
	for (int i = 0; i < HEIGHT; i++) {
        free(field[i]);
    }
    free(field);

    //close file
    fclose(file);

    return 0;
}

void makeMaze(int N, int M, char*** field) {

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
