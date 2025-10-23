#ifndef __ALBEIT_MATRIX_HPP__
#define __ALBEIT_MATRIX_HPP__

template<class T>
class AlbeitMatrix
{
    private:
        const int nb_rows_;
		const int nb_columns_;
		
    public:
        AlbeitMatrix(int nb_rows, int nb_colums);
        ~AlbeitMatrix();
};

#endif