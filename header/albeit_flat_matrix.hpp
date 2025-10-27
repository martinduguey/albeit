#ifndef __ALBEIT_FLAT_MATRIX_HPP__
#define __ALBEIT_FLAT_MATRIX_HPP__

#include "albeit_matrix.hpp"

class AlbeitFlatMatrix : public AlbeitMatrix{

    public:

        //Builder
        AlbeitFlatMatrix(int nb_rows, int nb_columns);
        ~AlbeitFlatMatrix();

        //Methods
        double& getValue(int row, int column);

    private:
        double* values_;

};


#endif