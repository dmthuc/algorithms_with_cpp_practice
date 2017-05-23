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
/* typedef row vector<int> vector<row> matrix; 
 * access with matrix[y][x]; 
 * y |        
 *   |
 *   |_______ x
 */
int distance(int x1,int y1, int x2, int y2)
{
    return abs(x1-x2)+ abs(y1-y2);
}
class Matrix
{
public:
    enum Direction{CENTER = 0,EAST, WEST, NORTH, SOUTH};
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
    Matrix& add_row(vector<int> row)
    {
        mat.push_back(row);
    } 
    int calculate_cost(int x, int y) const
    {
        int cost = 0;
        for(int row_index = 0; row_index< num_of_row;++row_index)
        {
            for (int col_index = 0; col_index< num_of_col;++col_index)
            {
               cost += mat[row_index][col_index] * distance(x,y,col_index,row_index);
            }
        }
        return cost;
    }
    void show_cost_matrix() const
    {
        cerr<<"cost matrix"<<endl;
        for(int row_index = 0; row_index< num_of_row;++row_index)
        {
            for (int col_index = 0; col_index< num_of_col;++col_index)
            {
                cerr<< calculate_cost(col_index,row_index)<<" "; 
            }
            cerr<<endl;
        }
        

    }
    int calculate_minimum_cost() const{
        int start_x = num_of_col/2; 
        int start_y = num_of_row/2;
        int current_cost = calculate_cost(start_x,start_y); 
        return find_minimum(start_x, start_y,current_cost, CENTER);
    }

    int find_minimum(int x, int y,int current_cost, Direction direction) const {
        Direction current_direction = CENTER;
        if ((direction != WEST) &&(x+1 < num_of_col)) {
            int east_cost = calculate_cost(x+1,y);   
            if( east_cost < current_cost) {
                current_direction = EAST;
                current_cost = east_cost;
            }
        }

        if ((direction != EAST) &&(x-1 >= 0)) {
            int west_cost = calculate_cost(x-1,y);   
            if( west_cost < current_cost) {
                current_direction = WEST;
                current_cost = west_cost;
            }
        }

        if ((direction != NORTH) &&(y+1 < num_of_row)) {
            int south_cost = calculate_cost(x,y+1);   
            if( south_cost < current_cost) {
                current_direction = SOUTH;
                current_cost = south_cost;
            }
        }

        if ((direction != SOUTH) &&(y-1 >= 0)) {
            int north_cost = calculate_cost(x,y-1);   
            if( north_cost < current_cost) {
                current_direction = NORTH;
                current_cost = north_cost;
            }
        }
        switch( current_direction) {
            case CENTER:
                return current_cost;
            case EAST:         
                return find_minimum(x+1,y,current_cost,EAST);
            case WEST:
                return find_minimum(x-1,y,current_cost,WEST);
            case SOUTH:
                return find_minimum(x,y+1,current_cost,SOUTH);
            case NORTH:
                return find_minimum(x,y-1,current_cost,NORTH);
        }
    
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
    for (auto &a: matrix.mat )
    {
        for (auto b: a)
        {
            os<<b<<" ";
        }
        os<<endl;
    }
    return os;
}

vector<Matrix> parse()
{
    string input;
    vector<Matrix> matrices;
    std::getline(cin,input);
    int number_of_input_matrix = 0;
    {
        istringstream iss(input);
        iss>>number_of_input_matrix;
    }
    for ( int k = 0; k< number_of_input_matrix;++k)
    {
        int num_of_row;
        int num_of_col;
        {
            std::getline(cin,input);
            istringstream iss(input);
            iss>> num_of_col>> num_of_row;
        }
        Matrix mat(num_of_row, num_of_col);

        for (unsigned int i = 0; i< num_of_row; ++i)
        {
            vector<int> row{};
            std::getline(cin,input);
            istringstream iss(input);
            for (unsigned int j = 0; j < num_of_col; ++j)
            {
                int element;
                iss>> element;
                row.push_back(element); 
            }
            mat.add_row(move(row));
        }
        matrices.push_back(move(mat));
    }
    return matrices;
}

int main(void) {
    vector<Matrix> matrices = parse();
    //cerr <<*mat<<endl;
    for (auto &a : matrices) {
        //cerr<<a;
        //a.show_cost_matrix();
        cout<<a.calculate_minimum_cost()<<" blocks"<<endl;
    }
    return 0;
}

