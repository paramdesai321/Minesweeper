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

	}

	return 0;
}

int main(void){

	runtime();
}