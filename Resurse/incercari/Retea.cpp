#include<iostream>
using namespace std;
int *dim = NULL; //vector care contine dimensiunile fiecarui strat + dimensiunea vectorului de intrare
int c = 0; //contor pentru vectorul de dimensiuni

class Nod{
	float w;
	Nod *next;
	
	public:
		Nod(){
			w = 0;
			next = NULL;
		}
		
		Nod *creare(Nod *prim){
			Nod *nou, *tmp;
			int n;
			if(prim!=NULL){
				cout<<"Lista de noduri nu este vida!"<<endl;
				return prim;
			}
			cout<<"introduceti numarul de noduri dorit pe acest strat: ";
			cin>>n;
			
			for(int i=0;i<n;i++){
				//creare si citirea unui nod individual:
				nou = new Nod;
				if(!nou){
					cout<<"Memoria nu a putut fi alocata"<<endl;
					return NULL;
				}
				cout<<"Valoarea pentru nodul nr "<<i+1<<":";
				cin>>nou->w;
				nou->next=NULL;
				//caz particular pentru primul nod:
				if(prim==NULL){
					prim = nou;
				}
				//in cazul celorlalte noduri:
				else{
					tmp = prim;
					while(tmp->next!=NULL) tmp=tmp->next;
					tmp->next=nou;
				}
			}
			return prim;
		}
		
		void afisare(Nod *prim){
			Nod *tmp;
			tmp = prim;
			if(prim==NULL){
				cout<<"Lista de noduri este goala!"<<endl;
			}
			else{
				while(tmp!=NULL){
					cout<<tmp->w<<" -> ";
					tmp=tmp->next;
				}
				cout<<"NULL"<<endl;
			}
		}
		
		Nod *stergere(Nod *prim){
			Nod *tmp;
			tmp = prim;
			if(prim==NULL){
				cout<<"Lista de noduri este vida!"<<endl;
				return NULL;
			}
			while(tmp!=NULL){
				tmp=tmp->next;
				delete prim;
				prim = tmp;
			}
			cout<<"Lista de noduri a fost stearsa!"<<endl;
			return NULL;
		}
};

class Retea{
	Nod *primul_nod; //primul nod din fiecare strat
	Retea *next;
	
	public:
		Retea(){
			primul_nod=NULL;
			next=NULL;
		}
		
		Retea *creare(Retea *prim){
			Retea *nou, *tmp;
			int n;
			if(prim!=NULL){
				cout<<"Lista de straturi nu este vida!"<<endl;
				return prim;
			}
			
			cout<<"Introduceti numarul de straturi (straturi ascunse + strat de iesire): ";
			cin>>n;
			dim = new int[n+1];  
			
			for(int i=0;i<n;i++){
				//creare si citirea unui nod individual:
				nou = new Retea;
				if(!nou){
					cout<<"Memoria nu a putut fi alocata"<<endl;
					return NULL;
				}
				if(i+1==n) cout<<"Stratul nr "<<i+1<<" (stratul de iesire): ";
				else cout<<"Stratul nr "<<i+1<<": ";
				nou->primul_nod = nou->primul_nod->creare(nou->primul_nod); //initializarea nodurilor de pe strtul curent
				nou->next=NULL;
				//caz particular pentru primul nod:
				if(prim==NULL){
					prim = nou;
				}
				//in cazul celorlalte noduri:
				else{
					tmp = prim;
					while(tmp->next!=NULL) tmp=tmp->next;
					tmp->next=nou;
				}
			}
			return prim;
		}
		
		void afisare(Retea *prim){
			Retea *tmp;
			tmp = prim;
			if(prim==NULL){
				cout<<"Lista de straturi este goala!"<<endl;
			}
			else{
				cout<<"Intrare"<<endl;
				cout<<"   |   "<<endl;
				while(tmp!=NULL){
					tmp->primul_nod->afisare(tmp->primul_nod);
					cout<<"   |   "<<endl;
					tmp=tmp->next;
				}
				cout<<" NULL"<<endl;
			}
		}
		
		Retea *stergere(Retea *prim){
			Retea *tmp;
			tmp = prim;
			if(prim==NULL){
				cout<<"Lista de straturi este vida!"<<endl;
				return NULL;
			}
			while(tmp!=NULL){
				tmp=tmp->next;
				prim->primul_nod = prim->primul_nod->stergere(prim->primul_nod);
				delete prim;
				prim = tmp;
			}
			cout<<"Lista de straturi a fost stearsa!"<<endl;
			return NULL;
		}
		
};


int main(){
	
	Retea *prim = NULL;
	
	prim = prim->creare(prim);
	cout<<endl;
	prim->afisare(prim);
	cout<<endl;
	
	prim = prim->stergere(prim);
	prim->afisare(prim);
	
	return 0;
}

