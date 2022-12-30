#include <stdio.h>
#include <stdlib.h>

void popuna(int** mat, int r, int s);
void ispis(int** mat, int r, int s);
void maxiIndex(int** mat, int r, int s, int* max, int* indxX, int* indxY);
void pretraga(int** mat, int r, int s, int vr, int* kooX, int* kooY);
void brisanjeRetka(int** mat, int r, int s, int br);
void ubacivanjeRetka(int** mat, int r, int s, int br);
void brisanjeStupca(int** mat, int r, int s, int br);
void ubacivanjeStupca(int** mat, int r, int s, int br);

int main()
{
    int i, j, r, s;
    while(1){
        scanf("%d %d", &r, &s);
        if(r < 1 || r > 100 || s < 1 || s > 100){
            if(r < 1 || r > 100){
                printf("Pogresan unos redaka!\nPonovi unos:");
            }
            else if(s < 1 || s > 100){
                printf("Pogresan unos stupaca!\nPonovi unos:");
            }
        }
        else{
            printf("Ispravan unos.");
            break;
        }
    }

    int** mat = NULL;
    mat = (int**)malloc(sizeof(int*) * r);
    if(mat == NULL){
        printf("Alokacija neuspjesna.\n");
        exit(1);
    }
    for(i = 0; i < r; i++){
        mat[i] = (int*)malloc(sizeof(int) * s);
        if(mat[i] == NULL){
            printf("Alokacija neuspjesna.\n");
        }
    }

    popuna(mat, r, s);
    ispis(mat, r, s);

    int max = -1000, indxX, indxY;
    maxiIndex(mat, r, s, &max, &indxX, &indxY);
    printf("\n\nMax broj je %d, a nalazi se na koordinatama (%d, %d).\n", max, indxX, indxY);

    printf("\nUnesi vrijednost koju zelis pronaci:");
    int vr, vrX, vrY;
    scanf("%d", &vr);
    pretraga(mat, r, s, vr, &vrX, &vrY);
    printf("Vrijednost %d se nalazi na koordinatama (%d, %d).\n", vr, vrX, vrY);

    printf("\nRedak koji zelis obrisati:");
    int brRet;
    scanf("%d", &brRet);
    brisanjeRetka(mat, r, s, brRet);
    r--;
    ispis(mat, r, s);

    printf("\n\nRedak koji se ubacuje:");
    int red;
    scanf("%d", &red);
    r++;
    ubacivanjeRetka(mat, r, s, red);
    ispis(mat, r, s);

    printf("\nStupac koji se brise:");
    int brisS;
    scanf("%d", &brisS);
    brisanjeStupca(mat, r, s, brisS);
    s--;
    ispis(mat, r, s);

    printf("\nStupac koji se dodaje:");
    int stupAdd;
    scanf("%d", &stupAdd);
    s++;
    ubacivanjeStupca(mat, r, s, stupAdd);
    ispis(mat, r, s);

    printf("\n\nKRAJ SVAKA CAST MAJSTORE TAKO SE TO RADI!!!!!!!!!!!!!!!!\n");

    return 0;
}

void popuna(int** mat, int r, int s)
{
    int i, j;
    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            mat[i][j] = rand() % 200;
        }
    }
}

void ispis(int** mat, int r, int s)
{
    int i, j;
    for(i = 0; i < r; i++){
        printf("\n");
        for(j = 0; j < s; j++){
            printf("%d ", mat[i][j]);
        }
    }
}

void maxiIndex(int** mat, int r, int s, int* max, int* indxX, int* indxY)
{
    int i, j;
    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            if(mat[i][j] > *max){
                *max = mat[i][j];
                *indxX = i;
                *indxY = j;
            }
        }
    }
}

void pretraga(int** mat, int r, int s, int vr, int* kooX, int* kooY)
{
    int i, j;
    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            if(mat[i][j] == vr){
                *kooX = i;
                *kooY = j;
            }
        }
    }
}

void brisanjeRetka(int** mat, int r, int s, int br)
{
    int i, j;
    for(i = br; i < r; i++){
        for(j = 0; j < s; j++){
            if(i != r-1){
                mat[i][j] = mat[i+1][j];
            }
        }
    }
}

void ubacivanjeRetka(int** mat, int r, int s, int br)
{
    int i, j;
    for(i = r-1; i > br; i--){
        for(j = 0; j < s; j++){
            if(i != r-1){
                mat[i][j] = mat[i-1][j];
            }
        }
    }
    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            if(i == br+1){
                mat[i][j] = 0;
            }
        }
    }
}

void brisanjeStupca(int** mat, int r, int s, int br)
{
    int i, j;
    for(i = 0; i < r; i++){
        for(j = br; j < s; j++){
            if(j != s-1){
                mat[i][j] = mat[i][j+1];
            }
        }
    }
}

void ubacivanjeStupca(int** mat, int r, int s, int br)
{
    int i, j;
    for(i = 0; i < r; i++){
        for(j = s-1; j > br; j--){
            if(j != s-1){
                mat[i][j] = mat[i][j-1];
            }
        }
    }

    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            if(j == br+1){
                mat[i][j] = 0;
            }
        }
    }
}

