#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>        // std::tuple, std::get, std::tie, std::ignore
#include <cmath>
#include <bitset>
using namespace std;

unsigned int maxInput(unsigned int num_of_bit)
{
    unsigned int max_input = 0;        
    for (unsigned int i = 0; i < num_of_bit; ++i)
    {
        max_input |= 0x01<<i;
    }
    //cerr <<"max_input is "<<max_input<<std::endl;
    return max_input;
}
bool add_module(unsigned int input, unsigned int size)
{
    unsigned int total = 0;
    for (int i = 0; i< size; ++i)
    {
        if(input & (0x01<<i))
            total += 1;
    }
    return total%2;
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
    Matrix& addRow(string row)
    {
        istringstream iss(row);
        unsigned int bit;
        unsigned int matrix_row = 0;
        for (unsigned int i = 0; i < num_of_col; ++i)
        {
            iss>> bit;
            matrix_row |= bit<<(num_of_col-i-1); 

        }
        mat.push_back(matrix_row);
    } 
    void findMinDistance()
    {
        unsigned int minimum_distance = 30;

        unsigned int max_input = maxInput(num_of_col); 
        for (unsigned int i = 1; i <= max_input; ++i)
        {
            unsigned int distance = 0;
            for ( unsigned int j = 0; j < num_of_row; ++j)
            {
                unsigned multiple = i & mat[j]; 
                if (add_module(multiple, num_of_col))
                {
                    ++distance;
                }
                if (distance >= minimum_distance) break;
            } 
            if (distance < minimum_distance) minimum_distance = distance;

        }
        cout <<minimum_distance<<endl;
    }

    friend ostream &operator<<(ostream&, const Matrix&);
private:
    unsigned int num_of_row;
    unsigned int num_of_col;
    vector<unsigned int> mat;
};

ostream &operator <<(ostream& os, const Matrix& mat)
{
    os <<"number of row: "<<mat.num_of_row<<" num of colume: "<<mat.num_of_col<<endl;
    for (auto a: mat.mat )
    {
        os<<std::bitset<32>(a)<<endl;
    }
    return os;
}

void parse(vector<Matrix>* matrices)
{
    string input;
    std::getline(cin,input);
    unsigned int num_of_mat;
    {
        istringstream iss(input);
        iss>> num_of_mat;
    }
    for ( unsigned int i = 0; i < num_of_mat; ++i)
    {
        std::getline(cin,input);
        unsigned int num_of_row;
        unsigned int num_of_col; 
        {
            istringstream iss(input);
            iss>> num_of_row >> num_of_col;
        }
        Matrix mat = Matrix(num_of_row, num_of_col);
        for (unsigned int j = 0; j< num_of_row; ++j)
        {
            std::getline(cin,input);
            mat.addRow(input);
        }
        (*matrices).push_back(std::move(mat));
    }
}

int main(void) {
    vector<Matrix> maxtrices;
    parse(&maxtrices);
    for(auto a: maxtrices)
    {
        //cerr <<a<<endl;
        
        a.findMinDistance();
    }
    return 0;
}

int main_test(void){
    for (unsigned int i = 0 ; i <=15; ++i)
    {
        cout << add_module(i, 4)<<endl;

    } 

}
