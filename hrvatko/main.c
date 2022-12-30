#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXR 200
#define MAXS 200

void unos(char mat[MAXR][MAXS], int r, int s);
void ispis(char mat[MAXR][MAXS], int r, int s);
double udaljenost(int x, int y);
double pravoZnanje(char mat[MAXR][MAXS], int x, int y, int r, int s);
double strogost(int x, int y, int hX, int hY, double post);

int main()
{
    int i, j, r, s, hrvX, hrvY, predavacY, predavacX = -1;
    char mat[MAXR][MAXS];
    double postotak, strogoca = 0, prepisat = 0, ukupno = 0;

    while(1){
        scanf("%d", &r);
        scanf("%d", &s);
        if((r < 3 || r > 20) || (s < 3 || s > 20)){
            if(r > 20 || s > 20){
                printf("Prevelika dvorana za ispit");
            }
            if(r < 3 || s < 3){
                printf("Premala dvorana za ispit");
            }
            break;
        }
        else{
            scanf("%d", &predavacY);
            scanf("%lf", &postotak);
            if(predavacY > s){
                printf("Nastavnik mora biti u predavaonici!");
                break;
            }
            predavacY -= 1;

            unos(mat, r, s);

            for(i = 0; i < r; i++){
                for(j = 0; j < s; j++){
                    if(mat[i][j] == 'H'){
                        hrvX = i;
                        hrvY = j;
                    }
                }
            }

            prepisat = pravoZnanje(mat, hrvX, hrvY, r, s);
            strogoca = strogost(predavacX, predavacY, hrvX, hrvY, postotak);

            ukupno = prepisat - strogoca;

            if(ukupno < 0){
                printf("Sanse za prolaz su 0.00%%");
            }
            else if(ukupno > 100){
                printf("Sanse za prolaz su 100.00%%");
            }
            else{
                printf("Sanse za prolaz su %.2f%%", ukupno);
            }

            break;
        }
    }

    return 0;
}

void unos(char mat[MAXR][MAXS], int r, int s)
{
    int i, j;
    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            scanf(" %c", &mat[i][j]);
        }
    }
}

void ispis(char mat[MAXR][MAXS], int r, int s)
{
    int i, j;
    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
}

double udaljenost(int x, int y)
{
    double ukupno = 0;
    ukupno = sqrt(pow(x, 2) + pow(y, 2));
    return ukupno;
}

double pravoZnanje(char mat[MAXR][MAXS], int x, int y, int r, int s)
{
    int i, j;
    double ukupno = 0, nes = 0, a, b;
    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            nes = 0;
            if(mat[i][j] == 'Z'){
                a = x - i;
                b = y - j;
                nes = udaljenost(a, b);
                ukupno += 90 / pow(nes, 2);
            }
        }
    }

    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            nes = 0;
            if(mat[i][j] == 'N'){
                a = x - i;
                b = y - j;
                nes = udaljenost(a, b);
                ukupno -= 30 / pow(nes, 2);
            }
        }
    }

    return ukupno;
}

double strogost(int x, int y, int hX, int hY, double post)
{
    double ukupno = 0, nes = 0;
    double a, b;
    a = hX + 1;
    b = hY - y;
    nes = udaljenost(a, b);
    ukupno = post / pow(nes, 2);
    return ukupno;
}
