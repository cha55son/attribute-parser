#pragma once
#include <string>
#include <vector>

using namespace std;

string ltrim(const string input);
string ltrim(const string input, const string toRemove);
string rtrim(const string input);
string rtrim(const string input, const string toRemove);
string trim(const string input);
string trim(const string input, const string toRemove);
vector<string> split(const string input, const char delimiter);