#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* korak1(char* recenica);

int main()
{
    char recenica[120+1];
    char* niz1 = NULL;

    int korak;

    scanf("%d", &korak);
    scanf("%s", recenica);

    if(korak == 1){
        niz1 = korak1(recenica);
    }

    return 0;
}

char* korak1(char* recenica)
{
    char* rec = NULL;
    rec = (char*)calloc(sizeof(char), 120+1);

    int i, j, brojac = 0;
    for(i = 0; i < strlen(recenica); i++){
        rec[i] = recenica[i];
    }

    for(i = 0; i < strlen(recenica); i++){
        if(recenica[i] == '*'){
            brojac = 0;
            while(recenica[i++] == '*'){
                if(i > strlen(recenica)){
                    break;
                }
                brojac++;
            }
            if(brojac % 2 == 0){
                rec[i - brojac - 1] = 'x';
            }
            else{
                rec[i - brojac - 1] = 'X';
            }
            i--;
        }
    }
    int poz = 0;
    char* rec2 = NULL;
    rec2 = (char*)calloc(sizeof(char), 120+1);
    for(i = 0; i < strlen(rec); i++){
        if(rec[i] != '*'){
            rec2[poz] = rec[i];
            poz++;
        }
    }

    printf("Nakon koraka 1:\n%s\n", rec2);

    return rec2;
}
