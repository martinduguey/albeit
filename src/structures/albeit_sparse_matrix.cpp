#include "../../header/albeit_sparse_matrix.hpp"
#include <stdexcept>
#include <cassert>

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

    assert(row_index.size() == column_index.size());
    assert(row_index.size() == values.size());
    assert(*std::max_element(row_index.begin(), row_index.end()) < nb_rows);
    assert(*std::max_element(column_index.begin(), column_index.end()) < nb_columns);
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