#include "tetris.h"

static struct sigaction act, oact;
int B,count;

int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);

	srand((unsigned int)time(NULL));

    createRankList();

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
        case MENU_RANK: rank(); break;
		case MENU_EXIT: exit=1; FreeList(&Rank); break;
		default: break;
		}
	}
	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
    nextBlock[2]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	DrawBlock(blockY,blockX,nextBlock[0],blockRotate,' ');
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){
	int i,j,p = 2;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	for (int k = 1; k < BLOCK_NUM; k++) {
        move(p,WIDTH+10);
	    printw("NEXT BLOCK");
	    DrawBox(p + 1,WIDTH+10,4,8);
        p += 7;
    }

	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(p,WIDTH+10);
	printw("SCORE");
	DrawBox(p + 1,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	int p = 2;
    for(int k = 1; k < BLOCK_NUM; k++) { p += 7; }
    move(p + 2,WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j, k, p = 4;
	for( k = 1; k < BLOCK_NUM; k++ ) {
        for( i = 0; i < 4; i++ ){
	        move(p+i,WIDTH+13);
	        for( j = 0; j < 4; j++ ){
                if( block[nextBlock[k]][0][i][j] == 1 ){
                    attron(A_REVERSE);
                    printw(" ");
                    attroff(A_REVERSE);
                }
                else printw(" ");
            }
	    }
        p += 7;
    }
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate){
    DrawBlock(y, x, blockID, blockRotate, ' ');
    DrawShadow(y, x, blockID, blockRotate);
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
    for(int i = 0; i < BLOCK_HEIGHT; i++) {
        for(int j = 0; j < BLOCK_WIDTH; j++) {
            if (block[currentBlock][blockRotate][i][j] == 1) {
                // 예상된 현재 블록이 필드 바깥으로 나갈 경우
                if (!(i + blockY >= 0 && j + blockX >= 0 && i + blockY < HEIGHT && j + blockX < WIDTH)) { return 0; }
                // 예상 현재 블록이 쌓여있는 블록과 겹치는 경우
                if (f[i + blockY][j+blockX] == 1) {return 0;}
            }
        }
    }
    return 1;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	// user code

    int y = blockY, x = blockX, r = blockRotate;
	//1. 이전 블록 정보를 찾는다. ProcessCommand의 switch문을 참조할 것
    switch(command){
	case KEY_UP:
        r = (blockRotate+3)%4;
		break;
	case KEY_DOWN:
        y--;
		break;
	case KEY_RIGHT:
        x--;
		break;
	case KEY_LEFT:
        x++;
		break;
    default:
        break;
	}
    //2. 이전 블록 정보를 지운다. DrawBlock함수 참조할 것.
	for(int i = 0; i < BLOCK_HEIGHT; i++) {
		for(int j = 0; j < BLOCK_WIDTH; j++){
			if(block[currentBlock][r][i][j] == 1 && i + y >= 0){
				move(i + y + 1, j + x + 1);
				printw("%c",'.');
			}
		}
    }
    //delete shadow
    int ShadowY = y;
    while(1) {
        if (CheckToMove(field, nextBlock[0], r, ShadowY + 1, x)) { ShadowY++; }
        else { break; }
    }
    for(int i = 0; i < BLOCK_HEIGHT; i++) {
        for(int j = 0; j < BLOCK_WIDTH; j++){
            if(block[currentBlock][r][i][j] == 1 && i + ShadowY >= 0){
                move(i + ShadowY + 1, j + x + 1);
                printw("%c",'.');
            }
        }
    }
    move(HEIGHT, WIDTH + 10);
    //3. 새로운 블록 정보를 그린다.
    DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate);
}

void BlockDown(int sig){
	// user code
	//강의자료 p26-27의 플로우차트를 참고한다.
    if(CheckToMove(field, nextBlock[0], blockRotate, blockY + 1, blockX)) {
        blockY++;
        DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
    }
    else{
        if (blockY == -1) {
            gameOver = TRUE;
        }

        score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
        score += DeleteLine(field);
        PrintScore(score);
        for (int i = 0; i < BLOCK_NUM - 1; i++) {
            nextBlock[i] = nextBlock[i + 1];
        }
        nextBlock[BLOCK_NUM - 1] = rand()%7;
        DrawNextBlock(nextBlock);
    
        blockRotate = 0;
        blockY = -1;
        blockX = WIDTH/2 - 2;
        DrawField();
    }
    timed_out = 0;
}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	//Block이 추가된 영역의 필드값을 바꾼다.
    int touched = 0;

    for(int i = 0; i < BLOCK_HEIGHT; i++) {
        for(int j = 0; j < BLOCK_WIDTH; j++) {
            if (block[currentBlock][blockRotate][i][j] == 1) { 
                f[blockY + i][blockX + j] = 1; 
                if (blockY + i == HEIGHT - 1 || f[blockY + i + 1][blockX + j] == 1) { touched++; }
            }
        }
    }
    return (touched * 10);
}

int DeleteLine(char f[HEIGHT][WIDTH]){
     // user code
     int lineflag = 0, deletedLine = 0;

     //1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
     for (int i = 0; i < HEIGHT; i++) {
        lineflag = 1;
        for(int j = 0; j < WIDTH; j++) {
           if (f[i][j] == 0) { lineflag = 0; break; }
        }
     //2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
        if (lineflag) {
            deletedLine++;
            for (int k = i - 1; k >= 0; k--) {
                for(int j = 0; j < WIDTH; j++) { f[k + 1][j] = f[k][j]; }
            }
            for(int j = 0; j < WIDTH; j++) { f[0][j] = 0; }
        }
     }

     return (deletedLine * deletedLine * 100);
}

void DrawShadow(int y, int x, int blockID,int blockRotate){
	// user code
    while(1) {
        if (CheckToMove(field, nextBlock[0], blockRotate, y + 1, x)) { y++; }
        else { break; }
    }

    int i,j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++){
            if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
                move(i+y+1,j+x+1);
                attron(A_REVERSE);
                printw("%c",'/');
                attroff(A_REVERSE);
        }
    }

    move(HEIGHT,WIDTH+10);
}

void createRankList(){
	// 목적: Input파일인 "rank.txt"에서 랭킹 정보를 읽어들임, 읽어들인 정보로 랭킹 목록 생성
	FILE *fp;
	int i, j;
    char name[NAMELEN + 1];
    int score; 
	
	fp = fopen("rank.txt", "r+");
    if (fp == NULL) {
        fp = fopen("rank.txt", "w+");
    }

	// 2. 정보읽어오기
	// return: 성공할 경우, fscanf 함수는 읽어들인 데이터의 수를 리턴, 실패하면 EOF리턴 */
	// EOF(End Of File): 실제로 이 값은 -1을 나타냄, EOF가 나타날때까지 입력받아오는 if문
    fscanf(fp, "%d", &score_number);
    while (fscanf(fp, "%s %d", name, &score) != EOF) {
        name[NAMELEN] = '\0';
        AddLinkedList(&Rank, name, score);
    }

	// 4. 파일닫기
	fclose(fp);
}

void rank(){
	//목적: rank 메뉴를 출력하고 점수 순으로 X부터~Y까지 출력함
	//1. 문자열 초기화
	int X = 1, Y = score_number, ch, i, j;
    RankPointer currNode;
	clear();

	//2. printw()로 3개의 메뉴출력
    printw("1. list ranks from X to Y\n");
    printw("2. list ranks by a specific name\n");
    printw("3. delete a specific rank\n");
	//3. wgetch()를 사용하여 변수 ch에 입력받은 메뉴번호 저장
    ch = wgetch(stdscr);
	//4. 각 메뉴에 따라 입력받을 값을 변수에 저장
	//4-1. 메뉴1: X, Y를 입력받고 적절한 input인지 확인 후(X<=Y), X와 Y사이의 rank 출력
	if (ch == '1') {
        printw("X: ");
        echo();
        scanw("%d", &X);
        printw("Y: ");
        scanw("%d", &Y);
        noecho();
        if (X > Y || X < 1 || Y > score_number) { printw("serch failure: no rank in the list\n"); }
        else {
            printw("       name       |   score   \n");
            printw("------------------------------\n");
            count = X;
            while(count >= X && count <= Y) {
                currNode = FindSpecificNode(Rank, count);
                printw(" %-17s| %d\n", currNode->name, currNode->score);
                count++;
            }
        }
	}

	//4-2. 메뉴2: 문자열을 받아 저장된 이름과 비교하고 이름에 해당하는 리스트를 출력
	else if ( ch == '2') {
        char str[NAMELEN+1];
        int check = 0;
        printw("input the name: ");
        echo();
        scanw("%s", str);
        noecho();
        str[NAMELEN] = '\0';
        
        printw("       name       |   score   \n");
        printw("------------------------------\n");
        RankPointer currNode;
        currNode = Rank;
        for (int i = 0; i < score_number; i++) {
            if (strcmp(currNode->name, str) == 0) {
                printw(" %-17s| %d\n", currNode->name, currNode->score);
                check++;
            }
            currNode = currNode->next;
        }
        if (check == 0) { printw("search failure: no name in the list\n"); }
        currNode = NULL;
	}

	//4-3. 메뉴3: rank번호를 입력받아 리스트에서 삭제
	else if ( ch == '3') {
        int num;
        printw("input the rank: ");
        echo();
        scanw("%d", &num);
        noecho();
        if (num >= 1 && num <= score_number) {
            RankPointer currNode;
            currNode = FindSpecificNode(Rank, num);
            DeleteSpecificNode(&Rank, num);
            score_number--;
            
            FILE *fp, *temp;
            int score;
            char name[NAMELEN + 1];
            
            fp = fopen("rank.txt", "r");
            if (fp == NULL) {
                fp = fopen("rank.txt", "w+");
            }
            temp = fopen("temp.txt", "w");
            fprintf(temp, "%d\n", score_number);
            fscanf(fp, "%d", &score);
            while (fscanf(fp, "%s %d", name, &score) != EOF) {
                name[NAMELEN] = '\0';
                if (strcmp(name, currNode->name) != 0 && score != currNode->score) {
                    fprintf(temp, "%s %d\n", name, score);
                }
            }
                
            fclose(fp);
            fclose(temp);
            remove("rank.txt");
            rename("temp.txt", "rank.txt");
            printw("result: the rank deleted\n");
            currNode = NULL;
        }
        else { printw("search failure: the rank not in the list\n"); }
	}

	getch();

}

void writeRankFile(){
	// 목적: 추가된 랭킹 정보가 있으면 새로운 정보를 "rank.txt"에 쓰고 없으면 종료
	int sn, i;
    RankPointer currNode;
	//1. "rank.txt" 연다
	FILE *fp = fopen("rank.txt", "r+");
    if (fp == NULL) {
        fp = fopen("rank.txt", "w+");
    }

	//2. 랭킹 정보들의 수를 "rank.txt"에 기록
    if (fscanf(fp, "%d", &sn) != 1) {
        sn = 0;
    }
    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "%d\n", score_number);
    fseek(fp, 0, SEEK_END);
	//3. 탐색할 노드가 더 있는지 체크하고 있으면 다음 노드로 이동, 없으면 종료
    if (sn == score_number) {
        fclose(fp);
        return;
    }
	else {
        while(sn != score_number) {
            sn++;
            fprintf(fp, "%s %d\n", NewRank->name, NewRank->score);
        }
	}

    FreeList(&NewRank);
	// for ( i= 1; i < score_number + 1 ; i++) {
	// 	free(a.rank_name[i]);
	// }
	// free(a.rank_name);
	// free(a.rank_score);
    fclose(fp);
}

void newRank(int score){
	// 목적: GameOver시 호출되어 사용자 이름을 입력받고 score와 함께 리스트의 적절한 위치에 저장
	char str[NAMELEN+1];
	int i, j;
	clear();
	//1. 사용자 이름을 입력받음
    printw("your name: ");
    echo();
    scanw("%s", str);
    noecho();
    str[NAMELEN] = '\0';

	//2. 새로운 노드를 생성해 이름과 점수를 저장, score_number가
	// if(score_number) {
    AddLinkedList(&Rank, str, score);
    AddnewRankList(&NewRank, str, score);
    score_number++;
	// }
	// else {

	// }
	writeRankFile();
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
}

// int recommend(char fieldOri[HEIGHT][WIDTH],int lv){

// }

void recommendedPlay(){
	// user code
}

void AddLinkedList(RankPointer *Rank, char *name, int score) {
    RankPointer newNode, currNode, prevNode;

    newNode = (RankPointer) malloc(sizeof(RankNode));
    strcpy(newNode->name, name);
    newNode->score = score;
    newNode->next = NULL;

    if (*Rank == NULL) {
        *Rank = newNode;
        return;
    }

    currNode = *Rank;
    prevNode = NULL;
    while (currNode != NULL && currNode->score > score) {
        prevNode = currNode;
        currNode = currNode->next;
    }

    if (prevNode == NULL) {
        newNode->next = *Rank;
        *Rank = newNode;
    }
    else {
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }
}

void AddnewRankList(RankPointer *NewRank, char *name, int score) {
    RankPointer newNode, currNode;

    newNode = (RankPointer) malloc(sizeof(RankNode));
    strcpy(newNode->name, name);
    newNode->score = score;
    newNode->next = NULL;

    if (*NewRank == NULL) {
        *NewRank = newNode;
        return;
    }

    currNode = *NewRank;
    while (currNode->next != NULL) {
        currNode = currNode->next;
    }

    currNode->next = newNode;
}

RankPointer FindSpecificNode(RankPointer Rank, int index) {
    RankPointer currNode;
    currNode = Rank;
    if (index == 0) { return NULL; }
    for (int i = 1; i < index; i++) {
        currNode = currNode->next;
    }
    return currNode;
}

void DeleteSpecificNode(RankPointer *Rank, int index) {
    RankPointer currNode, prevNode;
    prevNode = FindSpecificNode(*Rank, index - 1);
    currNode = FindSpecificNode(*Rank, index);
    if (prevNode == NULL) {
        *Rank = currNode->next;
    }
    else {
        prevNode->next = currNode->next;
    }
    free(currNode);
}

void FreeList(RankPointer *Rank) {
    RankPointer currNode, nextNode; 
    currNode = *Rank;

    while (currNode != NULL) {
        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }

    *Rank = NULL;
}
