//============================================================================
// Name        : questao1.cpp
// Author      : Raí Santos da Soledade, Juliany Rodrigus Raiol
// Description : Questao 1
//============================================================================

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Ordenacao{
	private:
		void quickSort(vector<string>&, int, int);
		int particao(vector<string>&, int, int);
	public:
		void ordenar(vector<string>&);
};

int Ordenacao::particao(vector<string> &l, int p, int r){
	string x = l[p], tmp = l[r+1];
	l[r+1] = x;
	int i = p, j = r+1;
	while( true ){
		while( l[++i]< x );
		while( l[--j]> x );
		if(i<j) swap(l[i], l[j]);
		else{
			swap(l[p], l[j]);
			l[r+1] = tmp;
			return j;
		}
	}
}

void Ordenacao::quickSort(vector<string> &l, int p, int r){
	if(p < r){
		int q = particao(l, p, r);
		quickSort(l, p, q-1);
		quickSort(l, q+1, r);
	}
}

void Ordenacao::ordenar(vector<string> &l){
	int tam = l.size()-1;
	string sentinela;
	l.push_back(sentinela);
	quickSort(l, 0, tam);
	l.pop_back();
}

class Acao{

private:
	string codigo;
	int valor;
	float percentual;
	int densidade;

public:
	Acao(){
	};

	Acao(string codigo, int valor, float percentual){
		this->codigo = codigo;
		this->valor = valor;
		this->percentual = percentual;
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

	float getPercentual(){
		return percentual;
	}

	void setPercentual(float percentual){
		this->percentual = percentual;
	}

	int getDensidade(){
		return densidade;
	}

	void setDensidade(int densidade){
		this->densidade = densidade;
	}

	void calculaDensidade(){
		float aux = this->percentual/(float)this->valor;
		aux = aux*1000;
		this->densidade = (int)aux;
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
			if (vetor[base].getDensidade() > aux.getDensidade()){
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
	        if (vetor[topo].getDensidade() < aux.getDensidade()){
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

vector<string> calcula_acoes(int pesoMax, vector<Acao> &itens){
	int pesoDisponivel = pesoMax;
	quicksort(itens, 0, itens.size()-1);

	vector<string> acoesParaComprar;
	bool continuar = true;
	int i = itens.size()-1;
	while(continuar){
		if(itens[i].getValor() <= pesoDisponivel){
			acoesParaComprar.push_back(itens[i].getCodigo());
			pesoDisponivel = pesoDisponivel - itens[i].getValor();
		}
		else{
			continuar = false;
		}
		i--;
	}
	return acoesParaComprar;
}

int main() {
	 vector<Acao> acoes;
	 vector<string> resp;
	 int qtdAcoes, valor, heranca = 100000;
	 float percentual;
	 string codigo;

	 cin >> qtdAcoes;
	 for(int i = 0; i < qtdAcoes; i++){
		 cin >> codigo;
		 cin >> valor;
		 cin >> percentual;
		 Acao acao(codigo, valor, percentual);
		 acao.calculaDensidade();
		 acoes.push_back(acao);
	 }

	 resp = calcula_acoes(heranca, acoes);

	 Ordenacao ordenacao;
	 ordenacao.ordenar(resp);

	 for(int i = 0; i < (int)resp.size(); i++){
		 cout << resp[i] << endl;
	 }

	return 0;
}
