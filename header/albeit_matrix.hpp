#ifndef __ALBEIT_MATRIX_HPP__
#define __ALBEIT_MATRIX_HPP__

class AlbeitMatrix{

    public:
    
        //Builder
        AlbeitMatrix(int nb_rows, int nb_columns);
        ~AlbeitMatrix() = default;

        //Methods
        int getNbRows() const;
        int getNbColumns() const;

    private:
    
        int nb_rows_;
	    int nb_columns_;

};

#endif