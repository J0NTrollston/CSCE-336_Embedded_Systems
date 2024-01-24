#include <stdio.h>
#include <string.h>

int main(){
int var = 12;
int data[] = {0,1,2,3,4,5,6,7};
int *p1 = &var;
int *p2 = data +2;

data[3] = *p1;
p2[2] = 0;




    printf("%d",data[7]);
    //printf("%d",data[]);


    return(0);
}