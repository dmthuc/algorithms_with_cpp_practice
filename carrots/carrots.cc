#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <cassert>
using namespace std;

std::vector<int> get_input()
{
    std::vector<int> ret;
    int number;
    while(cin >> number)
    {
        ret.push_back(number);
    } 
    ret.erase(ret.begin());
    return ret;
}


int main(void)
{
    std::vector<int> input = get_input();
    std::cout << input[0] << '\n';

    return 0;
}


