#pragma once
class combio
{
public:
	combio();
	~combio();
	int ntide(int length, std::string filename);
	int kmp(std::string patternfile, std::string dnafile, std::string resultfile);
	int naiveSearch(std::string patternfile, std::string dnafile, std::string resultfile);
	std::vector<std::vector<int>> combio::maketm(std::string pattern);
	int dna2num(char a);
	int michaelisMenten(int InitialEnzymeConcentration, int InitialSubstrateConcentration, float k1, float k2, float k3, int iterations);
};

