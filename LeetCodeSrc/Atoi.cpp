#include <string>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>
using namespace std;
using string = std::string;
class Solution
{
private:
    unordered_map<string, vector<string>> stateMachine;
    string curState = "start";

public:
    Solution()
    {
        stateMachine["start"] = vector<string>{"start", "signed", "num", "end"};
        stateMachine["signed"] = vector<string>{"end", "end", "num", "end"};
        stateMachine["num"] = vector<string>{"end", "end", "num", "end"};
        stateMachine["end"] = vector<string>{"end", "end", "end", "end"};
    }
    int myAtoi(string s)
    {
        long ans = 0;
        int sign = 1;
        for (auto it = s.begin(); it != s.end(); ++it)
        {
            int flag = 0;
            int res = convertInt(*it);
            cout << res << endl;
            if (res >= 0)
                flag = 2;
            else if (res == -1)
                flag = 0;
            else if (res == -2)
                flag = 1;
            else if (res == -3)
            {
                flag = 1;
                sign = -1;
            }
            else
            {
                flag = 3;
            }
            curState = stateMachine[curState][flag];
            ;
            if (curState == "end")
                return ans;
            if (curState == "num")
                ans = ans * 10 + (sign)*res;
            if (ans > numeric_limits<int>::max())
                return numeric_limits<int>::max();
            if (ans < numeric_limits<int>::min())
                return numeric_limits<int>::min();
        }
        return ans;
    }

private:
    int
    convertInt(char s)
    {
        switch (s)
        {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
            /* code */

        case ' ':
            return -1;
        case '+':
            return -2;
        case '-':
            return -3;
        default:
            return -4;
        }
    }
};