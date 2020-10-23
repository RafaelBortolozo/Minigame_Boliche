
// Alunos: Bruno Henrique Potrikus & Rafael Bortolozo
//
// OBS: A linguagem C++ nao foi muito eficiente na programacao do jogo, principalmente na questao da pontuacao, pois ela funciona de uma forma complexa
//      e exige que as pontuacoes dos rounds passados sejam atualizados em caso de Strike e Spare. Para resolver esse problema, teria que usar uma linguagem
//      que permite atualizar automaticamente as pontuacoes da tabela, ou estudar mais C++.


#include <stdio.h>
#include <stdlib.h>
#include <cstdlib> //necessario para pausar a execucao e continuar ao apertar qualquer botao
#include <time.h> //necessario para gerar numeros realmente aleatorios
#include <conio.h>

//declaracao do elemento das listas
typedef struct sPontuacao{
	struct sPontuacao *next;
	struct sPontuacao *prev;
	int pontos;
}Pontuacao;

//cada jogador aponta para uma lista
typedef struct sJogador{
	struct sPontuacao *head;
	struct sPontuacao *tail;
	int size;
	int totalPontos;
	int id;
}Jogador;

//prototipacao das funcoes
Jogador* criaJogador(int qtd);
void inserePontuacao(Jogador *jogador, int pontos, int x);
void imprimePlacar(Jogador *jogador, int qtd);
void calculaPontuacaoFinal(Jogador *jogador, int qtd);
int qtdJogadores();
void iniciarJogo(Jogador *jogador, int qtd);
void freeMemory(Jogador *jogador, int qtd);
void imprimeJogadoresOrdenados(Jogador *jogador, int qtd);
void ajuda();

main(){
	int op=0;
	Jogador *jogador;
	
	while(op==0){
        system("clear||cls");
		printf("\n\t*****Bem-vindo ao jogo de boliche*****\n\n\n");
        printf("\t1)Jogar\n");
        printf("\t2)Ajuda\n");
        printf("\t3)Sair\n");
        
        int qtd;
        scanf("%d",&op);
        switch (op){
            case 1: qtd= qtdJogadores();
					jogador= criaJogador(qtd);
					iniciarJogo(jogador, qtd);
					imprimePlacar(jogador, qtd);
					calculaPontuacaoFinal(jogador, qtd);
					imprimeJogadoresOrdenados(jogador, qtd);
					freeMemory(jogador, qtd);
					printf("\n\n\n");
					system("pause");
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

//aloca memória para os jogadores com suas respectivas listas de pontos
Jogador* criaJogador(int qtd){
    Jogador *jogador= (Jogador*)malloc(qtd * sizeof(Jogador));
    for(int i=0; i<qtd; i++){
    	jogador[i].head=NULL;
    	jogador[i].tail=NULL;
		jogador[i].size=0;
		jogador[i].totalPontos=0;
		jogador[i].id=i;
	}
	return jogador;
}

//lista encadeada dupla para armazenar a pontuacao de cada jogador de forma dinamica
//codigo retirado da materia de Estrutura de Dados I
void inserePontuacao(Jogador *jogador, int pontos, int x){
	Pontuacao *pivo= jogador[x].tail;
	Pontuacao *nova_Pontuacao= (Pontuacao*)malloc(sizeof(Pontuacao));
	nova_Pontuacao->pontos=pontos;
    
	if(jogador[x].size==0){
        jogador[x].head=nova_Pontuacao;
        jogador[x].head->prev=NULL;
        jogador[x].head->next=NULL;
        jogador[x].tail=nova_Pontuacao;
    }else{
        nova_Pontuacao->next=pivo->next;
        nova_Pontuacao->prev=pivo;

        if(pivo->next==NULL){
            jogador[x].tail= nova_Pontuacao;
        }else{
            pivo->next->prev=nova_Pontuacao;
        }
        pivo->next=nova_Pontuacao;
    }
    jogador[x].size++;
}

//imprime todos os pontos de cada jogador
void imprimePlacar(Jogador *jogador, int qtd){
	Pontuacao *aux;
	for(int i=0; i<qtd; i++){
		aux= jogador[i].head;
		printf("\nJogador %d: ", i+1);
		while(aux!=NULL){
			printf("%d ", aux->pontos);
			aux= aux->next;
		}
		printf("\n");
	}	
}

//soma todos os pontos dos jogadores
void calculaPontuacaoFinal(Jogador *jogador, int qtd){
	int soma=0;
	Pontuacao *aux;
	
	for(int i=0; i<qtd; i++){
		aux=jogador[i].head;
		while(aux!=NULL){
			soma+=aux->pontos;
			aux= aux->next;
		}
		jogador[i].totalPontos=soma;
		soma=0;
	}
}

//define a quantidade de jogadores
int qtdJogadores(){
	system("clear||cls");
    printf("\tSelecione a quantidade de jogadores:\n");
    int i;
	scanf("%d",&i);
	return i;
}

void iniciarJogo(Jogador *jogador, int qtd){
	system("clear||cls");
	int totalPinos=10;
	int pinos;
	int soma=0;
	srand(time(NULL));
	
	//10 Rounds
	for(int i=0; i<10; i++){
		printf("\n\n\t Round %d\n", i+1);
		
		//jogadores
		for(int x=0; x<qtd; x++){
			
			//os 9 primeiros rounds são normais
			if(i<9){
				printf("\nJogador %d\n", x+1);
				for(int y=0; y<2; y++){
					pinos=rand() % totalPinos+1;
					printf("tentativa %d, %d pinos derrubados.\n",y+1,pinos);
					totalPinos-=pinos;
					soma+=pinos;
					
					//calcula a pontuacao no round e adiciona na lista do jogador
					//se houver Strike, adiciona 15 pontos na lista
					if(totalPinos==0 && y==0){
						totalPinos=10;
						inserePontuacao(jogador, 15, x);
						break;
						
					//se for um Spare ou Normal, adiciona "soma" pontos na lista do jogador
					}else if(y==1){
						inserePontuacao(jogador, soma, x);
					}
				}
				totalPinos=10;
				soma=0;
			
			//o ultimo round tem 3 tentativas e suporta até 3 strikes	
			}else{
				printf("\nJogador %d\n", x+1);
				for(int y=0; y<3; y++){
					pinos=rand() % totalPinos+1;
					printf("tentativa %d, %d pinos derrubados.\n",y+1,pinos);
					totalPinos-=pinos;
					if(totalPinos==0){
						totalPinos=10;
					}
					
					//calcula a pontuacao no round e adiciona na lista do jogador
					if(pinos==10){
						soma+=15;
					}else{
						soma+=pinos;
					}
				}
				inserePontuacao(jogador, soma, x);
				totalPinos=10;
				soma=0;
			}
			
		}
	}
}

//remocao de toda a memoria alocada pela lista encadeada dupla
//primeiro remove os elementos, depois as listas.
void freeMemory(Jogador *jogador, int qtd){
	Pontuacao *aux;
    for(int i=0; i<qtd; i++){
		while(jogador[i].size>0){
            aux= jogador[i].head;
            jogador[i].head = aux->next;
            if(jogador[i].head==NULL){
                jogador[i].tail=NULL;
            }else{
                aux->next->prev=NULL;
            }
            free(aux);
            jogador[i].size--;
        }
    }
    free(jogador);
}

//imprime os jogadores ordenados com base na sua pontuacao
void imprimeJogadoresOrdenados(Jogador *jogador, int qtd){
	int i, j, aux, vet[qtd];
	
	//salva todas as pontuacoes em um vetor.
	for(i=0; i<qtd; i++){
		vet[i]=jogador[i].totalPontos;
	}
 	
 	//InsertionSort, ordena o vetor
 	//retirado de "https://www.youtube.com/watch?v=79buQYoWszA"
 	for(i=0; i<qtd; i++){
 		aux= vet[i];
 		for(j=i; (j>0) && (aux < vet[j-1]); j--)
 			vet[j]= vet[j-1];
 		vet[j]= aux;
	}
	
	//percorro o vetor ordenado e os jogadores, caso algum jogador
	//tenha a mesma pontuacao daquela posicao do vetor, ele sera impresso.
	for(i=qtd-1; i>=0; i--){
		for(j=0; j<qtd; j++){
			if(vet[i]==jogador[j].totalPontos){
				
				//o primeiro jogador, ou seja, aquele que tem mais pontos, eh o vencedor
				if(jogador[j].totalPontos==vet[qtd-1]){
					printf("\n\nJogador %d: %d pontos, VENCEDOR!!\n", j+1, vet[i]);
				}else{
					printf("Jogador %d: %d pontos\n", j+1, vet[i]);
				}
				jogador[j].totalPontos=-1;
				break;
			}
		}
	}
}

//algumas informacoes sobre o jogo
void ajuda(){
	printf("Esse eh um jogo de boliche automatico, todas as pontuacoes sao geradas aleatoriamente.\n");
	printf("As pontuacoes sao diferentes do padrao do boliche, devidos as limitacoes da linguagem e a falta de tempo dos programadores.\n");
	printf("A pontuacao ficou assim:\n\n");
	printf("\tStrike= 15 pontos\n");
	printf("\tSpare= 10 pontos\n");
	printf("\tNormal= ate 9 pontos\n\n");
	printf("O Strike acontece quando todos os 10 pinos sao derrubados de primeira.\n");
	printf("Ja o Spare, acontece quando eh necessario mais de uma tentativa para derrubar os 10 pinos.\n\n\n");
}
