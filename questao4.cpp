//============================================================================
// Name        : questao4.cpp
// Author      : Raí Santos da Soledade, Juliany Rodrigues Raiol
// Description : Questao 4
//============================================================================

#include<iostream>
#include<vector>
#include<algorithm>
#define INF 123456

using namespace std;

/*Classe Fila de Prioridade*/
template <class T>
class filaPrioridade{
	private:
		int pos;
		vector<T> minHeap;
		
		int filhoEsquerda(int);
		int filhoDireita(int);
		int pai(int);
		void inicializar();
		void heapificaBaixo(int);
		void heapificaCima();
	
	public:
		filaPrioridade();
		void enfileirar(T);
		T frente();
		void desenfileirar();
		void destruir();
		int tamanho();
		bool vazia();
};

template<class T>
void filaPrioridade<T>::inicializar(){
	T item;
	this->pos = 0;
	this->minHeap.push_back(item);
}

template<class T>
int filaPrioridade<T>::filhoEsquerda(int n){
	int esq = (n*n);
	if(esq <= this->pos) 
		return esq;
	else return -1;
}

template<class T>
int filaPrioridade<T>::filhoDireita(int n){
	int dir = (n*n) + 1;
	if(dir <= this->pos) 
		return dir;
	else return -1;
}

template<class T>
int filaPrioridade<T>::pai(int n){
	return n/2;
}

template<class T>
void filaPrioridade<T>::heapificaBaixo(int noAtual){
	int filho, no = noAtual;
	
	filho = this->filhoEsquerda(noAtual);
	if(filho != -1 && minHeap[no] > minHeap[filho]) 
		no = filho;

	filho = this->filhoDireita(noAtual);
	if(filho != -1 && minHeap[no] > minHeap[filho]) 
		no = filho;
	
	if(no != noAtual){
		swap(minHeap[noAtual], minHeap[no]);
		this->heapificaBaixo(no);
	}
}

template<class T>
void filaPrioridade<T>::heapificaCima(){
	int no = this->pos;
	while(pai(no) != 0 && minHeap[pai(no)]> minHeap[no]){
		swap(minHeap[pai(no)], minHeap[no]);
		no = pai(no);
	}
}

template<class T>
filaPrioridade<T>::filaPrioridade(){
	this->inicializar();
}

template<class T>
void filaPrioridade<T>::enfileirar(T item){
	this->minHeap.push_back(item);
	this->pos++;
	this->heapificaCima();
}

template<class T>
T filaPrioridade<T>::frente(){
	if(!this->vazia())
		return this->minHeap[1];
	return this->minHeap[0];
}

template<class T>
void filaPrioridade<T>::desenfileirar(){
	if(this->vazia()) 
		return;
	this->minHeap[1] = this->minHeap[pos];
	this->minHeap.pop_back();
	this->pos--;
	this->heapificaBaixo(1);
}

template<class T>
void filaPrioridade<T>::destruir(){
	if(this->vazia()) return;
	this->minHeap.clear();
	this->inicializar();
}

template<class T>
int filaPrioridade<T>::tamanho(){
	return this->pos;
}

template<class T>
bool filaPrioridade<T>::vazia(){
	return (this->pos == 0);
}

/*Classe Par*/
template <class T1, class T2>
class Par{
    private:
        T1 primeiro;
        T2 segundo;
    public:
    	Par();
        Par(T1, T2);
        bool operator <(Par<T1, T2>);
		bool operator >(Par<T1, T2>);
        T1 getPrimeiro();
        T2 getSegundo();
        void setPrimeiro(T1);
        void setSegundo(T2);
};

template <class T1, class T2>
Par<T1, T2>::Par(){
}

template <class T1, class T2>
Par<T1, T2>::Par(T1 a, T2 b){
	this->primeiro = a;
	this->segundo = b;
}

template <class T1, class T2>
bool Par<T1, T2>::operator<(Par<T1, T2> p){
	return (this->primeiro < p.getPrimeiro());
}

template <class T1, class T2>
bool Par<T1, T2>::operator>(Par<T1, T2> p){
	return (this->primeiro > p.getPrimeiro());
}

template <class T1, class T2>
T1 Par<T1, T2>::getPrimeiro(){
	return this->primeiro;
}

template <class T1, class T2>
T2 Par<T1, T2>::getSegundo(){
	return this->segundo;
}

/*Classe Grafo*/
template <class T>
class Grafo{
    private:
        vector< Par<int, double> > *Adj;
        int qntVertices;
		 
    public:
    	Grafo();
        Grafo(int);
        void iniciaAdj(int);
        void inserirAresta(int, int, double);
        void limpar();
        void dijkstra(int, int);
        void mostrarCaminho(vector<int>, int);
};


template<class T>
Grafo<T>::Grafo(){
	this->Adj = NULL;
    this->qntVertices = 0;
}

template<class T>
Grafo<T>::Grafo(int qntVertices){
	this->Adj = NULL;
    this->iniciaAdj(qntVertices);
}

template<class T>
void Grafo<T>::iniciaAdj(int n){
    this->qntVertices = n;
    this->Adj = new vector< Par<int, double> >[n];
}

template<class T>
void Grafo<T>::inserirAresta(int u, int v, double w){
    this->Adj[u].push_back(Par<int, double>(v, w));
}

template<class T>
void Grafo<T>::dijkstra(int inicio, int fim){
	
    vector<int> dist(this->qntVertices, INF); //Inicializa o vetor
    vector<int> pai(this->qntVertices, -1); //Inicializa o vetor
    
    filaPrioridade<Par <int, double> > fila_prioridade;
    
    fila_prioridade.enfileirar(Par <int, double> (0,inicio));
    dist[inicio] = 0; //A distância dele para ele mesmo é 0
    
	while( !fila_prioridade.vazia() ){
		Par<int, double> frente = fila_prioridade.frente();
		fila_prioridade.desenfileirar();
		
		int d = frente.getPrimeiro();
		int u = frente.getSegundo();
		
		if(d > dist[u])
			continue;
		
		for(int i = 0; i < (int)Adj[u].size(); i++){
			Par<int, double> v = Adj[u][i];
			
			if(dist[u] + v.getSegundo() < dist[v.getPrimeiro()]){
				
				dist[v.getPrimeiro()] = dist[u] + v.getSegundo();
				pai[v.getPrimeiro()] = u;
				
				fila_prioridade.enfileirar(Par <int, double> (dist[v.getPrimeiro()], v.getPrimeiro()));
			}
		}
	}
	
	mostrarCaminho(pai, fim);
}


template<class T>
void Grafo<T>::mostrarCaminho(vector<int> pai, int i)
{
    if (pai[i] !=-1)
        mostrarCaminho(pai, pai[i]);
 
    cout << i << " ";
}

/*Classe Processamento*/
class Processamento{
	private:
		Grafo<int> show;
		int inicio, fim, nPalco, mCaminho;
	public:
		void entrada();
		void saida();
};

void Processamento::entrada(){
	int u, v;
	double w;
	cin >> this->nPalco >> this->mCaminho;
	
	this->show.iniciaAdj(this->nPalco);

	for(int i=0; i<this->mCaminho; i++){
		cin >> u >> v >> w;
		this->show.inserirAresta(u, v, w);
		this->show.inserirAresta(v, u, w); 
	}
	
	cin >> this->inicio >> this->fim;
}

void Processamento::saida(){

	this->show.dijkstra(this->inicio, this->fim);
}

int main(){
	Processamento solucao;
	solucao.entrada();
	solucao.saida();
    return 0;
}
