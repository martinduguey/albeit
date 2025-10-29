#include "../../header/albeit_flat_matrix.hpp"
#include <stdexcept>

//Builder
AlbeitFlatMatrix::AlbeitFlatMatrix(unsigned int nb_rows, unsigned int nb_columns)
: AlbeitMatrix(nb_rows, nb_columns), values_(nb_rows * nb_columns, 0) {}; 

AlbeitFlatMatrix::AlbeitFlatMatrix(
    unsigned int nb_rows, unsigned int nb_columns, const std::vector<double>& values
) : AlbeitMatrix(nb_rows, nb_columns) {
    values_ = values;
}

AlbeitFlatMatrix::AlbeitFlatMatrix(const AlbeitFlatMatrix& m)
: AlbeitMatrix(m.nb_rows_, m.nb_columns_) {
    values_ = m.values_;
}

//Operator
double& AlbeitFlatMatrix::operator()(unsigned int row, unsigned int column){
    if (row >= this->nb_rows_ || column >= this->nb_columns_) {
        throw std::out_of_range("Indexes out of range");
    }
    return values_[row * this->nb_columns_ + column];
}

//Methods
const double& AlbeitFlatMatrix::getValue(unsigned int row, unsigned int column) const {
    if (row >= this->nb_rows_ || column >= this->nb_columns_) {
        throw std::out_of_range("Indexes out of range");
    }
    return values_[row * this->nb_columns_ + column];
}