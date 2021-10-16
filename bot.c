#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct cList{
	char *concept;
	char *conceptLower;
	char *sentence;
	char *sentenceLower;
	int timesUsed;
	char learnedFrom[5];
	struct cList* next;
}conceptList;
///// SOSOSOSOSOSOSOSOSOSOSOSOSOS
char *gnosto[5] = {"3B$ gnosto 1 %s\n", "3B$ gnosto 2 %s\n", "3B$ gnosto 5 %s\n",
					"3B$ gnosto 3 %s\n", "3B$ gnosto 4 %s\n"};
char *agnosto[5] = {"3B$ agnosto 1 %s\n", "3B$ agnosto 2 %s\n", "3B$ agnosto 5 %s\n",
					"3B$ agnosto 3 %s\n", "3B$ agnosto 4 %s\n"};
char *dialogos[5] = {"3B$ Hmm sounds like a topic!\n", 
			"3B$ I've never had a clear opinion on this!\n",
			"3B$ It sounds complicated as you put it...\n",
			"3B$ Well Ok that depends on the way you look it!\n",
			"3B$ Would you like to analyze it for me?\n"};
char *agnosti_apantisi[5] = {"3B$ I don't know what you ask, but I can tell you 1+1=2\n",
			"3B$ You think it is polite to ask me all this?\n",
			"3B$ AI needs to progress to answer you that\n",
			"3B$ not even Bill Gates can answer that!\n",
			"3B$ you can file a complaint for not asnwering that!\n"};
char * denEsvise[5] = {"3B$ 1 I never knew about %s\n",
				"3B$ 2 I never knew about %s\n",
				"3B$ 3 I never knew about %s\n",
				"3B$ 4 I never knew about %s\n",
				"3B$ 5 I never knew about %s\n"};
char *esvise[5] = {"3B$ 1 I used to know %s, but not anymore!\n",
				"3B$ 2 I used to know %s, but not anymore!\n",
				"3B$ 3 I used to know %s, but not anymore!\n",
				"3B$ 4 I used to know %s, but not anymore!\n",
				"3B$ 5 I used to know %s, but not anymore!\n"};
				
	
// 2, 7, 4, 5
void make_lower(char* str){
	int len, i;
	
	len = strlen(str);
	
	for (i = 0 ; i < len ; i++){
		str[i] = tolower(str[i]);
	}
}
conceptList* createNew(char* concept, char* sentence, char learnedFrom[5]){
	conceptList* new_node = (conceptList*)malloc(sizeof(conceptList));
	if (new_node == NULL){
		printf("3B$ My memory is arrested!\n");
		exit(1);	
	}
	
	new_node->concept = strdup(concept);	
	new_node->conceptLower = strdup(concept);
	make_lower(new_node->conceptLower);
	
	new_node->sentence = strdup(sentence);	
	new_node->sentenceLower = strdup(sentence);
	make_lower(new_node->sentenceLower);
	
	new_node->timesUsed = 0;
	strcpy(new_node->learnedFrom, learnedFrom);
	new_node->next = new_node;
	
	return new_node;
}
conceptList* insert(conceptList* list, char* concept, char* sentence, char learnedFrom[5]){
	conceptList* new_node = createNew(concept, sentence, learnedFrom);
	conceptList* last_node;
	
	if (list == NULL) return new_node;
	
	last_node = list;
	
	while (last_node->next != list) last_node = last_node->next;
	
	last_node->next = new_node;
	new_node->next = list;
	
	return list;
}
int exists(conceptList* list, char* concept){
	conceptList* node;
	
	if (list == NULL) return 0;
	
	node = list;
	
	while (strcmp(node->concept, concept) != 0 && node->next != list) node = node->next;
	
	if (strcmp(node->concept, concept) != 0) return 0;
	
	return 1;
}
void deleteList(conceptList* list){
	conceptList * d, *last_node;
	
	if (list == NULL) return;
	if (list->next == list) {
		free(list);
		return ;
	}
	
	last_node = list;
	
	while (last_node->next != list) last_node = last_node->next;
	
	do{
		d = list;
		list = list->next;
		free(d);
	}while (list != last_node);
	
	free(list);
}

conceptList* question(conceptList* list, char* concept, conceptList* pointer){
	conceptList* check;
	if (list == NULL) return NULL;
	if (pointer == NULL) pointer = list;
	
	check = pointer;
	
	make_lower(concept);
	//printf("%s\n", concept);
	
	while(strstr(pointer->conceptLower, concept) == NULL && pointer->next != check){
		pointer = pointer->next;
	}
	
	if (strstr(pointer->conceptLower, concept) != NULL) return pointer;
	
	while(strstr(pointer->sentenceLower, concept) == NULL && pointer->next != check){
		pointer = pointer->next;
	}
	
	if (strstr(pointer->sentenceLower, concept) != NULL) return pointer;
	
	return NULL;
}
conceptList* remove_node(conceptList*list, char *concept, FILE *fout){
	int rnd;
	conceptList* node = list;
	conceptList* prevNode;
	char *s;
	
	if (list == NULL){
		rnd = rand() % 5;
		printf(denEsvise[rnd], concept);
		fprintf(fout, denEsvise[rnd], concept);	
		return NULL;
	}
	
	while(concept[0] == ' ') concept++;
	
	make_lower(concept);	
	printf("%s\n", concept);
	
	if (list->next == list){ // 1 komvos sti lista mono
		if (strstr(list->conceptLower, concept) != 0){
			concept = strdup(list->concept);
			free(list);
			rnd = rand() % 5;
			printf(esvise[rnd], concept);
			fprintf(fout, esvise[rnd], concept);	
			return NULL;
		}
		else {
			rnd = rand() % 5;
			printf(denEsvise[rnd], concept);
			fprintf(fout, denEsvise[rnd], concept);	
			return list;
		}
	}
	
	while (strstr(node->conceptLower, concept) == NULL && node->next != list) node = node->next;
	//printf("1 %s %s \n", concept, node->conceptLower);
	if (strstr(node->conceptLower, concept) == NULL){
		rnd = rand() % 5;
		printf(denEsvise[rnd], concept);
		fprintf(fout, denEsvise[rnd], concept);	
		return list;
	}
	// diagrafi komvou
	prevNode = list;
	s = strdup(node->concept);
	
	
	while (prevNode->next != node) prevNode = prevNode->next;
	
	prevNode->next = node->next;
	if (list == node) list = prevNode->next;
	
	rnd = rand() % 5;
	printf(esvise[rnd], s);
	fprintf(fout, esvise[rnd], s);
	free(node);
	
	return list;
}

int main(){
	FILE *fout = NULL;
	conceptList* list = NULL;
	conceptList* l = NULL;
	conceptList* pointer = NULL;
	char eisodos[800];
	char *token;
	char *sentence;
	char *concept;
	int rnd;
	
	srand(time(NULL));
	
	fout = fopen("dialogue.txt", "w");
	if (fout == NULL){
		printf("3B$ I can't open file dialogue.txt!\n");
		return 1;
	}
	do{
		printf("me$ ");
		fprintf(fout, "me$ ");
		gets(eisodos);
		fprintf(fout, "%s\n", eisodos);
		
		if (strncmp(eisodos, "learn this > ", strlen("learn this > ")) == 0){
			token = strtok(eisodos, ">");
			concept = strtok(NULL, ":");
			sentence = strtok(NULL, "\0");
			
			if (list == NULL || exists(list, concept) == 0){
				list = insert(list, concept, sentence, "kbrd");
				rnd = rand() % 5;
				printf(agnosto[rnd], concept);
				fprintf(fout, agnosto[rnd], concept);
			}
			else {
				rnd = rand() % 5;
				printf(gnosto[rnd], concept);
				fprintf(fout, gnosto[rnd], concept);			
			}
		}
		else if (strncmp(eisodos, "forget this > ", strlen("forget this > ")) == 0){
			token = strtok(eisodos, ">");
			concept = strtok(NULL, ",");
			
			while (concept != NULL){
				list = remove_node(list, concept, fout);
				concept = strtok(NULL, ",");
			}
		}
		else if (strchr(eisodos, '*') != NULL && strchr(eisodos, '?') != NULL){
			token = strtok(eisodos, "*");
			concept = strtok(NULL, "*");

			pointer = question(list, concept, pointer);
			if (pointer == NULL){
				printf(agnosti_apantisi[rnd], concept);
				fprintf(fout, agnosti_apantisi[rnd], concept);
			}
			else {
				pointer->timesUsed++;
				printf("3B$ %s\n", pointer->sentence);
				fprintf(fout, "3B$ %s\n", pointer->sentence);
			}
		}
		else if (strcmp(eisodos, "exit") != 0){
			rnd = rand() % 5;
			printf(dialogos[rnd], concept);
			fprintf(fout, dialogos[rnd], concept);	
		}
		/*
		if (list != NULL){
			l = list;
			do{
				printf("%s\n", l->concept);
				l = l->next;
			} while (l!= list);
		}
		*/
	}while (strcmp(eisodos, "exit") != 0);

	fclose(fout);
	
	deleteList(list);
	return 0;
}