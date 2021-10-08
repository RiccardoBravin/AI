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

double logistic(double x){
    return 1/(1+exp(-x));
}

double sig_tan(double x){
    return (tanh(x)+1)/2;
}

double grad(double x){
    return x * (1 - x);
}

class NeuralNetwork{
    private:
        vector<int> layers;
        vector<Matrix> weights;
        vector<Matrix> biases;
        double learningRate {0.1}; //valore da cambiare in base alla velocità di allenamento

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
        void batch_train(vector<vector<double>>& inputs, vector<vector<double>>& results, int batch_size);
       


    friend ostream& operator<<(ostream& str, NeuralNetwork& nn);
};


vector<double> NeuralNetwork::feedForward(vector<double>& input){
    if (input.size() != layers[0]) throw new InvalidArgumentException;

    Matrix aux (input);

    for(int i = 0; i < layers.size()-1; i++){
        try{
            aux = weights[i].dot(aux);
        }catch(BadSizeException){
            cout << "FeedForward couldn't perform the dot product n: " << i;
            throw BadSizeException();
        }
        
        aux.add(biases[i]);
        aux.map(sig_tan);
    }

    vector<double> output = aux.to_vector();

    return output;
}


vector<Matrix> NeuralNetwork::feedForwardAll(vector<double>& input){
    if (input.size() != layers[0]) throw new InvalidArgumentException;

    vector<Matrix> values;
    Matrix aux (input);

    for(int i = 0; i < layers.size()-1; i++){
        values.push_back(aux);
        try{
            aux = weights[i].dot(aux);
        }catch(BadSizeException){
            cout << "FeedForward couldn't perform the dot product n: " << i;
            throw BadSizeException();
        }
        
        aux.add(biases[i]);
        aux.map(sig_tan);
    }
    values.push_back(aux);
    return values;

}

void  NeuralNetwork::train(vector<double>& inputs, vector<double>& results){

    
    
    vector<Matrix> outputs = feedForwardAll(inputs);
    Matrix errors(results); //prepara i risultati in forma matriciale
    
    errors.subtract(outputs.back()); //calcola la differenza con i risultati attesi
    
    for(int i = weights.size()-1; i >= 0; i--){

        //cout << "Calcolo gradiente:\n";
        Matrix gradient = outputs[i+1];
        gradient.map(grad);
        //cout << "output_val = " << gradient;
        gradient.multiply(errors);
        gradient.multiply(learningRate);

         
        //cout << "Calcolo delta\n";
        Matrix transposed = Matrix(outputs[i]);
        transposed.transpose();
        //cout << "grad = " << gradient;
        //cout << "trans = " << transposed;
        Matrix deltas = gradient.m_dot(transposed);
        //cout << "delta = " << deltas;

        //cout << "adding to actual weights\n";
        weights[i].add(deltas);
        //cout << "adding to actual bias\n";
        biases[i].add(gradient);

        
        //cout << "calcolo errori per passaggio successivo: " << endl;
        transposed = Matrix(weights[i]);
        transposed.transpose();
        errors = transposed.m_dot(errors);
        //cout << errors << endl;
        

        //cout << "\n\n";

    }
    
}

void NeuralNetwork::batch_train(vector<vector<double>> &inputs, vector<vector<double>>& results, int batch_size){
    
    vector<Matrix> average_d;
    vector<Matrix> average_g;
    for(int i = 0; i < weights.size(); i++){
        average_d.push_back(Matrix(weights[i].get_rows(), weights[i].get_columns(), 0));
        average_g.push_back(Matrix(weights[i].get_rows(), 1, 0));
    }
    
    for (int n = 0; n < batch_size; n++){
        vector<Matrix> outputs = feedForwardAll(inputs[n]);
        Matrix errors(results[n]); //prepara i risultati in forma matriciale
    
        errors.subtract(outputs.back()); //calcola la differenza con i risultati attesi
        
        for(int i = weights.size()-1; i >= 0; i--){

            //cout << "Calcolo gradiente:\n";
            Matrix gradient = outputs[i+1];
            gradient.map(grad);
            //cout << "output_val = " << gradient;
            gradient.multiply(errors);
            gradient.multiply(learningRate);

            //cout << "Calcolo delta\n";
            Matrix transposed = Matrix(outputs[i]);
            transposed.transpose();
            //cout << "grad = " << gradient;
            //cout << "trans = " << transposed;
            Matrix deltas = gradient.m_dot(transposed);
            //cout << "delta = " << deltas;
        
            average_d[i].add(deltas);
            average_g[i].add(gradient);
            
            
            //cout << "calcolo errori per passaggio successivo: " << endl;
            transposed = Matrix(weights[i]);
            transposed.transpose();
            errors = transposed.m_dot(errors);
            //cout << errors << endl;
            

        }
    }

    for(int i = weights.size()-1; i >= 0; i--){
        //cout << "adding to actual weights\n";
        weights[i].add(average_d[i]);
        //cout << "adding to actual bias\n";
        biases[i].add(average_g[i]);
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