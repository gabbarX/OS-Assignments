#include<stdio.h>
#include<stdlib.h>


void copy(int src[][], int dest[][], int r, int c)
{
    int tempbuffer[c]; 
    int buffer[r][c];
    int count=0;
    for(int i=0;i<r;i++){
        // int check = __copy_from_user(tempbuffer, src, sizeof(int)* (c));
        // __copy_to_user(dest, tempbuffer, sizeof(int)* (c));
        for(int j=0;j<c;j++){
            tempbuffer[j] = src[] 
        }

        for(int j=0;j<c;j++){
            buffer[count][j] = tempbuffer[j];
        }
        count++;
    }
    return 0;
}




int main(void){

    


}