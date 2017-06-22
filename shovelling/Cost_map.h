#ifndef __COST_MAP_H
#define __COST_MAP_H

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

using namespace std;
class Matrix;
class Cost_map
{
public:
    explicit Cost_map(Point p);
    const vector<vector<int>>& get_cost_map() const
    {
        return cost_map;
    }

    const vector<vector<Point>>& get_preceded_map() const
    {
        return preceded_map;
    }

    static vector<vector<int>> add(const vector<vector<int>>& a,const vector<vector<int>>& b);
    static Cost_map& set_matrix(const Matrix* _matrix) {
        matrix = _matrix;
    }
    static const Matrix* get_matrix() {
        return matrix;
    }

private:
    Cost_map& calculation_cost_map();
    Cost_map& handle_zero_cost_cell(Point p, vector<Point>& same_cost, int current_cost);
private:
    const static Matrix * matrix;
    Point start_point;
    vector<vector<int>> cost_map;
    vector<vector<Point>> preceded_map;
};
int minimum_val(vector<vector<int>> cost_map);
vector<Point> find_same_cost(int current_cost);

#endif

