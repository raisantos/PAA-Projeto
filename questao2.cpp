#include <iostream>
#include <vector>
#define MAXL 50
#define MAXC 100

using namespace std;

/*Classe Ação*/
class Acao{
	private:
		string codigo;
		int valor;
		double porcentagem;
	
	public:
		Acao();
		Acao(string, int, double);
		string getCodigo();
		void setCodigo(string);
		int getValor();
		void setValor(int);
		double getPorcentagem();
		void setPorcentagem(double);
};

Acao::Acao(string codigo, int valor, double porcentagem){
	this->codigo = codigo;
	this->valor = valor;
	this->porcentagem = porcentagem;
}

string Acao::getCodigo(){
	return codigo;
}

void Acao::setCodigo(string codigo){
	this->codigo = codigo;
}

int Acao::getValor(){
	return valor;
}

void Acao::setValor(int valor){
	this->valor = valor;
}

double Acao::getPorcentagem(){
	return porcentagem;
}

void Acao::setPorcentagem(double porcentagem){
	this->porcentagem = porcentagem;
}

/*Classe Mochila*/
class Mochila{
	private:
		double mochila[MAXL][MAXC];
		
	public:
		
		void resolverMochila(int, int, vector<Acao>);
		void listarResultado(int, int, vector<Acao>);
};

void Mochila::resolverMochila(int nitens, int mpeso, vector<Acao> itens){
	for(int i = 0; i <= nitens; i++){
		this->mochila[i][0] = 0;
	}
		
	for(int i = 0; i <= mpeso; i++){
		this->mochila[0][i] = 0;
	}
		
	for(int i = 1; i <= nitens; i++){
		for(int j = 1; j <= mpeso; j++){
			Acao acao = itens[i-1];
			if(acao.getValor() <= j){	
				if( acao.getPorcentagem() + this->mochila[i-1][j - acao.getValor() ] > this->mochila[i-1][j] )
					this->mochila[i][j] = acao.getPorcentagem() + this->mochila[i-1][j - acao.getValor() ];
				else
					this->mochila[i][j] = this->mochila[i-1][j]; 
			}
			else{
				this->mochila[i][j] = this->mochila[i-1][j];
			}
		}	
	}
	
	cout << this->mochila[nitens][mpeso] << endl;
}
void Mochila::listarResultado(int nitens, int mpeso, vector<Acao> itens){
	int i = nitens;
	int j = mpeso;
	vector<int> lista (nitens+1, -1);
	
	while( (i > 0) && (j > 0 )){
		
		if(this->mochila[i][j] != this->mochila[i-1][j]){
			lista[i] = 1;
			Acao acao = itens[i-1];
			j = j - acao.getValor();
			i--;
		}
		else{
			lista[i] = 0;
			i--;
		}
	}
	
	for(int i = 0; i < lista.size(); i++){
		if(lista[i] == 1)
		cout <<  i << " ";
	} 	
	cout << endl;
}

/*Classe Processamento*/
class Processamento{
	private:
		Mochila acao;
		vector<Acao> itens;
		int nitens, mpeso;
		
	public:
		void entrada();
		void saida();
};

void Processamento::entrada(){
	
	string codigo;
	int valor;
	double acoes;
	
	cin >> this->nitens >> this->mpeso;
	
	for(int i = 0; i < this->nitens; i++){
		cin >> codigo >> valor >> acoes;
		Acao item(codigo, valor, acoes);
		this->itens.push_back(item);
	}
	
	 /*this->nitens = 5;
	 this->mpeso = 100;
	
	 Acao item1("1", 10.0, 1);
	 Acao item2("2", 10.0, 10);
	 Acao item3("3", 300.0, 15);
	 Acao item4("4", 22.0, 30);
	 Acao item5("5", 280.0, 50);

	 this->itens.push_back(item1);
	 this->itens.push_back(item2);
	 this->itens.push_back(item3);
	 this->itens.push_back(item4);
	 this->itens.push_back(item5);*/
	 
}

void Processamento::saida(){
	acao.resolverMochila(this->nitens, this->mpeso, this->itens);
	acao.listarResultado(this->nitens, this->mpeso, this->itens);
}

int main() {
	
	Processamento solucao;
	solucao.entrada();
	solucao.saida();

	return 0;
}
