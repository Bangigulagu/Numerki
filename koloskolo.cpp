#include "pch.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;
struct Pair {
	int a, b;
};
struct PairsMatrix {
	int cols, rows;
	Pair **data;
};
void initPairsMatrix(PairsMatrix &M, int n, int k) {
	M.rows = n;
	M.cols = k;
	M.data = new Pair*[M.rows];
	for (int i = 0; i < M.rows; i++) {
		M.data[i] = new Pair[M.cols];
	}
}
void deletePairsMatrix(PairsMatrix &M) {
	for (int i = 0; i < M.rows; i++) {
		delete[] M.data[i];
		M.data[i] = NULL;
	}
	delete[] M.data;
	M.data = NULL;
}
void readPair(istream &source, Pair &p) {
	source >> p.a >> p.b;
}

void readPairsMatrix(istream &source, PairsMatrix &M) {
	for (int i = 0; i < M.rows; i++)
		for (int j = 0; j < M.cols; j++) {
			readPair(source, M.data[i][j]);
		}

}
void duplicateFirstRow(PairsMatrix const &in, PairsMatrix &out) {
	initPairsMatrix(out, in.rows+1, in.cols);
	int r=0, c;
	for (c = 0; c < in.cols; c++) {
		out.data[r][c] = in.data[r][c];
	}
	for (r = 0; r < in.rows; r++) {
		for (c = 0; c < in.cols; c++) {
			out.data[r+1][c] = in.data[r][c];
		}
	}

}
bool ppCompare(Pair const * const &l, Pair const * const &r) {
	return l[0].a + l[0].b > r[0].a + r[0].b;
}
void printPair(ostream &os, Pair const &p) {
	os << '(' << setw(3) << p.a << ", " << setw(3) << p.b << ')';
}

void printMatrix(ostream &os, PairsMatrix const &pm) {
	for (int i = 0; i < pm.rows; i++) {
		for (int j = 0; j < pm.cols; j++) {
			printPair(os, pm.data[i][j]);
			os << ' ';
		}
		os << '\n';
	}
}
int main()
{
	char path[261];
	cin.getline(path, 260);
	ifstream ifs(path);
	if (not ifs) {
		cerr << "Fail.\n";
		exit(1);
	}
	int n, k;
	ifs >> n >> k;
	PairsMatrix A;
	initPairsMatrix(A, n, k);
	readPairsMatrix(ifs, A);
	PairsMatrix B;
	duplicateFirstRow(A, B);
	for (int i = 0; i < n+1; i++) {
		for (int j = 0; j < k; j+=2) {
			int tmpa, tmpb;
			tmpa = B.data[i][j].b - B.data[i][j].a;
			tmpb = B.data[i][j].a + B.data[i][j].b;
			B.data[i][j].a = tmpa;
			B.data[i][j].b = tmpb;
		}
	}
	sort(B.data, B.data + B.rows, ppCompare);
	printMatrix(cout, B);
	//printMatrix(cout, A);
	deletePairsMatrix(B);
	deletePairsMatrix(A);

	return 0;
} /*
int main() {
	char path[261];
	cin >> path;
	ifstream ifs(path);
	if (not ifs) {
		cerr << "Fail.\n";
		exit(1);
	}
	int n, k;
	ifs >> n >> k;
	cout << "n=" << n << " k="<<k;
} */