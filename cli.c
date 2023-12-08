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

void display_cell(cell *cell){
    // if refer to fields by '.' when we don't have pointers but we use '->' for referring through fields by pointers
   if(cell->covered == 1) printf("%2s","/");
   else if(cell->flagged == 1) printf("%2s","F");
    
    else if(cell->mined == 1){
        printf("%2s", "*");
    }
    else if(cell->adjcount == 0){
        printf("%2s", ".");
    }
    else{
        printf("%2d", cell->adjcount);
    }

}

void command_show(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            display_cell(&board[i][j]);
        }
        printf("\n");
    }
}

int get_random(int range){
    return (rand() % range);
}

void place_mine(){
    if(mines == 0) return;
    
    for(int i = 1; i <= mines; i++){
        int r = get_random(rows);
        int c = get_random(cols);

        while(board[r][c].mined == true){
            r = get_random(rows);
            c = get_random(cols);
        }

        board[r][c].mined = 1;
    }
}

void adjacencycount(){
    int neighbourcount = 8;
    int rowneighbors[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int colneighbors[] = {0, 1, 1, 1, 0, -1, -1, -1};

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            int minecount = 0;
            for(int d = 0; d < neighbourcount; d++){
                int rn = i + rowneighbors[d];
                int cn = j + colneighbors[d];
                if(0 <= rn && rn < rows && 0 <= cn && cn < cols){
                    if(board[rn][cn].mined == 1) minecount++;
                }
            }
            board[i][j].adjcount = minecount;
        }
    }
}

void command_flag(int row, int col){
	if(board[row][col].covered ==0)
	 {
	 		printf("You can only flag a covered cell\n");
			return;
}

    if(board[row][col].flagged == 0){
        board[row][col].flagged = 1;
    }
    else printf("Cell %d has already been flagged\n", board[row][col].position);
}

void command_unflag(int row, int col){
    if(board[row][col].flagged == 1){
        board[row][col].flagged = 0;
    }
    else printf("Cell %d is already unflagged\n", board[row][col].position);
}

void command_new(){
    board = (cell **) malloc(sizeof(cell *) * rows); // memory allocation for rows
    for(int i = 0; i < rows; i++){
        board[i] = (cell *) malloc(sizeof(cell) * cols); // memory allocation for cols
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            board[i][j].position = i * rows + j;
            board[i][j].mined =0;
            board[i][j].adjcount=0;
            board[i][j].covered=0;
            board[i][j].flagged=0;
           // printf("%2d\n", board[i]);
           // display_cell(board[i]);
        }
    }
    place_mine();
    adjacencycount();
}

void uncover_recursive(int r, int c){
  
  if(board[r][c].mined == 0){  
    board[r][c].covered = 0;

    if(board[r][c].adjcount>0) return;
    int neighbourcount = 8;
    int rowneighbors[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int colneighbors[] = {0, 1, 1, 1, 0, -1, -1, -1};

   // command_show();
    
    if(board[r][c].adjcount == 0){
        for(int d = 0; d < 8; d++){
            int rn = r + rowneighbors[d];
            int cn = c + colneighbors[d];
            if(0 <= rn && rn < rows && 0 <= cn && cn < cols){
                if(board[rn][cn].covered == 1){
                    uncover_recursive(rn, cn);

                }
            }
        }
    }
}

else{
	printf("Game Over, you have lost!");
}
}
   
   


void coverall(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
        	board[i][j].covered = 1;
           
        }
        
    }
}

int runtime(){
    srand(time(0));

    // seeding the random according to the  it runs on the computer

    char line[80];
    char linecopy[80];
    char tokens[10][80];
    char *tok;
    int tokencount;
    int ranom  = get_random(10);

    while(1){
        printf(">> ");
        fgets(line, 80, stdin);
        line[strlen(line) - 1] = '\0';
        strcpy(linecopy, line);
        tok = strtok(linecopy, " ");
        tokencount = 0;
        while(tok != NULL){
            strcpy(tokens[tokencount], tok);
            tok = strtok(NULL, " ");
            tokencount++; // 
          }

        if(strcmp(tokens[0], "quit") == 0) break;
        if(strcmp(tokens[0], "new") == 0){
            rows = atoi(tokens[1]); // atoi is used to convert strings into int, this one converts the command line argument of the first index and converts it int to string
            cols = atoi(tokens[2]); // atoi for columns
            mines = atoi(tokens[3]); //atoi for mines
            command_new();
        }
        if(strcmp(tokens[0], "show") == 0){
            command_show();
        }

        if(strcmp(tokens[0], "uncover") == 0){
            int r = atoi(tokens[1]); // atoi is used to convert strings into int, this one converts the command line argument of the first index and converts it int to string
            int c = atoi(tokens[2]);
            uncover_recursive(r, c);
        }

        if(strcmp(tokens[0], "flag") == 0){
            int r = atoi(tokens[1]); // atoi is used to convert strings into int, this one converts the command line argument of the first index and converts it int to string
            int c = atoi(tokens[2]);
            command_flag(r, c); 
        }

        if(strcmp(tokens[0], "coverall") == 0) coverall();
    }

    return 0;
}

int main(void){
    runtime();
    return 0;
}
