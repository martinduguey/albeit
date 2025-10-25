#include "albeit_matrix.hpp"

//Builder
AlbeitMatrix::AlbeitMatrix(int nb_rows, int nb_columns){
    nb_rows_ = nb_rows;
    nb_columns_ = nb_columns;
}

AlbeitMatrix::~AlbeitMatrix() {};

//Methods
int AlbeitMatrix::getNbRows() const {
    return nb_rows_;
}

int AlbeitMatrix::getNbColumns() const {
    return nb_columns_;
}