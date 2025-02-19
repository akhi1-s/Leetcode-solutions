

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;



class Solution {
public:
    vector<string> addOperators(string num, int target) {

        if(num == "")
            return {};
        vector<string> ret;
        split(num, 0, target, "", ' ', -1, 0ll, ret);
        return ret;
    }

private:
    void split(const string& num, int index, int target, const string& expr,
               char lastop, long long pre, long long res, vector<string>& ret){

        if(index == num.size()){
            if(res == (long long)target)
                ret.push_back(expr);
            return;
        }

        int end = num.size();
        if(num[index] == '0')
            end = index + 1;

        for(int i = index + 1; i <= end; i ++){
            int len = i - index;
            string cur_num_s = num.substr(index, len);
            long long cur = atoll(cur_num_s.c_str());

            char next_lastop = ' ';
            long long next_pre = cur;
            long long next_res = res;

            if(expr != "" && expr[expr.size() - 1] == '*' && (lastop == '+' || lastop == '-')){
                assert(pre != -1);
                if(lastop == '+')
                    next_res -= pre, next_res += pre * cur;
                else
                    next_res += pre, next_res -= pre * cur;
                next_pre = pre * cur;
                next_lastop = lastop;
            }
            else if(expr != ""){
                switch(expr[expr.size() - 1]){
                    case '+': next_res += cur; break;
                    case '-': next_res -= cur; break;
                    case '*': next_res *= cur; break;
                    default:assert(false); break;
                }
                next_lastop = expr[expr.size() - 1];
            }
            else
                next_res = cur;

            if(index + len == num.size())
                split(num, index + len, target, expr + cur_num_s,
                      ' ', next_pre, next_res, ret);
            else{
                split(num, index + len, target, expr + cur_num_s + "*",
                      next_lastop, next_pre, next_res, ret);
                split(num, index + len, target, expr + cur_num_s + "+",
                      next_lastop, next_pre, next_res, ret);
                split(num, index + len, target, expr + cur_num_s + "-",
                      next_lastop, next_pre, next_res, ret);
            }
        }
    }
};


void print_vec(const vector<string>& vec){
    cout << "[ ";
    for(const string& e: vec)
        cout << e << " ";
    cout << "]" << endl;
}

