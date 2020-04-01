#include<iostream>

using namespace std;

class Nod{
	

	public:
	float w, b;
	Nod *next; //pointer spre urmatorul layer de noduri
	Nod *prev; //pointer spre stratul anterior(Pentru backwards prop)

	Nod(){
		w=0.93; //o sa le initializez random
		b=0;
		next=NULL;
		prev=NULL;
	}

};

class Retea{
	int n; //nr straturi ascunse
	int *v; //vector cu dim fiecarui strat de noduri
	Nod *start; //primul nod din retea
	
	public:
	Retea(){
		cout<<"Introduceti nr. de straturi ascunse: ";
		cin>>n;
		v = new int[n+1];

		for(int i=0;i<n;i++){
			cout<<"Introduceti nr. de noduri pentru stratul "<<i+1<<": ";
			cin>>v[i];
		}
		cout<<"Introduceti nr. nodurilor de iesire: ";
		cin>>v[n];
		
		cout<<"\nStructura retea: strat intrare -> ";
		for(int i=0;i<n+1;i++){
			cout<<v[i]<<" -> ";
		}
		cout<<"Iesire"<<endl;
		
		start = NULL;
	}

	void initializare(){
		Nod *nod_nou, *tmp;
		for(int i=0;i<n+1;i++){
			nod_nou = new Nod[v[i]];
			if(start == NULL) start = nod_nou;
			else{
				tmp = start;
				while(tmp->next!=NULL) tmp=tmp->next;
				tmp->next=nod_nou;
				nod_nou->prev=tmp;
			}
		}
	}

	void verificare_afisare(){
		Nod *tmp=start;
		while(tmp!=NULL){
			for(int i=0;i<n+1;i++){		
			cout<<"ponderi stratul nr "<<i+1<<": ";	
				for(int j=0;j<v[i];j++){
					cout<<tmp[j].w<<" ";
				}
				tmp=tmp->next;
				cout<<endl;
			}
		}
	}

	~Retea(){
		delete []v;
	}
};





int main(){
	
	cout<<endl;
	Retea r;
	r.initializare();
	cout<<endl;
	r.verificare_afisare();

	return 0;
}


