/*Unit test for Point.h and basic operation of Matrix.h except method minimum_work*/
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
#include "Matrix.h"
using namespace std;

int main()
{
    if ((Point{-1,-1} == Point{-1,-1} && !(Point{0,1} == Point{1,1}))) {
        cerr<<"test Point.h pass"<<endl;
    } else {
        cerr<<"test Point.h fail"<<endl;

    }
    vector<Matrix> matrices = parse();
    for (auto &a : matrices) {
        cerr<<a;
        vector<Point> adj_cells = a.find_traversable_adjacent_cell(Point{0,0});
        cerr<<"traverable adjacent cells of {0,0}"<<endl;    
        cerr<<adj_cells<<endl;
    #if 1
        cerr<<"traverable adjacent cells of {0,1}"<<endl;    
        adj_cells = a.find_traversable_adjacent_cell(Point{0,1});
        cerr<<adj_cells<<endl;
        if(a.is_cell_clear(Point{0,1}) && a.is_cell_clear(Point{7,1}) && (!a.is_cell_clear(Point{2,2}))) {
            cerr<<"test is cell clear pass"<<endl;
        } else {
            cerr<<"test is cell clear fail"<<endl;
        }
    #endif
    }
    throw 100;
    return 0;


}
