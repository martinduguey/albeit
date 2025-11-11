#include "../../header/albeit_sparse_matrix.hpp"
#include <stdexcept>
#include <cassert>
#include <iostream>

//Builder
AlbeitSparseMatrix::AlbeitSparseMatrix(unsigned int nb_rows, unsigned int nb_columns)
:   AlbeitMatrix(nb_rows, nb_columns),
    row_index_(1, 0),
    column_index_(1, 0),
    values_(1, 1)
    {};

AlbeitSparseMatrix::AlbeitSparseMatrix(
    unsigned int nb_rows,
    unsigned int nb_columns,
    const std::vector<unsigned int>& row_index,
    const std::vector<unsigned int>& column_index,
    const std::vector<double>& values
) : AlbeitMatrix(nb_rows, nb_columns) {

    if ((row_index.size() != column_index.size()) || (row_index.size() != values.size())){
        throw std::out_of_range("Indexes and values vector size should be equals");
    }

    if ( 
        (*std::max_element(row_index.begin(), row_index.end()) >= nb_rows) ||
        (*std::max_element(column_index.begin(), column_index.end()) >= nb_columns)
    ) {
        throw std::logic_error("Can't specify indexes out of matrix space");
    }

    row_index_ = row_index;
    column_index_ = column_index;
    values_ = values;
}

AlbeitSparseMatrix::AlbeitSparseMatrix(const AlbeitSparseMatrix& m)
: AlbeitMatrix(m.nb_rows_, m.nb_columns_) {
    row_index_ = m.row_index_;
    column_index_ = m.column_index_;
    values_ = m.values_;
}

//Operator
double& AlbeitSparseMatrix::operator()(unsigned int row, unsigned int column){
    
    if (row >= this->nb_rows_ || column >= this->nb_columns_) {
        throw std::out_of_range("Indexes out of range");
    }

    for(unsigned int item = 0; item != this->row_index_.size(); ++item){

        if(this->row_index_[item] == row && this->column_index_[item] == column) {
            return this->values_[item];
        }

    }

    this->row_index_.push_back(row);
    this->column_index_.push_back(column);
    this->values_.push_back(1.0);

    return this->values_.back();

}

bool AlbeitSparseMatrix::operator==(const AlbeitSparseMatrix& m) const {
    
    if (m.nb_rows_ != this->nb_rows_ || m.nb_columns_ != this->nb_columns_) {
        return false;
    }

    std::vector<unsigned int> sub_row_index(this->row_index_.size(), 0);
    std::vector<unsigned int> sub_column_index(this->column_index_.size(), 0);
    std::vector<double> sub_values(this->values_.size(), 0.0);
    std::vector<double> reference_double(this->values_.size(), 0.0);
    std::vector<unsigned int> reference_uint(this->row_index_.size(), 0);

    std::transform (
        this->row_index_.begin(),
        this->row_index_.end(),
        m.row_index_.begin(),
        sub_row_index.begin(),
        std::minus<unsigned int>()
    );

    std::transform (
        this->column_index_.begin(),
        this->column_index_.end(),
        m.column_index_.begin(),
        sub_column_index.begin(),
        std::minus<unsigned int>()
    );

    std::transform (
        this->values_.begin(),
        this->values_.end(),
        m.values_.begin(),
        sub_values.begin(),
        std::minus<double>()
    );

    if(
        std::equal(
            sub_row_index.begin(),
            sub_row_index.end(),
            reference_uint.begin()
        )
    ){
        if(
            std::equal(
                sub_column_index.begin(),
                sub_column_index.end(),
                reference_uint.begin()
            )
        ){
            return std::equal(
                sub_values.begin(),
                sub_values.end(),
                reference_double.begin()
            );
        }
    }

    return false;
}

//Methods
double AlbeitSparseMatrix::getValue(unsigned int row, unsigned int column) const {
    
    if (row >= this->nb_rows_ || column >= this->nb_columns_) {
        throw std::out_of_range("Indexes out of range");
    }

    auto it_column = this->column_index_.begin();

    for(auto it_row = this->row_index_.begin(); it_row != this->row_index_.end(); ++it_row){

        if(*it_row == row && *it_column == column) {
            int shift = it_row - this->row_index_.begin();
            auto it_value = this->values_.begin();
            return *(it_value + shift);
        }

        ++it_column;
    }

    return 0;

}