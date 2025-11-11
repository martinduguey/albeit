#ifndef __ALBEIT_SPARSE_MATRIX_HPP__
#define __ALBEIT_SPARSE_MATRIX_HPP__

#include "albeit_matrix.hpp"
#include <vector>

class AlbeitSparseMatrix : public AlbeitMatrix{

    public:

        //Builder
        AlbeitSparseMatrix(unsigned int nb_rows, unsigned int nb_columns);
        AlbeitSparseMatrix(
            unsigned int nb_rows,
            unsigned int nb_columns,
            const std::vector<unsigned int>& row_index,
            const std::vector<unsigned int>& column_index,
            const std::vector<double>& values
        );
        AlbeitSparseMatrix(const AlbeitSparseMatrix& m);
        ~AlbeitSparseMatrix() = default;

        //Operator
        double& operator()(unsigned int row, unsigned int column);
        bool operator==(const AlbeitSparseMatrix& m) const;

        //Methods
        double getValue(unsigned int row, unsigned int column) const;

    private:
        std::vector<unsigned int> row_index_;
        std::vector<unsigned int> column_index_;
        std::vector<double> values_;

};

#endif