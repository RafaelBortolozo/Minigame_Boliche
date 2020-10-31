
// Alunos: Bruno Henrique Potrikus & Rafael Bortolozo
//
// OBS: A linguagem C++ nao foi muito eficiente na programacao do jogo, principalmente na questao da pontuacao, pois ela funciona de uma forma complexa
//      e exige que as pontuacoes dos rounds passados sejam atualizados em caso de Strike e Spare. Para resolver esse problema, teria que usar uma linguagem
//      que permite atualizar automaticamente as pontuacoes da tabela, ou estudar mais C++.


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector> //necessario para declarar um vetor de objetos
#include <cstdlib> //necessario para limpar terminal e pausar a execucao e continuar ao apertar qualquer botao
#include <conio.h> //biblioteca de desenvolvimento, permite pausar a execucao e corrigir bugs

//CLASSES
#include "Jogo.h"
#include "Jogador.h"

main(){
	int op=0;
	Jogo *jogo= new Jogo();
	jogo->rodadaAtual=0;
	std::vector<Jogador*> jogador;
	
	while(op==0){
        op= jogo->menuInicial();
        switch (op){
            case 1: jogo->qtdJogadores= jogo->SetQtdJogadores(); //pergunta quantidade de jogadores
            		jogo->criaJogadores(jogador, jogo->qtdJogadores); //cria x objetos de jogador
            		jogo->iniciarJogo(jogador);
            		jogo->imprimePlacar(jogador);
            		jogo->calculaPontuacaoFinal(jogador);
            		jogo->imprimeJogadoresOrdenados(jogador);
					printf("\n\n\n");
					system("pause");
                    break;
			
			case 2: system("clear||cls");
					jogo->ajuda();
                    op=0;
                    system("pause");
					break;
                    
			case 3: break;
               
            default:op=0;
                    break;
        }
    }
}


