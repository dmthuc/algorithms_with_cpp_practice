/*Unit test for Point.h and basic operation of Matrix.h except method minimum_work*/
#include "Matrix.h"

int main()
{
    if ((Point{-1,-1} == Point{-1,-1} && Point{0,1} != Point{1,1})) {
        cerr<<"test Point.h pass"<<endl;
    }
    vector<Matrix> matrices = parse();
    for (auto &a : matrices) {
        cerr<<a;
        vector<Point> adj_cells = a.find_traversable_adjacent_cell(Point{0,0});
        cerr<<"traverable adjacent cells of {0,0}"<<endl;    
        cerr<<adj_cells<<endl;
        cerr<<"traverable adjacent cells of {0,1}"<<endl;    
        adj_cells = a.find_traversable_adjacent_cell(Point{0,1});
        cerr<<adj_cells<<endl;
        if(is_cell_clear(Point{0,1}) && is_cell_clear(Pointr{7,1})) {
            cerr<<"test is cell clear pass"<<endl;
        }
    }
    return 0;


}
