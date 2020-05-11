#include<iostream>
#include<random>
using namespace std;
int intrare[784][100]; // 784(28x28) -> pixeli, 100 -> fotografi(learning set) 
int X = 4; //nr. de pixeli la intrarea in retea (784 normal, dar pentru verificare am folosit 4)

class Strat {
	double** w; //weights
	double* b; //biases
	int neuroni; //stocheaza nr. de neuroni de pe stratul curent
	Strat* next;
	Strat* prev;

public:
	Strat() {
		w = NULL;
		b = NULL;
		neuroni = 0;
		next = NULL;
		prev = NULL;
	}

	Strat* creare(Strat* prim) {
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
					nou->w[j] = new double[X];
				}
				//initializare weights
				for (int j = 0; j < nou->neuroni; j++) {
					for (int k = 0; k < X; k++) {
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

	void afisare_w(Strat* prim) {
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
						for (int j = 0; j < X; j++) {
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
			//stergere strat
			delete prim;
			prim = tmp;
		}
		cout << "Lista de straturi a fost stearsa!" << endl;
		return NULL;
	}
};

int main() {
	Strat* prim = NULL;

	prim = prim->creare(prim);
	cout << endl;
	prim->afisare(prim);
	cout << endl;

	prim->afisare_w(prim);
	cout << endl;

	prim = prim->stergere(prim);
	prim->afisare(prim);

	return 0;
}