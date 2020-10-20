#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

typedef struct sJogador{
	int pontos;
}Jogador;

Jogador* criaJogador();
int qtdJogadores();
void iniciarJogo(int qtd);
void ajuda();

main(){
	int op=0;
	while(op==0){
        system("clear||cls");
		printf("\n\t*****Bem-vindo ao jogo de boliche*****\n\n\n");
        printf("\t1)Jogar\n");
        printf("\t2)Ajuda\n");
        printf("\t3)Sair\n");
        
        int n;
        scanf("%d",&op);
        switch (op){
            case 1: n= qtdJogadores();
					//iniciarJogo(n);
                    break;
			
			case 2: system("clear||cls");
					ajuda();
                    op=0;
                    system("pause");
					break;
                    
			case 3: break;
               
            default:op=0;
                    break;
        }
    }
	
}

Jogador* criaJogador(){
    Jogador *jogador= (Jogador*)malloc(sizeof(Jogador));
    return jogador;
}

int qtdJogadores(){
	system("clear||cls");
	int i=0;
	
	while(i==0){
        printf("\tSelecione a quantidade de jogadores: (2,3,4)\n");
        scanf("%d",&i);
		
		if(i!=2 || i!=3 || i!=4){
        	i==0;
		}
    }
	
	return i;
}

void iniciarJogo(int qtd){
	
}

void ajuda(){
	printf("Aqui precisa colocar um textinho, explicando como eh o funcionamento do jogo\n\n");
}





