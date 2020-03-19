#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "../Main/Employee.h"

using namespace std;

int main(int argc, char *argv[]){
	string fileName = argv[0];
	string ff = argv[1]; 
	
	ofstream out(fileName, ios::binary);

	int n = stoi(ff);
	out.write((char*)&n, sizeof(n));
	for (int i = 0; i < n; i++) {
		employee myEmployee;
		myEmployee.num = i;
		cout << "Enter name: ";
		cin >> myEmployee.name;
		cout << "Enter hours: ";
		cin >> myEmployee.hours;
		cout << endl;
		out.write((char*)&myEmployee, sizeof(employee));
	}
	out.close();
}
