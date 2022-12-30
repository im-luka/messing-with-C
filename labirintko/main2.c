#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXR 200
#define MAXS 200

void unos(char** mat, int r, int s);
void ispis(char** mat, int r, int s);
void ispisiFloat(float** mat, int r, int s);
void ispisInt(int ** mat, int r, int s);
double udaljenost(int x, int y);
float udaljenost2(int x1, int y1, int x2, int y2);
double pravoZnanje(char mat[MAXR][MAXS], int x, int y, int r, int s);
double strogost(int x, int y, int hX, int hY, double post);
float izracunPostotkaZaLokaciju(char** dvorana, int brRed, int brStup, int mjestoRed, int mjestoStupac, int prof, int profStrog);
float** izracunajProlaznosti(char** dvorana, int brRed, int brStup, int prof, int profStrog);
float nadjiNajboljeMjesto(float** matricaProlaznosti, int brRed, int brStup, int* najboljiRed, int* najboljiStupac);
int rekurzija(char** mat, float** prolaznosti, int ** labirint, int r, int s, float najboljiP, int uX, int uY);

int main()
{
    int i, j, r, s, hrvX, hrvY, predavacY, predavacX = -1, najX = 0, najY = 0, rek = 0;
    char** mat = NULL;
    double postotak, strogoca = 0, prepisat = 0, ukupno = 0;
    float **prolaznosti = NULL;
    int **labirint = NULL;
    float najboljiP = 0;
    char dio2;

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

        mat = (char**)malloc(r * sizeof(char*));
        if(mat == NULL){
            printf("Alokacija neuspjesna");
            exit(1);
        }
        for(i = 0; i < r; i++){
            mat[i] = (char*)malloc(s * sizeof(char));
            if(mat[i] == NULL){
                printf("Alokacija neuspjesna");
                exit(1);
            }
        }
            unos(mat, r, s);
            scanf(" %c", &dio2);
            prolaznosti = izracunajProlaznosti(mat, r, s, predavacY, postotak);
            ispisFloat(prolaznosti, r, s);
            najboljiP = nadjiNajboljeMjesto(prolaznosti, r, s, &najX, &najY);
            printf("Najveci postotak je: %.2f%% na koordinatama X=%d, Y=%d", najboljiP, najX, najY);
            if(dio2 == 'D'){
                int uX = 0, uY = 0;
                for(i = 0; i < r; i++){
                    for(j = 0; j < s; j++){
                        if((i == 0 || i == r - 1 || j == 0 || j == s) && mat[i][j] == 'X'){
                            uX = i;
                            uY = j;
                        }
                    }
                }
                labirint = (int**)calloc(r, sizeof(int*));
                if(labirint == NULL){
                    printf("Alokacija neuspjesna");
                    exit(1);
                }
                for(i = 0; i < r; i++){
                    labirint[i] = (int*)calloc(s, sizeof(int));
                    if(labirint[i] == NULL){
                        printf("Alokacija neuspjesna");
                        exit(1);
                    }
                }
                rek = rekurzija(mat, prolaznosti, labirint, r, s, najboljiP, uX, uY);
                ispisInt(labirint, r, s);
            }
            break;
        }
    }
    return 0;
}
int rekurzija(char** mat, float** prolaznosti, int **labirint, int r, int s, float najboljiP, int uX, int uY){
    if(prolaznosti[uX][uY] == najboljiP && mat[uX][uY] == 'X'){
        labirint[uX][uY] = 1;
        return 0;
    }
    if(uX >= 0 && uX < r && uY >= 0 && uY < s && mat[uX][uY] == 'X' && labirint[uX][uY] == 0){
        labirint[uX][uY] = 1;
        if(rekurzija(mat, prolaznosti, labirint, r, s, najboljiP, uX + 1, uY) == 0){
            return 0;
        }
        if(rekurzija(mat, prolaznosti, labirint, r, s, najboljiP, uX -1, uY) == 0){
            return 0;
        }
        if(rekurzija(mat, prolaznosti, labirint, r, s, najboljiP, uX, uY +1) == 0){
            return 0;
        }
        if(rekurzija(mat, prolaznosti, labirint, r, s, najboljiP, uX, uY -1) == 0){
            return 0;
        }
        labirint[uX][uY] = 0;
        return 1;
    }
    else{
        return 1;
    }
}

void unos(char** mat, int r, int s)
{
    int i, j;
    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            scanf(" %c", &mat[i][j]);
        }
    }
}

void ispis(char** mat, int r, int s)
{
    int i, j;
    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
}

void ispisFloat(float** mat, int r, int s){
    int i, j;
    for(i = 0; i < r; i++){
        for(j = 0; j < s; j++){
            printf("%6.2f", mat[i][j]);
        }
        printf("\n");
    }
}

void ispisInt(int **mat, int r, int s){
    int i, j;
    for(i = 0; i < r; i++){
        printf("\n");
        for(j = 0; j < s; j++){
            printf("%d", mat[i][j]);
        }
    }
}
float udaljenost2(int x1, int y1, int x2, int y2){
    float udaljenost2;
    udaljenost2 = pow(x1 - x2, 2) + pow(y1 - y2, 2);
    return udaljenost2;
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
float izracunPostotkaZaLokaciju(char** dvorana, int brRed, int brStup, int mjestoRed, int mjestoStupac, int prof, int profStrog)
{
    int i, j;
    float uk = 0, utjecajProf = 0;
    utjecajProf = profStrog / udaljenost2(-1, prof, mjestoRed, mjestoStupac);
    uk -= utjecajProf;
    for(i = 0; i < brRed; i++){
        for(j = 0; j < brStup; j++){
            if(dvorana[i][j] == 'Z'){
                uk += 90 / udaljenost2(i, j, mjestoRed, mjestoStupac);
            }
            else if(dvorana[i][j] == 'N'){
                uk -= 30 / udaljenost2(i, j, mjestoRed, mjestoStupac);
            }
        }
    }
    return uk;
}

float** izracunajProlaznosti(char** dvorana, int brRed, int brStup, int prof, int profStrog)
{
    int i, j;
    float** prolaznosti = NULL;
    float postotak;
    prolaznosti = (float**)malloc(brRed * sizeof(float*));
    if(prolaznosti == NULL){
        printf("Alokacija neuspjesna");
        exit(1);
    }
    for(i = 0; i < brRed; i++){
        prolaznosti[i] = (float*)calloc(brStup, sizeof(float));
        if(prolaznosti[i] == NULL){
            printf("Alokacija neuspjesna");
            exit(1);
        }
    }
    for(i = 0; i < brRed; i++){
        for(j = 0; j < brStup; j++){
            if(dvorana[i][j] == 'X'){
                postotak = izracunPostotkaZaLokaciju(dvorana, brRed, brStup, i, j, prof, profStrog);
                if(postotak < 0){
                    prolaznosti[i][j] = 0;
                }
                else if (postotak > 100){
                    prolaznosti[i][j] = 100;
                }
                else{
                    prolaznosti[i][j] = postotak;
                }
            }
        }
    }
    return prolaznosti;
}
float nadjiNajboljeMjesto(float** matricaProlaznosti, int brRed, int brStup, int* najboljiRed, int* najboljiStupac)
{
    float najboljiPostotak = 0;
    int i = 0, j = 0;
    for(i = 0; i < brRed; i++){
        for(j = 0; j < brStup; j++){
            if(matricaProlaznosti[i][j] > najboljiPostotak){
            *najboljiRed = i;
            *najboljiStupac = j;
            najboljiPostotak = matricaProlaznosti[i][j];
            }
        }
    }
    *najboljiRed +=1;
    *najboljiStupac +=1;
    return najboljiPostotak;
}
