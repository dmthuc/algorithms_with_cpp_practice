#ifndef __MATRIX_H
#define __MATRIX_H
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
#include "Cost_map.h"
using namespace std;
class Matrix
{
public:
    explicit Matrix(unsigned int _num_of_row,unsigned int _num_of_col)
        :num_of_row(_num_of_row), num_of_col{_num_of_col}, 
        mat{}
    {
    }
    Matrix(const Matrix& other)
        :num_of_row(other.num_of_row), 
            num_of_col(other.num_of_col),
            mat(other.mat)
    {
    }
    Matrix(Matrix&& other)
        :num_of_row(other.num_of_row), 
            num_of_col(other.num_of_col),
            mat(std::move(other.mat))
    {
    }

    Matrix& operator=(const Matrix &) = delete;
    Matrix& operator=(Matrix &&) = delete;
    Matrix& add_row(string row)
    {
        mat.push_back(row);
    } 

    const string& operator[] (const int row) const
    {
        return mat[row];
    }

    int number_of_row() const 
    {
        return num_of_row;
    }

    int number_of_col() const 
    {
        return num_of_col;
    }
    bool is_cell_clear(Point p) const
    {
        switch (mat[p.y][p.x]) {
            case '.':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
                return true;
            default:
                return false;
        }
    }
    vector<Point> find_traversable_adjacent_cell(Point point) const;
    void minimum_work() const;
private:
    unsigned int num_of_row;
    unsigned int num_of_col;
    vector<string> mat;
};

ostream &operator <<(ostream& os, const Matrix& matrix);
vector<Matrix> parse();
#endif

