#include<iostream>
#include<random>
using namespace std;

class Strat {
	double** w; //weights
	double* b; //biases
	int neuroni; //stocheaza nr. de neuroni de pe stratul curent
	double** Z; //Z = w*X + b (logistic regression); A = sigmoid(Z);
	Strat* next;
	Strat* prev;

public:
	Strat() {
		w = NULL;
		b = NULL;
		neuroni = 0;
		Z = NULL;
		next = NULL;
		prev = NULL;
	}

	double sigmoid(double Z) {
		return (double)1 / (1 + exp(-Z));
	}

	Strat* creare(Strat* prim, int dim_vect_intrare) {
		Strat* nou, * tmp;
		int n;
		default_random_engine generator;
		normal_distribution<double> distribution(0, 0.01); //distributie normala(Gauss) medie=0 si dispersie=0.01
		if (prim != NULL) {
			cout << "Lista de straturi nu este vida!" << endl;
			return prim;
		}
		cout << "introduceti numarul de straturi dorit(straturi ascunse + stratul de iesire): ";
		cin >> n;

		for (int i = 0; i < n; i++) {
			//creare si citirea unui nod individual:
			nou = new Strat;
			if (!nou) {
				cout << "Memoria nu a putut fi alocata" << endl;
				return NULL;
			}
			cout << "Numarul de neuroni pentru stratul nr " << i + 1 << ":";
			cin >> nou->neuroni;
			//alocare biases
			nou->b = new double[nou->neuroni];
			//initializare biases
			for (int j = 0; j < nou->neuroni; j++) {
				nou->b[j] = 0;
			}
			//caz particular pentru primul strat(weights):
			if (prim == NULL) {
				//alocare weights
				nou->w = new double* [nou->neuroni];
				for (int j = 0; j < nou->neuroni; ++j) {
					nou->w[j] = new double[dim_vect_intrare];
				}
				//initializare weights
				for (int j = 0; j < nou->neuroni; j++) {
					for (int k = 0; k < dim_vect_intrare; k++) {
						nou->w[j][k] = distribution(generator);
					}
				}
			}
			//in cazul celorlalte straturi(weights):
			else {
				tmp = prim;
				while (tmp->next != NULL) tmp = tmp->next;
				//alocare weights
				nou->w = new double* [nou->neuroni];
				for (int j = 0; j < nou->neuroni; ++j) {
					nou->w[j] = new double[tmp->neuroni];
				}
				//initializare weights
				for (int j = 0; j < nou->neuroni; j++) {
					for (int k = 0; k < tmp->neuroni; k++) {
						nou->w[j][k] = distribution(generator);
					}
				}
			}
			nou->next = NULL;
			nou->prev = NULL;
			//caz particular pentru primul strat:
			if (prim == NULL) {
				prim = nou;
			}
			//in cazul celorlalte straturi:
			else {
				tmp = prim;
				while (tmp->next != NULL) tmp = tmp->next;
				tmp->next = nou;
				nou->prev = tmp;
			}
		}
		return prim;
	}

	void afisare(Strat* prim) {
		Strat* tmp;
		tmp = prim;
		if (prim == NULL) {
			cout << "Lista de straturi este goala!" << endl;
		}
		else {
			cout << "NULL <-> ";
			while (tmp != NULL) {
				cout << tmp->neuroni << " <-> ";
				tmp = tmp->next;
			}
			cout << "NULL" << endl;
		}
	}

	void afisare_w_b(Strat* prim, int dim_vect_intrare) {
		Strat* tmp;
		tmp = prim;
		int counter = 1;
		if (prim == NULL) {
			cout << "Lista de straturi este goala!" << endl;
		}
		else {
			while (tmp != NULL) {
				cout << "W" << counter << ":" << endl;
				//caz particular primul strat
				if (tmp == prim) {
					for (int i = 0; i < tmp->neuroni; i++) {
						for (int j = 0; j < dim_vect_intrare; j++) {
							cout << tmp->w[i][j] << " ";
						}
						cout << endl;
					}
				}
				//in cazul celorlalte straturi
				else {
					for (int i = 0; i < tmp->neuroni; i++) {
						for (int j = 0; j < tmp->prev->neuroni; j++) {
							cout << tmp->w[i][j] << " ";
						}
						cout << endl;
					}
				}
				cout << "b" << counter << ":" << endl;
				counter++;
				for (int i = 0; i < tmp->neuroni; i++) {
					cout << tmp->b[i] << endl;
				}
				cout << endl;
				tmp = tmp->next;
			}
		}
	}

	Strat* stergere(Strat* prim) {
		Strat* tmp;
		tmp = prim;
		if (prim == NULL) {
			cout << "Lista de straturi este vida!" << endl;
			return NULL;
		}
		while (tmp != NULL) {
			tmp = tmp->next;
			//stergere weights
			for (int i = 0; i < prim->neuroni; i++) {
				delete[]prim->w[i];
			}
			delete[]prim->w;
			//stergere biases
			delete[]prim->b;
			//stergere Z
			for (int i = 0; i < prim->neuroni; i++) {
				delete[]prim->Z[i];
			}
			delete[]prim->Z;
			//stergere strat
			delete prim;
			prim = tmp;
		}
		cout << "Lista de straturi a fost stearsa!" << endl;
		return NULL;
	}

	Strat* forward(Strat* prim, int n, int m, double* X) {
		/*for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << *((X + i * m) + j) << " ";
			}
			cout << endl;
		}*/ //test afisare corecta X

		Strat* tmp;
		tmp = prim;
		if (prim == NULL) {
			cout << "Lista de straturi este goala!" << endl;
		}
		else {
			while (tmp != NULL) {
				//alocare spatiu Z
				tmp->Z = new double* [tmp->neuroni];
				for (int i = 0; i < tmp->neuroni; i++) {
					tmp->Z[i] = new double[m];
				}
				//calcul Z
				for (int i = 0; i < tmp->neuroni; i++) {
					for (int j = 0; j < m; j++) {
						tmp->Z[i][j] = 0;
						for (int k = 0; k < tmp->neuroni; k++) {
							//caz particular primul strat
							if (prim == tmp) {
								tmp->Z[i][j] += tmp->w[i][k] * (*((X + k * m) + j));
							}
							//pentru restul de noduri
							else {
								tmp->Z[i][j] += tmp->w[i][k] * tmp->prev->Z[k][j];
							}
						}
					}
				}
				//calcul A
				for (int i = 0; i < tmp->neuroni; i++) {
					for (int j = 0; j < m; j++) {
						tmp->Z[i][j] = tmp->sigmoid(tmp->Z[i][j]);
					}
				}
				tmp = tmp->next;
			}
		}
		return prim;
	}

	void afisare_A(Strat* prim, int m) {
		Strat* tmp;
		tmp = prim;
		int counter = 1;
		if (prim == NULL) {
			cout << "Lista de straturi este goala!" << endl;
		}
		else {
			while (tmp != NULL) {
				cout << "Z" << counter << ":" << endl;
				for (int i = 0; i < tmp->neuroni; i++) {
					for (int j = 0; j < m; j++) {
						cout << tmp->Z[i][j] << " ";
					}
					cout << endl;
				}
				counter++;
				tmp = tmp->next;
			}
		}
	}

};

int main() {
	double X[4][10] = {
		{0,1,0,1,0,1,0,1,0,1},
		{0,0,1,1,0,0,1,1,0,0},
		{0,0,0,0,1,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,1,1},
	}; //intrarea in retea(trainig set) 784(28x28) -> pixeli, 100 -> fotografi(learning set) 
	double Y[10] = { 0,0,0,1,0,1,1,0,0,1 }; //training set expected output

	int dim_vect_intrare = sizeof(X) / sizeof(X[0]); //nr. de pixeli la intrarea in retea (784 normal, dar pentru verificare am folosit 4)
	int m = sizeof(X[0]) / sizeof(X[0][0]); //m = numarul de exemple pentru antrenarea retelei(nr de poze)

	Strat* prim = NULL;

	prim = prim->creare(prim, dim_vect_intrare);
	cout << endl;
	prim->afisare(prim);
	cout << endl;

	prim->afisare_w_b(prim, dim_vect_intrare);
	cout << endl;

	prim->forward(prim, dim_vect_intrare, m, (double*)X);
	prim->afisare_A(prim, m);
	cout << endl;

	prim = prim->stergere(prim);
	prim->afisare(prim);

	return 0;
}