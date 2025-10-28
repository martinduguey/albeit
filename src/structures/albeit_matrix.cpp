#include "../../header/albeit_matrix.hpp"

//Builder
AlbeitMatrix::AlbeitMatrix(unsigned int nb_rows, unsigned int nb_columns){
    nb_rows_ = nb_rows;
    nb_columns_ = nb_columns;
}

//Methods
unsigned int AlbeitMatrix::getNbRows() const {
    return nb_rows_;
}

unsigned int AlbeitMatrix::getNbColumns() const {
    return nb_columns_;
}