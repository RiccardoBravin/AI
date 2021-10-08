
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <utility>

#include <chrono>

using namespace std;

#define UINT unsigned int



class BadSizeException: public exception{
  virtual const char* what() const throw()
  {
    return "The size of the passed Matrix is not suitable for the operation asked";
  }
};

class Matrix{
     private:
        UINT nRow;
        UINT nCol;
        vector<vector<double>> matrix;
        static constexpr int MAXTHREAD = 4; 

     public:
        Matrix(){
            nRow = 0;
            nCol = 0;
            matrix = vector<vector<double>>(nRow, vector<double>(nCol));
        }

        Matrix(UINT rowsNumber, UINT columsNumber){
            nRow = rowsNumber;
            nCol = columsNumber;
            matrix = vector<vector<double>>(nRow, vector<double>(nCol));

        }

        Matrix(UINT rowsNumber, UINT columsNumber, double number){
            nRow = rowsNumber;
            nCol = columsNumber;
            matrix = vector<vector<double>>(nRow, vector<double>(nCol));
            initialize(number);
        }

        Matrix(const Matrix& m){
            nRow = m.get_rows();
            nCol = m.get_columns();
            matrix = vector<vector<double>>(nRow, vector<double>(nCol));
            
            for(UINT i = 0; i < nRow; i++){
                for(UINT j = 0; j < nCol; j++){
                    matrix[i][j] = m.get(i,j);
                }
            }       
        }

        Matrix(const vector<double>& v){
            nRow = v.size();
            nCol = 1;
            matrix = vector<vector<double>>(nRow, vector<double>(nCol));
            
           for(UINT i = 0; i < nRow; i++){
                matrix[i][0] = v[i];
            }
        }

        ~Matrix(){
            //?????
        }

        UINT get_columns() const {return nCol;}
        const UINT get_rows() const {return nRow;}
        double get(UINT row, UINT col) const {return matrix[row][col];}
        void set(UINT row, UINT col, double num){matrix[row][col] = num;}
        UINT size(){return nRow*nCol;};

        void initialize(double number);
        void initialize()   {initialize(0);}
        void randomize();

        Matrix dot(Matrix& m);

        Matrix m_dot(Matrix& m);
        void r_c_dot(Matrix& m, int& row, int& , Matrix& res, mutex& mtx);

        void transpose();

        vector<double> to_vector();

        friend ostream& operator<< (ostream& str, Matrix& matrix);
};


void Matrix::initialize(double number){
    for(UINT i = 0; i < nRow; i++){
        for(UINT j = 0; j < nCol; j++){
            matrix[i][j] = number;
        }             
    }
}

void Matrix::randomize(){
    for(UINT i = 0; i < nRow; i++){
        for(UINT j = 0; j < nCol; j++){
            matrix[i][j] = double(rand())/RAND_MAX*2 - 1; //numero tra -1 e 1
        }
    }
}


Matrix Matrix::dot(Matrix& m){
    if(nCol != m.get_rows()) throw BadSizeException();

    Matrix res (nRow, m.get_columns(), 0);

    for(UINT i = 0; i < nRow; i++){
        for(UINT j = 0; j < m.get_columns(); j++){
            double sum = 0;
            for(UINT k = 0; k < nCol; k++){
                sum += get(i,k) * m.get(k,j);  
            }
            res.set(i, j, sum);
        }
    }

    return res;
}

Matrix Matrix::m_dot(Matrix& m){
    if(nCol != m.get_rows()) throw BadSizeException();

    vector<thread> threads;

    int row {0};
    int col {0};

    Matrix res (nRow, m.get_columns(), 0);

    mutex mtx;

    for (int i = 0; i < MAXTHREAD; i++){   
        
        threads.push_back(thread(&Matrix::r_c_dot, this, ref(m), ref(row), ref(col), ref(res), ref(mtx))); 
    }

    for (int i = 0; i < MAXTHREAD; i++){
        threads[i].join();   
    }
    return res;
}

void Matrix::r_c_dot(Matrix& m, int& row, int& col, Matrix& res, mutex& mtx){
    int i = 0; 
    int j = 0;

    while(true){

        mtx.lock();
        

        if(col >= m.get_columns()){
            i = ++row;
            col = 0;
        }

        i = row;
        j = col;
        col++;
        
        if(row >= nRow){
            mtx.unlock();
            break;
        }

        mtx.unlock();

        
        double sum = 0;

        for (int k = 0; k < nCol; k++)
        {
            sum += get(i,k) * m.get(k,j);
        }

        res.set(i, j, sum);
        
    }
    
}

ostream& operator<< (ostream& str, Matrix& matrix){
    for(UINT i = 0; i < matrix.get_rows(); i++){
        for(UINT j = 0; j < matrix.get_columns(); j++){
            str << matrix.get(i,j) << " ";
        }             
        str << endl;
    }
    return str;
}


int main(){


    
    Matrix test (2,2,1);
    Matrix test1 (2,2,2);

    Matrix res = test.m_dot(test1);

    cout << res;
    




}