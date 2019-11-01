#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include<locale.h>
#include <stdbool.h>

typedef struct releationList RL;
typedef struct term Term;
typedef struct Document Doc;

struct term{
    char word[20];
    RL *firstOrderReleations,*secondOrderReleations,*thirdOrderReleations;
    Doc *documents;
    Term *next;
};

struct releationList{
    Term *releatedTerm;
    RL *next;
};

struct Document{
    char name[40];
    int count;
    Doc *next;
};

struct dirent *d1,*d2;  // Pointer for directory entry
void printList(Term*);
void addToMasterLinkedList(char*,Term**,char*);
void startReading(Term**,char*);
int checkIsAlreadyInList(char*,Term*);
void increaseDocumentCount(Term*,char*,char*);
void printListWithDeteails(Term*);
void createRelations(Term*);
void createFirstOrderReleations(Term*);
void createSecondOrderReleations(Term*);
void createThirdOrderReleations(Term*);

bool checkIfHaveCommonDocument(Term*,Term*);

void addToFirstOrderList(Term*, Term*);

void printFirstOrderRl(Term *pTerm);

bool checkIfHaveCommonTermInFirstOrderList(Term *pTerm, Term *pTerm1);

void addToSecondOrderList(Term *pTerm, Term *pTerm1);

bool checkIsTwoHasFirstOrderReleationsEachOther(Term *term1, Term *term2);

void printSecondOrderRl(Term *pTerm);

int main() {
    Term *root=NULL;
    setlocale(LC_ALL, "Turkish");
    char path[20]={"dataset/"};
    // opendir() returns a pointer of DIR type.
    DIR *datasets = opendir("dataset");

    DIR *folders;

    if (datasets == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }


    while ((d1 = readdir(datasets)) != NULL){
        if (!strcmp (d1->d_name, "."))
            continue;                   //checking for undesired input
        if (!strcmp (d1->d_name, ".."))
            continue;

        folders = opendir(strcat(path,d1->d_name));//opening directorys with order inside dataset folder

        while ((d2 = readdir(folders)) != NULL){
            if (!strcmp (d2->d_name, "."))
                continue;                   //checking for undesired input
            if (!strcmp (d2->d_name, ".."))
                continue;

            strcat(path,"/");
            strcat(path,d2->d_name);//setting input path

            startReading(&root,path);//reading files

            memset(path,0,sizeof(path));
            strcat(path,"dataset/");//resetting path
            strcat(path,d1->d_name);
        }

        memset(path,0,sizeof(path));
        strcat(path,"dataset/");//resetting path

        closedir(folders);
    }

    closedir(datasets);
    createRelations(root);
   // printListWithDeteails(root);
    printFirstOrderRl(root);
    printSecondOrderRl(root);
    return 0;
}

void printSecondOrderRl(Term *root) {
    RL* iter;
    while(root != NULL){
        if(root->secondOrderReleations==NULL){
            root = root->next;
            continue;
        }

        printf("\nWORD: %s\nSecond Order List: ",root->word);

        iter=root->secondOrderReleations;
        while(iter != NULL){
            printf("%s--",iter->releatedTerm->word);
            iter = iter->next;
        }

        root = root->next;
    }
}

void printFirstOrderRl(Term *root) {
    RL* iter;
    while(root->next!= NULL){
        if(root->firstOrderReleations==NULL){
            root = root->next;
            continue;
        }

        printf("\nWORD: %s\nFirst Order List: ",root->word);

        iter=root->firstOrderReleations;
        while(iter->next!=NULL){
            printf("%s:",iter->releatedTerm->word);
            iter = iter->next;
        }
        printf("%s:",iter->releatedTerm->word);
        root = root->next;
    }

}

void startReading(Term** root,char *path){
    FILE *fp;
    char buffer[255];
    int c =1;
    fp = fopen(path,"r");
    printf("PATH:%s\n",path);
    while(fscanf(fp, "%s", buffer) != EOF)
        addToMasterLinkedList(buffer,root,path);
    fclose(fp);
}

void addToMasterLinkedList(char* name,Term** root,char* docname) {    //MLL= Master Linked List

    Doc* tempDocument= (Doc *)malloc(sizeof(Doc));
    strcpy(tempDocument->name,docname);//Creating temp document.
    tempDocument->count=1;
    tempDocument->next=NULL;
    if (*root == NULL) {//Checking is MLL empty
        (*root) = (Term *) malloc(sizeof(Term));//If MLL empty initilazing root
        strcpy(((*root)->word), name);
        (*root)->documents=tempDocument;
        (*root)->firstOrderReleations=NULL;
        (*root)->secondOrderReleations=NULL;
        (*root)->thirdOrderReleations=NULL;
        (*root)->documents->next=NULL;
        (*root)->next = NULL;
    }else{
        if (!checkIsAlreadyInList(name, *root)) {//Checking if term already in MLL
            Term *iter, *temp2;
            iter = (*root);
            while (iter->next != NULL)//Finding end of list to add new node
                iter = iter->next;
            temp2 = (Term *) malloc(sizeof(Term));//Creating node
            temp2->firstOrderReleations=NULL;
            temp2->secondOrderReleations=NULL;
            temp2->thirdOrderReleations=NULL;
            strcpy((temp2->word), name);
            temp2->documents=tempDocument;
            temp2->next = NULL;
            iter->next = temp2;//Setting last elements next to null
        } else {
            increaseDocumentCount(*root,name,docname);
        }
    }
}

void increaseDocumentCount(Term *root, char *name, char *docname) {
    Doc *iterDoc;
    while(strcmp((root->word),name) !=0)//finding word in Master Linked List
        root=root->next;
    iterDoc = root->documents;
    while(iterDoc->next != NULL && strcmp(iterDoc->name,docname)!=0)//now searching document linked list of word to find corresponding document
        iterDoc=iterDoc->next;

    if(strcmp(iterDoc->name,docname)==0) {
        iterDoc->count=(iterDoc->count)+1;//increasing document count
    }else{
        iterDoc->next = (Doc *) malloc(sizeof(Doc));
        iterDoc->next->count=1;
        strcpy(iterDoc->next->name,docname);//Adding new Document Node to words Document List
        iterDoc->next->next=NULL;
    }

}

int checkIsAlreadyInList(char* name,Term* root){
    if(strcmp(root->word,name)==0)//checking if there is only 1 element in list
        return 1;
    while(root->next!= NULL) {
        if (strcmp(root->word, name) == 0)
            return 1;
        root = root->next;
    }
    return 0;
}

void printList(Term* root){
    int c = 1;
    printf("%d:%s\n",++c,root->word);
    while(root->next!=NULL){
        root=root->next;
        printf("%d:%s\n",++c,root->word);
    }
}

void printListWithDeteails(Term* root){
    Doc *iter;
    while(root->next!=NULL){
        iter=root->documents;

        printf("WORD: %s\n",root->word);
        if(iter->next==NULL)
            printf("Document Name: %s|\tCount: %d\n", iter->name, iter->count);
        while(iter->next != NULL){
            printf("Document Name: %s|\tCount: %d\n", iter->name, iter->count);
            iter=iter->next;

        }
        root=root->next;
        printf("----------------------------------\n");

    }
}

void createRelations(Term *root){
   createFirstOrderReleations(root);
   createSecondOrderReleations(root);
   createThirdOrderReleations(root);
}

void createFirstOrderReleations(Term* root){//While creating first order list the idea is checking if 2 term has occures in same document
    Term *iter=root;
    Term * iter2=root;


    while(iter !=NULL){
        while(iter2 !=NULL){
            if(checkIfHaveCommonDocument(iter,iter2)){
                addToFirstOrderList(iter,iter2);
            }
            iter2 = iter2->next;
        }

        iter=iter->next;
        iter2=root;
    }
}

void addToFirstOrderList(Term *term1, Term *term2) {
    RL *iter;
    if(term1->firstOrderReleations == NULL){
        term1->firstOrderReleations = malloc(sizeof(RL));
        term1->firstOrderReleations->releatedTerm=term2;
        term1->firstOrderReleations->next=NULL;
    }else{
        iter = term1->firstOrderReleations;

        while(iter->next != NULL)
            iter = iter->next;

        iter->next = malloc(sizeof(RL));
        iter->next->releatedTerm=term2;
        iter->next->next=NULL;
    }


}


void createSecondOrderReleations(Term* root){//While creating second order list the idea is checking they have common term in their first order lists
                                            // but they are not first order with eachother

    Term *iter=root;
    Term * iter2=root->next;


    while(iter !=NULL){
        while(iter2!=NULL) {
            if (checkIsTwoHasFirstOrderReleationsEachOther(iter, iter2)){
                iter2 = iter2->next;
                continue;
            }
            if(checkIfHaveCommonTermInFirstOrderList(iter,iter2)){
                addToSecondOrderList(iter,iter2);
            }
            iter2 = iter2->next;
        }

        iter=iter->next;
        iter2=root->next;
    }

}

bool checkIsTwoHasFirstOrderReleationsEachOther(Term *term1, Term *term2) {
    RL* iter=term1->firstOrderReleations;
    while(iter->next != NULL){
        if(strcmp(iter->releatedTerm->word,term2->word) == 0)
            return 1;
        iter = iter->next;
    }
    if(strcmp(iter->releatedTerm->word,term2->word) == 0)
        return 1;
    else
        return 0;
}

bool checkIfHaveCommonTermInFirstOrderList(Term *term1, Term *term2) {

    RL *iter1 = term1->firstOrderReleations,*iter2=term2->firstOrderReleations;

    if(strcmp(term1->word,term2->word) == 0)
        return 0;
    while(iter1 != NULL) {
        while (iter2 != NULL) {
            if(strcmp(iter1->releatedTerm->word,iter2->releatedTerm->word) == 0)
                return 1;
            iter2 = iter2->next;
        }
        iter1 = iter1->next;
    }
    return 0;
}

void addToSecondOrderList(Term *term1, Term *term2) {
    RL *iter;
    if(term1->secondOrderReleations == NULL){
        term1->secondOrderReleations = malloc(sizeof(RL));
        term1->secondOrderReleations->releatedTerm=term2;
        term1->secondOrderReleations->next=NULL;
    }else{
        iter = term1->secondOrderReleations;

        while(iter->next != NULL)
            iter = iter->next;

        iter->next = malloc(sizeof(RL));
        iter->next->releatedTerm=term2;
        iter->next->next=NULL;
    }
}



void createThirdOrderReleations(Term* root){

}

bool checkIfHaveCommonDocument(Term *term1, Term *term2) {//In this method checking two rods documents lists,there is 3 possibilities
    // they both have only 1 document, one of them has 1 document other one more than one document , both of them has more than 1 document

    Doc *term1Doc = term1->documents, *term2Doc = term2->documents;
    if(strcmp(term1->word,term2->word)==0)
        return 0;
    if (term1Doc->next == NULL) {
        if (term2Doc->next == NULL) {
            return strcmp(term1Doc->name, term2Doc->name) == 0 ? 1 : 0;//Here both have only 1 document
        } else {//here term1 has 1 document term2 has more than 1 document
            while (term2Doc->next != NULL) {
                if (strcmp(term1Doc->name, term2Doc->name) == 0)
                    return 1;
                term2Doc = term2Doc->next;
            }
            if (strcmp(term1Doc->name, term2Doc->name) == 0)
                return 1;
            else
                return 0;
        }
    } else {
        if (term2Doc->next == NULL) {//here term1 has more than 1 document term 2 has 1 document
            while (term1Doc->next != NULL) {
                if (strcmp(term1Doc->name, term2Doc->name) == 0)
                    return 1;
                term1Doc = term1Doc->next;
            }
            if (strcmp(term1Doc->name, term2Doc->name) == 0)
                return 1;
            else
                return 0;
        } else {//here term1 and term2 have more than 1 document
            while (term1Doc->next != NULL) {
                while (term2Doc->next != NULL) {
                    if (strcmp(term1Doc->name, term2Doc->name) == 0)
                        return 1;
                    term2Doc = term2Doc->next;
                }
                if (strcmp(term1Doc->name, term2Doc->name) == 0)
                    return 1;
                term1Doc = term1Doc->next;
            }
            if (strcmp(term1Doc->name, term2Doc->name) == 0)
                return 1;
            else
                return 0;
        }

    }
}

