#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include "structy.h"
#include "smieciarka.h"
#include "odczyt.h"
#include "komunikacja.h"
#include "kopia.h"
int main() //glowna logika programu na poczatku wywoluje funkcje do wybrania folderu, potem uzytkownik decyduje co chce zrobic
{
    int opcja = 0;
    folder* glowa = NULL;
    glowa = komunikacjaStart();
    do{
    printf("%s","\nCo chcesz zrobic?\n0. Zamknij Program\n1. Zmien folder\n2. Wyszukaj Slowo\n3. Skopiuj pliki z folderow do innej lokalizacji\n");
    scanf("%d",&opcja);
    switch(opcja){
case 0:
    break;
case 1:
    smieciarkaFolderu(glowa);
    glowa = komunikacjaStart();
    break;
case 2:
    komunikacjaIloscSlow(glowa);
    break;
case 3:
    kopiaStart(glowa);
    break;
    }
    }while(opcja!=0);
    return 0;
}
