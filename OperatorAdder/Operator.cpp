# include<string>
# include<vector>
# include "Operator.h"
using namespace std;
vector<string> addOperators(string num, long long target) {
        vector<string> ans;
        if(num.size() == 0) return ans;
        vector<long long> lastVals;
        BackTrack("", lastVals, 1, ans, num, (long long)target);
        return ans;
}

void BackTrack(string lastOps, vector<long long> lastVals,
                  int currIdx, vector<string>& ans, const string num, long long target)
   {
       if(currIdx == num.size())
       {
           if(lastVals.back() == target){
               string res = "";
               res += num[0];
               for(int i=0;i<lastOps.size();i++)
               {
                   if(lastOps[i] == 'n') res += num[i+1];
                   else {res += lastOps[i]; res += num[i+1];}
               }
               ans.push_back(res);
            }
           return;
       } 
       if(currIdx==1)
       {
           long long firstVal = (long long)(num[0]-'0');
           long long secondVal = (long long)(num[1]-'0');
           lastVals.push_back(firstVal+secondVal);
           BackTrack(lastOps+'+', lastVals, currIdx+1, ans, num, target);
           lastVals.pop_back();
           
           lastVals.push_back(firstVal-secondVal);
           BackTrack(lastOps+'-', lastVals, currIdx+1, ans, num, target);
           lastVals.pop_back();
           
           lastVals.push_back(firstVal*secondVal);
           BackTrack(lastOps+'*', lastVals, currIdx+1, ans, num, target);
           lastVals.pop_back();
           
           if(firstVal!=0LL){
               lastVals.push_back(firstVal*10LL + secondVal);
               BackTrack(lastOps+'n', lastVals, currIdx+1, ans, num, target);
               lastVals.pop_back();
           }
           return;
       }
       long long toAdd = (long long) (num[currIdx]-'0');
       
       lastVals.push_back(lastVals.back()+toAdd);
       BackTrack(lastOps+'+', lastVals, currIdx+1, ans, num, target);
       lastVals.pop_back();
       
       lastVals.push_back(lastVals.back()-toAdd);
       BackTrack(lastOps+'-', lastVals, currIdx+1, ans, num, target);
       lastVals.pop_back();
       
       int closestIdx = lastOps.size()-1;
       for(;closestIdx>=0;closestIdx--) // find the closest '+' or '-'
           if(lastOps[closestIdx]=='+' || lastOps[closestIdx]=='-') break;
       if(closestIdx<0)
       {
           lastVals.push_back(lastVals.back()*toAdd);
           BackTrack(lastOps+'*', lastVals, currIdx+1, ans, num, target);
           lastVals.pop_back();
       }
       else
       {
           long long x;
           long long left;
           if(lastOps[closestIdx]=='-')
           {
               if(closestIdx == 0) left = (long long)(num[0]-'0');
               else left = lastVals[closestIdx-1];
               x = left - lastVals.back();
               lastVals.push_back(left-x*toAdd);
               BackTrack(lastOps+'*', lastVals, currIdx+1, ans, num, target);
               lastVals.pop_back();
           }
           else
           {
               if(closestIdx == 0) left = (long long)(num[0]-'0');
               else left = lastVals[closestIdx-1];
               x = lastVals.back() - left;
               lastVals.push_back(left+x*toAdd);
               BackTrack(lastOps+'*', lastVals, currIdx+1, ans, num, target);
               lastVals.pop_back();
           }
       }
       
       if(lastOps.back()!='n' && num[currIdx-1]=='0') return;
       
       int closestIdx_ = lastOps.size()-1;
       for(;closestIdx_>=0;closestIdx_--) // find the closest '*' or '-' or '+'
           if(lastOps[closestIdx_]!='n') break;
       if(closestIdx_<0)
       {
           lastVals.push_back(lastVals.back()*10LL+toAdd);
           BackTrack(lastOps+'n', lastVals, currIdx+1, ans, num, target);
           lastVals.pop_back();
           return;
       }
       if(closestIdx_==0)
       {
           long long left = (long long)(num[0]-'0');
           if(lastOps[closestIdx_] == '*')
           {
               if(left == 0LL) 
               {
                   lastVals.push_back(0LL);
                   BackTrack(lastOps+'n', lastVals, currIdx+1, ans, num, target);
                   lastVals.pop_back();
               }
               else
               {
                   long long right;
                   right = lastVals.back() / left;
                   right = right * 10LL + toAdd;
                   lastVals.push_back(left*right);
                   BackTrack(lastOps+'n', lastVals, currIdx+1, ans, num, target);
                   lastVals.pop_back();
               }
           }
           if(lastOps[closestIdx_] == '+')
           {
               long long right = lastVals.back() - left;
               right = right * 10LL + toAdd;
               lastVals.push_back(left+right);
               BackTrack(lastOps+'n', lastVals, currIdx+1, ans, num, target);
               lastVals.pop_back();
           }
           if(lastOps[closestIdx_] == '-')
           {
               long long right = left - lastVals.back();
               right = right * 10LL + toAdd;
               lastVals.push_back(left+right);
               BackTrack(lastOps+'n', lastVals, currIdx+1, ans, num, target);
               lastVals.pop_back();
           }
       }
       else if(closestIdx_ == closestIdx)
       {
           long long left = lastVals[closestIdx-1];
           if(lastOps[closestIdx] == '+')
           {
               long long right = lastVals.back() - left;
               right = right * 10LL + toAdd;
               lastVals.push_back(left+right);
               BackTrack(lastOps+'n', lastVals, currIdx+1, ans, num, target);
               lastVals.pop_back();
           }
           else
           {
               long long right = left - lastVals.back();
               right = right * 10LL + toAdd;
               lastVals.push_back(left-right);
               BackTrack(lastOps+'n', lastVals, currIdx+1, ans, num, target);
               lastVals.pop_back();
           }
       }
       else if(closestIdx >= 0)
       {
           long long left, mid, right;
           if(closestIdx == 0) left = (long long)(num[0]-'0');
           else left = lastVals[closestIdx-1];
           if(lastOps[closestIdx] == '+')
           {
               mid = lastVals[closestIdx_-1] - left;
               right = lastVals.back() - left;
               right = right * 10LL + mid * toAdd;
               lastVals.push_back(left+right);
               BackTrack(lastOps+'n', lastVals, currIdx+1, ans, num, target);
               lastVals.pop_back();
           }
           else
           {
               mid = left - lastVals[closestIdx_-1];
               right = left - lastVals.back();
               right = right * 10LL + mid * toAdd;
               lastVals.push_back(left-right);
               BackTrack(lastOps+'n', lastVals, currIdx+1, ans, num, target);
               lastVals.pop_back();
           }
       }
       else
       {
           long long mid = lastVals[closestIdx_-1];
           long long right = lastVals.back();
           lastVals.push_back(right*10LL + mid*toAdd);
           BackTrack(lastOps+'n', lastVals, currIdx+1, ans, num, target);
           lastVals.pop_back();
       }
       return;
   }