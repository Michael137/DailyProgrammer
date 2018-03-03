#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

static const unordered_map<int, string> digitsMap = {
    { 1, "one" },
    { 2, "two" },
    { 3, "three" },
    { 4, "four" },
    { 5, "five" },
    { 6, "six" },
    { 7, "seven" },
    { 8, "eight" },
    { 9, "nine" },
    { 10, "ten" },
    { 11, "eleven" },
    { 12, "twelve" },
    { 13, "thirteen" },
    { 14, "fourteen" },
    { 15, "fifteen" },
    { 16, "sixteen" },
    { 17, "seventeen" },
    { 18, "eighteen" },
    { 19, "nineteen" },
    { 20, "twenty" },
    { 30, "thirty" },
    { 40, "fourty" },
    { 50, "fifty" }
};

int convert(const int h)
{
    if (h == 0)
        return 12;

    return (h > 12) ? h - 12 : h;
}

string hrsToString(const int h)
{
    return digitsMap.find(convert(h))->second;
}

int firstDigit(int n)
{
    while (n >= 10)
        n /= 10;

    return n;
}

string minToString(const int m)
{
    ostringstream oss("");

    if (m != 0) {
        if (m < 10)
            oss << "oh ";

        if (m < 20)
            oss << digitsMap.find(m)->second;
        else {
            int first = firstDigit(m) * 10;
            oss << digitsMap.find(first)->second << " ";
            oss << digitsMap.find(m - first)->second;
        }
    }

    return oss.str();
}

bool isPm(const int h)
{
    return h >= 12;
}

int main()
{
    int h, m;

    cin >> h;
    cin.ignore();
    cin >> m;

    ostringstream oss("It's ");
    oss << hrsToString(h) << " ";
    oss << minToString(m) << " " << (isPm(h) ? "pm" : "am");
    cout << oss.str() << endl;
}
