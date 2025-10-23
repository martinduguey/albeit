#ifndef __ALBEIT_MATRIX_HPP__
#define __ALBEIT_MATRIX_HPP__

class AlbeitMatrix{

    private:
    
        int nb_rows_;
	    int nb_columns_;
		
    public:
    
        //Builder
        AlbeitMatrix(int nb_rows, int nb_colums);
        ~AlbeitMatrix();

};

#endif