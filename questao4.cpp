#include<iostream>
#include<vector>
#include<algorithm>

#define INFINITO 100000000.0
#define MAXN 100

using namespace std;

/*Classe Nó*/
template <class T>
class No{
	private:
		T item;
		No* prox;
	public:
		No();
		No(T item);
		T getItem();
		No* getProx();
		void setItem(T);
		void setProx(No*);
};

template<class T>
No<T>::No(){
    this->prox = NULL;
}

template<class T>
No<T>::No(T item){
    this->item = item;
}

template<class T>
T No<T>::getItem(){
    return this->item;
}

template<class T>
No<T>* No<T>::getProx(){
    return this->prox;
}

template<class T>
void No<T>::setItem(T item){
    this->item = item;
}

template<class T>
void No<T>::setProx(No* prox){
    this->prox = prox;
}

/*Classe Fila de Prioridade*/
template <class T>
class FilaDePrioridade{
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
		FilaDePrioridade();
		void enfileirar(T);
		T frente();
		void desenfileirar();
		void desenfileirar(T&);
		void destruir();
		int tamanho();
		bool vazia();
};

template<class T>
void FilaDePrioridade<T>::inicializar(){
	T item;
	this->pos = 0;
	this->minHeap.push_back(item);
}

template<class T>
int FilaDePrioridade<T>::filhoEsquerda(int n){
	int esq = (n<<1);
	if(esq <= this->pos) return esq;
	else return -1;
}

template<class T>
int FilaDePrioridade<T>::filhoDireita(int n){
	int dir = (n<<1) + 1;
	if(dir <= this->pos) return dir;
	else return -1;
}

template<class T>
int FilaDePrioridade<T>::pai(int n){
	return n>>1;
}

template<class T>
void FilaDePrioridade<T>::heapificaBaixo(int noAtual){
	int filho, no = noAtual;
	
	filho = this->filhoEsquerda(noAtual);
	if(filho != -1 && minHeap[no]>minHeap[filho]) no = filho;

	filho = this->filhoDireita(noAtual);
	if(filho != -1 && minHeap[no]>minHeap[filho]) no = filho;
	
	if(no != noAtual){
		swap(minHeap[noAtual], minHeap[no]);
		this->heapificaBaixo(no);
	}
}

template<class T>
void FilaDePrioridade<T>::heapificaCima(){
	int no = this->pos;
	while(pai(no) != 0 && minHeap[pai(no)]>minHeap[no]){
		swap(minHeap[pai(no)], minHeap[no]);
		no = pai(no);
	}
}

template<class T>
FilaDePrioridade<T>::FilaDePrioridade(){
	this->inicializar();
}

template<class T>
void FilaDePrioridade<T>::enfileirar(T item){
	this->minHeap.push_back(item);
	this->pos++;
	this->heapificaCima();
}

template<class T>
T FilaDePrioridade<T>::frente(){
	if(!this->vazia())
		return this->minHeap[1];
	return this->minHeap[0];
}

template<class T>
void FilaDePrioridade<T>::desenfileirar(){
	if(this->vazia()) return;
	this->minHeap[1] = this->minHeap[pos];
	this->minHeap.pop_back();
	this->pos--;
	this->heapificaBaixo(1);
}

template<class T>
void FilaDePrioridade<T>::desenfileirar(T &item){
	if(this->vazia()) return;
	item = this->minHeap[1];
	this->desenfileirar();
}

template<class T>
void FilaDePrioridade<T>::destruir(){
	if(this->vazia()) return;
	this->minHeap.clear();
	this->inicializar();
}

template<class T>
int FilaDePrioridade<T>::tamanho(){
	return this->pos;
}

template<class T>
bool FilaDePrioridade<T>::vazia(){
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

template <class T1, class T2>
void Par<T1, T2>::setPrimeiro(T1 a){
	this->primeiro = a;
}

template <class T1, class T2>
void Par<T1, T2>::setSegundo(T2 b){
	this->segundo = b;
}

/*Classe Vértice*/
template <class T>
class Vertice{
    private:
        T item;
        double dist;
    public:
    	Vertice();
        T getItem();
        double getDist();
        void setItem(T);
        void setDist(double);
        void mostraVertice();
};

template<class T>
Vertice<T>::Vertice(){
    this->dist = INFINITO;
}

template<class T>
T Vertice<T>::getItem(){
    return this->item;
}

template<class T>
double Vertice<T>::getDist(){
    return this->dist;
}

template<class T>
void Vertice<T>::setItem(T item){
    this->item = item;
}

template<class T>
void Vertice<T>::setDist(double dist){
    this->dist = dist;
}

/*Classe Grafo*/
template <class T>
class Grafo{
    private:
        vector< Par<int, double> > *listaAdjacencias;
        int qntVertices, qntArestas;

    public:
    	Grafo();
        Grafo(int);
        void inicializar(int);
        void inserirAresta(int, int, double);
        int getQntArestas();
        void mostrarGrafo();
        void limpar();
        void dijkstra(int, int); 
        void printPath(vector<int> parent, int j);
};


template<class T>
Grafo<T>::Grafo(){
	this->listaAdjacencias = NULL;
    this->qntArestas = this->qntVertices = 0;
}

template<class T>
Grafo<T>::Grafo(int qntVertices){
	this->listaAdjacencias = NULL;
    this->inicializar(qntVertices);
}

template<class T>
void Grafo<T>::inicializar(int n){
    if(n <= 0) return;
    this->qntArestas = 0;
    this->qntVertices = n;
    this->listaAdjacencias = new vector< Par<int, double> >[n];
}

template<class T>
void Grafo<T>::inserirAresta(int u, int v, double w){
    if(u<=qntVertices && v<=qntVertices){
        this->qntArestas++;
        this->listaAdjacencias[u].push_back(Par<int, double>(v, w));
    }
}

template<class T>
int Grafo<T>::getQntArestas(){
	return this->qntArestas;
}

template<class T>
void Grafo<T>::mostrarGrafo(){
    for(int i=0; i<this->qntVertices; i++){
        cout << i << ": ";
        for(int j=0; j<this->listaAdjacencias[i].size(); j++)
            cout << this->listaAdjacencias[i][j].getPrimeiro() << ' ' << this->listaAdjacencias[i][j].getSegundo() << ' ';
        cout << endl;
    }
    cout << endl;
}

template<class T>
void Grafo<T>::limpar(){
    for(int i=1; i<=this->qntVertices; i++)
        this->listaAdjacencias[i].clear();
    this->qntVertices = this->qntArestas = 0;
    delete[] this->listaAdjacencias;
}

template<class T>
void Grafo<T>::dijkstra(int inicio, int fim){
	
    vector<int> dist(this->qntVertices, INFINITO); //Inicializa o vetor
    vector<int> pai(this->qntVertices, -1); //Inicializa o vetor
    
    FilaDePrioridade<Par <int, double> > fila_prioridade;
    
    fila_prioridade.enfileirar(Par <int, double> (0,inicio));
    dist[inicio] = 0; //A distância dele para ele mesmo é 0
    
	while( !fila_prioridade.vazia() ){
		Par<int, double> frente = fila_prioridade.frente();
		fila_prioridade.desenfileirar();
		
		int d = frente.getPrimeiro();
		int u = frente.getSegundo();
		
		if(d > dist[u])
			continue;
		
		for(int i = 0; i < (int)listaAdjacencias[u].size(; i++){
			Par<int, double> v = listaAdjacencias[u][i];
			
			if(dist[u] + v.getSegundo() < dist[v.getPrimeiro()]){
				
				dist[v.getPrimeiro()] = dist[u] + v.getSegundo();
				pai[v.getPrimeiro()] = u;
				
				fila_prioridade.enfileirar(Par <int, double> (dist[v.getPrimeiro()], v.getPrimeiro()));
			}
		}
	}
	
	printPath(pai, fim);
}


template<class T>
void Grafo<T>::printPath(vector<int> parent, int j)
{
    // Base Case : If j is source
    if (parent[j] !=-1)
        printPath(parent, parent[j]);
 
    cout << j << " ";
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
	int u, v, w;
	cin >> this->nPalco >> this->mCaminho;
	
	this->show.inicializar(this->nPalco);

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
