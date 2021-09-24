#include "matrix.hpp"
#include "neural_network.hpp"
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>

using namespace std;

ostream& operator<<(ostream& str, vector<double> v);

int main(int argc, char const *argv[])
{
    srand(time(0));

    /*Matrix test (2,5);
    
    test.initialize(0);

    cout << test;
    test.add(1);
    cout << test;
    test.subtract(2);
    cout << test;
    test.multiply(-6);
    cout << test;
    test.divide(3);
    cout << test << endl;

    Matrix test1 (2,5);
    test1.randomize();
    cout << test1;
    test1.multiply(test1);
    cout << test1 << endl;


    test = Matrix(2,3);
    test1 = Matrix(3,2);
    test.randomize();
    test1.randomize();
    cout << test << endl;
    cout << test1 << endl;
    Matrix res = test.dot(test1); 
    cout << res << endl;

    test1.transpose();
    cout << test1;

    test1.map(atan);
    cout << test1;*/


    NeuralNetwork test (vector<int> {2,2,1});
    //cout << "pesi del network inizializzato" << endl << test << endl;
    
    vector<double> input {1,0};
    vector<double> answers {1};
    
    cout << test.feedForwardAll(input)[0] << endl;
    cout << test.feedForwardAll(input)[1] << endl;
    

    //test.train(input, answers);
    //cout << test;

    return 0;
}

ostream& operator<<(ostream& str, vector<double> v){
    for(int i = 0; i < v.size(); i++){
        str << v[i] << " ";
    }
    str << endl;
    return str;
}
