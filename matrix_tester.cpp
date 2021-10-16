#include "matrix.hpp"
#include "neural_network.hpp"
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>


using namespace std;

ostream& operator<<(ostream& str, vector<double> v);

vector<double> to_percent(vector<double> x);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
   
    Matrix test (1200,1200,1.31235512);
    Matrix test1 (1200,1200,0.123134412);

    auto t1 = chrono::high_resolution_clock::now();
    Matrix res = test.m_dot(test1);
    auto t2 = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> ms_double = t2 - t1;

    cout << "multithread " << ms_double.count() << "ms\n";


    t1 = chrono::high_resolution_clock::now();
    res = test.dot(test1);
    t2 = chrono::high_resolution_clock::now();

    ms_double = t2 - t1;
    cout << "singlethread " << ms_double.count() << "ms\n";

    //cout << res;


    return 0;
}




ostream& operator<<(ostream& str, vector<double> v){
    for(int i = 0; i < v.size(); i++){
        str << v[i] << " ";
    }
    str << endl;
    return str;
}


vector<double> to_percent(vector<double> x){
    double sum = 0;
    for (int i = 0; i < x.size(); i++)
    {
        sum += x[i];
    }

    vector<double> res;

    for (int i = 0; i < x.size(); i++)
    {
        res.push_back(x[i]/sum);
    }

    return res;
}