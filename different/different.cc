#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <cassert>
using namespace std;

std::vector<long> get_input()
{
    std::vector<long> ret;
    long number;
    while(true)
    {
        cin >> number;
 
        if (cin.eof() || cin.bad()) {
            break;
        } else if (cin.fail()) {
            cin.clear(); // unset failbit
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip bad input
        } else {
            ret.push_back(number);
        }
    }
    return ret;
}

int main(void)
{
    std::vector<long> input = get_input();
    for (int i = 0; i < input.size(); i+=2)
    {
        //std::cout << input[i+1] << ' ' << input[i] << '\n';
        std::cout << std::abs(input[i+1] -input[i]) << '\n';
    }
    return 0;
}


