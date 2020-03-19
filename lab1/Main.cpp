#include <Windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "Employee.h"

using namespace std;

void startProcess(string filePath, string commandArgs) {
	STARTUPINFO cif;
	PROCESS_INFORMATION pid;
	ZeroMemory(&cif, sizeof(cif));
	if (!CreateProcess(filePath.c_str(), const_cast<LPSTR>(commandArgs.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &cif, &pid)) {
		throw exception("Can't open process!");
	}
	WaitForSingleObject(pid.hProcess, INFINITE);

	CloseHandle(pid.hProcess);
	CloseHandle(pid.hThread);
}

int main() {
	cout << "Enter file name: ";
	string bfFileName, bfCount, bfReportName, bfPrice;
	getline(cin, bfFileName);

	cout << "Enter count of notes: ";
	getline(cin, bfCount);
	
	try{
		startProcess("C:\\Users\\mmkle\\source\\repos\\os_lab1\\Debug\\Creator.exe", bfFileName + " " + bfCount);
	}
	catch (exception ex) {
		cerr << ex.what();
		return 0;
	}
	
	ifstream in(bfFileName);
	string s;
	while (getline(in, s)) {
		cout << s << endl;
	}

	cout << "Enter report name: ";
	getline(cin, bfReportName);

	cout << "Enter price for hour: ";
	getline(cin, bfPrice);
	try {
		startProcess("C:\\Users\\mmkle\\source\\repos\\os_lab1\\Debug\\Reporter.exe", bfFileName + " " + bfReportName + " " + bfPrice);
	}
	catch (exception ex){
		cerr << ex.what();
		return 0;
	}
}
