#include<Windows.h>
#include<iomanip>
#include<stdio.h>
#include<iostream>
#include<vector>

using namespace std;

typedef struct {
	double* a;
	int n, mx, mn;
	double average;
}params;

void printMinAndMax(params* params) {
	cout << "Min; Max:\n" << params->mn << "; " << params->mx << endl;
}

void printAverage(params* params) {
	cout << fixed << setprecision(5) << "Average:\n" << params->average << endl;
}


DWORD WINAPI min_maxFunc(LPVOID myParams) {
	params* v = (params*)myParams;
	for (int j = 0; j < v->n; j++) {
		v->mn = min(v->mn, v->a[j]);
		v->mx = max(v->mx, v->a[j]);
		Sleep(7);
	}
	printMinAndMax(v);
	return 0;
}

DWORD WINAPI averageFunc(LPVOID myParams) {
	params* v = (params*)myParams;
	int sum = 0;
	for (int j = 0; j < v->n; j++) {
		sum += v->a[j];
		Sleep(12);
	}
	v->average = 1.0 * sum / v->n;
	printAverage(v);
	return 0;
}

void readArray(params &params) {
	cout << "Enter number of elements:\n";
	cin >> params.n;
	cout << "Enter elements:\n";

	params.a = new double[params.n];

	for (int i = 0; i < params.n; i++) {
		cin >> params.a[i];
	}
}

void replaceMinAndMaxWithAverage(params params) {
	for (int i = 0; i < params.n; i++) {
		if (params.a[i] == params.mn || params.a[i] == params.mx) {
			params.a[i] = params.average;
		}
	}
}

void printArray(params params) {
	cout << "Array:\n";
	for (int i = 0; i < params.n; i++) {
		cout << params.a[i] << ' ';
	}
	cout << endl;
}

void init(params &myParams) {
	myParams.mn = INT_MAX - 1;
	myParams.mx = INT_MIN + 1;
	myParams.average = 0;
}

int main() {
	HANDLE hThread[2];
	DWORD dwThread[2];

	params myParams;
	init(myParams);

	readArray(myParams);
				
	hThread[0] = CreateThread(NULL, 0, min_maxFunc, (void*)&myParams, 0, &dwThread[0]);

	hThread[1] = CreateThread(NULL, 0, averageFunc, (void*)&myParams, 0, &dwThread[1]);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	replaceMinAndMaxWithAverage(myParams);
	printArray(myParams);
}
