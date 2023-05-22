#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int N, M;			//N: WIDTH, M: HEIGHT
int WIDTH, HEIGHT;	//폭과 높이
char** field;		//maze를 나타내는 이차원 배열
int** set;			//칸이 속해있는 집합을 나타내는 배열
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
// N,M 칸은 field[N * 2 + 1][M * 2 + 1]에 저장되어있음
