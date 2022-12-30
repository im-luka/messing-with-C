#include <stdio.h>

typedef struct {
    int id;
    char naziv[100];
    char kategorija[50];
    float duljina;
    int brLez;
    int brSoba;
    int cijena;
}Model;

typedef struct {
    char reg[6+1];
    int sifraModela;
    char naziv[100+1];
    char luka[3+1];
    Model model;
}Jahta;

typedef struct {
    char kod[3+1];
    char naziv[100+1];
    double lat;
    double lng;
}Luka;

Model* ucitajModele(int* n)
{
    FILE* fin = fopen("modeli.dat", "rb");

    fseek(fin, 0, SEEK_END);
    *n = ftell(fin) / sizeof(Model);
    rewind(fin);

    Model* result = malloc(sizeof(Model) * (*n));
    fread(result, sizeof(Model), *n, fin);

    fclose(fin);

    return result;
}

Jahta* ucitajJahte(int* n)
{
    FILE* fin = fopen("mojejahte.txt", "r");

    Jahta* result = calloc(500, sizeof(Jahta));

    int br = 0;
    while(fscanf(fin, "%s%d %[^#]#%s", result[br].reg, &result[br].sifraModela, result[br].naziv, result[br].luka) == 4)
    {
        br++;
    }

    fclose(fin);

    *n = br;

    return result;
}

Luka* ucitajLuke(int* n)
{
    FILE* fin = fopen("luke.txt", "r");

    Luka* result = calloc(75, sizeof(Luka));

    int br = 0;
    while(fscanf(fin, "%s %[^(](%lf, %lf)", result[br].kod, result[br].naziv, &result[br].lat, &result[br].lng) == 4)
    {
        result[br].naziv[strlen(result[br].naziv) - 1] = 0;
        br++;
    }

    fclose(fin);

    *n = br;

    return result;
}

Luka* nadjiLuku(char* kod, Luka* luke, int n)
{
    int i;
    for(i = 0; i < n; i++){
        if (strcmp(kod, luke[i].kod) == 0){
            return &luke[i];
        }
    }
    return NULL;
}

Model nadjiModel(int id, Model* modeli, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        if (modeli[i].id == id) return modeli[i];
    }
    return *(Model*)calloc(1, sizeof(Model));
}

void sortJahte(Jahta* niz, int n)
{
    int i,j;
    for(i = 0; i < n; i++){
        for(j = i + 1; j < n; j++){
            if (niz[i].model.cijena > niz[j].model.cijena){
                Jahta tmp = niz[i];
                niz[i] = niz[j];
                niz[j] = tmp;
            }
        }
    }
}

int main()
{
    int i, j;

    int nModel;
    Model* modeli = ucitajModele(&nModel);

    int nJahte;
    Jahta* jahte = ucitajJahte(&nJahte);
    for(i = 0; i < nJahte; i++)
        jahte[i].model = nadjiModel(jahte[i].sifraModela, modeli, nModel);

    sortJahte(jahte, nJahte);

    int nLuke;
    Luka* luke = ucitajLuke(&nLuke);

    char polazisteKod[100];
    scanf("%s", polazisteKod);

    FILE* fout = fopen("rezultat.out", "w");

    Luka* polaziste = nadjiLuku(polazisteKod, luke, nLuke);
    if (polaziste == NULL){
        fprintf(fout, "Nepoznata marina.");
        exit(0);
    }
    fprintf(fout, "%s (%.6f, %.6f)\n", polaziste->naziv, polaziste->lat, polaziste->lng);

    int minCijena, maxCijena;
    scanf("%d%d", &minCijena, &maxCijena);

    int nasao = 0;
    for(i = 0; i < nJahte; i++){
        if (strcmp(jahte[i].luka, polazisteKod) == 0){
            if (jahte[i].model.cijena >= minCijena && jahte[i].model.cijena <= maxCijena){
                fprintf(fout, "%s %s %s %.2fft EUR%d\n", jahte[i].reg, jahte[i].model.kategorija, jahte[i].naziv, jahte[i].model.duljina, jahte[i].model.cijena);
                nasao = 1;
            }
        }
    }

    if (!nasao){
        fprintf(fout, "Nema brodova za danu pretragu.");
    }

    return 0;
}
