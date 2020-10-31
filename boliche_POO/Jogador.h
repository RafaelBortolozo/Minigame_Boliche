#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED
#include <stdio.h>
#include <vector> //necessario para declarar um vetor de objetos

class Jogador{
	public:
		std::vector<int> pontuacoes;
		int id;
		int totalPontos;
		void setTotalPontos();
		void imprimirPontuacoes();
		void inserePontuacao(int valor);
};

void Jogador::setTotalPontos(){
	for(int i=0; i<10; i++){
		this->totalPontos= this->totalPontos + this->pontuacoes[i];
	}
}

void Jogador::imprimirPontuacoes(){
	printf("\nJogador %d: ", (this->id)+1);
	for(int i=0; i<this->pontuacoes.size() ; i++){
		printf("%d ", this->pontuacoes[i]);
	}
	printf("\n");
}

void Jogador::inserePontuacao(int valor){
	this->pontuacoes.push_back(valor);
}

#endif // JOGADOR_H_INCLUDED
