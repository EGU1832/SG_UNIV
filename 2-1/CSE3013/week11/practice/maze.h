#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int N, M;			//N: WIDTH, M: HEIGHT for maze
int WIDTH, HEIGHT;	//WIDTH and HEIGHT for field
char** field;		//represent maze
int** set;			//represent set
int setNum;

void makeBasicMaze(char*** field, int*** set);
void makeMaze();
void determineRow(int currM);
void determineLastRow(int currM);
void determineColumn(int currM);
void determineSet(int currM);
void print();
int findMin(int a, int b);
int findMax(int a, int b);
//maze[height][width]
//maze[M][N] == field[M * 2 + 1][N * 2 + 1]
