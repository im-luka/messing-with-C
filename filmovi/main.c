#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char naziv[50+1];
    char redatelj[50+1];
    int godina;
    float ocjena;
    char zanr[50+1];
}Film;

void sort(Film* niz, int n);

int main()
{
    FILE* fin = NULL;
    fin = fopen("filmovi.txt", "r");
    if(fin == NULL){
        printf("Neuspjesno otvaranje datoteke.\n");
        exit(1);
    }

    int i, n = 0;
    Film* niz;
    niz = (Film*)malloc(sizeof(Film) * 1000);

    while(fscanf(fin, "%[^#]#%[^#]#%d#%f#%s", niz[n].naziv, niz[n].redatelj, &niz[n].godina, &niz[n].ocjena, niz[n].zanr) == 5){
        n++;
    }

    sort(niz, n);

    FILE* fout = NULL;
    fout = fopen("lista.txt", "w");

    for(i = 0; i < n; i++){
        if(niz[i].ocjena > 5){
            fprintf(fout, "%s#%s#%d#%.1f#%s\n", niz[i].naziv, niz[i].redatelj, niz[i].godina, niz[i].ocjena, niz[i].zanr);
        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}

void sort(Film* niz, int n)
{
    int i, j;
    Film tmp;
    for(i = 0; i < n; i++){
        for(j = i+1; j < n; j++){
            if(niz[i].ocjena < niz[j].ocjena){
                tmp = niz[i];
                niz[i] = niz[j];
                niz[j] = tmp;
            }
        }
    }
}

