///////////////////////////////////////////////
// HEADER PARA INCLUIR DIVERSAS BIBLIOTECAS ///
///////////////////////////////////////////////

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <ctype.h>
#include <climits>
#include <cmath>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <queue>

using namespace std;


//Prototipos
bool valid_word(string word);
bool valid_number_double(string number);
bool valid_number(string number);
void mensagemInicial();

//funcao auxiliar a KMP
vector<int> PrefixFunction(string S);
//algoritmo que retorna o numero de ocorrencias de um padrao numa string
unsigned int KMP(string t, string p);
//algoritmo que encontra a string com mais ocorrencias de um padrao num vetor de strings
void findMinExact(const string&s1, const vector<string> ruas);
//algoritmo que retorna o numero de diferenças entre as strings
unsigned int approximateDistance(const string& s1, const string& s2);
//algoritmo que encontra as strings mais proximas da inserida num vetor de strings
void findMinApproximate(const string&s1, const vector<string> ruas);

