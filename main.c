#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include<locale.h>
#include <stdbool.h>
#include <math.h>

typedef struct relationList RL;
typedef struct term Term;           //struct's type def
typedef struct Document Doc;
typedef struct MostFrequentWords MFW;

struct term{
    char word[20];
    RL *firstOrderReleations,*secondOrderReleations,*thirdOrderReleations;
    Doc *documents;
    Term *next;
};

struct relationList{
    Term *releatedTerm;
    RL *next;
};

struct Document{
    char name[40];
    int count;
    Doc *next;
};

struct MostFrequentWords{
    char category[40];
    Term* word;
    int count;
    double idfTimesTf;
    MFW *next;
};

struct dirent *d1,*d2;  // Pointer for directory entry
//function's prototype
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
bool checkIfHaveCommonTermInFirstTermsSecondOrderAndSecondTermsFirstORderList(Term *pTerm, Term *pTerm1);
void addToThirdOrderList(Term *pTerm, Term *pTerm1);
void printThirdOrderRl(Term *pTerm);
bool HasTwoTermFirstORderRelations(Term *pTerm, Term *pTerm1);
bool HasTwoTermSecondORderRelations(Term *pTerm, Term *pTerm1);
void printFirstORderOfGivenTerm(Term *pTerm, char* );
void printSecondORderOfGivenTerm(Term *pTerm, char* );
void printThirdORderOfGivenTerm(Term *root, char *term);
void printGivenTermsDetails(Term *root, char *term);
void printFirstOrderTermOcurrence(Term *pTerm);
void printSecondOrderTermOcurrence(Term *pTerm);
void printThirdOrderTermOcurrence(Term *pTerm);
void printMostFrequentWords(MFW*,MFW*,MFW*);
void printMostFrequentWordsByCategory(MFW*);
void createMostFrequentWordsList(Term *root,MFW**,MFW**,MFW**);
void creteMFWListFor(Term *root,MFW**, char *category,int,int);
void addToMFWList(MFW **mfwRoot, char *category, Term *term,int,Term*);
bool isInMfwList(MFW *root, char *word);
int getNumOfDocuments(Term *term, Term *root);
void printMostFrequentWordsWithIdf(MFW *pWords, MFW *pWords1, MFW *pWords2);
void printMostFrequentWordsByCategoryWithIdf(MFW *pWords);
int DocNum=0;


int main() {
    setlocale(LC_ALL, "Turkish");
    Term *root=NULL;
    MFW *mfwRootHealth=NULL;
    MFW *mfwRootMag=NULL;
    MFW *mfwRootEcon=NULL;

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
            DocNum++;
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

     createMostFrequentWordsList(root,&mfwRootMag,&mfwRootHealth,&mfwRootEcon);

     printMostFrequentWords(mfwRootEcon,mfwRootHealth,mfwRootMag);
     printMostFrequentWordsWithIdf(mfwRootEcon,mfwRootHealth,mfwRootMag);
     //printFirstOrderTermOcurrence(root);
     //printSecondOrderTermOcurrence(root);
     //printThirdOrderTermOcurrence(root);
   // printGivenTermsDetails(root,"ve");
    //printFirstORderOfGivenTerm(root,"ve");
    //printSecondORderOfGivenTerm(root,"livaneli");
   // printThirdORderOfGivenTerm(root,"hak");
    //printList(root);
   //printListWithDeteails(root);
   //printFirstOrderRl(root);
  //printSecondOrderRl(root);
  // printThirdOrderRl(root);
    return 0;
}

void printMostFrequentWordsWithIdf(MFW *rootEcon,MFW *rootHealth, MFW *rootMag) {
    printMostFrequentWordsByCategoryWithIdf(rootMag);
    printMostFrequentWordsByCategoryWithIdf(rootEcon);
    printMostFrequentWordsByCategoryWithIdf(rootHealth);
}

void printMostFrequentWordsByCategoryWithIdf(MFW *root) {
    printf("\t--------------------%s-------------------------\n\n",root->category);
    while(root != NULL){
        printf("\t|%s:%f\n",root->word->word,root->idfTimesTf);
        root = root->next;
    }
    printf("\t_________________\n");
}

void printMostFrequentWords(MFW *rootEcon,MFW *rootHealth, MFW *rootMag) {
    printMostFrequentWordsByCategory(rootMag);
    printMostFrequentWordsByCategory(rootEcon);
    printMostFrequentWordsByCategory(rootHealth);

}

void printMostFrequentWordsByCategory(MFW *root) {

    printf("\t--------------------%s-------------------------\n\n",root->category);
    while(root != NULL){
        printf("\t|%s:%d\n",root->word->word,root->count);
        root = root->next;
    }
    printf("\t_________________\n");
}

void createMostFrequentWordsList(Term *root,MFW **mfwRootMag,MFW **mfwRootHealth,MFW **mfwRootEcon) {
    creteMFWListFor(root,mfwRootEcon,"econ",0,10);
    creteMFWListFor(root,mfwRootHealth,"health",0,10);
    creteMFWListFor(root,mfwRootMag,"magazin",0,10);
}

void creteMFWListFor(Term *root,MFW **mfwRoot, char *category,int maxCount,int forTenTerm) {

    int max=maxCount;

    Doc *iterDoc;
    Term *iterTerm=root,*termToAdd=NULL;
    int count=0;
    while(iterTerm != NULL){
        if(isInMfwList(*mfwRoot,iterTerm->word)){
            iterTerm = iterTerm->next;
            continue;
        }
        iterDoc = iterTerm->documents;
        while(iterDoc != NULL){
            if(strstr(iterDoc->name,category) != NULL){

                    count = count + iterDoc->count;



            }
            iterDoc = iterDoc->next;
        }
        if(max <= count){
            max = count;
            termToAdd = iterTerm;
        }
        iterTerm = iterTerm->next;
        count =0;
    }
    if(termToAdd != NULL)
        addToMFWList(mfwRoot,category,termToAdd,max,root);
    if(forTenTerm==1)//checking for 10 term have added
        return;
    creteMFWListFor(root,mfwRoot,category,0,--forTenTerm);//re calling itself
}

bool isInMfwList(MFW *root, char *word) {//simple function that checking is term already mfw list
    while(root != NULL){
        if(strcmp(root->word->word,word) == 0)
            return 1;
        root = root->next;
    }
    return 0;
}

void addToMFWList(MFW **mfwRoot, char *category, Term *term,int count,Term* root) {
    MFW *iter = (*mfwRoot);



   double tempIdf = log(DocNum / getNumOfDocuments(term, root));//creating temp idf

    if((*mfwRoot) == NULL){ //checking for list is empty
        (*mfwRoot) = (MFW*)malloc(sizeof(MFW));
        strcpy((*mfwRoot)->category,category);
        (*mfwRoot)->word=term;
        (*mfwRoot)->count=count;
        (*mfwRoot)->idfTimesTf=count*tempIdf;
        (*mfwRoot)->next = NULL;
    }else{
        while(iter->next != NULL)//adding new node to end of list
            iter = iter->next;
        iter->next = (MFW*)malloc(sizeof(MFW));
        strcpy(iter->next->category,category);
        iter->next->word = term;
        iter->next->count = count;
        iter->idfTimesTf = count*tempIdf;
        iter->next->next = NULL;
    }

}

int getNumOfDocuments(Term *term, Term *root) {//simple function that returns given terms number of document it occured
    Doc *iter = root->documents;
    int counter = 0;
    while(iter != NULL){
        counter++;
        iter = iter->next;
    }
    return counter;
}

void printThirdOrderTermOcurrence(Term *root) {//this function prints all terms with third order
    RL* iter;
    printf("3rd -order term co-occurrence:\n");
    while(root->next!= NULL){
        if(root->thirdOrderReleations==NULL){
            root = root->next;
            continue;
        }
        iter=root->thirdOrderReleations;

        while(iter !=NULL){
            printf("{%s, %s}, ",root->word,iter->releatedTerm->word);
            iter = iter->next;
        }

        root = root->next;
        printf("\n");

    }
    printf("\n");
}

void printSecondOrderTermOcurrence(Term *root) {//this function prints all term with second order
    RL* iter;
    printf("2nd -order term co-occurrence:\n");
    while(root->next!= NULL){
        if(root->secondOrderReleations==NULL){
            root = root->next;
            continue;
        }
        iter=root->secondOrderReleations;

        while(iter !=NULL){
            printf("{%s, %s}, ",root->word,iter->releatedTerm->word);
            iter = iter->next;
        }

        root = root->next;
        printf("\n");
    }

    printf("\n");
}

void printFirstOrderTermOcurrence(Term *root) {//this function prints all terms with first order
    RL* iter;
    printf("1st -order term co-occurrence:\n");
    while(root->next!= NULL){
        if(root->firstOrderReleations==NULL){
            root = root->next;
            continue;
        }
        iter=root->firstOrderReleations;

        while(iter !=NULL){
            printf("{%s, %s}, ",root->word,iter->releatedTerm->word);
            iter = iter->next;
        }

        root = root->next;
        printf("\n");
    }

    printf("\n");
}

void printGivenTermsDetails(Term *root, char *term) {//this function prints all the details of given term
    Doc *iter;
    while(root != NULL){

        if(strcmp(root->word,term)==0){
            iter=root->documents;
            printf("WORD: %s\n",root->word);
            printFirstORderOfGivenTerm(root,term);
            printSecondORderOfGivenTerm(root,term);
            printThirdORderOfGivenTerm(root,term);
            while(iter != NULL){
                printf("Document Name: %s|\tCount: %d\n", iter->name, iter->count);
                iter=iter->next;

            }
            printf("----------------------------------\n");
        }

        root=root->next;
    }
}

void printThirdORderOfGivenTerm(Term *root, char *term) {//this function prints given terms third order list
    RL* iter;
    while(root != NULL){
        if(strcmp(root->word,term)==0){
            printf("\nWORD: %s\nThird Order List: ",root->word);
            iter=root->thirdOrderReleations;
            while(iter != NULL){
                printf("%s:",iter->releatedTerm->word);
                iter = iter->next;
            }
        }
        root = root->next;
    }
}

void printSecondORderOfGivenTerm(Term *root, char* term) {//this function prints given terms second order list
    RL* iter;
    while(root != NULL){
        if(strcmp(root->word,term)==0){
            printf("\nWORD: %s\nSecond Order List: ",root->word);
            iter=root->secondOrderReleations;
            while(iter != NULL){
                printf("%s:",iter->releatedTerm->word);
                iter = iter->next;
            }
        }
        root = root->next;
    }
}

void printFirstORderOfGivenTerm(Term *root, char *term) {//this function prints given terms first order list
   RL* iter;
    while(root != NULL){
        if(strcmp(root->word,term)==0){
         printf("\nWORD: %s\nFirst Order List: ",root->word);
         iter=root->firstOrderReleations;
         while(iter != NULL){
             printf("%s:",iter->releatedTerm->word);
             iter = iter->next;
         }
        }
        root = root->next;
    }


}

void printThirdOrderRl(Term *root) {//this function prints all term's third order list
    RL* iter;
    while(root != NULL){

        if(root->thirdOrderReleations==NULL){
            root = root->next;
            continue;
        }
        printf("\nWORD: %s\nThird Order List: ",root->word);

        iter=root->thirdOrderReleations;
        while(iter != NULL){
            printf("%s--",iter->releatedTerm->word);
            iter = iter->next;
        }

        root = root->next;
    }
}

void printSecondOrderRl(Term *root) {//this function prints all term's second order list
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

void printFirstOrderRl(Term *root) {//this function prints all term's first order list
    RL* iter;
    while(root != NULL){
        if(root->firstOrderReleations==NULL){
            root = root->next;
            continue;
        }

        printf("\nWORD: %s\nFirst Order List: ",root->word);

        iter=root->firstOrderReleations;
        while(iter != NULL){
            printf("%s--",iter->releatedTerm->word);
            iter = iter->next;
        }

        root = root->next;
    }

}

void printList(Term* root){//this function prints all terms in MLL
    int c = 1;
    printf("%s\n",root->word);
    while(root->next!=NULL){
        root=root->next;
        printf(":%s\n",root->word);
    }
}

void printListWithDeteails(Term* root){//This function prints all the words in MLL with their document info
    Doc *iter;
    while(root != NULL){
        iter=root->documents;

        printf("WORD: %s\n",root->word);

        while(iter != NULL){
            printf("Document Name: %s|\tCount: %d\n", iter->name, iter->count);
            iter=iter->next;

        }
        root=root->next;
        printf("----------------------------------\n");

    }
}

void startReading(Term** root,char *path){ //this function begins reading files
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
    if(strcmp(name,"") == 0)
        return;
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
    while(root != NULL) {
        if (strcmp(root->word, name) == 0)
            return 1;
        root = root->next;
    }
    return 0;
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
    if(term1->firstOrderReleations == NULL){//creating linked list
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
    Term * iter2=root;


    while(iter !=NULL){
        while(iter2!=NULL) {
            if((strcmp(iter->word,"1")== 0))
                if((strcmp(iter2->word,"5")== 0))
                    printf("sss");
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
        iter2=root;
    }

}

bool checkIsTwoHasFirstOrderReleationsEachOther(Term *term1, Term *term2) {
    RL* iter=term1->firstOrderReleations;
    while(iter != NULL){
        if(strcmp(iter->releatedTerm->word,term2->word) == 0)
            return 1;
        iter = iter->next;
    }
    return 0;
}

bool checkIfHaveCommonTermInFirstOrderList(Term *term1, Term *term2) {

    RL *iter1 = term1->firstOrderReleations,*iter2=term2->firstOrderReleations;

    if(strcmp(term1->word,term2->word) == 0)
        return 0;
    while(iter1 != NULL) {
        while (iter2 != NULL) {
            if(strcmp(iter1->releatedTerm->word,iter2->releatedTerm->word) == 0){
                //printf("\n1:%s \n -4:%s",iter1->releatedTerm->word,iter2->releatedTerm->word);
                return 1;
            }

            iter2 = iter2->next;
        }
        iter2 = term2->firstOrderReleations;
        iter1 = iter1->next;
    }
    return 0;
}

void addToSecondOrderList(Term *term1, Term *term2) {//simple linked list addition function
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

void createThirdOrderReleations(Term* root){//while creating third order relation if second term's first order list and first term's first order list have common term and vice versa
                                            // and if this two terms are dont have second or first order relation then they have third order relation
    Term *iter=root;
    Term * iter2=root;


    while(iter !=NULL){
        while(iter2!=NULL) {
            if( HasTwoTermSecondORderRelations(iter,iter2)){//checking id they have second order relation
                iter2 = iter2->next;
                continue;
            }
            if(HasTwoTermFirstORderRelations(iter,iter2) ){//checking id they have second order relation
                iter2 = iter2->next;
                continue;
            }

            if(checkIfHaveCommonTermInFirstTermsSecondOrderAndSecondTermsFirstORderList(iter,iter2)){//checking if they common word
                addToThirdOrderList(iter,iter2);
            }
            iter2 = iter2->next;
        }
        iter2=root;
        iter=iter->next;

    }
}

bool HasTwoTermSecondORderRelations(Term *term1, Term *term2) {//simple function that checks whether given 2 term has second order relation
    RL *iter = term1->secondOrderReleations;
    while(iter != NULL){
        if(strcmp(iter->releatedTerm->word,term2->word) == 0)
            return 1;
        iter = iter->next;
    }
    return 0;
}

bool HasTwoTermFirstORderRelations(Term *term1, Term *term2) {//simple function that checks whether given 2 term has first order relation
    RL *iter = term1->firstOrderReleations;
    while(iter != NULL){
        if(strcmp(iter->releatedTerm->word,term2->word) == 0)
            return 1;
        iter = iter->next;
    }
    return 0;
}

void addToThirdOrderList(Term *term1, Term *term2) {//linked list addition for third order
    RL *iter;
    if(term1->thirdOrderReleations == NULL){
        term1->thirdOrderReleations = malloc(sizeof(RL));
        term1->thirdOrderReleations->releatedTerm=term2;
        term1->thirdOrderReleations->next=NULL;
    }else{
        iter = term1->thirdOrderReleations;

        while(iter->next != NULL)
            iter = iter->next;

        iter->next = malloc(sizeof(RL));
        iter->next->releatedTerm=term2;
        iter->next->next=NULL;
    }
}

bool checkIfHaveCommonTermInFirstTermsSecondOrderAndSecondTermsFirstORderList(Term *term1, Term *term2) {//checking if term1's second order list and term2's first order list have common term
    RL *iter1=term1->secondOrderReleations,*iter2=term2->firstOrderReleations;

    while(iter1 != NULL){
        while(iter2 != NULL){
            if(strcmp(iter1->releatedTerm->word,iter2->releatedTerm->word) == 0)
                return 1;
            iter2 = iter2->next;
        }
        iter2 = term2->firstOrderReleations;
        iter1 = iter1->next;

    }
    return 0;
}

bool checkIfHaveCommonDocument(Term *term1, Term *term2) {//In this method checking two words documents lists,there is 3 possibilities
    // they both have only 1 document, one of them has 1 document other one more than one document , both of them has more than 1 document

    Doc *term1Doc = term1->documents, *term2Doc = term2->documents;
    while(term1Doc != NULL){
        while(term2Doc != NULL){
            if(strcmp(term1Doc->name,term2Doc->name) == 0)
                return 1;
            term2Doc = term2Doc->next;

        }
        term1Doc = term1Doc->next;
    }
    return 0;

}
