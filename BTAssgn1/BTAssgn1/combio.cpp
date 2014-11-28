#include "stdafx.h"
#include "combio.h"


combio::combio()
{
}


combio::~combio()
{
}

int combio::ntide(int length, std::string filename)
{
	int a = rand() * 4 / RAND_MAX;
	std::string ntide;
	std::ofstream dna(filename);
	if (dna.is_open())
	{
		for (int i = 0; i <= length; i++)
		{
			switch (a)
			{
			case 0:
				ntide += "A";
				break;
			case 1:
				ntide += "T";
				break;
			case 2:
				ntide += "G";
				break;
			case 3:
				ntide += "C";
				break;
			default:
				break;
			}
			a = rand() * 4 / RAND_MAX;
		}
		dna << ntide;
		dna.close();
		return 0;
	}
	else
	{
		std::cout << "Couldn't Open File \n";
		return -1;
	}
}

int combio::dna2num(char a)
{
	int x;
	if (a == 'A')x = 0;
	if (a == 'T')x = 1;
	if (a == 'G')x = 2;
	if (a == 'C')x = 3;
	return x;
}

std::vector<std::vector<int>> combio::maketm(std::string pattern)
{
	std::vector<std::vector<int>> tm(4, std::vector<int>(pattern.length()));
	int X = 0, hitcount = 0;
	tm[dna2num(pattern[0])][0] = 1;
	//X = tm[][0];
	for (int i = 1; i < pattern.length(); i++)
	{
		for (int c = 0; c <= 3; c++)
		{
			tm[c][i] = tm[c][X];
		}
		tm[dna2num(pattern[i])][i] = i + 1;
		X = tm[dna2num(pattern[i])][X];
		hitcount += 1;
	}
	std::cout << "tm hitcount = " << hitcount << "\n";
	return tm;
}

int combio::kmp(std::string patternfile, std::string dnafile, std::string resultfile)
{
	std::ifstream pattern(patternfile), dna(dnafile);
	std::ofstream result(resultfile);
	std::string needle, haystack;
	std::vector < std::vector<int>> tm;
	int location, hitcount = 0;
	if (pattern.is_open()&dna.is_open()&result.is_open())
	{
		std::getline(pattern, needle);
		std::getline(dna, haystack);
		tm = maketm(needle);
		for (int i = 0,X=0; i < haystack.length(); i++)
		{
			X = tm[dna2num(haystack[i])][X];
			if (X == needle.length())
			{
				X = 0;
				location = i + 1 - needle.length();
				result << location << ",";
			}
			hitcount += 1;
		}
	}
	else
	{
		std::cout << "Couldn't open file \n";
		return -1;
	}
	std::cout << hitcount << "\n";
	return 0;
}

int combio::naiveSearch(std::string patternfile, std::string dnafile, std::string resultfile)
{
	std::ifstream pattern(patternfile), dna(dnafile);
	std::ofstream result(resultfile);
	std::string needle, haystack;
	int flag = 0;
	int hitcount = 0;
	if (pattern.is_open()&dna.is_open()&result.is_open())
	{
		std::getline(pattern, needle);
		std::getline(dna, haystack);
		for (int j = 0; j < haystack.length(); j++)
		{
			flag = 1;
			for (int i = 0; i < needle.length(); i++)
			{
				hitcount += 1;
				if (needle[i] != haystack[j + i])
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				result << j << ",";
			}
		}
	}
	else
	{
		std::cout << "Couldn't Open File \n";
		return -1;
	}
	std::cout << hitcount << "\n";
	return 0;
}

int combio::michaelisMenten(int InitialEnzymeConcentration, int InitialSubstrateConcentration, float k1, float k2, float k3, int iterations)
{
	float alpha1, alpha2, alpha3, alpha, p1, p2, p3, V;
	double r1, r2, tau, ttime;
	int enz, sub, ensub, P;
	/*std::vector<int> Enzyme(1000,0);
	std::vector<int> Protein(1000, 0);
	std::vector<float> Time(1000, 0);*/
	for (int i = 1; i <= iterations; i++)
	{
		std::string filename("sub"+std::to_string(InitialSubstrateConcentration)+"iter" + std::to_string(i) + ".txt");
		std::ofstream myfile(filename);
		ttime = 0;
		enz = InitialEnzymeConcentration;
		sub = InitialSubstrateConcentration;
		ensub = 0;
		P = 0;
		while (P<InitialSubstrateConcentration-1)
		{
			r1 = 1.0*rand() / RAND_MAX;
			r2 = 1.0*rand() / RAND_MAX;
			alpha1 = k1*enz*sub;
			alpha2 = k2*ensub;
			alpha3 = k3*ensub;
			alpha = alpha1 + alpha2 + alpha3;
			tau = -log(r1) / alpha;
			/*if (tau>1)
			{
				std::cout << "Probs";
			}*/
			p1 = alpha1 / alpha;
			p2 = alpha2 / alpha;
			p3 = alpha3 / alpha;
			if (r2 < p1)
			{
				enz = enz - 1;
				sub = sub - 1;
				ensub = ensub + 1;
			}
			if (p1<r2 && r2<p1+p2)
			{
				enz = enz + 1;
				sub = sub + 1;
				ensub = ensub - 1;
			}
			if (p1+p2<r2)
			{
				ensub = ensub - 1;
				enz = enz + 1;
				P = P + 1;
			}
			ttime = ttime + tau;
			V = k3*ensub;
			myfile << ttime << " ";
			myfile << enz << " ";
			myfile << sub << " ";
			myfile << ensub << " ";
			myfile << P << " ";
			myfile << V << "\n";
		}
		myfile.close();
	}
	return 0;
}
