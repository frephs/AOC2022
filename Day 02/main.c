#include <stdio.h>
#include <stdlib.h>

int score(char a, char b){
    int s;
    if (a == b){
        s = 3
    }else if((a -'A') % 3 + 1 == b - 'X' % 3){ // ABC are defeated by BCA which means YXZ
        s = 6
    }else{
        s = 0;
    }
}

