#include <iostream>
#include <string>
#include <cstring> 
#include <sstream>
#include <cmath>

using namespace std;

int check(string I1, string I2, int B)
{

    if (I1.length() > 100)
    {
        printf("I1 no longer than 100 digit");
        exit(1);
    }

    if (I2.length() > 100)
    {
        printf("I2 no longer than 100 digit");
        exit(1);
    }

    if (B > 10 or B < 2)
    {
        printf("B from 2 to 10");
        exit(1);
    }
    return 0;
}

string SUMM(string I1, string I2, int B) {
    size_t length = max(I1.size(), I2.size());
    int carry = 0;
    int sum_col;  
    string result;

    while (I1.size() < length)
        I1.insert(0, "0");

    while (I2.size() < length)
        I2.insert(0, "0");

    for (int i = length - 1; i >= 0; i--) {
        sum_col = (I1[i] - '0') + (I2[i] - '0') + carry;
        carry = sum_col / B;
        result.insert(0, to_string(sum_col % B));
    }

    if (carry)
        result.insert(0, to_string(carry));

    return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}


bool Compare(string I1, string I2)
{
    int len1 = I1.size();
    int len2 = I2.size();
    if (len1 < len2)
        return false;
    else if (len1 == len2 && I1 < I2) {
        return false;
    }
    else if (I1[0] == '0')
        return false;
    return true;
}

string subtract(string I1, string I2, int B) {
    size_t length = max(I1.size(), I2.size());
    int diff;
    string result;

    while (I1.size() < length)
        I1.insert(0, "0");

    while (I2.size() < length)
        I2.insert(0, "0");

    for (int i = length - 1; i >= 0; i--) {
        diff = (I1[i] - '0') - (I2[i] - '0');
        if (diff >= 0)
            result.insert(0, to_string(diff));
        else {
            int j = i - 1;
            while (j >= 0) {
                I1[j] = ((I1[j] - '0') - 1) % B + '0';
                if (I1[j] != B+'0'-1)
                    break;
                else
                    j--;
            }
            result.insert(0, to_string(diff + B));
        }
    }
    return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}


void Ratio(string I1, string I2, int B)
{
    string s;
    string result;
    int count=0;
    int index = 0;
    if ("0" == I2)
    {
        cout << "NULL" << endl;
        return;
    } else
    {
        index = 0;
        while ('0' == I1[index])
            index++;
        I1.erase(0, index);
        index = 0;
        while ('0' == I2[index])
            index++;
        I2.erase(0, index);
    }

    if (!Compare(I1, I2))
    {
        cout << 0 << endl;
        return;
    }
    int len = I1.size();
    index = 0;
    for (int i = 0; i < len; i++)
    {
        count=0;
        s.push_back(I1[i]);
        if (s.find_first_not_of('0') != std::string::npos)
            s.erase(0, min(s.find_first_not_of('0'), s.size() - 1));
        while (Compare(s, I2))
        {
            s = subtract(s, I2, B);
            count++;
        }
        result.push_back(count+'0');
    }
    index = 0;
    while ('0' == result[index])
        index++;
    result.erase(0, index);
    cout << result << endl;
}

string Karatsuba(string I1, string I2, int B) 
{
    size_t length = max(I1.size(), I2.size());
    
    while (I1.size() < length)
        I1.insert(0, "0");
    while (I2.size() < length)
        I2.insert(0, "0");

    if (length == 1)
    {
        string a,b,sum;
        a.insert(0, "0");
        a[0] = I1[0];
        b.insert(0, "0");
        b[0] = I2[0];
        sum.insert(0, "0");

        for (int i = 0; i < I1[0]-'0'; i++)
            sum = SUMM(sum, b, B);
        return sum;
    }
    string I10 = I1.substr(0, length / 2);
    string I11 = I1.substr(length / 2, length - length / 2);
    string I20 = I2.substr(0, length / 2);
    string I21 = I2.substr(length / 2, length - length / 2);

    string p0 = Karatsuba(I10, I20, B);
    string p1 = Karatsuba(I11, I21, B);
    string p2 = Karatsuba(SUMM(I10, I11, B), SUMM(I20, I21, B), B);
    string p3 = subtract(p2, SUMM(p0, p1, B), B);

    for (size_t i = 0; i < 2 * (length - length / 2); i++)
        p0.append("0");
    for (size_t i = 0; i < length - length / 2; i++)
        p3.append("0");

    string result = SUMM(SUMM(p0, p1, B), p3, B);

    return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

int main() {
    string I1, I2;
    int B;
    cin >> I1 >> I2 >> B;
    check(I1, I2, B);
    cout << SUMM(I1, I2, B) << " " << Karatsuba(I1, I2, B) << " ";
    Ratio(I1, I2, B);

    return 0;
}
