# ifndef OPERATOR_H
# define OPERATOR_H
# include<vector>
# include<string>

using namespace std;
vector<string> addOperators(string, long long);
void BackTrack(string lastOps, vector<long long> lastVals,
               int currIdx, vector<string>& ans, const string num, long long target);

# endif