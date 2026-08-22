#include "albeit_sparse_matrix.hpp"
#include "common/albeit_checks.hpp"
#include <stdexcept>

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

    ALBEIT_CHECK(
        row_index.size() == values.size(),
        std::out_of_range("Row index and values vectors' size should be equals")
    );

    ALBEIT_CHECK(
        (*std::max_element(row_index.begin(), row_index.end()) < nb_rows) &&
        (*std::max_element(column_ptr.begin(), column_ptr.end()) < nb_rows),
        std::logic_error("Can't specify indexes out of matrix space")
    );

    ALBEIT_CHECK(
        column_nnz.size() == nb_columns,
        std::logic_error(
            "Can't specify column_nnz with "
            "different from number of columns"
        )
    );

    ALBEIT_CHECK(
        column_ptr.size() == nb_columns + 1,
        std::logic_error(
            "Can't specify column_ptr with "
            "different size from number of columns + 1"
        )
    );

    ALBEIT_CHECK(
        column_ptr[column_ptr.size() - 1] == values.size(),
        std::logic_error(
            "Can't specify column_ptr with last element "
            "different from values size"
        )
    );

    ALBEIT_CHECK(
        values.size() <= nb_rows * nb_columns,
        std::logic_error("Can't specify values out of matrix space")
    );

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
double& AlbeitSparseMatrix::operator()(unsigned int row, unsigned int column){

    ALBEIT_CHECK(
        row < this->nb_rows_ && column < this->nb_columns_,
        std::out_of_range("Indexes out of range")
    );

    if (this->column_nnz_[column] == 0) {

        this->column_nnz_[column] += 1;
        unsigned int insert_position = this->column_ptr_[column + 1];
        std::vector<unsigned int> unit_vect(this->column_ptr_.size() - column - 1, 1);
        
        std::transform(
            this->column_ptr_.begin() + column + 1,
            this->column_ptr_.end(),
            unit_vect.begin(),
            this->column_ptr_.begin() + column + 1,
            std::plus<unsigned int>()
        );
        this->row_index_.insert(this->row_index_.begin() + insert_position, row);
        this->values_.insert(this->values_.begin() + insert_position, 1.0);
        
        return this->values_[insert_position];
    }

    unsigned int count_shift = 0;

    if (this->column_nnz_[column] != 0) {

        unsigned int start_ptr = this->column_ptr_[column];
        unsigned int end_ptr = this->column_ptr_[column + 1];

        for(unsigned int item = start_ptr; item != end_ptr; ++item){

            if(this->row_index_[item] == row) {
                return this->values_[item];
            }

            if(this->row_index_[item] < row) {
                ++count_shift;
            }
        }

    }

    this->column_nnz_[column] += 1;
    unsigned int insert_position = this->column_ptr_[column] + count_shift;
        
    if (count_shift == 0) {
        this->column_ptr_[column] = insert_position;
    }

    std::vector<unsigned int> unit_vect(this->column_ptr_.size() - column - 1, 1);
        
    std::transform(
        this->column_ptr_.begin() + column + 1,
        this->column_ptr_.end(),
        unit_vect.begin(),
        this->column_ptr_.begin() + column + 1,
        std::plus<unsigned int>()
    );
    this->row_index_.insert(this->row_index_.begin() + insert_position, row);
    this->values_.insert(this->values_.begin() + insert_position, 1.0);
        
    return this->values_[insert_position];

}

bool AlbeitSparseMatrix::operator==(const AlbeitSparseMatrix& m) const {
    
    if (m.nb_rows_ != this->nb_rows_ || m.nb_columns_ != this->nb_columns_) {
        return false;
    }

    std::vector<unsigned int> sub_row_index(this->row_index_.size(), 0);
    std::vector<unsigned int> sub_column_ptr(this->column_ptr_.size(), 0);
    std::vector<unsigned int> sub_column_nnz(this->column_nnz_.size(), 0);
    std::vector<double> sub_values(this->values_.size(), 0.0);
    
    std::vector<double> reference_double(this->values_.size(), 0.0);
    std::vector<unsigned int> reference_uint_row(this->row_index_.size(), 0);
    std::vector<unsigned int> reference_uint_column_ptr(this->column_ptr_.size(), 0);
    std::vector<unsigned int> reference_uint_column_nnz(this->column_nnz_.size(), 0);

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
        this->column_nnz_.begin(),
        this->column_nnz_.end(),
        m.column_nnz_.begin(),
        sub_column_nnz.begin(),
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
            reference_uint_row.begin()
        )
    ){
        if(
            std::equal(
                sub_column_ptr.begin(),
                sub_column_ptr.end(),
                reference_uint_column_ptr.begin()
            )
        ){
            if (
                std::equal(
                    sub_column_nnz.begin(),
                    sub_column_nnz.end(),
                    reference_uint_column_nnz.begin()
                )
            ){
                return std::equal(
                    sub_values.begin(),
                    sub_values.end(),
                    reference_double.begin()
                );
            }  
        }
    }

    return false;
}

AlbeitSparseMatrix AlbeitSparseMatrix::operator+(const AlbeitSparseMatrix& m) const {
    ALBEIT_CHECK(
        m.nb_rows_ == this->nb_rows_ && m.nb_columns_ == this->nb_columns_,
        std::logic_error("Can't add matrices with different sizes")
    );

    AlbeitSparseMatrix result(this->nb_rows_, this->nb_columns_);

    for (unsigned int row = 0; row < this->nb_rows_; ++row) {
        for (unsigned int column = 0; column < this->nb_columns_; ++column) {
            double value = this->getValue(row, column) + m.getValue(row, column);
            if (value != 0.0) {
                result(row, column) = value;
            }
        }
    }

    return result;
}

AlbeitSparseMatrix AlbeitSparseMatrix::operator-(const AlbeitSparseMatrix& m) const {
    ALBEIT_CHECK(
        m.nb_rows_ == this->nb_rows_ && m.nb_columns_ == this->nb_columns_,
        std::logic_error("Can't subtract matrices with different sizes")
    );

    AlbeitSparseMatrix result(this->nb_rows_, this->nb_columns_);

    for (unsigned int row = 0; row < this->nb_rows_; ++row) {
        for (unsigned int column = 0; column < this->nb_columns_; ++column) {
            double value = this->getValue(row, column) - m.getValue(row, column);
            if (value != 0.0) {
                result(row, column) = value;
            }
        }
    }

    return result;
}

AlbeitSparseMatrix AlbeitSparseMatrix::operator*(const AlbeitSparseMatrix& m) const {
    ALBEIT_CHECK(
        this->nb_columns_ == m.nb_rows_,
        std::logic_error("Can't multiply matrices with incompatible sizes")
    );

    AlbeitSparseMatrix result(this->nb_rows_, m.nb_columns_);

    for (unsigned int row = 0; row < this->nb_rows_; ++row) {
        for (unsigned int column = 0; column < m.nb_columns_; ++column) {
            double value = 0.0;
            for (unsigned int k = 0; k < this->nb_columns_; ++k) {
                value += this->getValue(row, k) * m.getValue(k, column);
            }
            if (value != 0.0) {
                result(row, column) = value;
            }
        }
    }

    return result;
}

//Methods
double AlbeitSparseMatrix::getValue(unsigned int row, unsigned int column) const {

    ALBEIT_CHECK(
        row < this->nb_rows_ && column < this->nb_columns_,
        std::out_of_range("Indexes out of range")
    );

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