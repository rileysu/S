#include "stack.h"

stackrep_t* SinitStackRep(){
	stackrep_t* sr = malloc(sizeof(stackrep_t));

	sr->head = NULL;
	sr->tail = NULL;
	sr->size = 0;

	return sr;	
}

stacknode_t* SinitStackNode(){
	stacknode_t* sn = malloc(sizeof(stacknode_t));

	sn->data = 0;
	sn->next = NULL;

	return sn;
}

void Spush(stackrep_t* sr, int data){

	if (SisEmpty(sr)){
		sr->head = SinitStackNode();
		sr->tail = sr->head;
	}
	else{
		stacknode_t* curr = SinitStackNode();
		curr->next = sr->head;
		sr->head = curr;
	}

	sr->head->data = data;
	sr->size++;
}

void SpushAll(stackrep_t* srnew, stackrep_t* srold){
        while(!SisEmpty(srold)){
                Spush(srnew,Spop(srold));
        }
}

void ScopyAll(stackrep_t* srnew, stackrep_t* srold){

        stacknode_t* curr = srold->head;

        while(curr != NULL){
                Spush(srnew,curr->data);
                curr = curr->next;
        }
}


int Speek(stackrep_t* sr){

	return sr->head->data;	
}

int Spop(stackrep_t* sr){

	stacknode_t* curr = sr->head;
	int data = curr->data;

	sr->head = sr->head->next;
	free(curr);
	sr->size--;

	if (sr->head == NULL || sr->head->next == NULL){ // Do not like this conditional
		sr->tail = sr->head;
	}

	return data;
}

void Sclear(stackrep_t* sr){
	stacknode_t* curr = sr->head;
	
	for (int i = 0; i < sr->size; i++){
		stacknode_t* temp = sr->head;
		curr = curr->next;
		sr->head = curr;
		free(temp);
	}
	
	sr->head = NULL;
	sr->tail = NULL;
	sr->size = 0;
}

void Sfree(stackrep_t* sr){
	Sclear(sr);
	free(sr);
}

int Scontains(stackrep_t* sr, int data){
	stacknode_t* curr = sr->head;
	int found = 0;

	while (curr != NULL && found != 1){
		if (curr->data == data){
			found = 1;
		}
		else{
			curr = curr->next;
		}
	}

	return found;
}

int ScontainsCount(stackrep_t* sr, int data){
	stacknode_t* curr = sr->head;
	int found = 0;

	for (int i = 0; i < sr->size; i++){
		if (curr->data == data){
			found++;
		}
		curr = curr->next;
	}

	return found;
}

int ScontainsAll(stackrep_t* srto, stackrep_t* srfrom){
        stacknode_t* curr = srfrom->head;
        int found = 1;

        while(curr != NULL && found){
                found = Scontains(srto,curr->data);
                curr = curr->next;
        }

        return found;
}


int SisEmpty(stackrep_t* sr){
	if (sr->head == NULL){
		return 1;
	}
	else{
		return 0;
	}
}

void Sremove(stackrep_t* sr, stacknode_t* snpre, stacknode_t* snrem){

	if (snpre == NULL){
		snpre = snrem;
		snrem = snrem->next;
		free(snpre);
		sr->head = snrem;
		if (sr->head == NULL){
			sr->tail = NULL;
		}
		sr->size--;
	}
	else{
		snpre->next = snrem->next;
		if (sr->tail == snrem){
			sr->tail = snpre;
		}
		free(snrem);
		sr->size--;
	}
}

void SremoveIfPresent(stackrep_t* sr, int data){
	while (sr->head->data == data){
		Sremove(sr,NULL,sr->head);
	}

	stacknode_t* pre = sr->head;

	for (int i = 0; i < sr->size - 1; i++){
		if (pre->next->data == data){
			Sremove(sr,pre,pre->next);
		}
	
		pre = pre->next;		
	}
}

void SremoveAllIfPresent(stackrep_t* srto, stackrep_t* srfrom){
	stacknode_t* curr = srfrom->head;

	for (int i = 0; i < srfrom->size; i++){
		SremoveIfPresent(srto,curr->data);
		curr = curr->next;
	}
}

int Ssize(stackrep_t* sr){
	return sr->size;
}

//DIAG

void SprintDiag(stackrep_t* sr){
	printf("------------------------------\n");
	
	printf("Stack Data:");
	
	stacknode_t* curr = sr->head;

	while (curr != NULL){
		printf(" %d",curr->data);
		curr = curr->next;
	}
	printf("\n");
	if (!SisEmpty(sr)){
		printf("Stack Head: %d\n",sr->head->data);
		printf("Stack Tail: %d\n",sr->tail->data);
		printf("Stack Size: %d\n",sr->size);
	}
	else{
		printf("Queue Empty!\n");
		printf("Queue Size: %d\n",sr->size);
	}

	printf("------------------------------\n");
}
