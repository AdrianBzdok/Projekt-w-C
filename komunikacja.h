
void komunikacjaWypiszSlowa(slowo* lista){ //funkcja mi sluzyla do testow czy zczytywanie slow dobrze dziala
if(lista!=NULL){
    printf("%c",'|');
    printf("%s",lista->World);
    komunikacjaWypiszSlowa(lista->Next);
} else {
    printf("%s","\n----------------KONIEC PLIKU----------------\n");
}
}

void komunikacjaWypiszfolder(folder* folder,int rekurencja){ //funkcja przyjmuje struct folder ktory ma juz wpisany podfoldery i pliki i sluszy do wypisywania ich na ekran. char wciecia sluzy do dodania wizualizacji hierarchii folderow za pomoca spacji
if(folder!=NULL){
    char* wciecia = (char*)malloc(sizeof(char)*((rekurencja+1)*5));
    strcpy(wciecia,"");
    int a = 0;
        while(a<=rekurencja){
        strcat(wciecia,"    ");
        a++;
        }
    printf("\n%s",wciecia);
    printf("%s",folder->Name);
    free(wciecia);
    komunikacjaWypiszPliki(folder->Files,rekurencja+1);
    komunikacjaWypiszfolder(folder->Directories,rekurencja+1);
    komunikacjaWypiszfolder(folder->Next,rekurencja);
    return;
}
}
void komunikacjaWypiszPliki(plik* plik,int rekurencja){ //funkcja wypisuje pliki na ekran, dziala prawie tak samo jak wypiszfoldery z pominieciem wywolan funkcji poza kolejenym elementem w folderze
if(plik!=NULL){
    char* wciecia = (char*)malloc(sizeof(char)*((rekurencja+1)*5));
    strcpy(wciecia,"");
    int a = 0;
        while(a<=rekurencja){
        strcat(wciecia,"    ");
        a++;
        }
    printf("\n%s",wciecia);
    printf("%s",plik->Name);
    free(wciecia);
    //komunikacjaWypiszSlowa(plik->Text);
    komunikacjaWypiszPliki(plik->Next,rekurencja);
}
return;
}
folder* komunikacjaStart(){ //funkcja uruchamiajaca tworzenie folderow. jezeli nie bedzie mozna otworzyc katalogu to funkcja sie zapetla do momentu podania prawidlowego folderu
folder* test = NULL;
char input[256];
printf("%s","\nPodaj sciezke folderu z plikami\n");
scanf("%s",&input);
DIR* directory = opendir(input);
if(directory == NULL){
    printf("%s","\nNieprawidlowy folder!\n");
    return komunikacjaStart();
} else {
test = odczytFolder(input,"");
komunikacjaWypiszfolder(test->Directories,1);
komunikacjaWypiszPliki(test->Files,1);
}
closedir(directory);
return test;
}
int komunikacjaTestCzyPasuje(char* sprawdzany,slowo* slowo){ //sprawdza podany char z slowem i jezeli sa takie same to dodaje 1 do a, rekurencyjnie dodaje do a wynik kolejnych elementow
    int a = 0;
    if(slowo!=NULL){
        a += komunikacjaTestCzyPasuje(sprawdzany,slowo->Next);
        if(stricmp(slowo->World,sprawdzany)==0){
            a++;
        }
    }
    return a;
}
int komunikacjaTestPlikow(char* sprawdzany,plik* plik){ //rekurencyjnie dodaje do a wynik testu swojego textu i kolejnych elementow
    int a = 0;
    if(plik!=NULL){
        a += komunikacjaTestPlikow(sprawdzany,plik->Next);
        a += komunikacjaTestCzyPasuje(sprawdzany,plik->Text);
    }
    return a;
}
int komunikacjaTestFolderow(char* sprawdzany,folder* folder){ //rekurencyjnie dodaje do a wynik testu dla podkatalogow,elementow nastepnych i swoich plikow
    int a = 0;
    if(folder!=NULL){
        a += komunikacjaTestFolderow(sprawdzany,folder->Next);
        a += komunikacjaTestFolderow(sprawdzany,folder->Directories);
        a += komunikacjaTestPlikow(sprawdzany,folder->Files);
    }
    return a;
}
void komunikacjaIloscSlow(folder* folder){ //funkcja glowna ktora wywoluje pierwszy test glownego foldera a na koniec wyswietla wynik
char input[256];
int ilosc = 0;
printf("%s","\nPodaj slowo ktore szukasz\n");
scanf("%s",&input);
ilosc += komunikacjaTestFolderow(input,folder);
printf("%s","\nZnaleziono ");
printf("%d",ilosc);
printf("%s"," wystapien slowa ");
printf("%s",input);
printf("%s"," \n");
}//c:\Users\Edamski\pictures

