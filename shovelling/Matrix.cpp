#include "Matrix.h"
#include "Point.h"
#include "Mincost_calculation.h"

void Matrix::minimum_work() const
{
    Point pA;
    Point pB;
    Point pC;
    Point pD;
    for (int i = 0; i< num_of_row; ++i) {
        for (int j = 0; j < num_of_col;++j) {
            if( mat[i][j] == 'A') {
                pA={j,i};
            } else if ( mat[i][j] == 'B') {
                pB={j,i};
            } else if ( mat[i][j] == 'C') {
                pC={j,i};
            } else if ( mat[i][j] == 'D') {
                pD={j,i};
            }
        }
    }
    Cost_map::set_matrix(this);
    Cost_map cost_map_A{pA};
    Cost_map cost_map_B{pB};
    Cost_map cost_map_C{pC};
    #if 0
    Cost_map cost_map_D{pD};
    cerr<<"print cost mapA"<<endl;
    cerr<<cost_map_A.get_cost_map();
    cerr<<"print cost mapB"<<endl;
    cerr<<cost_map_B.get_cost_map();
    cerr<<"print cost mapC"<<endl;
    cerr<<cost_map_C.get_cost_map();
    //cerr<<"print cost mapD"<<endl;
    //cerr<<cost_map_D.get_cost_map();
    cerr<<"print preceded map"<<endl;
    cerr<<cost_map_A.get_preceded_map();
    #endif
    Mincost_calculation(pD,cost_map_A,cost_map_B,cost_map_C);
}

ostream &operator <<(ostream& os, const Matrix& matrix)
{
    os <<"number of row: "<<matrix.number_of_row()<<" num of colume: "<<matrix.number_of_col()<<endl;
    for (auto i = 0; i< matrix.number_of_row(); ++i) {
        for (auto j = 0; j < matrix.number_of_col();++j) {
            os<<matrix[i][j]<<"\t";
        }
        os<<endl;
    }
    return os;
}


vector<Point> Matrix::find_traversable_adjacent_cell(Point p) const
{
    vector<Point> adjs;
    vector<Point> traversable_adjs;
    #if 0
    if ((p.y >= num_of_row) && (p.y <0) &&(p.x >= num_of_col) && (p.x <0)) 
    {
        throw 101;
    }
    #endif
    if( (p.x +1) < num_of_col ) adjs.push_back(Point{p.x+1,p.y});
    if( (p.x -1) >= 0 ) adjs.push_back(Point{p.x-1,p.y});
    if( (p.y +1) < num_of_row ) adjs.push_back(Point{p.x,p.y+1});
    if( (p.y -1) >= 0 ) adjs.push_back(Point{p.x,p.y-1});
    for( auto adj : adjs) {
        if (mat[adj.y][adj.x] != '#') {
            traversable_adjs.push_back(adj);
        }
    }
    return traversable_adjs;
}

vector<Matrix> parse()
{
    string input;
    vector<Matrix> matrices;
    while(true)
    {
        int num_of_row;
        int num_of_col;
        {
            std::getline(cin,input);
            istringstream iss(input);
            iss>> num_of_col>> num_of_row;
            if( (0 == num_of_col ) && (0 == num_of_row)) {
                return matrices;
            }
            
        }
        Matrix mat(num_of_row, num_of_col);

        for (unsigned int i = 0; i< num_of_row; ++i)
        {
            std::getline(cin,input);
            mat.add_row(move(input));
        }
        matrices.push_back(move(mat));
        std::getline(cin,input);
    }
}

