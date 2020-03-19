#include<Windows.h>
#include<iomanip>
#include<stdio.h>
#include<iostream>
#include<vector>

using namespace std;

int n;
int mn = INT_MAX - 1, mx = INT_MIN + 1;
double average = 0;

DWORD WINAPI min_maxFunc(LPVOID a) {
	int* b = static_cast<int*>(a);
	int m = b[0];
	for (int j = 1; j <= m; j++) {
		mn = min(mn, b[j]);
		Sleep(7);
		mx = max(mx, b[j]);
		Sleep(7);
	}
	return 0;
}

DWORD WINAPI averageFunc(LPVOID a) {
	int* b = static_cast<int*>(a);
	int m = b[0];
	int sum = 0;
	for (int j = 1; j <= m; j++) {
		sum += b[j];
		Sleep(12);
	}
	average = sum / m;
	return 0;
}

int main() {
	HANDLE hThreadMinMax;
	DWORD IDThreadMinMax;

	HANDLE hThreadAverage;
	DWORD IDThreadAverage;
	cout << "Enter number of elements:\n";
	cin >> n;
	cout << "Enter elements:\n";
	vector<int> v(n);
	int* a = new int[n + 1];
	a[0] = n;
	for (int i = 1; i <= n; i++) cin >> a[i];		

	hThreadMinMax = CreateThread(NULL, 0, min_maxFunc, (void*)a, 0, &IDThreadMinMax);
	WaitForSingleObject(hThreadMinMax, INFINITE);
	TerminateThread(hThreadMinMax, 0);
	CloseHandle(hThreadMinMax);
	cout << "Min; Max: " << mn << "; " << mx << endl;

	hThreadAverage = CreateThread(NULL, 0, averageFunc, (void*)a, 0, &IDThreadAverage);
	WaitForSingleObject(hThreadAverage, INFINITE);
	TerminateThread(hThreadAverage, 0);
	CloseHandle(hThreadAverage);
	cout << fixed << setprecision(5) << "Average: " << average << endl;
	


}
