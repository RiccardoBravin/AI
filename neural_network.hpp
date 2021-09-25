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

double grad(double x){
    return x * (1 - x);
}

class NeuralNetwork{
    private:
        vector<int> layers;
        vector<Matrix> weights;
        vector<Matrix> biases;
        double learningRate {0.1}; //valore da cambiare in base alla velocità di 

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

        vector<double> feedForward(vector<double>& input); //returns a vector
        vector<Matrix> feedForwardAll(vector<double>& input);
        
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

/*vector<Matrix> NeuralNetwork::feedForwardAll(vector<double>& input){
    if (input.size() != layers[0]) throw new InvalidArgumentException;

    vector<Matrix> values;
    Matrix aux (input);
    values.push_back(weights[0].dot(aux));
    for(int i = 0; i < layers.size()-2; i){
        values[i].add(biases[i]);
        values[i].map(sigmoid);
        i++;
        values.push_back(weights[i].dot(values[i-1]));
    }

    return values;
}*/

vector<Matrix> NeuralNetwork::feedForwardAll(vector<double>& input){
    if (input.size() != layers[0]) throw new InvalidArgumentException;

    vector<Matrix> values;
    Matrix aux (input);

    for(int i = 0; i < layers.size()-1; i++){
        aux = weights[i].dot(aux);
        aux.add(biases[i]);
        aux.map(sigmoid);
        values.push_back(aux);
    }

    return values;

}

void  NeuralNetwork::train(vector<double>& inputs, vector<double>& results){
    
    vector<Matrix> outputs = feedForwardAll(inputs);
    Matrix errors(results); //prepara i risultati in forma matriciale
    
    errors.subtract(outputs[layers.size()-2]); //calcola la differenza con i risultati attesi
    
    Matrix transposed;
    

    for(int i = layers.size()-2; i > 0; i--){
        
        /*cout << "errore:" << endl << errors << endl;
        transposed = Matrix(weights[i]);
        cout << "presi i pesi" << endl << transposed << endl;
        transposed.transpose();
        cout << "trasposta" << endl << transposed << endl;
        errors = transposed.dot(errors);
        cout << "prodotto" << endl << errors << endl;*/

        cout << "gradient:\n";
        Matrix gradient = outputs[i];
        gradient.map(grad);
        cout << "grad = " << gradient;
        cout << "errors = " << errors;
        gradient.dot(errors);
        gradient.multiply(learningRate);
         
        cout << "transposition\n";
        transposed = Matrix(weights[i]);
        transposed.transpose();
        cout << "grad = " << gradient;
        cout << "trans = " << transposed;
        Matrix deltas = gradient.dot(transposed);

        cout << "adding to actual weights\n";
        weights[i].add(deltas);
        biases[i].add(gradient);

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