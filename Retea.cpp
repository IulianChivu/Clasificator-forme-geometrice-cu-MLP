#include<iostream>
#include<math.h>

using namespace std;

class Nod{
	
	public:
	float w, b;
	Nod *next; 

	Nod(){
		w=0.93; //o sa le initializez random
		b=0;
		next=NULL;
	}
	
	float sigmoid(float x){
		return (float)1 / (1 + exp(-x));
	}
};

class Retea{
	
	public:
	Nod *first_nod;
	Retea *next;
	Retea *prev; //pentru backwards prop
	
	Retea(){
		first_nod = NULL;
		next = NULL;
		prev = NULL;
	}
	
	Retea *initializare(int &v, int n, Retea *prim){
		Retea *layer_nou;
		Retea *tmp;
		Nod *nod_nou;
		Nod *nod_tmp;
		for(int i=0;i<n+1;i++){
			layer_nou = new Retea;
			
			for(int j=0;j<*(&v+i);j++){
				nod_nou = new Nod;
				if(first_nod == NULL){
					first_nod = nod_nou;
				}
				else{
					nod_tmp = first_nod;
					while(nod_tmp->next!=NULL) nod_tmp=nod_tmp->next;
					nod_tmp->next=nod_nou;
				}
			}
			
			if(prim == NULL) {
				prim = layer_nou;
			}
			else{
				tmp = prim;
				while(tmp->next!=NULL) tmp=tmp->next;
				tmp->next=layer_nou;
				layer_nou->prev=tmp;
			}
		}
		return prim;
	}
};

int main(){
	
	int n;
	int *v;
	
	cout<<"Introduceti nr. de straturi ascunse: ";
	cin>>n;
	v = new int[n+1];

	for(int i=0;i<n;i++){
		cout<<"Introduceti nr. de noduri pentru stratul "<<i+1<<": ";
		cin>>v[i];
	}
	cout<<"Introduceti nr. nodurilor de iesire: ";
	cin>>v[n];
		
	cout<<"\nStructura retea: intrare -> ";
	for(int i=0;i<n+1;i++){
		cout<<v[i]<<" -> ";
	}
	cout<<"Iesire"<<endl;
	
	Retea *r = NULL;
	r = r->initializare(*v,n,r);
	

	return 0;
}
