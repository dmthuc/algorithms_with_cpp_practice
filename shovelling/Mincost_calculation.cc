#include "Mincost_calculation.h"
#include "Matrix.h"
#include "Point.h"
#include "Cost_map.h"
using namespace std;
vector<Point> find_same_cost(const vector<vector<int>> &v,int cost);

Mincost_calculation::Mincost_calculation(Point p, Cost_map a, Cost_map b, Cost_map c)
    :final_point(p), cost_maps{a,b,c}, matrix(Cost_map::get_matrix()),
     cost_map(Cost_map::get_matrix()->number_of_row(),vector<int>(Cost_map::get_matrix()->number_of_col(),-1)),
     preceded_map(Cost_map::get_matrix()->number_of_row(),vector<Point>(Cost_map::get_matrix()->number_of_col(),Point{-1,-1}))
{
    calculation_cost_map();
}

Mincost_calculation& Mincost_calculation::calculation_cost_map()
{
    cost_map = Cost_map::add(cost_maps[0].get_cost_map(), cost_maps[1].get_cost_map());
    cost_map = Cost_map::add(cost_map, cost_maps[2].get_cost_map());
    //cerr<<"cost map after adding"<<endl;
    //cerr<<cost_map<<endl;
    int current_cost = minimum_val(cost_map);
    vector<vector<int>> cost_map_cp(cost_map);
    vector<Point> same_cost = find_same_cost(cost_map_cp, current_cost);
    make_path_base_on_same_cost(same_cost, current_cost);
    vector<Point> same_cost_tmp;
    for (auto p: same_cost) {
        preceded_map[p.y][p.x] = p;
        vector<Point> adjs = matrix->find_traversable_adjacent_cell(p);
        for( auto adj : adjs) {
            if ((Point{-1,-1} == preceded_map[adj.y][adj.x]) && (matrix->is_cell_clear(adj))) {
                preceded_map[adj.y][adj.x] = p; 
                cost_map[adj.y][adj.x] = current_cost;
                same_cost_tmp.push_back(adj);
                handle_clear_cell(adj, same_cost, current_cost);
            }
        }
    }
    same_cost.insert(same_cost.end(), same_cost.begin(), same_cost.end());
    ++current_cost;
    //cerr<<cost_map;
#if 1
    while(true) {
        same_cost_tmp = same_cost;
        same_cost.clear();
        vector<Point> same_cost_local = find_same_cost(cost_map_cp, current_cost);
        make_path_base_on_same_cost(same_cost_local, current_cost);
        //cerr<<"after make path"<<endl;
        //cerr<<cost_map;
        for ( auto p : same_cost_tmp) {
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
                            handle_clear_cell(a, same_cost, current_cost);
                        }
                    }
                }
            }
        }
        same_cost.insert(same_cost.end(),same_cost_local.begin(), same_cost_local.end());
        if( !(preceded_map[final_point.y][final_point.x] == Point{-1,-1})) {
            cout<<cost_map[final_point.y][final_point.x]<<endl;
            break;
        } 
        if( true == same_cost.empty()) break;
        //cerr<<"after increase curretn code"<<endl;
        //cerr<<cost_map<<endl;
        current_cost++;
    } 
    //cerr<<cost_map;
#endif
    //cout<<0<<endl;
    return *this;
}

Mincost_calculation& Mincost_calculation::handle_clear_cell(Point p, vector<Point>& same_cost, int current_cost)
{
    vector<Point> adjs = matrix->find_traversable_adjacent_cell(p);
    for ( auto adj : adjs) {
        if (( Point{-1,-1} == preceded_map[adj.y][adj.x]) && matrix->is_cell_clear(adj)) {
            preceded_map[adj.y][adj.x] = p; 
            cost_map[adj.y][adj.x] = current_cost;
            same_cost.push_back(adj);
            handle_clear_cell(adj, same_cost, current_cost);
        }
    }
    return *this; 
}

int Mincost_calculation::minimum_val(const vector<vector<int>>& cost_map) const
{
    int min_val = (*matrix)[final_point.y][final_point.x];
    for (auto i: cost_map) {
        for (auto j: i) {
            if ( (0 <= j) && (j < min_val)) min_val = j;
        }
    }
    return min_val;
}

vector<Point> find_same_cost(const vector<vector<int>> &v,int cost)
{
    vector<Point> result;
    for (int i = 0; i< v.size();++i) {
        for (int j = 0; j <v[0].size(); ++j) {
            if( v[i][j] == cost) {
                result.push_back(Point{j,i});
            }
        }
    }
    return result;
}

Mincost_calculation& Mincost_calculation::make_path_base_on_same_cost(vector<Point>& v, int current_cost)
{
    vector<Point> tmp;
    for (auto cell : v) {
        if(Point{-1,-1} == preceded_map[cell.y][cell.x]) {
            preceded_map[cell.y][cell.x] = cell; //modify it later
        }
        for( auto cos_map : cost_maps) {
            Point p = cos_map.get_preceded_map()[cell.y][cell.x];
            Point previous = cell;
            while( !(cos_map.get_preceded_map()[p.y][p.x] == p)) {
                if(Point{-1,-1} == preceded_map[p.y][p.x]) {
                    cost_map[p.y][p.x] = current_cost;
                    tmp.push_back(p);
                    preceded_map[p.y][p.x] = previous; 
                }
                previous = p;
                p = cos_map.get_preceded_map()[p.y][p.x];
            }
        }
    }
    v.insert(v.end(),tmp.begin(),tmp.end());
    return *this;
}

