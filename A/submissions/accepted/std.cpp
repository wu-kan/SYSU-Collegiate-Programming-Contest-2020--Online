#include <bits/stdc++.h>
using namespace std;
int main()
{
	string s("SYSU");
	sort(s.begin(), s.end());
	int n;
	for (scanf("%d", &n); --n;)
		next_permutation(s.begin(), s.end());
	printf("%s", s.c_str());
}