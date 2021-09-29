#include "matrix.hpp"
#include "neural_network.hpp"
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <fstream>

#include <sstream>


using namespace std;

ostream& operator<<(ostream& str, vector<double> v);

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

    fstream training_data ("training_data.txt");

    vector<vector<double>> images (0, vector<double>(784));
    vector<vector<double>> labels (0, vector<double>(1));

    //while(!training_data.eof()){
        
        
        vector<double> img;

        char str[3];
        training_data >> str;
        //training_data >> str;
        training_data.getline(str, 3, ' ');
        double x = (double)(atoi(str))/255;
        
        img.push_back(x);
        cout << x;


    //}

    cout << img;
    


    return 0;
}




ostream& operator<<(ostream& str, vector<double> v){
    for(int i = 0; i < v.size(); i++){
        str << v[i] << " ";
    }
    str << endl;
    return str;
}
