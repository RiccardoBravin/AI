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

double xp(int x);

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    NeuralNetwork math (vector <int> {1, 2, 20, 1});
    vector<double> input {0};
    vector<double> result {0};

    double error = 1;
    for (int i = 0; i < 200000 && error > 0.001; i++){

        double start = rand()%50;
        input[0] = start;
        result[0] = xp(start)/10000;
        math.train(input, result);
        
        if(i % 1000 == 0){
            start = rand()%50;
            input[0] = start;
            error = abs(xp(start)/10000 - math.feedForward(input)[0]);
            cout << error << endl;
        } 
    }
    
    for (int i = 0; i < 10; i++)
    {
        double start = rand()%50;
        input[0] = start;
        cout << endl << math.feedForward(input)[0]*10000 << endl;
        cout << xp(start) << endl;    
    }
    
    
    
    

    /*int max = 0;
    for (int i = 1; i < 100; i++)
    {   
        int x = i; 
        while(x != 1){
            x = xp(x);
            if(x > max) max = x;
        }
    }

    cout << max;*/



    return 0;
}


double xp(int x){
    if(x % 2 == 0){
        x/=2;
    }else{
        x = 3 * x + 1;
    }
    return double(x);
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