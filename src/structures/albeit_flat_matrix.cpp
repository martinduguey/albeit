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

bool AlbeitFlatMatrix::operator==(const AlbeitFlatMatrix& m) const {

    if (m.nb_rows_ != this->nb_rows_ || m.nb_columns_ != this->nb_columns_) {
        return false;
    }

    std::vector<double> sub_values(this->nb_rows_ * this->nb_columns_, 0.0);
    std::vector<double> reference(this->nb_rows_ * this->nb_columns_, 0.0);
    
    std::transform (
        this->values_.begin(),
        this->values_.end(),
        m.values_.begin(),
        sub_values.begin(),
        std::minus<double>()
    );

    return std::equal(sub_values.begin(), sub_values.end(), reference.begin());
}

AlbeitFlatMatrix AlbeitFlatMatrix::operator+(const AlbeitFlatMatrix& m) const {

    if (m.nb_rows_ != this->nb_rows_ || m.nb_columns_ != this->nb_columns_) {
        throw std::length_error("Matrix of different size are not additive");
    }

    std::vector<double> sum_values(this->nb_rows_ * this->nb_columns_, 0.0);
    
    std::transform (
        this->values_.begin(),
        this->values_.end(),
        m.values_.begin(),
        sum_values.begin(),
        std::plus<double>()
    );

    return AlbeitFlatMatrix(this->nb_rows_, this->nb_columns_, sum_values);
}

AlbeitFlatMatrix AlbeitFlatMatrix::operator-(const AlbeitFlatMatrix& m) const {

    if (m.nb_rows_ != this->nb_rows_ || m.nb_columns_ != this->nb_columns_) {
        throw std::length_error("Matrix of different size are not additive");
    }

    std::vector<double> sub_values(this->nb_rows_ * this->nb_columns_, 0.0);
    
    std::transform (
        this->values_.begin(),
        this->values_.end(),
        m.values_.begin(),
        sub_values.begin(),
        std::minus<double>()
    );

    return AlbeitFlatMatrix(this->nb_rows_, this->nb_columns_, sub_values);
}


//Methods
const double& AlbeitFlatMatrix::getValue(unsigned int row, unsigned int column) const {

    if (row >= this->nb_rows_ || column >= this->nb_columns_) {
        throw std::out_of_range("Indexes out of range");
    }

    return values_[row * this->nb_columns_ + column];
}