//============================================================================
// Name        : mochila.cpp
// Author      : Raí Soledade
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Acao{

private:
	string codigo;
	int valor;
	float porcentagem;

public:
	Acao(){
	};

	Acao(string codigo, int valor, float porcentagem){
		this->codigo = codigo;
		this->valor = valor;
		this->porcentagem = porcentagem;
	};

	string getCodigo(){
		return codigo;
	}

	void setCodigo(string codigo){
		this->codigo = codigo;
	}

	int getValor(){
		return valor;
	}

	void setValor(int valor){
		this->valor = valor;
	}

	float getPorcentagem(){
		return porcentagem;
	}

	void setPorcentagem(float porcentagem){
		this->porcentagem = porcentagem;
	}
};

int particao(vector<Acao> &vetor, int p, int r){
	Acao aux;
	aux = vetor[r];
	int base = p-1, topo = r; bool continuar = false;

	while (!continuar){
		while (!continuar){
			base = base + 1;
			if (base == topo){
		       	continuar = true;
	            break;
	        }
			if (vetor[base].getPorcentagem() > aux.getPorcentagem()){
	    	   vetor[topo] = vetor[base];
	    	   break;
			}
		}
		while (!continuar){
			topo = topo-1;
	        if (topo == base){
	        	continuar = 1;
			    break;
			}
	        if (vetor[topo].getPorcentagem() < aux.getPorcentagem()){
			    vetor[base] = vetor[topo];
			    break;
			}
		}
	}
	vetor[topo] = aux;
	return topo;

}


void quicksort(vector<Acao> &vetor, int p, int r){
	int q;
	if(p < r){
		q = particao(vetor, p, r);
		quicksort(vetor, p, q-1);
		quicksort(vetor, q+1, r);
	}
}

vector<string> calcula_acoes(int peso_max, vector<Acao> &itens){
	int peso_disponivel = peso_max;
	quicksort(itens, 0, itens.size()-1);
	vector<string> acoes_a_comprar;
	//float total = 0.0;

	for(int i = itens.size()-1; i >= 0; i--){
		if(itens[i].getValor() <= peso_disponivel){
			acoes_a_comprar.push_back(itens[i].getCodigo());
			//total = total + itens[i].getPorcentagem();
			peso_disponivel = peso_disponivel - itens[i].getValor();
		}
	}
	return acoes_a_comprar;
}

int main() {
	 vector<Acao> itens;
	 Acao item1("A01", 1, 20.35);
	 Acao item2("A02", 100, 10.25);
	 Acao item3("A03", 18, 15.19);
	 Acao item4("A04", 73, 30.66);
	 Acao item5("A05", 28, 50.55);

	 itens.push_back(item1);
	 itens.push_back(item2);
	 itens.push_back(item3);
	 itens.push_back(item4);
	 itens.push_back(item5);

	 vector<string> resp;
	 resp = calcula_acoes(100, itens);

	 for(int i = 0; i < (int)resp.size(); i++){
		 cout << resp[i] << endl;
	 }

	return 0;
}
