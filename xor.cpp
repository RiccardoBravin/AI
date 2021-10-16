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
ostream& operator<<(ostream& str, vector<int> v);

vector<double> to_percent(vector<double> x);

void save_nn(NeuralNetwork nn, fstream &str);
NeuralNetwork load_nn(fstream& str);

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    fstream str ("nn.txt");


    NeuralNetwork xxor (vector <int> {2,2,1});
    vector<vector<double>> inputs {{0,1},{1,0},{0,0},{1,1}};
    vector<vector<double>> outputs {{1},{1},{0},{0}};

    for(int i = 0; i < 5000; i++){
        int aux = rand()%4;
        xxor.train(inputs[aux], outputs[aux]);
    }

    //cout << xxor.feedForward(inputs[0]);
    //cout << xxor.feedForward(inputs[1]);
    //cout << xxor.feedForward(inputs[2]);
    //cout << xxor.feedForward(inputs[3]);
    
    save_nn(xxor, str);
    str = fstream("nn.txt");
    NeuralNetwork loaded = load_nn(str);

    cout << loaded.feedForward(inputs[0]);
    cout << loaded.feedForward(inputs[1]);
    cout << loaded.feedForward(inputs[2]);
    cout << loaded.feedForward(inputs[3]);

    return 0;
}

ostream& operator<<(ostream& str, vector<double> v){
    for(int i = 0; i < v.size(); i++){
        str << v[i] << " ";
    }
    str << endl;
    return str;
}

ostream& operator<<(ostream& str, vector<int> v){
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



void save_nn(NeuralNetwork nn, fstream &str){
    vector<int> layers = nn.get_size();
    str << layers << "\\" << endl;
    for(int i = 0; i < layers.size()-1; i++){
        Matrix w = nn.get_weight(i);
        Matrix b = nn.get_bias(i); 
        str << w;
        str << b;
    }
    
}

NeuralNetwork load_nn(fstream& str){
    vector<int> layers;
    vector<Matrix> weights;
    vector<Matrix> biases;

    string aux;
    str >> aux;
    
    while(aux != "\\"){
        //cout << aux<< endl<< endl;
        layers.push_back(stoi(aux));
        str >> aux;
    }

    for (int n = 0; n < layers.size()-1; n++){
        
        Matrix w (layers[n+1],layers[n]);

        for (int i = 0; i < w.get_rows(); i++){
            for (int j = 0; j < w.get_columns(); j++)
            {
                str >> aux;
                w.set(i, j, stod(aux));
            }
        }

        Matrix b (layers[n+1],1);

        for (int i = 0; i < w.get_rows(); i++){
            str >> aux;
            b.set(i, 0, stod(aux));
        }
        
        weights.push_back(w);
        biases.push_back(b);
    }
    
    return NeuralNetwork(layers, weights, biases);
}