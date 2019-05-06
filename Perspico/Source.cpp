#include <iostream>

using namespace std;

struct conf {
	int C[5][5];
	int h;
	int cost;
	conf* tata;
	conf* urm;
	conf* prec;
	conf* fiu;
};

int L(int C[5][5], int i, int j) {
	// Calculeaza L(C[i][j])
	int l[4][4] = { 0 }, k, r;
	if (j < 4) {
		for (k = j + 1; k <= 4; ++k) {
			if (C[i][k] < C[i][j]) {
				l[i][j]++;
			}
		}
	}
	if (i < 4) {
		for (r = i + i; r <= 4; ++r) {
			for (k = 1; k <= 4; ++k) {
				if (C[r][k] < C[i][j]) {
					l[i][j]++;
				}
			}
		}
	}
	return l[4][4];
}

int S(int C[5][5]) {
	int S = 0, i, j, l = 0, c = 0;
	for (i = 1; i <= 4; ++i) {
		for (j = 1; j <= 4; ++j) {
			S += L(C, i, j);
			if (C[i][j] == 16) {
				l = i;
				c = j;
			}
		}
	}
	if ((l + c) % 2) {
		S++;
	}
	return S;
}

int costC(int C[5][5]) {
	// Calculeaza costul configuratiei C: cate numere nu sunt la locul din configuratia finala
	int i, j, k, cost = 0;
	k = 1;
	for (i = 1; i <= 4; ++i) {
		for (j = 1; j <= 4; ++j) {
			if (C[i][j] != k) {
				cost++;
			}
			k++;
		}
	}
	return cost;
}

int compara_final(int C[5][5]) {
	int i, j, k;
	k = 1;
	for (i = 1; i <= 4; ++i) {
		for (j = 1; j <= 4; ++j) {
			if (C[i][j] != k) {
				return 0;
			}
			k++;
		}
	}
	return 1;
}


int main() {
	// citeste configuratia initiala
	int C0[5][5] = { 0 }, k;
	conf* inchisa, * deschisa, * ultim_i, * ultim_d, * q;
	int x[5]{ 0,0,-1,0,0 };
	int y[5]{ 0,-1,0,1,0 };

	deschisa = new conf;
	deschisa = nullptr;
	ultim_d = nullptr;

	for (int i = 1; i <= 4; ++i) {
		for (int j = 1; j <= 4; ++j) {
			cout << "C0[" << i << "][" << j << "]= ";
			cin >> C0[i][j];
		}
	}

	// deschidem lista inchisa
	inchisa = new conf;
	/*for (int i = 0; i <= 4; ++i) {
		for (int j = 0; j <= 4; ++j) {
			inchisa->C[i][j] = C0[i][j];
		}
	}*/
	memcpy(&inchisa->C, &C0, sizeof(C0));
	inchisa->h = 0;
	inchisa->cost = costC(C0);
	inchisa->tata = nullptr;
	inchisa->urm = nullptr;
	inchisa->prec = nullptr;

	ultim_i = inchisa;

	cout << "Capatul listei inchise este\n";

	for (int i = 1; i <= 4; ++i) {
		for (int j = 1; j <= 4; ++j) {
			cout << inchisa->C[i][j] << " ";
		}
		cout << '\n';
	}

	//deschidem lista deschisa
	// calculam pozitia casutei libere
	int l = 1, c = 1;

	for (int i = 1; i <= 4; ++i) {
		for (int j = 1; j <= 4; ++j) {
			if (C0[i][j] == 16) {
				l = i; c = j;
			}
		}
	}

	for (k = 1; k <= 4; ++k) {
		if ((l + x[k] <= 4) && (l+x[k]>=1) && (c+y[k]<=4) && (c+y[k]>=1)) {
			q = new conf;
			memcpy(&q->C, &ultim_i->C, sizeof(ultim_i->C));
			swap(q->C[l][c], q->C[l + x[k]][c + y[k]]);
			q->h = ultim_i->h + 1;
			q->cost = costC(q->C);
			q->tata = ultim_i;
			q->fiu = nullptr;
			if (!deschisa) {
				q->prec = nullptr;
				q->urm = nullptr;
				deschisa = q;
				ultim_d = q;
			}
			else {
				q->prec = ultim_d;
				ultim_d->urm = q;
				ultim_d = q;
			}
		}
	}

	// TODO : restul
	

	// completeaza lista inchisa cu conf cu costuri din ce in ce mai mici

	//conf finala are cost 0
	return 0;
}