#ifndef MATRIX_LIB
#define MATRIX_LIB

#include <iostream>
#include <vector>

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

        //scalar
        void add(double number);
        void subtract(double number)    {add(-number);}
        void multiply(double number);
        void divide(double number)  {multiply(1/number);}

        //elementwise
        void add(Matrix& m);
        void subtract(Matrix& m);
        void multiply(Matrix& m);
        void divide(Matrix& m);
        void map(double (*f)(double));

        Matrix dot(Matrix& m);

        void transpose();

        vector<double> to_vector();

        
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

void Matrix::add(double number){
    for(UINT i = 0; i < nRow; i++){
        for(UINT j = 0; j < nCol; j++){
            matrix[i][j] += number;
        }
    }
}

void Matrix::multiply(double number){
    for(UINT i = 0; i < nRow; i++){
        for(UINT j = 0; j < nCol; j++){
            matrix[i][j] *= number;
        }
    }
            
}

void Matrix::add(Matrix& m){
    if(m.get_columns() != this->get_columns() || m.get_rows() != this->get_rows()){
        throw BadSizeException();
    }
    for(UINT i = 0; i < nRow; i++){
        for(UINT j = 0; j < nCol; j++){
            matrix[i][j] += m.get(i,j);
        }
    }
}

void Matrix::subtract(Matrix& m){
    if(m.get_columns() != this->get_columns() || m.get_rows() != this->get_rows()){
        throw BadSizeException();
    }
    for(UINT i = 0; i < nRow; i++){
        for(UINT j = 0; j < nCol; j++){
            matrix[i][j] -= m.get(i,j);
        }
    }
}

void Matrix::multiply(Matrix& m){
    if(m.get_columns() != this->get_columns() || m.get_rows() != this->get_rows()){
        throw BadSizeException();
    }
    for(UINT i = 0; i < nRow; i++){
        for(UINT j = 0; j < nCol; j++){
            matrix[i][j] *= m.get(i,j);
        }
    }       
}

void Matrix::divide(Matrix& m){
    if(m.get_columns() != this->get_columns() || m.get_rows() != this->get_rows()){
        throw BadSizeException();
    }
    for(UINT i = 0; i < nRow; i++){
        for(UINT j = 0; j < nCol; j++){
            matrix[i][j] /= m.get(i,j);
        }
    }
}

void Matrix::map(double (*f)(double)){
    for(UINT i = 0; i < nRow; i++){
        for(UINT j = 0; j < nCol; j++){
            matrix[i][j] = (*f)(matrix[i][j]);
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

void Matrix::transpose(){
    
    vector<vector<double>> aux = vector<vector<double>>(nCol, vector<double>(nRow));
    for(UINT i = 0; i < nRow; i++){
        for(UINT j = 0; j < nCol; j++){
            aux[j][i] = matrix[i][j];
        }
    }
    matrix = aux;
    nCol = nRow;
    nRow = aux.size();
    
}


vector<double> Matrix::to_vector(){
    vector<double> vec;
    for(UINT i = 0; i < nRow; i++){
        for(UINT j = 0; j < nCol; j++){
            vec.push_back(matrix[i][j]);
        }
    }
    return vec;
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

#endif