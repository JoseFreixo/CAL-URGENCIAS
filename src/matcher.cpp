/*
 * matcher.cpp
 */

#include "matcher.h"

using namespace std;

bool naive(string text, string pattern){
	int maxSize = text.size() - pattern.size() + 1;
	for (size_t i = 0; (int)i < maxSize; i++) {
		bool failed = false;
		for (size_t j = 0; j < pattern.size(); j++) {
			if (text.at(i + j) != pattern.at(j)) {
				failed = true;
				break;
			}
		}
		if (!failed) {
			return true;
		}
	}

	return false;
}

int solNaive(std::string input, std::string toSearch) {
	unsigned int occ = 0;
	int maxSize = input.size() - toSearch.size() + 1;
	for (size_t i = 0; (int)i < maxSize; i++) {
		bool failed = false;
		for (size_t j = 0; j < toSearch.size(); j++) {
			if (input.at(i + j) != toSearch.at(j)) {
				failed = true;
				break;
			}
		}
		if (!failed) {
			occ++;
		}
	}

	return occ;
}

int numNaive(string filename, string pattern){
	ifstream fich(filename.c_str());
	if (!fich)
	{ cout << "Erro a abrir ficheiro de leitura\n"; return 0; }

	string line1;
	int num=0;

	while (!fich.eof()) {
		getline(fich,line1);
		num+=solNaive(line1, pattern);
	}
	fich.close();
	return num;
}

void pre_kmp(string pattern, vector<int> & prefix)
{
	int m=pattern.length();
	prefix[0]=-1;
	int k=-1;
	for (int q=1; q<m; q++) {
		while (k>-1 && pattern[k+1]!=pattern[q])
			k = prefix[k];
		if (pattern[k+1]==pattern[q]) k=k+1;
		prefix[q]=k;
	}
}

bool kmp(string text, string pattern)
{
	int m=pattern.length();
	vector<int> prefix(m);
	pre_kmp(pattern, prefix);

	int n=text.length();

	int q=-1;
	for (int i=0; i<n; i++) {
		while (q>-1 && pattern[q+1]!=text[i])
			q=prefix[q];
		if (pattern[q+1]==text[i])
			q++;
		if (q==m-1) {
			return true;
		}
	}
	return false;
}

int solKmp(string text, string pattern)
{
	int num=0;
	int m=pattern.length();
	vector<int> prefix(m);
	pre_kmp(pattern, prefix);

	int n=text.length();

	int q=-1;
	for (int i=0; i<n; i++) {
		while (q>-1 && pattern[q+1]!=text[i])
			q=prefix[q];
		if (pattern[q+1]==text[i])
			q++;
		if (q==m-1) {
			num++;
			q=prefix[q];
		}
	}
	return num;
}

int numStringMatching(string filename,string toSearch)
{
	ifstream fich(filename.c_str());
	if (!fich)
	   { cout << "Erro a abrir ficheiro de leitura\n"; return 0; }

	string line1;
	int num=0;

	while (!fich.eof()) {
		getline(fich,line1);
		num+=solKmp(line1,toSearch);
	}
	fich.close();
	return num;
}


int editDistance(string pattern, string text)
{
	int n=text.length();
	vector<int> d(n+1);
	int old,neww;
	for (int j=0; j<=n; j++)
		d[j]=j;
	int m=pattern.length();
	for (int i=1; i<=m; i++) {
		old = d[0];
		d[0]=i;
		for (int j=1; j<=n; j++) {
			if (pattern[i-1]==text[j-1]) neww = old;
			else {
				neww = min(old,d[j]);
				neww = min(neww,d[j-1]);
				neww = neww +1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}

bool approximateStringMatching(string text,string toSearch)
{
	string word;
	int num=0;
	stringstream s1(text);
	while (!s1.eof()) {
		s1 >> word;
		num = editDistance(toSearch, word);
		if (num <= 2)
			return true;
	}
	return false;
}

float numApproximateStringMatching(string filename,string toSearch)
{
	ifstream fich(filename.c_str());
	if (!fich)
	{ cout << "Erro a abrir ficheiro de leitura\n"; return 0; }

	string line1, word1;
	int num=0, nwords=0;

	while (!fich.eof()) {
		getline(fich,line1);
		stringstream s1(line1);
		while (!s1.eof()) {
			s1 >> word1;
			num += editDistance(toSearch,word1);
			nwords++;
		}
	}
	fich.close();
	float res=(float)num/nwords;
	return res;
}
