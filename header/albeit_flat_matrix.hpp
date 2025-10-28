#ifndef __ALBEIT_FLAT_MATRIX_HPP__
#define __ALBEIT_FLAT_MATRIX_HPP__

#include "albeit_matrix.hpp"
#include <vector>

class AlbeitFlatMatrix : public AlbeitMatrix{

    public:

        //Builder
        AlbeitFlatMatrix(unsigned int nb_rows, unsigned int nb_columns);
        ~AlbeitFlatMatrix() = default;

        //Methods
        double& getValue(unsigned int row, unsigned int column);

    private:
        std::vector<double> values_;

};


#endif