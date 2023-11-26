#include <stdio.h>
#include <string.h>

int main(void){

    char x = 'a';
    char y = 'A';
    char str[100] = "abc";
    int len = strlen(str);
    
    printf("%s and it has a length of %d \n", str, len);

    strcpy(str, "Harry Potter is pure-blood");
    len = strlen(str);

    printf("%s and %d\n", str, len);


    // accessing index in the array

    char str0 = str[0];
    printf("%c\n",str0);


    // pointers for the array



    char *str1 = "abc";
    printf("%p\n",str);  // this is how you print pointers

    // the function strcmp is string comparison alphabetically

    if (strcmp("abc", "pqr") < 0) {
        printf("abc comes before pqr	\n");
    } else {
        printf("pqr comes before abc\n");
    }


    // loops (same as java)
    int i=0;
    while(i!=10){

    	printf("%c\n",str[i]);
    	i++;
    }


    // 2d Arrays

    char tokens[5][20]; // max number of rows it can have is 5, and max number of colums(or you can see it as the length of string) is 20

    strcpy(tokens[0],"abc");
    strcpy(tokens[1],"a longer string");
    strcpy(tokens[2],"!!!! XXXXX YYYY");
    strcpy(tokens[3],"another string");
    strcpy(tokens[4],"final string");

    for(int i=0;i<5;i++){
    	printf("row %d string= %s\n",i,tokens[i]);

    }


    return 0;
}
