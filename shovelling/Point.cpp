#include "Point.h"

const bool operator==(const Point a, const Point b)
{
    if ( (a.x == b.x) && (a.y == b.y))
        return true;
    return false;
}
ostream& operator<<(ostream & os, const Point a)
{
    os<<"{"<<a.x<<","<<a.y<<"}";
    return os;
}

ostream& operator<<(ostream & os,const vector<vector<int>>& a)
{
    for (auto& b: a) {
        for (auto c : b) {
            os<<c<<"\t";
        }
        os<<endl;
    }
    return os;
}
ostream& operator<<(ostream & os, const vector<vector<Point>> &a)
{
    for (auto& b: a) {
        for (auto c : b) {
            os<<c<<"\t";
        }
        os<<endl;
    }
    return os;
}


ostream& operator<<(ostream & os, const vector<Point> &a)
{
    for (auto& b:a) {
        os<<b<<" ";
    }
    os<<endl;
    return os;
}
