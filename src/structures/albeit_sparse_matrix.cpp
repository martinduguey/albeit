#include "../../header/albeit_sparse_matrix.hpp"
#include <stdexcept>

//Builder
AlbeitSparseMatrix::AlbeitSparseMatrix(unsigned int nb_rows, unsigned int nb_columns)
:   AlbeitMatrix(nb_rows, nb_columns),
    row_index_(1, 0),
    column_index_(1, 0),
    values_(1, 1)
    {};


//Methods
double AlbeitSparseMatrix::getValue(unsigned int row, unsigned int column) const {
    
    if (row >= this->nb_rows_ || column >= this->nb_columns_) {
        throw std::out_of_range("Indexes out of range");
    }

    auto it = std::find(
        this->row_index_.begin(),
        this->row_index_.end(),
        row
    );

    if (
        (
            it != this->row_index_.end()
        )
        &&
        (
            std::find(
                this->column_index_.begin(),
                this->column_index_.end(),
                column
            ) != this->column_index_.end()
        )
    ) {
        int shift = it - this->row_index_.begin();
        auto itv = this->values_.begin();
        return *(itv + shift);
    }

    return 0;

}