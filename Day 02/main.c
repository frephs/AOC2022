#include <stdio.h>
#include <stdlib.h>

#define FILENAME "input.txt"

/*PART !*/

int score(char a, char b){
    int s;
    a -= 'A'; b -= 'X';
    if ((a % 3) == (b % 3)){
        s = 3;
    }else if((a + 1) % 3 == (b % 3)){ // ABC are defeated by BCA which means YXZ
        s = 6;
    }else{
        s = 0;
    }
    return (b % 3) + 1 + s;
}

int getScore(FILE *fp){
    char a,b;
    int s;
    s = 0;
    fscanf(fp, "%c %c ", &a, &b);
    while(!feof(fp)){
        s += score(a,b);
        fscanf(fp, "%c %c ", &a, &b);
    }
    s += score(a,b);
    return s;
}

char decryptInstruction(char a, char b){
   return a - 'A' + 'X' + (b - 'X' + 2) % 3;
}

/*PART 2*/
int getActualScore(FILE *fp){
    char a,b;
    int s;
    s = 0;
    fscanf(fp, "%c %c ", &a, &b);
    while(!feof(fp)){
        b = decryptInstruction(a,b);
        s += score(a, b);
        fscanf(fp, "%c %c ", &a, &b);
    }   
    b = decryptInstruction(a,b);
    s += score(a, b);
    return s;
}

int main (){
    FILE *fp;
    int score;
    fp = fopen(FILENAME, "r");
    if(fp){
        score = getScore(fp);
        fclose(fp);
        printf("Score: %d\n", score);
    }else{
        printf("Could not open the file");
    }
    fp = NULL;
    fp = fopen(FILENAME, "r");
    if(fp){
        score = getActualScore(fp);
        fclose(fp);
        printf("Actual score: %d\n", score);
    }else{
        printf("Could not open the file");
    }
}

