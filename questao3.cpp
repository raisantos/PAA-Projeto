//============================================================================
// Name        : questao3.cpp
// Author      : Raí Santos da Soledade, Juliany Rodrigues Raiol
// Description : Questao 3
//============================================================================

#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <climits>
#include <iomanip>
using namespace std;

typedef int Vertice;

template<class T>
class Grafo {
private:
	vector<vector<T> > adj;
	int ordem, tam;

	 void troca(vector<int> &, int, int);
	 int encontraMaiorMovel(vector<int> &, vector<int> &);
	 bool verificaMovel(vector<int> &, vector<int> &);
	 void inverteSetas(vector<int> &, vector<int> &, int);

public:
	Grafo(int);
	void iniciar(int);
	void preenche();
	void insere(Vertice, Vertice, float);
	int caixeiroViajante(int, vector<int> &);
	float johnsonTrotter(int, vector<int> &);

	vector<vector<T> > getAdj() {
		return adj;
	}
	void setAdj(vector<vector<T> > adj) {
		this->adj = adj;
	}
	int getOrdem() {
		return ordem;
	}
	void setOrdem(int n) {
		this->ordem = ordem;
	}
	int getTam() {
		return tam;
	}
	void setTam(int tam) {
		this->tam = tam;
	}
};

template<class T>
Grafo<T>::Grafo(int ordem) {
	iniciar(ordem);
	preenche();
}

template<class T>
void Grafo<T>::iniciar(int ordem) {
	this->ordem = ordem;
	for(int i = 0; i < ordem; i++){
	    vector<T> aux(ordem);
	    adj.push_back(aux);
	}
}

template<class T>
void Grafo<T>::preenche() {
	for (int i = 0; i < ordem; i++) {
	    for(int j = 0; j < ordem; j++){
		    adj[i][j] = 0.0;
		}
	}
}

template<class T>
void Grafo<T>::insere(Vertice v1, Vertice v2, float peso) {
	adj[v1][v2] = peso;
	adj[v2][v1] = peso;
}

template<class T>
void Grafo<T>::troca(vector<int> &vetor, int i, int j){
	int temp = vetor[i];
	vetor[i] = vetor[j];
	vetor[j] = temp;
}

template<class T>
int Grafo<T>::encontraMaiorMovel(vector<int> &atualPermutacao, vector<int> &setas){
	int maior = 0;
	int indiceMaior = 0;
	for(int i = 0; i < (int)atualPermutacao.size(); i++){
		if((setas[i] == 0) && (i != 0)){
			if(atualPermutacao[i] > atualPermutacao[i-1]){
				if(atualPermutacao[i] > maior){
					maior = atualPermutacao[i];
					indiceMaior = i;
				}
			}
		}
		else if((setas[i] == 1) && (i != (int)atualPermutacao.size()-1)){
			if(atualPermutacao[i] > atualPermutacao[i+1]){
				if(atualPermutacao[i] > maior){
					maior = atualPermutacao[i];
					indiceMaior = i;
				}
			}
		}
	}
	return indiceMaior;
}

template<class T>
bool Grafo<T>::verificaMovel(vector<int> &atualPermutacao, vector<int> &setas){
	for(int i = 0; i < (int)atualPermutacao.size(); i++){
		if((setas[i] == 0) && (i != 0)){
			if(atualPermutacao[i] > atualPermutacao[i-1]){
				return true;
			}
		}
		else if((setas[i] == 1) && (i != (int)atualPermutacao.size()-1)){
			if(atualPermutacao[i] > atualPermutacao[i+1]){
				return true;
			}
		}
	}
	return false;
}

template<class T>
void Grafo<T>::inverteSetas(vector<int> &atualPermutacao, vector<int> &setas, int maiorMovel){
	int valorMaiorMovel = atualPermutacao[maiorMovel];
	for(int i = 0; i < (int)atualPermutacao.size(); i++){
		if(atualPermutacao[i] > valorMaiorMovel){
			if(setas[i] == 0){
				setas[i] = 1;
			}
			else if(setas[i] == 1){
				setas[i] = 0;
			}
		}
	}
}

template<class T>
float Grafo<T>::johnsonTrotter(int inicio, vector<int> &lista){
	vector<int> atualPermutacao;
	atualPermutacao = lista;

	vector<int> setas;
	for(int i = 0; i < (int)atualPermutacao.size(); i++){
		setas.push_back(0);
	}

	int maiorMovel;
	float soma = 0, aux;
	vector<int> menorCaminho;

	soma = caixeiroViajante(inicio, atualPermutacao);
	menorCaminho = atualPermutacao;
	while(verificaMovel(atualPermutacao, setas)){
		aux = 0;
		maiorMovel = encontraMaiorMovel(atualPermutacao, setas);

		if(setas[maiorMovel] == 0){
			troca(atualPermutacao, maiorMovel, maiorMovel-1);
			troca(setas, maiorMovel, maiorMovel-1);
			maiorMovel = maiorMovel-1;
		}
		else if(setas[maiorMovel] == 1){
			troca(atualPermutacao, maiorMovel, maiorMovel+1);
			troca(setas, maiorMovel, maiorMovel+1);
			maiorMovel = maiorMovel+1;
		}
		inverteSetas(atualPermutacao, setas, maiorMovel);
		aux = caixeiroViajante(inicio, atualPermutacao);

		if(aux < soma){
			soma = aux;
			menorCaminho = atualPermutacao;
		}
	}
	return soma;
}

template<class T>
int Grafo<T>::caixeiroViajante(int inicio, vector<int> &permutacao){
	vector<int> listaVizinhos, resp;
	int soma = 0;

	soma = soma + adj[inicio][permutacao[0]];
	for(int i = 0; i < (int)permutacao.size()-1; i++){
		soma = soma + adj[permutacao[i]][permutacao[i+1]];
	}
	soma = soma + adj[permutacao[permutacao.size()-1]][inicio];

	return soma;
}


int main() {
    int ordem, tamanho, v1, v2, verticeInicial;
    float peso;
    cin >> ordem;
    cin >> tamanho;

    Grafo<int> palcos(ordem);

    for (int i = 0; i < tamanho; ++i) {
    	cin >> v1;
    	cin >> v2;
    	cin >> peso;
    	palcos.insere(v1,v2,peso);
	}

    cin >> verticeInicial;
    vector<int> lista;
    for (int i = 0; i < ordem; ++i) {
        if(i != verticeInicial){
        	lista.push_back(i);
        }
    }

    float resp;
    resp = palcos.johnsonTrotter(verticeInicial, lista);
    cout.precision(1);
    cout << fixed << resp;

	return 0;
}
