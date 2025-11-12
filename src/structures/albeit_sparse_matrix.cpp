#include "../../header/albeit_sparse_matrix.hpp"
#include <stdexcept>
#include <cassert>

//Builder
AlbeitSparseMatrix::AlbeitSparseMatrix(unsigned int nb_rows, unsigned int nb_columns)
:   AlbeitMatrix(nb_rows, nb_columns),
    row_index_(1, 0),
    column_ptr_(nb_columns + 1, 1),
    column_nnz_(nb_columns, 0),
    values_(1, 1)
    {
        column_nnz_[0] = 1;
        column_ptr_[0] = 0;
    };

AlbeitSparseMatrix::AlbeitSparseMatrix(
    unsigned int nb_rows,
    unsigned int nb_columns,
    const std::vector<unsigned int>& row_index,
    const std::vector<unsigned int>& column_ptr,
    const std::vector<unsigned int>& column_nnz,
    const std::vector<double>& values
) : AlbeitMatrix(nb_rows, nb_columns) {

    if ((row_index.size() != values.size())){
        throw std::out_of_range("Row index and values vectors' size should be equals");
    }

    if ( 
        (*std::max_element(row_index.begin(), row_index.end()) >= nb_rows) ||
        (*std::max_element(column_ptr.begin(), column_ptr.end()) >= nb_rows)
    ) {
        throw std::logic_error("Can't specify indexes out of matrix space");
    }

    if (
        column_nnz.size() != nb_columns
    ) {
        throw std::logic_error(
            "Can't specify column_nnz with "
            "different from number of columns"
        );
    }

    if (
        column_ptr.size() != nb_columns + 1
    ) {
        throw std::logic_error(
            "Can't specify column_ptr with "
            "different size from number of columns + 1"
        );
    }

    if (column_ptr[column_ptr.size() - 1] != values.size()) {
        throw std::logic_error(
            "Can't specify column_ptr with last element "
            "different from values size"
        );
    }

    if (
        values.size() > nb_rows * nb_columns
    ) {
        throw std::logic_error("Can't specify values out of matrix space");
    }

    row_index_ = row_index;
    column_ptr_ = column_ptr;
    column_nnz_ = column_nnz;
    values_ = values;
}

AlbeitSparseMatrix::AlbeitSparseMatrix(const AlbeitSparseMatrix& m)
: AlbeitMatrix(m.nb_rows_, m.nb_columns_) {
    this->row_index_ = m.row_index_;
    this->column_ptr_ = m.column_ptr_;
    this->column_nnz_ = m.column_nnz_;
    this->values_ = m.values_;
}

//Operator
// double& AlbeitSparseMatrix::operator()(unsigned int row, unsigned int column){
    
//     if (row >= this->nb_rows_ || column >= this->nb_columns_) {
//         throw std::out_of_range("Indexes out of range");
//     }

//     for(unsigned int item = 0; item != this->row_index_.size(); ++item){

//         if(this->row_index_[item] == row && this->column_index_[item] == column) {
//             return this->values_[item];
//         }

//     }

//     this->row_index_.push_back(row);
//     this->column_index_.push_back(column);
//     this->values_.push_back(1.0);

//     return this->values_.back();

// }

bool AlbeitSparseMatrix::operator==(const AlbeitSparseMatrix& m) const {
    
    if (m.nb_rows_ != this->nb_rows_ || m.nb_columns_ != this->nb_columns_) {
        return false;
    }

    std::vector<unsigned int> sub_row_index(this->row_index_.size(), 0);
    std::vector<unsigned int> sub_column_ptr(this->column_ptr_.size(), 0);
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
        this->column_ptr_.begin(),
        this->column_ptr_.end(),
        m.column_ptr_.begin(),
        sub_column_ptr.begin(),
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
                sub_column_ptr.begin(),
                sub_column_ptr.end(),
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

    if (this->column_nnz_[column] == 0) {
        return 0.0;
    }

    if (this->column_nnz_[column] != 0) {

        unsigned int start_ptr = this->column_ptr_[column];
        unsigned int end_ptr = this->column_ptr_[column + 1];

        for(unsigned int item = start_ptr; item != end_ptr; ++item){

            if(this->row_index_[item] == row) {
                return this->values_[item];
            }

        }
    }

    return 0.0;
}