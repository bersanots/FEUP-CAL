/*
 * Strings.h
 */

#ifndef STRINGS_CPP_
#define STRINGS_CPP_

#include "Includes.h"


vector<int> PrefixFunction(string S) {
	vector<int> p(S.size());
	int j = 0;
	for (int i = 1; i < (int)S.size(); i++) {
		while (j > 0 && S[j] != S[i])
			j = p[j-1];

		if (S[j] == S[i])
			j++;
		p[i] = j;
	}
	return p;
}

unsigned int KMP(string t, string p)
{
	unsigned int n = t.length(), m = p.length(), q=0, res=0;
	vector<int> pi = PrefixFunction(p);

	for(unsigned int i=0; i<n; i++){
		while(q>0 && p[q]!=t[i])
			q=pi[q-1];
		if(p[q]==t[i])
			q++;
		if(q==m){
			res++;
			q=pi[q-1];
		}
	}
	return res;
}

void findMinExact(const string&s1, const vector<string> ruas){
	//elemento com mais ocorrencias do padrao
	pair<unsigned int,string> st;

	for(unsigned int i=0; i<ruas.size(); i++)
		if(ruas.at(i).length()>=s1.length() && KMP(ruas.at(i),s1)>st.first)
			st={KMP(ruas.at(i),s1),ruas.at(i)};

	if(st.second!="")
		cout << "Sera que quis dizer: "<< st.second << " ?" << endl;
}

unsigned int approximateDistance(const string& s1, const string& s2)
{
	const size_t len1 = s1.size();
	const size_t len2 = s2.size();
	vector<vector<unsigned int> > d(len1 + 1, vector<unsigned int>(len2 + 1));

	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

	for(unsigned int i = 1; i <= len1; ++i)
		for(unsigned int j = 1; j <= len2; ++j)
			d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1)});

	return d[len1][len2];
}

void findMinApproximate(const string&s1, const vector<string> ruas){
	//priority queue ordenada pelo menor elemento
	priority_queue<pair<int,string >, vector<pair<int,string> >, std::greater<pair<int,string> > > pq;

	for(unsigned int i=0; i<ruas.size(); i++){
		pq.emplace(approximateDistance(s1, ruas.at(i)), ruas.at(i));
	}

	const auto& pair = pq.top();
	cout<<"A rua com nome mais proximo e: "<< pair.second<<endl;
	pq.pop();

	const auto& pair2 = pq.top();
	cout<<"A segunda rua com nome mais proximo e: "<< pair2.second<<endl;
	pq.pop();

	const auto& pair3 = pq.top();
	cout<<"A terceira rua com nome mais proximo e: "<< pair3.second<<endl;
	pq.pop();
}



#endif /* STRINGS_CPP_ */
