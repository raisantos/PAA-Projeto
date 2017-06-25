//============================================================================
// Name        : mochila.cpp
// Author      : Raí Soledade
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

class Acao{

private:
	int codigo;
	float valor;
	int porcentagem;

public:
	Acao(){
	};

	Acao(int codigo, float valor, int porcentagem){
		this->codigo = codigo;
		this->valor = valor;
		this->porcentagem = porcentagem;
	};

	int getCodigo(){
		return codigo;
	}

	void setCodigo(int codigo){
		this->codigo = codigo;
	}

	float getValor(){
		return valor;
	}

	void setValor(float valor){
		this->valor = valor;
	}

	int getPorcentagem(){
		return porcentagem;
	}

	void setPorcentagem(int porcentagem){
		this->porcentagem = porcentagem;
	}
};

int particao(vector<Acao> &list, int start, int end){
	Acao pivot;
	pivot = list[end];
	int bottom = start-1;
	int top = end;

	bool done = false;
	while (!done){

		while (!done){
			bottom = bottom + 1;

			if (bottom == top){
		       	done = true;
	            break;
	        }
			if (list[bottom].getPorcentagem() > pivot.getPorcentagem()){
	    	   list[top] = list[bottom];
	    	   break;
			}
		}
		while (!done){
			top = top-1;

	        if (top == bottom){
	        	done = 1;
			    break;
			}

	        if (list[top].getPorcentagem() < pivot.getPorcentagem()){
			    list[bottom] = list[top];
			    break;
			}
		}
	}
	list[top] = pivot;
	return top;

}


void quicksort(vector<Acao> &list, int start, int end){
	int split;
	if(start < end){
		split = particao(list, start, end);
		quicksort(list, start, split-1);
		quicksort(list, split+1, end);
	}
}

vector<int> calcula_acoes(int peso_max, vector<Acao> &itens){
	int peso_disponivel = peso_max;
	quicksort(itens, 0, itens.size()-1);
	vector<int> acoes_a_comprar;
	int total = 0;

	for(int i = itens.size()-1; i >= 0; i--){
		if(itens[i].getValor() <= peso_disponivel){
			acoes_a_comprar.push_back(itens[i].getCodigo());
			total = total + itens[i].getPorcentagem();
			peso_disponivel = peso_disponivel - itens[i].getValor();
		}
	}
	return acoes_a_comprar;
}

int main() {
	 vector<Acao> itens;
	 Acao item1(1, 1.0, 20);
	 Acao item2(2, 100.0, 10);
	 Acao item3(3, 18.0, 15);
	 Acao item4(4, 22.0, 30);
	 Acao item5(5, 28.0, 50);

	 itens.push_back(item1);
	 itens.push_back(item2);
	 itens.push_back(item3);
	 itens.push_back(item4);
	 itens.push_back(item5);

	 vector<int> resp;
	 resp = calcula_acoes(100, itens);

	 for(int i = 0; i < (int)resp.size(); i++){
		 cout << resp[i] << " ";
	 }

	 //item2.calculaPotencial();
	 //cout << item2.getPotencial();

	return 0;
}
