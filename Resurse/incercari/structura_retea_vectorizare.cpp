#include<iostream>
using namespace std;

class Strat{
	float w;
	Strat *next;
	Strat *prev;
	
	public:
		Strat(){
			w = 0;
			next = NULL;
			prev = NULL;
		}
		
		Strat *creare(Strat *prim){
			Strat *nou, *tmp;
			int n;
			if(prim!=NULL){
				cout<<"Lista de straturi nu este vida!"<<endl;
				return prim;
			}
			cout<<"introduceti numarul de straturi dorit(straturi ascunse + stratul de iesire): ";
			cin>>n;
			
			for(int i=0;i<n;i++){
				//creare si citirea unui nod individual:
				nou = new Strat;
				if(!nou){
					cout<<"Memoria nu a putut fi alocata"<<endl;
					return NULL;
				}
				cout<<"Valoarea pentru stratul nr "<<i+1<<":";
				cin>>nou->w;
				nou->next=NULL;
				nou->prev=NULL;
				//caz particular pentru primul nod:
				if(prim==NULL){
					prim = nou;
				}
				//in cazul celorlalte noduri:
				else{
					tmp = prim;
					while(tmp->next!=NULL) tmp=tmp->next;
					tmp->next=nou;
					nou->prev=tmp;
				}
			}
			return prim;
		}
		
		void afisare(Strat *prim){
			Strat *tmp;
			tmp = prim;
			if(prim==NULL){
				cout<<"Lista de straturi este goala!"<<endl;
			}
			else{
				while(tmp!=NULL){
					cout<<tmp->w<<" -> ";
					tmp=tmp->next;
				}
				cout<<"NULL"<<endl;
			}
		}
		
		void verificare(Strat *prim){
			Strat *tmp;
			tmp = prim;
			if(prim==NULL){
				cout<<"Lista de straturi este goala!"<<endl;
			}
			else{
				cout<<"NULL <-> ";
				while(tmp->next!=NULL){
					cout<<tmp->w<<" <-> ";
					tmp=tmp->next;
				}
				cout<<tmp->w<<" <-> ";
				cout<<"NULL <-> ";
				while(tmp!=NULL){
					cout<<tmp->w<<" <-> ";
					tmp=tmp->prev;
				}
				cout<<"NULL"<<endl;
			}
		}
		
		Strat *stergere(Strat *prim){
			Strat *tmp;
			tmp = prim;
			if(prim==NULL){
				cout<<"Lista de straturi este vida!"<<endl;
				return NULL;
			}
			while(tmp!=NULL){
				tmp=tmp->next;
				delete prim;
				prim = tmp;
			}
			cout<<"Lista de straturi a fost stearsa!"<<endl;
			return NULL;
		}
};





int main(){
	Strat *prim = NULL;
	
	prim = prim->creare(prim);
	cout<<endl;
	prim->afisare(prim);
	cout<<endl;
	prim->verificare(prim);
	cout<<endl;
	
	prim = prim->stergere(prim);
	prim->afisare(prim);
	
	return 0;
}
