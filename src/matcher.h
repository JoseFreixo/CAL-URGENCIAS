#ifndef MATCHER_H_
#define MATCHER_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

bool naive(string text, string pattern);

int solNaive(string input, string toSearch);

int numNaive(string filename, string pattern);

void pre_kmp(string pattern, vector<int> & prefix);

bool kmp(string text, string pattern);

int solKmp(string text, string pattern);

int numStringMatching(string filename,string toSearch);

int editDistance(string pattern, string text);

bool approximateStringMatching(string text,string toSearch);

float numApproximateStringMatching(string filename,string toSearch);

#endif //MATCHER_H_
