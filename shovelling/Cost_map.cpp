#include "Cost_map.h"
#include "Matrix.h"
const Matrix* Cost_map::matrix = nullptr;

Cost_map::Cost_map(Point p)
    :start_point(p),
    cost_map(matrix->number_of_row(),vector<int>(matrix->number_of_col(),-1)),
    preceded_map(matrix->number_of_row(),vector<Point>(matrix->number_of_col(),Point{-1,-1}))
{
    cost_map[p.y][p.x] = 0;
    preceded_map[p.y][p.x] = p;
    //cerr<<"orecede nao before cal"<<endl;
    //print_preceded_map();
    calculation_cost_map();
}

Cost_map& Cost_map::handle_zero_cost_cell(Point p, vector<Point>& same_cost, int current_cost)
{
    //cerr<<"handle zero cost cell"<<p<<endl;
    vector<Point> adjs = matrix->find_traversable_adjacent_cell(p);
    for ( auto adj : adjs) {
        if (( Point{-1,-1} == preceded_map[adj.y][adj.x]) && matrix->is_cell_clear(adj)) {
            preceded_map[adj.y][adj.x] = p; 
            cost_map[adj.y][adj.x] = current_cost;
            same_cost.push_back(adj);
            handle_zero_cost_cell(adj, same_cost, current_cost);
        }
    }
    return *this; 
}

Cost_map& Cost_map::calculation_cost_map()
{
    vector<Point> same_cost;
    vector<Point> same_cost_cp;
    int current_cost = 0;
    same_cost.push_back(start_point);
    vector<Point> adjs = matrix->find_traversable_adjacent_cell(start_point);
    for( auto adj : adjs) {
        if (matrix->is_cell_clear(adj)) {
            preceded_map[adj.y][adj.x] = start_point; 
            cost_map[adj.y][adj.x] = current_cost;
            same_cost.push_back(adj);
            handle_zero_cost_cell(adj, same_cost, current_cost);
        }
    }
    ++current_cost;
    while(true) {
        same_cost_cp = same_cost;
        same_cost.clear();
        for ( auto p : same_cost_cp) {
            vector<Point> adjs = matrix->find_traversable_adjacent_cell(p);
            for( auto adj : adjs) {
                if ( Point{-1,-1} == preceded_map[adj.y][adj.x]) {
                    preceded_map[adj.y][adj.x] = p; 
                    cost_map[adj.y][adj.x] = current_cost;
                    same_cost.push_back(adj);
                    vector<Point> as = matrix->find_traversable_adjacent_cell(adj);
                    for( auto a: as) {
                        if (( Point{-1,-1} == preceded_map[a.y][a.x]) && matrix->is_cell_clear(a)) {
                            //cerr<<"found zero cost cell"<<a<<"at cost"<<current_cost<<endl;
                            preceded_map[a.y][a.x] = adj; 
                            cost_map[a.y][a.x] = current_cost;
                            same_cost.push_back(a);
                            handle_zero_cost_cell(a, same_cost, current_cost);
                        }
                    }
                }
            }
        }
        if( true == same_cost.empty()) break;
        current_cost++;
    } 
}

vector<vector<int>> Cost_map::add(const vector<vector<int>>& a,const vector<vector<int>>& b)
{
    vector<vector<int>> c{a};
    for (int i = 0; i< c.size();++i) {
        for (int j = 0; j <c[0].size(); ++j) {
            c[i][j] +=b[i][j] -1;
            if(matrix->is_cell_clear(Point{j,i}))
                ++c[i][j];
        }
    }
    return c;
}


