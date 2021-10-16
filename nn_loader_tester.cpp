#include "matrix.hpp"
#include "neural_network.hpp"
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>


using namespace std;


ostream& operator<<(ostream& str, vector<double> v);
ostream& operator<<(ostream& str, vector<int> v);

vector<double> to_percent(vector<double> x);

void save_nn(NeuralNetwork nn, fstream &str);
NeuralNetwork load_nn(fstream& str);

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    ifstream training_data ("test_data.txt");

    vector<vector<double>> images (500, vector<double>());
    vector<vector<double>> labels (500, vector<double>());


    cout << "Memorizzazione dei dati";
    
    int i = 0;
    while(!training_data.eof() && i < images.size()){
        
        
        vector<double> img {};

        string str;
        training_data >> str;
        
        
        
        for (int k = 0; k < 784; k++)
        {
            training_data >> str;
            images[i].push_back(double(stoi(str)/255));
            
        }
        
        training_data >> str;
        training_data >> str;
        
        int aux = stoi(str);

        for (int k = 0; k < 10; k++)
        {   
            if(k == aux){
                labels[i].push_back(1);
            }else{
                labels[i].push_back(0);
            }
        }

        i++;
        
    }

    cout << " completata\n";


    fstream nn ("nn abbastanza buono.txt");
    NeuralNetwork doodle = load_nn(nn);

    double error = 0;
    for(int i = 0; i < images.size(); i++){
        vector<double> result = doodle.feedForward(images[i]);
        int res_ind = distance(result.begin(), max_element(result.begin(), result.end()));
        int label_ind = distance(labels[i].begin(), max_element(labels[i].begin(), labels[i].end()));
        if(res_ind == label_ind){
            error++;
        }

        //cout << result;
        //cout<<label[i];
    }
    cout << error/images.size()*100 << "%" <<endl;

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