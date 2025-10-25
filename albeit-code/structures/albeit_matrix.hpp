class AlbeitMatrix{

    public:
    
        //Builder
        AlbeitMatrix(int nb_rows, int nb_columns);
        virtual ~AlbeitMatrix();

        //Methods
        int getNbRows() const;
        int getNbColumns() const;

    private:
    
        int nb_rows_;
	    int nb_columns_;

};
