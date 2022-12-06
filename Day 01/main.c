#include <stdio.h>
#include <stdlib.h>

typedef struct elfList{
    int calories;
    int originalIndex;
    struct elfList *next;
}elfList_t;

#define FILENAME "input.txt"
#define MAXLEN 15
#define INDEX_PART_1 1
#define INDEX_PART_2 3

elfList_t * getElfsInOrder(FILE *fp);
elfList_t * insertElf(elfList_t *head, int elfCalories, int elfIndex);
int getTopCalories(int index, elfList_t *elf);
void printElfs(elfList_t *h);
void * destroyList(elfList_t *h);
/*This problem is not indeded to be solved with linked list but rather a 3 cell array maximum in the second part, i know.
I decided to solve it with linked lists for revising purpuses */


int main(){
    FILE *fp;
    elfList_t *elfs;
    int maxCalories;
   
    fp = fopen(FILENAME, "r");
    if(fp){
        elfs = getElfsInOrder(fp);
        maxCalories = getTopCalories(INDEX_PART_1, elfs);
        printf("Top Calories index %d: %d\n", INDEX_PART_1, maxCalories);
        maxCalories = getTopCalories(INDEX_PART_2, elfs);
        printf("Top Calories index %d: %d\n", INDEX_PART_2, maxCalories);
        fclose(fp);
        destroyList(elfs)
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

// void printElfs(elfList_t *h){
//     for(h; h->next;h=h->next){
//         printf("%d -> ", h->calories);
//     }
//     printf("\n");
// }

void * destroyList(elfList_t *h){
    if(h->next){
        destroyList(h->next);
    }
    free(h) 
}