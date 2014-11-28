// BTAssgn1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	combio wf;
	//wf.kmp("pattern.txt","DNA_100mil.txt","result_100mil.txt");
	//wf.naiveSearch("pattern.txt", "DNA_1bill.txt", "NaiveResult_1bill.txt");
	//wf.ntide(1e9,"DNA_1bill.txt");
	wf.michaelisMenten(100, 2000, 0.001, 0.1, 0.1, 10);
	getchar();
	return 0;
}

