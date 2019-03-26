# include<iostream>
# include<string>
# include<vector>
# include "Operator.h"
using namespace std;

int main()
{
	string s;
	long long target;
	cin>>s>>target;
	vector<string> res = addOperators(s, target);
	for(string str: res) cout<<str<<endl;
	cout<<"There's altogether "<<res.size()<<" ways to get "<<target<<" from "<<s<<endl;
	return 0;
}
