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


    /*NeuralNetwork xxor (vector <int> {2,2,1});
    vector<vector<double>> inputs {{0,1},{1,0},{0,0},{1,1}};
    vector<vector<double>> outputs {{1},{1},{0},{0}};

    for(int i = 0; i < 20000; i++){
        int aux = rand()%4;
        xxor.train(inputs[aux], outputs[aux]);
    }

    cout << xxor.feedForward(inputs[0]);
    cout << xxor.feedForward(inputs[1]);
    cout << xxor.feedForward(inputs[2]);
    cout << xxor.feedForward(inputs[3]);*/

    

    /*
    ifstream training_data ("training_data.txt");

    vector<vector<double>> images (1000, vector<double>());
    vector<vector<double>> labels (1000, vector<double>());


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

    //out << images[0].size() << endl;
    //cout << labels[0].size();
    

    NeuralNetwork doodle (vector <int> {784, 512, 10});

    
    double err = 1;
    int x = 1;
    constexpr int BS = 20;//batch size
    while(err > 0.01){
        for(int i = 0; i < images.size()/BS; i++){
            vector<vector<double>> batch_i(&images[i*BS], &images[i*BS+BS]);
            vector<vector<double>> batch_l(&labels[i*BS], &labels[i*BS+BS]);
            doodle.batch_train(batch_i, batch_l, 10);
        
            cout << "*";

        }

        for (int k = 0; k < 10; k++)
        {
            int rnd = rand() % images.size();

            vector<double> res = doodle.feedForward(images[rnd]);

            err = 0;
            for (int i = 0; i < 10; i++)
            {
                if(labels[rnd][i] == 1){
                    err += abs(res[i] - labels[rnd][i]);
                }
            }    

            err /= 10;
        }
        
        
        
        cout << "Training " << x << " errore " << err << endl;
        x++;
    }





        string str;
        training_data >> str;
        vector<double> test_img;
        vector<double> test_lbl;
        
        for (int k = 0; k < 784; k++)
        {
            training_data >> str;
            test_img.push_back(double(stoi(str)/255));
            
        }
        
        training_data >> str;
        training_data >> str;
        
        int aux = stoi(str);

        for (int k = 0; k < 10; k++)
        {   
            if(k == aux){
                test_lbl.push_back(1);
            }else{
                test_lbl.push_back(0);
            }
        }
        
        
        i++;





    cout << to_percent(doodle.feedForward(test_img)) << endl;
    cout << test_lbl << endl;
    */

    

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