#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int meni = 0;
int brojKvizova;
int redniBroj;
int odabir;
int x = 0;
int broj;
int v1;
int v2;
int v3;

typedef struct studenti
{
    char index[10];
    char ime[20];
    char prezime[20];
    int kviz[10];
} studenti;

typedef struct pomoc
{
    char index[10];
    char ime[20];
    char prezime[20];
    int kviz[10];
} pomoc;

int init_load(pomoc *pomoc, FILE *file, studenti student[120])
{
    if (3 != fscanf(file, "%9s%19s%19s", pomoc->index, pomoc->ime, pomoc->prezime))
    {
        return 0;
    }

    strcpy(student[x].index, pomoc->index);
    strcpy(student[x].ime, pomoc->ime);
    strcpy(student[x].prezime, pomoc->prezime);

    char buffer[256];


    if (fgetc(file) != '\n' || !fgets(buffer, sizeof buffer, file))
    {
        return 0;
    }

    size_t i = 0;
    char *token = strtok(buffer, "|");

    if (token)
    {

        do
        {
        pomoc->kviz[i] = (int) strtol(token, NULL, 10);
        student[x].kviz[i] = pomoc->kviz[i];
        i++;
        } while (i < 10 && (token = strtok(NULL, "|")));
    }

    if (i != 10 || !fgets(buffer, sizeof buffer, file) || 0 != strncmp(buffer, "----------", 10))
    {
        return 0;
    }

    x++;

    return 1;
}

void print_studenti(studenti student[120])
{
    for(int i = 0; i < 120; i++)
    {
        printf("%s\n%s\n%s\n", student[i].index, student[i].ime, student[i].prezime);

        for (int j = 0; j < 10; j++)
        {
            printf("%d ", student[i].kviz[j]);
        }
        putchar('\n');
        putchar('\n');
    }
}

void Indeks(studenti student[120])
{
    studenti zamjena;

    for(int i = 0; i < 120-1; i++)
    {
        for(int j = 0; j < 120-i-1; j++)
        {
            if(strcmp(student[j].index, student[j+1].index) > 0)
            {
                zamjena = student[j];
                student[j] = student[j+1];
                student[j+1] = zamjena;
            }
        }
    }
}

void Ime(studenti student[120])
{
    int pozicija;
    studenti zamjena;

    for (int i = 0; i < (120 - 1); i++)
    {
        pozicija=i;
        for (int j = i + 1; j < 120; j++)
        {
            if(strcmp(student[pozicija].ime, student[j].ime) > 0)
            {
                pozicija = j;
            }
        }
        if (pozicija != i)
        {
            zamjena = student[i];
            student[i] = student[pozicija];
            student[pozicija] = zamjena;
        }
    }
}

void Prezime(studenti student[120])
{
    int pozicija;
    studenti zamjena;

    for (int i = 0; i < (120 - 1); i++)
    {
        pozicija=i;
        for (int j = i + 1; j < 120; j++)
        {
            if(strcmp(student[pozicija].prezime, student[j].prezime) > 0)
            {
                pozicija = j;
            }
        }
        if (pozicija != i)
        {
            zamjena = student[i];
            student[i] = student[pozicija];
            student[pozicija] = zamjena;
        }
    }
}


void Kviz(studenti student[120],int redniBroj[], int brojKvizova)
{
    studenti zamjena;
    int bodovi[120];
    int pomocniBodovi;

    for(int i = 0; i < 120; i++)
    {
        bodovi[i] = 0;
        for(int a = 0; a < brojKvizova; a++)
        {
            bodovi[i] += student[i].kviz[redniBroj[a]-1];
        }
    }

    for(int i = 0; i < 120; i++)
    {
        for(int j = 0; j < 120-i-1; j++)
        {
            if(bodovi[j] > bodovi[j+1])
            {
                zamjena = student[j];
                student[j] = student[j+1];
                student[j+1] = zamjena;

                pomocniBodovi = bodovi[j];
                bodovi[j] = bodovi[j+1];
                bodovi[j+1] = pomocniBodovi;
            }
        }
    }
}


void Grupe(studenti student[120], int meni, int izbor)
{

        if(meni == 2 || meni == 4)
        {
            for(int i = (izbor - 1) * 40; i < 40 * izbor; i++)
            {
                printf("Redni broj %d\n", i + 1);
                printf("%s\n%s\n%s\n", student[i].index, student[i].ime, student[i].prezime);

                for (int j = 0; j < 10; j++)
                {
                    printf("%d ", student[i].kviz[j]);

                }
                putchar('\n');
                putchar('\n');
            }

        }else if(meni == 1 || meni == 3)
        {
            for(int i = (izbor - 1) * 40; i < 40 * izbor; i++)
            {
                printf("%s\n%s\n%s\n", student[i].index, student[i].ime, student[i].prezime);

                for (int j = 0; j < 10; j++)
                {
                    printf("%d ", student[i].kviz[j]);
                }
                putchar('\n');
                putchar('\n');
            }
        }
}

void TraziUredi(FILE *file, studenti student[120])
{
    int izbor;
    int unos;
    int bodovi;
    int index;
    char s[20];
    fopen("studenti_2022.txt", "r+");

    printf("Unesite prezime:");

    scanf("%s",s);
    for(int i = 0; i < 120; i++)
    {
        if(strcmp(student[i].prezime,(s))==0)
        {
            printf("%s\n%s\n%s\n", student[i].index, student[i].ime, student[i].prezime);
            for (int j = 0; j < 10; j++)
            {
                printf("%d ", student[i].kviz[j]);
            }
            printf("\n");
        }
    }

    do
    {
        printf("Da li zelite urediti kviz(1-DA, 0-NE)?");
        scanf("%d", &izbor);
        if(izbor == 1){
            fopen("studenti_2022.txt", "w+");
            do
            {
                printf("Unesite koji kviz zelite urediti: ");
                scanf("%d", &unos);
                index = unos - 1;
                if(unos > 0 && unos < 11)
                {
                    do
                    {
                        printf("Unesite broj bodova: ");
                        scanf("%d", &bodovi);
                        if(bodovi > 0 && bodovi < 21)
                        {
                          for(int i = 0; i < 120; i++)
                          {
                                fprintf(file, "%s\n%s\n%s\n", student[i].index, student[i].ime ,student[i].prezime);
                                for (int j = 0; j < 10; j++)
                                {
                                    if(j == index && strcmp(student[i].prezime,(s))==0)
                                    {
                                            student[i].kviz[j] = bodovi;
                                    }
                                    fprintf(file, "%2d | ", student[i].kviz[j]);
                                }
                                fprintf(file, "\n-----------------------------------------------------\n");
                            }
                        }else
                        {
                            printf("Greska !\n");
                        }
                    }while(bodovi < 0 || bodovi > 20);
                }else
                {
                    printf("Greska pri unosu !\n");
                }
            }while(unos < 0 || unos > 10);
        fclose(file);
        }else if(izbor == 0)
        {
            system("cls");
            return -1;
        }
    }while(izbor < 0 || izbor > 1);

}


int varijabilnaFunkcija(int broj,...)
{
    va_list valist;
    int i;
    int suma = 0;


    va_start(valist, broj);

    for (i = 0; i < broj; i++)
    {
        suma += va_arg(valist, int);
    }

    va_end(valist);

    return suma;

}


void Amfiteatar(studenti student[120], int izbor)
{
    unsigned char crna = 176;
    unsigned char siva = 177;
    unsigned char bijela = 178;
    char prazno = ' ';
    int index[40];
    int a;
    int b = 40;
    int c = 80;

    for(a = 0; a < 40; a++)
    {
        if(izbor == 1)
        {
            index[a] = a;

        }else if(izbor == 2)
        {
            index[a] = b;
            b++;

        }else if(izbor == 3)
        {
            index[a] = c;
            c++;
        }

    }

    for(int h = 0; h < 8; h++)
    {
        if( h == 0 || h == 3 || h == 6)
        {
            for(int i = 0; i < 6; i++)
            {
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                if(h == 0 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[0]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[0]].prezime))/2)
                        {
                            printf("%s",student[index[0]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }

                }else if(h == 0 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 3 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[1]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[1]].prezime))/2)
                        {
                            printf("%s",student[index[1]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 3 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 6 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[2]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[2]].prezime))/2)
                        {
                            printf("%s",student[index[2]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 6 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", prazno);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                        printf("%c", bijela);
                }
                if(h == 0 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[3]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[3]].prezime))/2)
                        {
                            printf("%s",student[index[3]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 0 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 3 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[4]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[4]].prezime))/2)
                        {
                            printf("%s",student[index[4]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else  if(h == 3 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 6 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[5]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[5]].prezime))/2)
                        {
                            printf("%s",student[index[5]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 6 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                if(h == 0 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[6]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[6]].prezime))/2)
                        {
                            printf("%s",student[index[6]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else  if(h == 0 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 3 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[7]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[7]].prezime))/2)
                        {
                            printf("%s",student[index[7]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else  if(h == 3 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 6 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[8]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[8]].prezime))/2)
                        {
                            printf("%s",student[index[8]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 6 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", prazno);
                }
                if(h == 0 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[9]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[9]].prezime))/2)
                        {
                            printf("%s",student[index[9]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else  if(h == 0 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 3 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[10]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[10]].prezime))/2)
                        {
                            printf("%s",student[index[10]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 3 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 6 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[11]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[11]].prezime))/2)
                        {
                            printf("%s",student[index[11]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 6 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                if(h == 0 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[12]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[12]].prezime))/2)
                        {
                            printf("%s",student[index[12]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else  if(h == 0 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 3 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[13]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[13]].prezime))/2)
                        {
                            printf("%s",student[index[13]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 3 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 6 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[14]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[14]].prezime))/2)
                        {
                            printf("%s",student[index[14]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 6 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }

            printf("\n");
            }
        }else if(h == 1 || h == 4 || h == 7)
        {
            for(int i = 0; i < 6; i++)
            {
                if(h == 1 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[15]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[15]].prezime))/2)
                        {
                            printf("%s",student[index[15]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 1 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 4 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[16]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[16]].prezime))/2)
                        {
                            printf("%s",student[index[16]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 4 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 7 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[17]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[17]].prezime))/2)
                        {
                            printf("%s",student[index[17]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 7 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                if(h == 1 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[18]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[18]].prezime))/2)
                        {
                            printf("%s",student[index[18]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 1 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 4 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[19]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[19]].prezime))/2)
                        {
                            printf("%s",student[index[19]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 4 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 7 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[20]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[20]].prezime))/2)
                        {
                            printf("%s",student[index[20]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 7 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", prazno);
                }
                if(h == 1 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[21]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[21]].prezime))/2)
                        {
                            printf("%s",student[index[21]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 1 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 4 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[22]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[22]].prezime))/2)
                        {
                            printf("%s",student[index[22]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 4 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 7 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[23]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[23]].prezime))/2)
                        {
                            printf("%s",student[index[23]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 7 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                if(h == 1 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[24]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[24]].prezime))/2)
                        {
                            printf("%s",student[index[24]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 1 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 4 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[25]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[25]].prezime))/2)
                        {
                            printf("%s",student[index[25]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 4 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 7 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[26]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[26]].prezime))/2)
                        {
                            printf("%s",student[index[26]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 7 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                if(h == 1 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[27]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[27]].prezime))/2)
                        {
                            printf("%s",student[index[27]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 1 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 4 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[28]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[28]].prezime))/2)
                        {
                            printf("%s",student[index[28]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 4 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 7 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[29]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[29]].prezime))/2)
                        {
                            printf("%s",student[index[29]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 7 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", prazno);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                if(h == 1 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[30]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[30]].prezime))/2)
                        {
                            printf("%s",student[index[30]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 1 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 4 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[31]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[31]].prezime))/2)
                        {
                            printf("%s",student[index[31]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 4 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 7 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[32]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[32]].prezime))/2)
                        {
                            printf("%s",student[index[32]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 7 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                if(h == 1 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[33]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[33]].prezime))/2)
                        {
                            printf("%s",student[index[33]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 1 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 4 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[34]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[34]].prezime))/2)
                        {
                            printf("%s",student[index[34]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 4 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 7 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[35]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[35]].prezime))/2)
                        {
                            printf("%s",student[index[35]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 7 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
            printf("\n");
            }
        }else if( h == 2 || h == 5)
        {
            for(int i = 0; i < 6; i++)
            {
                for(int j = 0; j < 20; j++)
                {
                printf("%c", bijela);
                }
                if(h == 2 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[36]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[36]].prezime))/2)
                        {
                            printf("%s",student[index[36]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 2 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 5 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[37]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[37]].prezime))/2)
                        {
                            printf("%s",student[index[37]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 5 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                if(h == 2 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[38]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[38]].prezime))/2)
                        {
                            printf("%s",student[index[38]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 2 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                if(h == 5 && i == 3)
                {
                    for(int i = 0; i <= 20-strlen(student[index[39]].prezime); i++)
                    {
                        if(i == (20-strlen(student[index[39]].prezime))/2)
                        {
                            printf("%s",student[index[39]].prezime);
                        }else
                        {
                            printf("%c",siva);
                        }
                    }
                }else if(h == 5 && i != 3)
                {
                    for(int j = 0; j < 20; j++)
                    {
                        printf("%c", siva);
                    }
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", prazno);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", siva);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", siva);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                printf("%c", bijela);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", prazno);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", siva);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", crna);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", bijela);
                }
                for(int j = 0; j < 20; j++)
                {
                    printf("%c", siva);
                }
            printf("\n");
            }
        }

    }

}
