#include <stdio.h>
#include <stdlib.h>

void ispuna(FILE* datoteka, int r, int s, int** mat);
void sortiranje(FILE* dat, int r, int s, int** mat);
void zamjena(FILE* dat, int r, int s, int** mat);

int main()
{
    FILE* datoteka = NULL;
    datoteka = fopen("primjer.txt", "w");

    int r, s, i, j;
    scanf("%d %d", &r, &s);

    int** mat = NULL;
    mat = (int**)malloc(sizeof(int*) * r);
    if(mat == NULL){
        printf("alokacija neuspjesna\n");
        exit(1);
    }
    for(i = 0; i < r; i++){
        mat[i] = (int*)malloc(sizeof(int) * s);
        if(mat[i] == NULL){
            printf("alokacija neuspjesna\n");
            exit(1);
        }
    }

    ispuna(datoteka, r, s, mat);

    for(i = 0; i < r; i++){
        printf("\n");
        for(j = 0; j < s; j++){
            printf("%d ", mat[i][j]);
        }
    }

    printf("\n\nPoslije sorta:\n");
    sortiranje(datoteka, r, s, mat);
    for(i = 0; i < r; i++){
        printf("\n");
        for(j = 0; j < s; j++){
            printf("%d ", mat[i][j]);
        }
    }
    printf("\n");
    fclose(datoteka);

    FILE* datoteka2 = NULL;
    datoteka2 = fopen("primjer.txt", "a");
    fprintf(datoteka2, "\n\nNova:\n");
    zamjena(datoteka2, r, s, mat);
    printf("\n\n");
    for(i = 0; i < r; i++){
        printf("\n");
        for(j = 0; j < s; j++){
            printf("%d ", mat[i][j]);
        }
    }

    fclose(datoteka2);

    return 0;
}

void ispuna(FILE* datoteka, int r, int s, int** mat)
{
    int i, j;
    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            mat[i][j] = rand() % 40;
            fprintf(datoteka, "%d ", mat[i][j]);
        }
        fprintf(datoteka, "\n");
    }
}

void sortiranje(FILE* dat, int r, int s, int** mat)
{
    int i, j, k, xvar;
    for(i = 0; i < r; i++){
        xvar = -1000;
        for(j = 0; j < s; j++){
            for(k = j+1; k < s; k++){
                if(mat[i][j] > mat[i][k]){
                    xvar = mat[i][j];
                    mat[i][j] = mat[i][k];
                    mat[i][k] = xvar;
                }
            }
        }
    }
}

void zamjena(FILE* dat, int r, int s, int** mat)
{
    int i, j;
    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            if(mat[i][j] % 2 == 0){
                mat[i][j] = 0;
                fprintf(dat, "%d ", mat[i][j]);
            }
            else{
                mat[i][j] = 1;
                fprintf(dat, "%d ", mat[i][j]);
            }
        }
        fprintf(dat, "\n");
    }
}


