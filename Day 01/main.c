#include <stdio.h>
#include <stdlib.h>

typedef struct elfList{
    int calories;
    int originalIndex;
    struct elfList *next;
}elfList_t;

#define FILENAME "input.txt"
#define MAXLEN 15
#define INDEX1 1
#define INDEX2 3

elfList_t * getElfsInOrder(FILE *fp);
elfList_t * insertElf(elfList_t *head, int elfCalories, int elfIndex);
int getTopCalories(int index, elfList_t *elf);
void printElfs(elfList_t *h);

int main(){
    FILE *fp;
    elfList_t *elfs;
    int maxCalories;
   
    fp = fopen(FILENAME, "r");
    if(fp){
       
        elfs = getElfsInOrder(fp);
        maxCalories = getTopCalories(INDEX1, elfs);
        printf("Top Calories index %d: %d\n", INDEX1, maxCalories);
        maxCalories = getTopCalories(INDEX2, elfs);
        printf("Top Calories index %d: %d\n", INDEX2, maxCalories);
        fclose(fp);
    } else {
        printf("Could not open the file!\n");
    }
}


elfList_t * getElfsInOrder(FILE *fp){
    char currCaloriesString[MAXLEN+1];
    int currIndex, currElfCalories;

    elfList_t *elfs;
    elfs = NULL;

    currIndex = currElfCalories = 0;

    fgets(currCaloriesString, MAXLEN+1, fp);
    while(!feof(fp)){
        if(currCaloriesString[0]=='\n'){
            elfs = insertElf(elfs, currElfCalories, currIndex);
            currIndex++;
            currElfCalories=0;
        }else{
            currElfCalories +=  atoi(currCaloriesString);
        }
        fgets(currCaloriesString, MAXLEN+1, fp);
    }
    return elfs;
}

elfList_t * insertElf(elfList_t *head, int elfCalories, int elfIndex){
    elfList_t *tmp, *prec, *succ;
    
    tmp = malloc(sizeof(elfList_t));
    if(tmp){
        tmp->calories = elfCalories;
        tmp->originalIndex = elfIndex;
        tmp->next = NULL;
        if(!head){
            head = tmp;
        }else{
            for (prec=head, succ=head->next; succ && succ->next && succ->calories > tmp->calories; prec=succ, succ=succ->next);            prec->next = tmp;
            tmp->next = succ; 
        }
    }else{
        printf("Unable to allocate memory");
    }
    return head;
}

int getTopCalories(int index, elfList_t *elf){
    int i, calories;
    for (elf, i=0, calories = 0; elf->next && i<index; i++, elf=elf->next, calories+=elf->calories);
    return calories;
}

void printElfs(elfList_t *h){
    for(h; h->next;h=h->next){
        printf("%d -> ", h->calories);
    }
    printf("\n");
}