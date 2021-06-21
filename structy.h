typedef struct slowo {
    int Length;
    char* World;
    struct slowo* Next;
} slowo;

typedef struct plik {
    char* Name;
    struct slowo* Text;
    struct plik* Next;
} plik;

typedef struct folder {
    char* Name;
    char* Filename;
    int NumberOfFiles;
    struct plik* Files;
    int NumberOfDirectories;
    struct folder* Directories;
    struct folder* Next;
} folder;
