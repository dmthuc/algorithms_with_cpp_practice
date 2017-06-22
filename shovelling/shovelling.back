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
using namespace std;
/* typedef row vector<int> vector<row> matrix; 
 * access with matrix[y][x]; 
 * y |        
 *   |
 *   |_______ x
 */
enum Sea_map_area {NOT_SPECIFIED = 0, SEA = 1, NOT_SEA = 2};

int get_length(const vector<vector<int>> *sea_map);

void print_matrix(const vector<vector<int>> *mat)
{
    for (auto row :(*mat)) {
        for (auto col : row) {
            cerr<<col<<" ";
        }
        cerr<<endl;
    }
}

bool is_in_map(pair<int, int> pos, int width, int hieght)
{
    if ((pos.first < 0) || (pos.first >= width) || (pos.second < 0) || (pos.second >= hieght))
        return false;
    return true;
}

void find_sea(int x, int y, int width, int height,const vector<vector<int>> *info, vector<vector<int>> *sea_map)
{
    vector<pair<int,int>> adj_cells = {{x-1,y},{x+1,y},{x,y-1},{x,y+1}};
    for( auto cell : adj_cells)
    {
        if( is_in_map(cell,width, height)) {
            if((*sea_map)[cell.second][cell.first]== NOT_SPECIFIED)
            {
                if((*info)[cell.second][cell.first] == 0) {
                    (*sea_map)[cell.second][cell.first] = SEA;
                    find_sea(cell.first,cell.second, width, height,info, sea_map);
                } else {
                    (*sea_map)[cell.second][cell.first] = NOT_SEA;
                }
                
            }
        }
    }
}
vector<vector<int>> get_sea_map(const vector<vector<int>> *mat)
{
    vector<vector<int>> sea_map{*mat};
    for ( auto &a : sea_map)
    {
        for( auto &b: a) 
        {
            b = NOT_SPECIFIED;
        }
    }
    sea_map[0][0] = SEA;
    find_sea(0, 0, sea_map[0].size(),sea_map.size(), mat, &sea_map); 
    return sea_map;
}
int get_cell_coast_length( int x, int y, int width, int height, const vector<vector<int>> * sea_map)
{
    int len = 0;
    vector<pair<int,int>> adj_cells = {{x-1,y},{x+1,y},{x,y-1},{x,y+1}};
    for( auto cell : adj_cells)
    {
        if( is_in_map(cell,width, height)) {
            if ((*sea_map)[cell.second][cell.first] == NOT_SEA)
                ++len; 
        }
    }
    //cerr<<"at cell"<<y<<x<<"add cast length"<<len<<endl;
    return len;


}

int get_length_from_sea_map(const vector<vector<int>> *sea_map)
{
    int len = 0;
    int height = sea_map->size();
    int width = (*sea_map)[0].size();
    for ( int x = 0; x< width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            if ((*sea_map)[y][x] == SEA) {
                len += get_cell_coast_length(x,y,width, height, sea_map);
            }

        }
    }
 
    return len;
}
class Matrix
{
public:
    explicit Matrix(unsigned int _num_of_row,unsigned int _num_of_col)
        :num_of_row(_num_of_row), num_of_col{_num_of_col}, 
        mat{}
    {
    }
    Matrix& operator=(const Matrix &) = delete;
    void calculate_coast_length() const
    {
        vector<vector<int>> sea_map = get_sea_map(&mat);
        //cerr<<" sea map is"<<endl;
        //print_matrix(&sea_map);
        cout<<get_length_from_sea_map(&sea_map)<<endl;
    }
    Matrix& add_row(vector<int> row)
    {
        mat.push_back(row);
    } 
    friend ostream &operator<<(ostream&, const Matrix&);
private:
    unsigned int num_of_row;
    unsigned int num_of_col;
    vector<vector<int>> mat;
};

ostream &operator <<(ostream& os, const Matrix& matrix)
{
    os <<"number of row: "<<matrix.num_of_row<<" num of colume: "<<matrix.num_of_col<<endl;
    for (auto a: matrix.mat )
    {
        for (auto b: a)
        {
            os<<b<<" ";
        }
        os<<endl;
    }
    return os;
}

unique_ptr<Matrix> parse()
{
    string input;
    std::getline(cin,input);
    int num_of_row;
    int num_of_col;
    {
        istringstream iss(input);
        iss>> num_of_row>> num_of_col;
    }
    unique_ptr<Matrix> mat{new Matrix(num_of_row+2, num_of_col+2)};
    mat->add_row(vector<int>(num_of_col+2, 0));
    for (unsigned int i = 0; i< num_of_row; ++i)
    {
        vector<int> row{};
        row.push_back(0); 
        std::getline(cin,input);
        istringstream iss(input);
        for (unsigned int j = 0; j < num_of_col; ++j)
        {
            char c;
            iss.get(c);
            if (c == '0') {  
                row.push_back(0); 
            } else {
                row.push_back(1); 
            }
        }
        row.push_back(0); 
        mat->add_row(row);
    }
    mat->add_row(vector<int>(num_of_col+2, 0));
    return mat;
}

int main(void) {
    unique_ptr<Matrix> mat = parse();
    //cerr <<*mat<<endl;
    (*mat).calculate_coast_length();
    return 0;
}

