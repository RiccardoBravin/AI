#ifndef NN_LIB
#define NN_LIB

#include "matrix.hpp"
#include <vector>
#include <math.h>


class InvalidArgumentException : public exception{
    virtual const char* what() const throw()
    {
        return "The argument passed doesn't fit the requirements for the function";
    }
};

double sigmoid(double x){
    return 1/(1+exp(x));
}

class NeuralNetwork{
    private:
        vector<int> layers;
        vector<Matrix> weights;
        vector<Matrix> biases;

    public:
        NeuralNetwork(vector<int> _layers){
            if(_layers.size() < 3) throw InvalidArgumentException();
            layers = _layers;
            for(int i = 0; i < layers.size()-1; i++){
                weights.push_back(Matrix(layers[i+1], layers[i]));
                weights[i].randomize();
                biases.push_back(Matrix(layers[i+1],1,1));
            }
        }

        vector<double> feedForward(vector<double>& input);
        
        void train(vector<double>& inputs, vector<double>& results);
       


    friend ostream& operator<<(ostream& str, NeuralNetwork& nn);
};


vector<double> NeuralNetwork::feedForward(vector<double>& input){
    if (input.size() != layers[0]) throw new InvalidArgumentException;

    Matrix aux (input);

    for(int i = 0; i < layers.size()-1; i++){
        aux = weights[i].dot(aux);
        aux.add(biases[i]);
        aux.map(sigmoid);
    }

    vector<double> output = aux.to_vector();

    return output;
}

void  NeuralNetwork::train(vector<double>& inputs, vector<double>& results){
    
    Matrix outputs = feedForward(inputs);
    Matrix errors(results); //prepara 
    
    errors.subtract(outputs);
    
    Matrix transposed;
    

    for(int i = layers.size()-2; i > 0; i--){
        
        //cout << "errore:" << endl << errors << endl;
        transposed = Matrix(weights[i]);
        //cout << "presi i pesi" << endl << transposed << endl;
        transposed.transpose();
        //cout << "trasposta" << endl << transposed << endl;
        errors = transposed.dot(errors);
        //cout << "fatto prodotto" << endl << errors << endl;
    }

    
    
}

ostream& operator<<(ostream& str, NeuralNetwork& nn){
    vector<Matrix> aux = nn.weights;
    for(int i = 0; i < aux.size(); i++){
        str << aux[i] << endl;
    }

    return str;
}



#endif