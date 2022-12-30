#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* korak1(char* recenica);
char* korak2(char* recenica);
char* korak3(char* recenica);
char* korak4(char* recenica);
char* korak5(char* recenica);
char* korak6(char* recenica);

int main()
{
    int i, koraci;
    char recenica[120+1];
    char* niz1 = NULL;
    char* niz2 = NULL;
    char* niz3 = NULL;
    char* niz4 = NULL;
    char* niz5 = NULL;
    char* niz6 = NULL;
    scanf("%d", &koraci);
    scanf("%s", recenica);

    if(koraci == 1){
        niz1 = korak1(recenica);
    }
    else if(koraci == 2){
        niz1 = korak1(recenica);
        niz2 = korak2(niz1);
    }
    else if(koraci == 3){
        niz1 = korak1(recenica);
        niz2 = korak2(niz1);
        niz3 = korak3(niz2);
    }
    else if(koraci == 4){
        niz1 = korak1(recenica);
        niz2 = korak2(niz1);
        niz3 = korak3(niz2);
        niz4 = korak4(niz3);
    }
    else if (koraci == 5){
        niz1 = korak1(recenica);
        niz2 = korak2(niz1);
        niz3 = korak3(niz2);
        niz4 = korak4(niz3);
        niz5 = korak5(niz4);
    }
    else{
        niz1 = korak1(recenica);
        niz2 = korak2(niz1);
        niz3 = korak3(niz2);
        niz4 = korak4(niz3);
        niz5 = korak5(niz4);
        niz6 = korak6(niz5);
    }

    return 0;
}

char* korak1(char* recenica)
{
    int dulj = strlen(recenica);
    char* rec = NULL;
    rec = (char*)calloc(120+1, sizeof(char));
    char* rec2 = NULL;
    rec2 = (char*)calloc(120+1, sizeof(char));

    int i, brojac = 0;
    for(i = 0; i < dulj; i++){
        rec[i] = recenica[i];
    }

    for(i = 0; i < dulj; i++){
        if(recenica[i] == '*'){
            brojac = 0;
            while(recenica[i++] == '*'){
                if(i > dulj){
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
    for(i = 0; i < dulj; i++){
        if(rec[i] != '*'){
            rec2[poz] = rec[i];
            poz++;
        }
    }
    printf("Nakon koraka 1:\n%s\n", rec2);

    return rec2;
}

char* korak2(char* recenica)
{
    int dulj = strlen(recenica);
    char* rec = NULL;
    rec = (char*)calloc(120+1, sizeof(char));
    char* rec2 = NULL;
    rec2 = (char*)calloc(120+1, sizeof(char));
    char* rec3 = NULL;
    rec3 = (char*)calloc(120+1, sizeof(char));

    int i, brojac = 0, pozicija;
    for(i = 0; i < dulj; i++){
        rec[i] = recenica[i];
    }

    for(i = 0; i < dulj; i++){
        if((recenica[i] < 48 || recenica[i] > 57) && (recenica[i] < 65 || recenica[i] > 90) && (recenica[i] < 97 || recenica[i] > 122)){
            rec[i] = '$';
        }
    }
    for(i = 0; i < dulj; i++){
        rec2[i] = rec[i];
    }

    int indx = 0, vell = 0, varPom = 0, varBr = 0;
    int niz[10];
    for(i = 0; i < dulj; i++){
        if(rec[i] == '$'){
            brojac = 0;
            while(rec[i++] == '$'){
                if(i > dulj){
                    break;
                }
                brojac++;
            }
            if(brojac == 1){
                rec2[i - brojac - 1] = ' ';
            }
            else if(brojac > 1 && brojac < 10){
                rec2[i - brojac - 1] = brojac + 48;
            }
            else{
                varPom = i;
                varBr = brojac;
                while(brojac){
                    niz[indx] = brojac % 10;
                    indx++;
                    brojac /= 10;
                    vell++;
                }
            }
            i--;
        }
    }
    int pomoc = varPom - varBr - 1;
    for(i = vell-1; i >= 0; i--){
        rec2[pomoc] = niz[i] + 48;
        pomoc++;
    }

    int poz = 0;
    for(i = 0; i < dulj; i++){
        if(rec2[i] != '$'){
            rec3[poz] = rec2[i];
            poz++;
        }
    }

    int test = strlen(rec3);
    printf("Nakon koraka 2:\n");
    for(i = 0; i < test; i++){
        printf("%c", rec3[i]);
    }
    printf("\n\n");

    return rec3;
}

char* korak3(char* recenica)
{
    int dulj = strlen(recenica);
    char* rec = NULL;
    rec = (char*)calloc(2000, sizeof(char));
    char* rijec;
    int i;
    rijec = strtok (recenica, " ");
    int br = 0;
    int brZnam = 0;
    while (rijec != NULL)
    {
        for(i = 0; i < strlen(rijec); i++){
            if(rijec[i] >= 48 && rijec[i] <= 57){
                br *= 10;
                br += rijec[i] - 48;
            }
            else if((rijec[i] >= 65 && rijec[i] <= 90) || (rijec[i] >= 97 && rijec[i] <= 122)){
                br = 0;
            }
        }
        int tempZnam = br;
        while(tempZnam){
            brZnam++;
            tempZnam /= 10;
        }
        if(br == 0){
           strncat(rec, rijec, strlen(rijec) - brZnam);
        }
        else{
            for(i = 0; i < br; i++){
                strncat(rec, rijec, strlen(rijec) - brZnam);
            }
        }
        brZnam = 0;
        strcat(rec, " ");
        rijec = strtok (NULL, " ");
    }
    rec[strlen(rec)-1] = '\0';
    printf("\nNakon koraka 3:\n%s\n", rec);

    return rec;
}

char* korak4(char* recenica)
{
    int dulj = strlen(recenica);
    char* rec = NULL;
    rec = (char*)calloc(2000, sizeof(char));
    int i;

    for(i = 0; i < dulj; i++){
        if(((recenica[i] >= 65 && recenica[i] <= 90) || (recenica[i] >= 97 && recenica[i] <= 122)) && !((recenica[i+1] >= 65 && recenica[i+1] <= 90) || (recenica[i+1] >= 97 && recenica[i+1] <= 122))){
            strcat(rec, "*");
        }
        else if((recenica[i] >= 48 && recenica[i] <= 57) && !(recenica[i+1] >= 48 && recenica[i+1] <= 57)){
            strcat(rec, "_");
        }
        else if(recenica[i] == ' '){
            strcat(rec, " ");
        }
    }
    printf("\nNakon koraka 4:\n%s\n", rec);

    return rec;
}

char* korak5(char* recenica)
{
    int dulj = strlen(recenica);
    char* rec = NULL;
    rec = (char*)calloc(2000, sizeof(char));
    int i, j;
    int brojacZvj = 0, brojacUnd = 0;
    for(i = 0; i < dulj; i++){
        if(recenica[i] == '*'){
            brojacZvj++;
        }
        else if(recenica[i] == '_'){
            brojacUnd++;
        }
        else if(recenica[i] == ' '){
            for(j = 0; j < brojacZvj; j++){
                strcat(rec, "*");
            }
            for(j = 0; j < brojacUnd; j++){
                strcat(rec, "_");
            }
            brojacZvj = 0;
            brojacUnd = 0;
            strcat(rec, " ");
        }
        if(recenica[i + 1] == '\0'){
            for(j = 0; j < brojacZvj; j++){
                strcat(rec, "*");
            }
            for(j = 0; j < brojacUnd; j++){
                strcat(rec, "_");
            }
            brojacZvj = 0;
            brojacUnd = 0;
        }
    }
    printf("\nNakon koraka 5: \n%s\n", rec);
    return rec;
}

char* korak6 (char* recenica){
    int dulj = strlen(recenica);
    char* rec = NULL;
    rec = (char*)calloc(2000, sizeof(char));
    char* rijec;
    rijec = strtok (recenica, " ");

    int i;
    int maxZvj = 0;
    int minUnd = 1000;
    char* strZvj = calloc(2000, sizeof(char));
    char* strUnd = calloc(2000, sizeof(char));
    while (rijec != NULL)
    {
        int brojacZvj = 0;
        int brojacUnd = 0;
        for(i = 0; i < strlen(rijec); i++){
            if(rijec[i] == '*'){
                brojacZvj++;
            }
            if(rijec[i] == '_'){
                brojacUnd++;
            }
        }
        if(brojacZvj > maxZvj){
            strcpy(strZvj, rijec);
            maxZvj = brojacZvj;
        }
        if(brojacUnd < minUnd){
            strcpy(strUnd, rijec);
            minUnd = brojacUnd;
        }
        rijec = strtok (NULL, " ");
    }
    strcat(rec, strZvj);
    strcat(rec, " ");
    strcat(rec, strUnd);

    printf("\nNakon koraka 6: \n%s", rec);
    return rec;
}




