#include <stdio.h>
#include "tetris.h"
#include <stdlib.h>

int boxexist = 0;
int box_exist(){
	if (boxexist)
		return 1;
	else
	{
		printf("devi prima generare una scatola \n");
		return 0;
	}
}

int main( void ) {
	int flag = 1;
	rbtree *box;
	int param[3];
	char* cmd = (char*) malloc(sizeof(char));
	printf("*************************************\n");
	printf("Laboratiorio di Algoritmi\n");
	printf("Progetto Giugno 2009 Tetris\n");
	printf("*************************************\n");
	printf("Digitare il carattere dell'operazione da svolgere secondo il seguente menu:\n");
// fatta
	printf("s (m) scatola di dimensione m \n");  	
// fatta
	printf("i (x) inserisce rettangolo in posizione x\n"); 
// manca
	printf("e (x) elimina il più alto rettangolo in posizione x\n");
// fatta
	printf("c (x)  calcola sottocatasta elemento in posizione x più alto\n");
// fatta
	printf("a (x)  calcola anticatasta elemento in posizione x più alto\n");
// manca
	printf("p estrae i pezzi liberi \n");
// fatta
	printf("t (n,m,k) esegue la statistica \n");
	printf("!!! ATTENZIONE : dalla specifiche la statistica si invoca con il comando 't' e più 's' \n");
// fatta
	printf("v visualizza\n");
// fatta
	printf("f Esci\n");
	while(flag){
		printf(">");
		scanf("%s", cmd);
		switch (cmd[0]){
			case 's':
				scanf("%d", param);
				box = scatola(param[0]);
				if(box == NULL)
					printf("errore \n");
				else
					boxexist = 1;
				break;
		    case 'i':
				if(!box_exist()) break;
					scanf("%d", param);
					if(inserisci(box,param[0]) == -1)
						printf("errore \n");
				break;
			case 'v':
			if(!box_exist()) break;
				visualizza(box);
				printf("\n");
			break;
			
			case 'c':
				if(!box_exist()) break;
				scanf("%d", param);
				if(sottocatasta(box,param[0]) == NULL)
					printf("vuoto \n");
				break;
			
			case 'a':
				if(!box_exist()) break;
				scanf("%d", param);
				if(anticatasta(box,param[0]) == NULL)
				printf("vuoto \n");
			break;
				break;
			
			case 't':
				scanf("%d", param);
				scanf("%d", param +1);
				scanf("%d", param +2);
				statistica(param[0], param[1],param[2]);
				break;
			case 'f':
				flag = 0;
				break;
				
		}
	}
}
