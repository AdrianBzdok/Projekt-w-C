void kopiaWykonanie(char* wejscie,char* wyjscie){
FILE* plikwej;
FILE* plikwyj;
plikwej = fopen(wejscie,"rb");
if(plikwej==NULL){
    return;
}
plikwyj = fopen(wyjscie,"wb");
if(plikwyj==NULL){
    fclose(plikwej);
    return;
}
int a;
while(!feof(plikwej)){
    a = fgetc(plikwej);
    fputc(a,plikwyj);
}
fclose(plikwej);
fclose(plikwyj);
return;
}
void kopiaPlik(plik* plik,char* wejscie,char* wyjscie){
    char* wejsciefull = malloc(strlen(plik->Name)+strlen(wejscie)+(sizeof(char)*2));
    char* wyjsciefull = malloc(strlen(plik->Name)+strlen(wyjscie)+(sizeof(char)*2));
    strcpy(wejsciefull,wejscie);
    strcpy(wyjsciefull,wyjscie);
    strcat(wyjsciefull,"\\");
    strcat(wejsciefull,plik->Name);
    strcat(wyjsciefull,plik->Name);
    kopiaWykonanie(wejsciefull,wyjsciefull);
    printf("\nskopiowano: %s",wejsciefull);
    printf("\ndo: %s",wyjsciefull);
    free(wejsciefull);
    free(wyjsciefull);
    if(plik->Next!=NULL){
        kopiaPlik(plik->Next,wejscie,wyjscie);
    }
    return;
}
void kopiaFolder(folder* folder,char* wyjscie){
if(folder->Files!=NULL){
//    printf("%s",folder->Filename);
//    printf("%s","\\");
//    printf("%s",folder->Files->Name);
char* fullname = malloc(strlen(folder->Filename)+(sizeof(char)*2));
strcpy(fullname,folder->Filename);
strcat(fullname,"\\");
kopiaPlik(folder->Files,fullname,wyjscie);
free(fullname);
}
if(folder->Next!=NULL){
kopiaFolder(folder->Next,wyjscie);
}
if(folder->Directories!=NULL){
kopiaFolder(folder->Directories,wyjscie);
}
return;
}
void kopiaStart(folder* folder){
char input[256];
printf("%s","\nPodaj sciezke folderu gdzie pliki maja byc wklejone\n");
scanf("%s",&input);
DIR* directory = opendir(input);
if(directory == NULL){
    printf("%s","\nNieprawidlowy folder!\n");
    return;
} else {
    kopiaFolder(folder,input);
    return;
}
}
