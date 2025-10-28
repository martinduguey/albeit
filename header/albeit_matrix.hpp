#ifndef __ALBEIT_MATRIX_HPP__
#define __ALBEIT_MATRIX_HPP__

class AlbeitMatrix{

    public:
    
        //Builder
        AlbeitMatrix(unsigned int nb_rows, unsigned int nb_columns);
        ~AlbeitMatrix() = default;

        //Methods
        unsigned int getNbRows() const;
        unsigned int getNbColumns() const;

    protected:
    
        unsigned int nb_rows_;
	    unsigned int nb_columns_;

};

#endif