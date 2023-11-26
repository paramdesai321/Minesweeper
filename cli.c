# include <stdio.h>
# include <string.h>
int runtime(){

	char line[80];
	char linecopy[80];
	char tokens[10][80];
	char *tok;
	int tokencount;

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
		printf("Total tokens %d\n",tokencount);
		printf("name command = %s\n", tokens[0]);

		if(strcmp(tokens[0],"quit") == 0) break;
		if(strcmp(tokens[0],"new")==0) printf("New Board command\n");
		if(strcmp(tokens[0],"show")==0) printf("Show Board command\n");
		


	}


	return 0;
}

int main(void){

	runtime();

}