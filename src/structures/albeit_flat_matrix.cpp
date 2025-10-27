#include "../../header/albeit_flat_matrix.hpp"

//Builder
AlbeitFlatMatrix::AlbeitFlatMatrix(int nb_rows, int nb_columns)
: AlbeitMatrix(nb_rows, nb_columns){
    int size = nb_rows * nb_columns;
    values_ = new double[size](); 
}

AlbeitFlatMatrix::~AlbeitFlatMatrix(){
    if (values_ != nullptr){
        delete[] values_;
    }
}

double& AlbeitFlatMatrix::getValue(int row, int column){
    int nb_columns = this->getNbColumns();
    return values_[row * nb_columns + column];
}