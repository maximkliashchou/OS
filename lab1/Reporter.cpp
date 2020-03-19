#include <Windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "..\Main\Employee.h"

using namespace std;

int main(int argc, char* argv[]) {
	string fileName = argv[0];
	string reportName = argv[1];
	string bfPrice = argv[2];

	ifstream in(fileName, ios::binary);
	ofstream cout(reportName);
	int price = stoi(bfPrice);
	int n;
	in.read((char*)&n, sizeof(n));
	
	cout << "File report «" << fileName << "»" << endl;

	for (int i = 0; i < n; i++) {
		employee myEmployee;
		in.read((char*)&myEmployee, sizeof(employee));
		cout << "Num: " << myEmployee.num << " Name: " << myEmployee.name << " Hours: " << myEmployee.hours <<
			" Salary: " << myEmployee.hours * price << endl;
	}
}
