#ifndef __MINCOSTCALCULATION_H
#define __COST_MAP3P_H

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
#include "Point.h"
#include "Matrix.h"
using namespace std;
class Mincost_calculation
{
public:
    explicit Mincost_calculation(Point p, Cost_map a, Cost_map b, Cost_map c);
    const vector<vector<Point>>& get_preceded_map() const
    {
        return preceded_map;
    }
private:
    Mincost_calculation& calculation_cost_map();
    Mincost_calculation& handle_clear_cell(Point p, vector<Point>& same_cost, int current_cost);
    int minimum_val(const vector<vector<int>>& cost_map) const;
    Mincost_calculation& make_path_base_on_same_cost(vector<Point>& same_cost, int current_cost);
private:
    Point final_point;
    const Matrix * matrix;
    Cost_map cost_maps[3];
    vector<vector<int>> cost_map;
    vector<vector<Point>> preceded_map;
};
#endif
