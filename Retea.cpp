#include<iostream>
#include <random>
using namespace std;

class Retea{
	private:
		float **w, **b;
		int *dim_layer;
	public:
		Retea(int *dim_layer){ //dim_layer = vector a carui dimensiune reprezinta nr. de straturi, iar fiecare valoare din acesta reprezinta nr de neuroni de pe stratul respectiv
			this->dim_layer = dim_layer;
			//alocare spatiu weights and biases:
			for(int i=1;i<*dim_layer;i++){
				w = new float*[dim_layer[i]]; //nr. de linii
				for(int l=0;l<i;l++) w[l] = new float[dim_layer[i-1]];//nr. de coloane
				
				b = new float*[dim_layer[i]]; //nr. de linii
				for(int l=0;l<i;l++) b[l] = new float[1];//nr. de coloane
			}
			//initializare weights and biases:
			for(int i=1;i<*dim_layer;i++){
				for(int l=0;l<dim_layer[i];l++){
					for(int j=0;j<dim_layer[i-1];j++){
						w[l][j] = ((-1) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1-(-1)))))*0.01;
						b[l][1] = 0;
					}
				}
			}
		}

		~Retea(){
			//cout<<"dest"<<endl;
		}

		void coutwandb(){
			for(int i=1;i<*dim_layer;i++){
				for(int l=0;l<dim_layer[i];l++){
					for(int j=0;j<dim_layer[i-1];j++){
						cout<<w[l][j]<<" ";
					}
					cout<<endl;
				}
			}
			
			for(int i=1;i<*dim_layer;i++){
				for(int l=0;l<dim_layer[i];l++){
					for(int j=0;j<1;j++){
						cout<<b[l][j]<<" ";
					}
					cout<<endl;
				}
			}
		}
};



int main(){
	int *layer;
	int nr;
	cout<<"introduceti nr de straturi ascunse nr straturi ascunse:";
	cin>>nr;
	layer = new int[nr];
	
	for(int i=0; i<nr; i++){
		cout<<"nr neuroni strat "<<i+1<<":";
		cin>>layer[i];
	}

	Retea r1(layer);
	r1.coutwandb();
	

	return 0;
}

