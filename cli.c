# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
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
}

void display_cell(cell *cell){

	printf("%4d",cell->position); // if refer to fields by '.' when we don't have pointers but we use '->' for refering through fields by pointers

}

void command_show(){
for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){

			display_cell(&board[i][j]);
		}
		printf("\n");
	}

}


int get_random(int range){

		return (rand()%range);

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
		printf("You entered %s\n",line);

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
	
	srand(time(0));
		int my_rand = get_random(10);
		printf("%d\n",my_rand);

//	runtime();

}