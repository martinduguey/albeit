#include "../../header/albeit_flat_matrix.hpp"

//Builder
AlbeitFlatMatrix::AlbeitFlatMatrix(unsigned int nb_rows, unsigned int nb_columns)
: AlbeitMatrix(nb_rows, nb_columns), values_(nb_rows * nb_columns, 0) {}; 

AlbeitFlatMatrix::AlbeitFlatMatrix(
    unsigned int nb_rows, unsigned int nb_columns, const std::vector<double>& values
) : AlbeitMatrix(nb_rows, nb_columns) {
    values_ = values;
}

AlbeitFlatMatrix::AlbeitFlatMatrix(const AlbeitFlatMatrix& m)
: AlbeitMatrix(m.getNbRows(), m.getNbColumns()) {
    values_ = m.values_;
}

//Methods
const double& AlbeitFlatMatrix::getValue(unsigned int row, unsigned int column) const {
    unsigned int nb_columns = this->getNbColumns();
    return values_[row * nb_columns + column];
}