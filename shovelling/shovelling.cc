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
/* typedef row vector<int>; 
 * vector<row> matrix
 * access with matrix[y][x]; 
 * y |        
 *   |
 *   |_______ x
 */
/*cost_map_recalculate*/
#if 0
#endif
/*Matrix.h*/

int main(void) {
    vector<Matrix> matrices = parse();
    for (auto &a : matrices) {
        //cerr<<a;
        a.minimum_work();
        //cout<<a.calculate_minimum_cost()<<" blocks"<<endl;
    }
    return 0;
    #if 0
        vector<Point> adjs = a.find_traversable_adjacent_cell(Point{1,1});
        for (auto adj: adjs) {
            cerr<<adj<<endl;
        }
    #endif
}
