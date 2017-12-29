#ifndef QUINE_MCLUSKY
#define QUINE_MCLUSKY

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>

using namespace std;

class DFF
{

  public:
    const static map<int, pair<int, int>> extendedtruthtable;
    const static vector<char> VAR;
    const static map<pair<int, int>, int> excitationtable;
    void ToT();
    void ToJK();
    void ToSR();
    
};

class TFF
{
public:
  const static map<int, pair<int, int>> extendedtruthtable;
  const static vector<char> VAR;
  const static map<pair<int, int>, int> excitationtable;
  void ToD();
  void ToJK();
  void ToSR();
};

class SRFF
{
  public:
    const static map<pair<int, int>, pair<int, int>> excitationtable;
    const static map<int, pair<int, int>> extendedtruthtable;
    const static vector<char> VAR;
    void ToD();
    void ToJK();
    void ToT();
};

class JKFF
{
  public:
    const static map<pair<int, int>, pair<int, int>> excitationtable;
    const static map<int, pair<int, int>> extendedtruthtable;
    const static vector<char> VAR;
    void ToSR();
    void ToD();
    void ToT();
};

void DecimalToBinary();
int OneCounter(int *binary, int NumberOfDigit);
int Combination(int n, int ColumnNo, int k);
int IsPowerOfTwo(int n);
int IsDontCare(int MT);
void ShowResult();
void Recursion_For_Loop(int m);
int QuineMc(vector<int>, vector<int>, vector<char>);
void freeallmem(vector<int *>, vector<int **>, vector<int ***>, vector<int ****>);
void printTableSingle(string message, auto excitationtable, auto truthtable, auto variableset1, auto variableset2);
void printTableDouble(string message, auto excitationtable, auto truthtable, auto variableset1, auto variableset2);
#endif
