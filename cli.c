# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <stdbool.h>
struct cell{


	int position;
	int adjcount;
	int mined;
	int flagged;
	int covered;

};
typedef struct cell cell; // alias for struct cell as "cell"

cell **board; // 2-D array
int rows;
int cols;
int mines;

int minedarr[256];






void display_cell(cell *cell){

	printf("%4d",cell->position); // if refer to fields by '.' when we don't have pointers but we use '->' for refering through fields by pointers
	if(cell->mined == 1) printf("%2s","*");
	else if(cell->adjcount==0) printf("%2s",".");	
	else printf("%2d",cell->adjcount);
}

void command_show(){
for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){

			display_cell(&board[i][j]);
		}
		printf("\n");
	}

}


bool mine_lookup(int row, int col){

	for(int i=0;i<256;i++){

		if(board[row][col].position == minedarr[i]) return true;

	}

	return false;
}

int get_random(int range){

		return (rand()%range);

}

void place_mine(){


	if(mines ==0) return;

	for(int i=1;i<=mines;i++){

		int r  = get_random(rows);
		int c = get_random(cols);

		while(mine_lookup(r,c) == true){
		  
			r=  get_random(rows);
			c = get_random(cols);
		}

		minedarr[i] = board[r][c].position; 
		board[r][c].mined = 1; 

	//	printf("%d\n",minedarr[i]);


	}



}


void adjacencycount(){


int neighbourcount = 8;
int rowneighbors[] = {-1,-1,0,1,1,1,0,-1};
int colneighbors[] = {0,1,1,1,0,-1.-1,-1};


for(int i=0;i<rows;i++){
	for(int j=0;j<cols;j++){
		int minecount  = 0;
		for(int d=0;d<neighbourcount;d++){
		int rn = i+ rowneighbors[d];
		//printf("%2d\n", rows);
		int cn = j  + colneighbors[d];
		//printf("%3d\n",cols); 

		if(0<= rn && rn<rows && 0<=cn && cn<cols){
			if(board[rn][cn].mined == 1) minecount++;
		}
		
		}
		board[i][j].adjcount = minecount;

	}		

}


}

void command_flag(int row, int col){

	if(board[row][col].flagged == 0){
		board[row][col].flagged = 1;
	}
	else printf("Cell %d has already been flagged",board[row][col].position);
}

void command_new(){

	board =(cell **) malloc(sizeof(cell *)* rows); // memory allocation for rows
	for(int i=0;i<rows;i++){
	board[i] = (cell *) malloc(sizeof(cell)*cols);		// memory allocation for cols
	}	


	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){

			board[i][j].position = i*rows+ j;
		}
	}
	place_mine();
	adjacencycount();
}

int runtime(){

	 // seeding the random according to the time it runs on the computer

	char line[80];
	char linecopy[80];
	char tokens[10][80];
	char *tok;
	int tokencount;
	int ranom  = get_random(10);
	

	while(1){
		printf(">> ");
		fgets(line,80,stdin);
		line[strlen(line)-1] = '\0';
	//	printf("You entered %s\n",line);

		strcpy(linecopy,line);
		tok = strtok(linecopy," ");
		tokencount=0;
		while(tok != NULL){
			strcpy(tokens[tokencount],tok);
		//	printf("current token = %s\n",tok);
			tok = strtok(NULL," ");
			tokencount++;

		}
//		printf("Total tokens %d\n",tokencount);
//		printf("name command = %s\n", tokens[0]);
		
		if(strcmp(tokens[0],"quit") == 0) break;
		if(strcmp(tokens[0],"new")==0){
		rows = atoi(tokens[1]); // atoi is used to convert strings into int, this one converts the command line argument of the first index and converts it int to string
		cols = atoi(tokens[2]);	// atoi for columns 
		mines= atoi(tokens[3]);	//atoi for mines
		 command_new();
		}
		if(strcmp(tokens[0],"show")==0){
		 command_show();
		}
		


	}


	return 0;
}

int main(void){
	

//	runtime();
	runtime();
//	display_cell();

}

