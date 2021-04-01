class Solution
{
public:
    int clumsy(int num)
    {
        int res = 0;
        if (num / 4)
        {
            res += num * (num - 1) / (num - 2) + num - 3;
            num -= 4;
        }
        else
        {
            switch (num % 4)
            {
            case 0:
                return res + 0;
            case 1:
                return res + 1;
            case 2:
                return res + 2 * 1;
            case 3:
                return res + 3 * 2 / 1;
            }
        }
        while (num / 4)
        {
            res = res - num * (num - 1) / (num - 2) + num - 3;
            num -= 4;
        }
        switch (num % 4)
        {
        case 0:
            return res - 0;
        case 1:
            return res - 1;
        case 2:
            return res - 2 * 1;
        case 3:
            return res - 3 * 2 / 1;
        }
        return res;
    }
};
int main()
{
    return 0;
}