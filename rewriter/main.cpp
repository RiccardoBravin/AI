#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    
    ifstream input ("mnist_handwritten_train.json");
    //ifstream input ("test.json");
    ofstream output ("training_data.txt");

    string aux;

    input >> aux;
    while(!input.eof()){
        input >> aux;
        if(!aux.compare("]")) continue;
        input >> aux;
        output << "image: ";
        input >> aux;

        for(int i = 0; i < 783; i++){
            input >> aux;
            aux.pop_back();
            output << aux << " ";
        }
        input >> aux;
        output << aux;

        input >> aux;
        input >> aux;
        output << "\nlabel: ";
        input >> aux;
        output << aux << endl;
        input >> aux;

    }
    
    input.close();
    output.close(); 

    return 0;
}
