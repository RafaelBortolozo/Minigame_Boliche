#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

#include <stdio.h>
#include <cstdlib> //necessario para limpar terminal e pausar a execucao e continuar ao apertar qualquer botao
#include <vector> //necessario para declarar um vetor de objetos
#include <time.h> //necessario para gerar numeros realmente aleatorios
#include <algorithm> //necessario para a funcao reverse()

//CLASSES (heranca)
#include "Jogador.h"

class Jogo{
	public:
		int rodadaAtual;
		int qtdJogadores;
		int menuInicial();
		void ajuda();
		int SetQtdJogadores();
		void iniciarJogo(std::vector<Jogador*> &jogador);
		void criaJogadores(std::vector<Jogador*> &jogador, int qtd);
		void imprimePlacar(std::vector<Jogador*> &jogador);
		void calculaPontuacaoFinal(std::vector<Jogador*> &jogador); //calcula a pontuacao total de cada jogador
		void imprimeJogadoresOrdenados(std::vector<Jogador*> &jogador);
};

//classe jogo
	int Jogo::menuInicial(){
		int op;
		system("clear||cls");
		printf("\n\t*****Bem-vindo ao jogo de boliche*****\n\n\n");
	    printf("\t1)Jogar\n");
	    printf("\t2)Ajuda\n");
	    printf("\t3)Sair\n");
		scanf("%d",&op);
		return op;	
	}
	
	//Algumas informacoes sobre o jogo
		void Jogo::ajuda(){
			printf("Esse eh um jogo de boliche automatico, todas as pontuacoes sao geradas aleatoriamente.\n");
			printf("As pontuacoes sao diferentes do padrao do boliche, devidos as limitacoes da linguagem e a falta de tempo dos programadores.\n");
			printf("A pontuacao ficou assim:\n\n");
			printf("\tStrike= 15 pontos\n");
			printf("\tSpare= 10 pontos\n");
			printf("\tNormal= ate 9 pontos\n\n");
			printf("O Strike acontece quando todos os 10 pinos sao derrubados de primeira.\n");
			printf("Ja o Spare, acontece quando eh necessario mais de uma tentativa para derrubar os 10 pinos.\n\n\n");
		}
	
	//define a quantidade de jogadores
	int Jogo::SetQtdJogadores(){
		system("clear||cls");
	    printf("\tSelecione a quantidade de jogadores:\n");
	    int i;
		scanf("%d",&i);
		return i;
	}
	
	void Jogo::iniciarJogo(std::vector<Jogador*> &jogador){
		system("clear||cls");
		int totalPinos=10;
		int pinos;
		int soma=0;
		srand(time(NULL));
		
		//10 Rounds
		for(int i=0; i<10; i++){
			this->rodadaAtual=i;
			printf("\n\n\t Round %d\n", this->rodadaAtual+1);
			
			//jogadores
			for(int x=0; x<this->qtdJogadores; x++){
				
				//os 9 primeiros rounds são normais
				if(i<9){
					printf("\nJogador %d\n", x+1);
					for(int y=0; y<2; y++){
						pinos=rand() % (totalPinos+1);
						printf("tentativa %d, %d pinos derrubados.\n",y+1,pinos);
						totalPinos-=pinos;
						soma+=pinos;
						
						//calcula a pontuacao no round e adiciona na lista do jogador
						//se houver Strike, adiciona 15 pontos na lista
						if(totalPinos==0 && y==0){
							totalPinos=10;
							jogador[x]->inserePontuacao(15);
							//inserePontuacao(jogador, 15, x);
							break;
							
						//se for um Spare ou Normal, adiciona "soma" pontos na lista do jogador
						}else if(y==1){
							jogador[x]->inserePontuacao(soma);
						}
					}
					totalPinos=10;
					soma=0;
				
				//o ultimo round tem 3 tentativas e suporta até 3 strikes	
				}else{
					printf("\nJogador %d\n", x+1);
					for(int y=0; y<3; y++){
						pinos=rand() % (totalPinos+1);
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
					jogador[x]->inserePontuacao(soma);
					totalPinos=10;
					soma=0;
				}	
			}
		}
	}
	
	void Jogo::criaJogadores(std::vector<Jogador*> &jogador, int qtd){
		for(int i=0; i<qtd; i++){
			jogador.push_back(new Jogador()); //adiciona um objeto na ultima posicao do vector
			jogador[i]->id=i; //define um id
			jogador[i]->totalPontos=0;
		}
	}
	
	void Jogo::imprimePlacar(std::vector<Jogador*> &jogador){
		for(int i=0; i<jogador.size() ;i++){
			jogador[i]->imprimirPontuacoes();
		}
	}
	
	void Jogo::calculaPontuacaoFinal(std::vector<Jogador*> &jogador){
		for(int i=0; i<jogador.size() ;i++){
			jogador[i]->setTotalPontos();
		}
	}
	
	void Jogo::imprimeJogadoresOrdenados(std::vector<Jogador*> &jogador){
		int i,j;
		Jogador *aux= new Jogador();
	
	 	//InsertionSort, ordena os jogadores
	 	//retirado de "https://www.youtube.com/watch?v=79buQYoWszA"
	 	for(i=0; i<jogador.size() ;i++){
	 		aux= jogador[i];
	 		for(j=i; (j>0) && (aux->totalPontos < jogador[j-1]->totalPontos) ;j--){
	 			jogador[j]= jogador[j-1];
			}
	 		jogador[j]= aux;
		}
		
		//inverte a ordenacao ASC em DESC
		reverse(jogador.begin(), jogador.end());
		
		//imprime os jogadores
		for(i=0; i<jogador.size() ;i++){
			if(jogador[i]->totalPontos == jogador[0]->totalPontos){
				printf("\n\nJogador %d: %d pontos, VENCEDOR!!\n", jogador[i]->id+1, jogador[i]->totalPontos);
			}else{
				printf("Jogador %d: %d pontos\n", jogador[i]->id+1, jogador[i]->totalPontos);
			}
		}
	}

#endif // JOGO_H_INCLUDED
