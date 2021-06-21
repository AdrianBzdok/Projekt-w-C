folder* odczytFolder(char* filename,char* name);

void odczytTest(){
printf("Hello world!\n");
}

int czyPlik(const char *path) //funkcja zwraca 0 jezeli napotka folder i 1 jezeli nie udalo jej sie otworzyc folderu
{
DIR* directory = opendir(path);
if(directory != NULL){
    closedir(directory);
    return 0;
}else {
    return 1;
}
}

slowo* odczytPlik(char* filename){ //na poczatku przydzielam odpowiednia ilosc pamieci do kazdego elementu listy
    FILE* plik;
    plik = fopen(filename,"r");
    if(plik==NULL){
        return NULL;
    } else{
    slowo* glowa = (slowo*)malloc(sizeof(slowo));
    glowa->Length = 0;
    glowa->Next = NULL;
    slowo* aktualna = glowa;
    char znak;
    while (!feof(plik)){
        znak = fgetc(plik);
        if(znak==EOF){
            break;
        } else {
            if(znak==' '||znak=='\n'||znak=='\t'||znak==','||znak=='.'){
                aktualna->Next = (slowo*)malloc(sizeof(slowo));
                aktualna = aktualna->Next;
                aktualna->Length = 0;
                aktualna->Next = NULL;
            } else {
                aktualna->Length++;
            }
        }
    }
    fclose(plik); //w tej chwili koncze inicializowac liste i teraz bede do niej zapisywac
    int i = 0;
    aktualna = glowa;
    plik = fopen(filename,"r");
    aktualna->World = (char*)calloc((aktualna->Length+1),sizeof(char));
    while (!feof(plik)){
        znak = fgetc(plik);
        if(znak==EOF){
            break;
        } else {
            if(znak==' '||znak=='\n'||znak=='\t'||znak==','||znak=='.'){
                aktualna = aktualna->Next;
                aktualna->World = (char*)calloc((aktualna->Length+1),sizeof(char));
                i = 0;
            } else {
                aktualna->World[i]=znak;
                i++;
            }
        }
    }
    return glowa;
}
}

folder* dodajFolder(char* fullpath,char* name,folder* folderx){ //funkcja sprawdza rekurencyjnie czy aktualny element listy jest pusty, jezeli tak to wywoluje funkcje zczytania folderu ktory jest nizej i zapisuje go jako element
if(folderx==NULL){
folderx = odczytFolder(fullpath,name);
folderx->Next = NULL;
return folderx;
} else {
folderx->Next = dodajFolder(fullpath,name,folderx->Next);
return folderx;
}
}

plik* dodajPlik(char* fullpath,char* name,plik* plikx){ //funkcja dodaje plik do listy oraz uruchamia funkcje zczytujaca slowa i zapisuje glowe wyniku jako ->Text
if(plikx==NULL){
plikx = (plik*)malloc(sizeof(plik));
plikx->Name = malloc(strlen(name)+1);
plikx->Next = NULL;
strcpy(plikx->Name,name);
//printf("%s",fullpath);
plikx->Text = odczytPlik(fullpath);
//printf("%s",pomoc->Name);
return plikx;
} else {
plikx->Next = dodajPlik(fullpath,name,plikx->Next);
return plikx;
}
}

folder* odczytFolder(char* filename,char* name){ //funkcja otwiera na poczatku folder i sprawdza czy sie to udalo
struct dirent* pDirent;
DIR* pDir;
pDir = opendir(filename);
if(pDir==NULL){
    return NULL;
};
folder* aktualnyFolder = (folder*)malloc(sizeof(folder)); //w tym momencie inicjalizuje nowy obiekt i ustawiam mu parametry
aktualnyFolder->NumberOfDirectories = 0;
aktualnyFolder->NumberOfFiles = 0;
aktualnyFolder->Files = NULL;
aktualnyFolder->Directories = NULL;
aktualnyFolder->Next = NULL;
aktualnyFolder->Name = malloc(strlen(name)+1);
aktualnyFolder->Filename = malloc(strlen(filename)+1);
strcpy(aktualnyFolder->Name,name);
strcpy(aktualnyFolder->Filename,filename);
//printf("%s",aktualnyFolder->Name);
while((pDirent = readdir(pDir)) != NULL){ //odczytuje dane z folderu z wyjatkiem . i .. i odpalam zaleznie od wyniku czyplik() dodajfolder() lub  dodajplik()
    if(strcmp(pDirent->d_name,"..")!=0&&strcmp(pDirent->d_name,".")!=0){
        char* fullpath = malloc(strlen(filename)+strlen(pDirent->d_name)+2);
        strcpy(fullpath,filename);
        strcat(fullpath,"\\");
        strcat(fullpath,pDirent->d_name);
        if(czyPlik(fullpath)==0){
        aktualnyFolder->NumberOfDirectories++;
        aktualnyFolder->Directories = dodajFolder(fullpath,pDirent->d_name,aktualnyFolder->Directories);
        } else {
        aktualnyFolder->NumberOfFiles++;
        aktualnyFolder->Files = dodajPlik(fullpath,pDirent->d_name,aktualnyFolder->Files);
        }
        /*printf("%s ",fullpath);
        printf("%d ",czyPlik(fullpath));
        printf("%s\n",pDirent->d_name);      TEST CZY TO DZIALA*/
        free(fullpath);
    }
}
closedir(pDir);
return aktualnyFolder;
}
