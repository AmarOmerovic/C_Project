#include <stdio.h>
#include "student.h"

int main()
{
    system("MODE 401,800");
    pomoc p;
    studenti student[120];

    FILE *file = fopen("studenti_2022.txt", "r");
    if (file) while (init_load(&p, file, student));
    fclose(file);

    print_studenti(student);


    /* printf("Unesite koliko kvizova zelite ureditit(1-3): ");
    scanf("%d", &broj);
    if(broj == 1)
    {
        printf("Unesite redni broj kviza(1-10): ");
        scanf("%d", &v1);
        v1=v1-1;
        for(int i = 0; i < 120; i++)
        {
            printf("%d\n",varijabilnaFunkcija(broj, student[i].kviz[v1]));
        }

    }else if(broj == 2)
    {
        printf("Unesite redni broj kviza(1-10): ");
        scanf("%d", &v1);
        printf("Unesite redni broj kviza(1-10): ");
        scanf("%d", &v2);
        v1=v1-1;
        v2=v2-1;
        for(int i = 0; i < 120; i++)
        {
            printf("%d\n", varijabilnaFunkcija(broj, student[i].kviz[v1], student[i].kviz[v2]));
        }

    }else if(broj == 3)
    {
        printf("Unesite redni broj kviza(1-10): ");
        scanf("%d", &v1);
        printf("Unesite redni broj kviza(1-10): ");
        scanf("%d", &v2);
        printf("Unesite redni broj kviza(1-10): ");
        scanf("%d", &v3);
        v1=v1-1;
        v2=v2-1;
        v3=v3-1;
        for(int i = 0; i < 120; i++)
        {
            printf("%d\n", varijabilnaFunkcija(broj, student[i].kviz[v1], student[i].kviz[v2], student[i].kviz[v3]));
        }
    }else
    {
        printf("Pogresan unos!");
    } */




        do {
        if (meni == 0)
        {
            printf("Kako zelite sortirati studente?(1-5)\n ");
            printf("1 Po broju indexa\n 2 Po imenu\n 3 Po prezimenu\n 4 Po broju bodova iz kviza\n 5 Izlaz\n");
            printf("\n\nUnos:");
            scanf("%d", &meni);
        }else if(meni == 1)
        {
            system("cls");
            do{
                printf("Izaberite grupu studenata(1-4).\n");
                printf("1 Grupa A(prvih 40)\n");
                printf("2 Grupa B(drugih 40)\n");
                printf("3 Grupa C(zadnjih 40)\n");
                printf("4 Nazad\n\n\n");
                printf("Odabir grupe: ");
                scanf("%d", &odabir);
                if(odabir == 1 || odabir == 2 || odabir == 3)
                {
                    system("cls");
                    Indeks(student);
                    Grupe(student, meni, odabir);
                    Amfiteatar(student, odabir);
                    TraziUredi(file, student);

                }else if (odabir ==4)
                {
                    system("cls");
                }else
                {
                    system("cls");
                    printf("Pogresan unos!\n\n");
                }
            }while(odabir != 4);
        meni = 0;
        }else if(meni == 2)
        {
            system("cls");
            do{
                printf("Izaberite grupu studenata(1-4).\n");
                printf("1 Grupa A(prvih 40)\n");
                printf("2 Grupa B(drugih 40)\n");
                printf("3 Grupa C(zadnjih 40)\n");
                printf("4 Nazad\n\n\n");
                printf("Odabir grupe: ");
                scanf("%d", &odabir);
                if(odabir == 1 || odabir == 2 || odabir == 3)
                {
                    system("cls");
                    Ime(student);
                    Grupe(student, meni, odabir);
                    Amfiteatar(student, odabir);
                    TraziUredi(file, student);
                }else if (odabir ==4)
                {
                    system("cls");
                }else
                {
                    system("cls");
                    printf("Pogrešan unos!\n\n");
                }
            }while(odabir != 4);

        meni = 0;
        }else if(meni == 3)
        {
            system("cls");
            do{
                printf("Izaberite grupu studenata(1-4).\n");
                printf("1 Grupa A(prvih 40)\n");
                printf("2 Grupa B(drugih 40)\n");
                printf("3 Grupa C(zadnjih 40)\n");
                printf("4 Nazad\n\n\n");
                printf("Odabir grupe: ");
                scanf("%d", &odabir);
                if(odabir == 1 || odabir == 2 || odabir == 3)
                {
                    system("cls");
                    Prezime(student);
                    Grupe(student, meni, odabir);
                    Amfiteatar(student, odabir);
                    TraziUredi(file, student);
                }else if (odabir ==4)
                {
                    system("cls");

                }else
                {
                    system("cls");
                    printf("Pogresan unos!\n\n");
                }
            }while(odabir != 4);
        meni = 0;
        }else if(meni == 4)
        {
                system("cls");
                printf("Na osnovu koliko kvizova zelite da izvrsite sortiranje(1-10)?");
                printf("Unos: ");
                scanf("%d", &brojKvizova);
                    int redniBroj[brojKvizova];
                    printf("Unesite redne broje kvizova(1-10).\n");
                    for(int i = 0; i < brojKvizova; i++)
                    {
                        printf("Unosite redni broj: ");
                        scanf("%d", &redniBroj[i]);

                    }
                system("cls");

            do{
                printf("Izaberite grupu studenata.(1-4)\n");
                printf("1 Grupa A(prvih 40)\n");
                printf("2 Grupa B(drugih 40)\n");
                printf("3 Grupa C(zadnjih 40)\n");
                printf("4 Nazad\n\n\n");
                printf("Odabir grupe: ");
                scanf("%d", &odabir);
                if(odabir == 1 || odabir == 2 || odabir == 3)
                {
                    system("cls");
                    Kviz(student, redniBroj, brojKvizova);
                    Grupe(student, meni, odabir);
                    Amfiteatar(student, odabir);
                    TraziUredi(file, student);
                }else if (odabir ==4)
                {
                    system("cls");

                }else
                {
                    system("cls");
                    printf("Pogresan unos!\n\n");
                }

            }while(odabir != 4);
        meni = 0;
        }else
        {
            system("cls");
            printf("Pogresan unos!\n\n");
            meni = 0;
        }
    } while((meni!=5) || (meni >0 && meni<5));

    return 0;

}
