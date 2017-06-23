#ifndef __POINT1_H
#define __POINT1_H

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>        // std::tuple, std::get, std::tie, std::ignore
#include <cmath>
#include <bitset>
#include <memory>
#include <cstdlib>

using namespace std;
struct Point{
    int x;
    int y;
};
const bool operator==(const Point a, const Point b);
ostream& operator<<(ostream & os, const Point a);
ostream& operator<<(ostream & os, const vector<vector<Point>> &a);
ostream& operator<<(ostream & os, const vector<Point> &a);
ostream& operator<<(ostream & os, const vector<vector<int>>& a);

#endif

