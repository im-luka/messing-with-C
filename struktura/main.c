#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int redniBroj;
    char prezime[50+1];
    char ime[50+1];
    char brOsobne[9+1];
    char jeliGlasao;
}GlasaciBiraliste;

typedef struct
{
    char prezime[50+1];
    char ime[50+1];
    int datumDan;
    int datumMj;
    int datumGod;
    char adresa[50+1];
    char grad[50+1];
    char brOsobne[9+1];
    int godSmrti;
}Mrtvaci;

typedef struct
{
    char brOsobne[9+1];
    char prezime[50+1];
    char ime[50+1];
    int datumDan;
    int datumMj;
    int datumGod;
    char ulica[100+1];
    int ulBroj;
    char grad[30+1];
}Puk;

typedef struct
{
    char ime[50+1];
    char prezime[50+1];
    int godSmrti;
}Smrtnici;

typedef struct
{
    char ime[50+1];
    char prezime[50+1];
    char adresa[100+1];
    int adrBroj;
    int datumDan;
    int datumMj;
    int datumGod;
}Pravnici;

typedef struct
{
    char grad[50+1];
    float postotak;
}Gradovi;

int main()
{
    FILE* ulaz = NULL;
    ulaz = fopen("biraliste.txt", "r");

    FILE* izlaz = NULL;
    izlaz = fopen("statistika.txt", "w");

    FILE* mrtvi = NULL;
    mrtvi = fopen("osmrtnice.txt", "r");

    FILE* pucani = NULL;
    pucani = fopen("puk.dat", "rb");
    fseek(pucani, 0, SEEK_END);
    int n = ftell(pucani) / sizeof(Puk);
    rewind(pucani);

    GlasaciBiraliste* nizGlasaci = NULL;
    nizGlasaci = (GlasaciBiraliste*)malloc(sizeof(GlasaciBiraliste) * 200);

    Mrtvaci* nizMrtvaci = NULL;
    nizMrtvaci = (Mrtvaci*)malloc(sizeof(Mrtvaci) * 300);

    Puk* nizPuk = NULL;
    nizPuk = (Puk*)malloc(sizeof(Puk) * n);

    Gradovi* nizGrad = NULL;
    nizGrad = (Gradovi*)malloc(sizeof(Gradovi) * 200);

    Gradovi* nizGrad2 = NULL;
    nizGrad2 = (Gradovi*)malloc(sizeof(Gradovi) * 200);

    int i, j, k, l, ukupnoGlasaca = 0;
    int brojacIzlaznost = 0;

    while(fscanf(ulaz, "#%d %[^/]/%[^/]/%[^;]; %c\n", &nizGlasaci[ukupnoGlasaca].redniBroj, nizGlasaci[ukupnoGlasaca].prezime, nizGlasaci[ukupnoGlasaca].ime, nizGlasaci[ukupnoGlasaca].brOsobne, &nizGlasaci[ukupnoGlasaca].jeliGlasao) >= 0){
        ukupnoGlasaca++;
    }

    int brojMrtvih = 0;
    while(fscanf(mrtvi, "%[^,], %[^#]#%d/%d/%d %[^(](%[^)]) %[^/]/%d\n", nizMrtvaci[brojMrtvih].prezime, nizMrtvaci[brojMrtvih].ime, &nizMrtvaci[brojMrtvih].datumDan, &nizMrtvaci[brojMrtvih].datumMj, &nizMrtvaci[brojMrtvih].datumGod, nizMrtvaci[brojMrtvih].adresa, nizMrtvaci[brojMrtvih].grad, nizMrtvaci[brojMrtvih].brOsobne, &nizMrtvaci[brojMrtvih].godSmrti) == 9){
        brojMrtvih++;
    }

    fread(nizPuk, sizeof(Puk), n, pucani);

    int glasacaMrtvih = 0;
    int neglasaca = 0;

    for(i = 0; i < ukupnoGlasaca; i++){
        if(nizGlasaci[i].jeliGlasao == 'D'){
            brojacIzlaznost++;
        }
    }
    for(i = 0; i < ukupnoGlasaca; i++){
        if(nizGlasaci[i].jeliGlasao == 'D'){
            for(j = 0; j < brojMrtvih; j++){
                if(strcmp(nizGlasaci[i].brOsobne, nizMrtvaci[j].brOsobne) == 0){
                    glasacaMrtvih++;
                }
            }
        }
    }
    for(i = 0; i < ukupnoGlasaca; i++){
        if(nizGlasaci[i].jeliGlasao == 'D'){
            for(j = 0; j < n; j++){
                if(strcmp(nizGlasaci[i].brOsobne, nizPuk[j].brOsobne) == 0){
                    neglasaca++;
                }
            }
        }
    }
    neglasaca = brojacIzlaznost - neglasaca;

    float izlaznost = (float)brojacIzlaznost / ukupnoGlasaca * 100;
    float izlaznostMrtvih = (float)glasacaMrtvih / brojacIzlaznost * 100;
    float izlaznostNE = (float)neglasaca / brojacIzlaznost * 100;

    fprintf(izlaz, "Izlaznost: %.2f%%\n", izlaznost);
    fprintf(izlaz, "Mrtvih: %.2f%%\n", izlaznostMrtvih);
    fprintf(izlaz, "Nisu na popisu: %.2f%%\n\n", izlaznostNE);
    fprintf(izlaz, "Mrtvi glasaci:\n");

    Smrtnici* nizMrtvihGlasaca = NULL;
    nizMrtvihGlasaca = (Smrtnici*)malloc(sizeof(Smrtnici) * 300);
    int brojac = 0, counter = 0;

    for(i = 0; i < ukupnoGlasaca; i++){
        if(nizGlasaci[i].jeliGlasao == 'D'){
            for(j = 0; j < brojMrtvih; j++){
                if(strcmp(nizGlasaci[i].brOsobne, nizMrtvaci[j].brOsobne) == 0){
                    strcpy(nizMrtvihGlasaca[brojac].ime, nizMrtvaci[j].ime);
                    strcpy(nizMrtvihGlasaca[brojac].prezime, nizMrtvaci[j].prezime);
                    nizMrtvihGlasaca[brojac].godSmrti = nizMrtvaci[j].godSmrti;
                    brojac++;
                    counter++;
                }
            }
        }
    }

    for(i = 0; i < brojac; i++){
        for(j = i+1; j < brojac; j++){
            if(nizMrtvihGlasaca[i].godSmrti > nizMrtvihGlasaca[j].godSmrti){
                Smrtnici tmp = nizMrtvihGlasaca[i];
                nizMrtvihGlasaca[i] = nizMrtvihGlasaca[j];
                nizMrtvihGlasaca[j] = tmp;
            }
        }
    }

    if(counter == 0){
        fprintf(izlaz, "NE POSTOJE\n");
    }
    else{
        for(i = 0; i < brojac; i++){
            fprintf(izlaz, "%d: %s %s\n", nizMrtvihGlasaca[i].godSmrti, nizMrtvihGlasaca[i].prezime, nizMrtvihGlasaca[i].ime);
        }
    }

    fprintf(izlaz, "\nLegalni glasaci:\n");
    Pravnici* nizLegalnih = NULL;
    nizLegalnih = (Pravnici*)malloc(sizeof(Pravnici) * 200);
    int lega = 0;
    int cnt = 0;
    for(i = 0; i < ukupnoGlasaca; i++){
        if(nizGlasaci[i].jeliGlasao == 'D'){
            for(j = 0; j < n; j++){
                if(strcmp(nizGlasaci[i].brOsobne, nizPuk[j].brOsobne) == 0){
                    cnt = 0;
                    for(k = 0; k < brojMrtvih; k++){
                        if(strcmp(nizGlasaci[i].brOsobne, nizMrtvaci[k].brOsobne) == 0){
                            cnt++;
                        }
                    }
                    if(cnt == 0){
                        strcpy(nizLegalnih[lega].ime, nizPuk[j].ime);
                        strcpy(nizLegalnih[lega].prezime, nizPuk[j].prezime);
                        strcpy(nizLegalnih[lega].adresa, nizPuk[j].ulica);
                        nizLegalnih[lega].adrBroj = nizPuk[j].ulBroj;
                        nizLegalnih[lega].datumDan = nizPuk[j].datumDan;
                        nizLegalnih[lega].datumMj = nizPuk[j].datumMj;
                        nizLegalnih[lega].datumGod = nizPuk[j].datumGod;
                        lega++;
                    }
                }
            }
        }
    }

    for(i = 0; i < lega; i++){
        for(j = i+1; j < lega; j++){
            if(strcmp(nizLegalnih[i].adresa, nizLegalnih[j].adresa) == 1){
                Pravnici tmp = nizLegalnih[i];
                nizLegalnih[i] = nizLegalnih[j];
                nizLegalnih[j] = tmp;
            }
            else if(strcmp(nizLegalnih[i].adresa, nizLegalnih[j].adresa) == 0){
                if(nizLegalnih[i].adrBroj > nizLegalnih[j].adrBroj){
                    Pravnici tmp2 = nizLegalnih[i];
                    nizLegalnih[i] = nizLegalnih[j];
                    nizLegalnih[j] = tmp2;
                }
                else if(nizLegalnih[i].adrBroj == nizLegalnih[j].adrBroj){
                    if(nizLegalnih[i].datumGod > nizLegalnih[j].datumGod){
                        Pravnici tmp3 = nizLegalnih[i];
                        nizLegalnih[i] = nizLegalnih[j];
                        nizLegalnih[j] = tmp3;
                    }
                    else if(nizLegalnih[i].datumGod == nizLegalnih[j].datumGod){
                        if(nizLegalnih[i].datumMj > nizLegalnih[j].datumMj){
                            Pravnici tmp4 = nizLegalnih[i];
                            nizLegalnih[i] = nizLegalnih[j];
                            nizLegalnih[j] = tmp4;
                        }
                        else if(nizLegalnih[i].datumMj == nizLegalnih[j].datumMj){
                            if(nizLegalnih[i].datumDan > nizLegalnih[j].datumDan){
                                Pravnici tmp5 = nizLegalnih[i];
                                nizLegalnih[i] = nizLegalnih[j];
                                nizLegalnih[j] = tmp5;
                            }
                        }
                    }
                }
            }
        }
    }

    for(i = 0; i < lega; i++){
        fprintf(izlaz, "%s %d: %d.%d.%d - %s %s\n", nizLegalnih[i].adresa, nizLegalnih[i].adrBroj, nizLegalnih[i].datumDan, nizLegalnih[i].datumMj, nizLegalnih[i].datumGod, nizLegalnih[i].ime, nizLegalnih[i].prezime);
    }

    int brojacGrad = 0;
    for(i = 0; i < ukupnoGlasaca; i++){
        for(j = 0; j < n; j++){
            if(strcmp(nizGlasaci[i].brOsobne, nizPuk[j].brOsobne) == 0){
                strcpy(nizGrad[brojacGrad].grad, nizPuk[j].grad);
                brojacGrad++;
            }
        }
    }

    for(i = 0; i < brojacGrad; i++){
        for(j = i+1; j < brojacGrad; j++){
            if(strcmp(nizGrad[i].grad, nizGrad[j].grad) == 1){
                Gradovi tmp = nizGrad[i];
                nizGrad[i] = nizGrad[j];
                nizGrad[j] = tmp;
            }
        }
    }

    int brojacGradTOCAN = 0;
    for(i = 0; i < brojacGrad; i++){
        if(strcmp(nizGrad[i].grad, nizGrad[i+1].grad) != 0){
            strcpy(nizGrad2[brojacGradTOCAN].grad, nizGrad[i].grad);
            brojacGradTOCAN++;
        }
    }

    int aktivno = 0, ukupno = 0;
    for(i = 0; i < brojacGradTOCAN; i++){
        aktivno = 0, ukupno = 0;
        for(j = 0; j < ukupnoGlasaca; j++){
            for(k = 0; k < n; k++){
                if(strcmp(nizGlasaci[j].brOsobne, nizPuk[k].brOsobne) == 0){
                    if(strcmp(nizGrad2[i].grad, nizPuk[k].grad) == 0){
                        if(nizGlasaci[j].jeliGlasao == 'D'){
                            aktivno++;
                            ukupno++;
                            for(l = 0; l < brojMrtvih; l++){
                                if(strcmp(nizMrtvaci[l].brOsobne, nizGlasaci[j].brOsobne) == 0){
                                    aktivno--;
                                    ukupno--;
                                }
                            }
                        }
                        else{
                            ukupno++;
                            for(l = 0; l < brojMrtvih; l++){
                                if(strcmp(nizMrtvaci[l].brOsobne, nizGlasaci[j].brOsobne) == 0){
                                    ukupno--;
                                }
                            }
                        }
                        nizGrad2[i].postotak = (float)aktivno / ukupno * 100;
                    }
                }
            }
        }
    }

    fprintf(izlaz, "\nStatistika po gradu:\n");
    if(brojacGradTOCAN == 1){
        fprintf(izlaz, "NIJE POTREBNO\n");
    }
    else{
        for(i = 0; i < brojacGradTOCAN; i++){
            if(nizGrad2[i].postotak >= 0 && nizGrad2[i].postotak <= 100){
                fprintf(izlaz, "%s: %.2f%%\n", nizGrad2[i].grad, nizGrad2[i].postotak);
            }
        }
    }

    fclose(pucani);
    fclose(mrtvi);
    fclose(izlaz);
    fclose(ulaz);

    return 0;
}
