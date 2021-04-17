#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <cassert>
using namespace std;

struct Input 
{
    string alien_number;
    string source_lang;
    string dest_lang;
};

std::vector<Input> get_input()
{
    std::vector<Input> ret;
    string line;
    std::getline(cin, line);
    istringstream iss(line);
    int number;
    iss >> number;
    for (int i = 0; i < number; ++i)
    {
        std::getline(cin, line);
        istringstream iss(line);
        Input inp;
        iss >> inp.alien_number >> inp.source_lang >> inp.dest_lang; 
        ret.push_back(inp);
    }
    return ret;
}

    
std::map<int, char> make_dest_map(const string& lang)
{
    std::map<int, char> ret;

    for (int i = 0; i < lang.size(); ++i)
       ret[i] = lang[i];
    return ret;
}

std::map<char, int> make_source_map(const string& lang)
{
    std::map<char, int> ret; 
    for (int i = 0; i < lang.size(); ++i)
       ret[lang[i]] = i;
    return ret;
}

int to_dec(const std::string& alien_number, const std::map<char, int>& source_map)
{
    int res = 0;
    int multi_factor = 1;
    for (int i = alien_number.size() - 1; i >=0; --i)
    {
        res+= multi_factor * source_map.at(alien_number[i]); 
        multi_factor *= source_map.size();
    }
    return res;
}

string to_alien(int dec, const std::map<int, char>& dest_map)
{
    string res;
    while(dec >= dest_map.size())
    {
        res = dest_map.at(dec % dest_map.size()) + res;
        dec /= dest_map.size();
    }
    res = dest_map.at(dec) + res;
    return res;
}

std::string solution(Input inp)
{
    std::map<char, int> source_map = make_source_map(inp.source_lang);
    std::map<int, char> dest_map = make_dest_map(inp.dest_lang);
    int dec = to_dec(inp.alien_number, source_map);
    return to_alien(dec, dest_map); 
}

int main(void)
{
    auto inp = get_input();
    for (int i = 0; i < inp.size(); ++i)
    {
        std::cout << "Case #" << i+1 << ": " << solution(inp[i]) << '\n';
    }
    return 0;
}


