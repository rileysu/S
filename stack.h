
// Date: 2017-07-29
// Description: First attempt at a Stack library

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode{
        int data;
        struct StackNode* next;
} stacknode_t;

typedef struct StackRep{
        struct StackNode* head;
        struct StackNode* tail;
        int size;
} stackrep_t;

stackrep_t* SinitStackRep();
stacknode_t* SinitStackNode();

void Spush(stackrep_t* sr, int data);
void SpushAll(stackrep_t* srnew, stackrep_t* srold);
void ScopyAll(stackrep_t* srnew, stackrep_t* srold);
int Speek(stackrep_t* sr);
int Spop(stackrep_t* sr);
void Sclear(stackrep_t* sr);
void Sfree(stackrep_t* sr);
int Scontains(stackrep_t* sr, int data);
int ScontainsCount(stackrep_t* sr, int data);
int ScontainsAll(stackrep_t* srto, stackrep_t* srfrom);
int SisEmpty(stackrep_t* sr);
void Sremove(stackrep_t* sr, stacknode_t* qnpre, stacknode_t* qnrem);
void SremoveIfPresent(stackrep_t* sr, int data);
void SremoveAllIfPresent(stackrep_t* srto, stackrep_t* srfrom);
int Ssize(stackrep_t* sr);

//DIAG
void SprintDiag(stackrep_t* sr);        
