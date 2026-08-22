#include <iostream>

#define CHECK_BINARY(test, x, y) do {\
    if (!((x) test (y))) {\
        std::cerr << "ERROR in " __FILE__ ":" << __LINE__\
             << ": CHECK violated: \"" #x " " #test " " #y "\" (values: "\
            << (x) << " " #test " " << (y) <<  ")" << std::endl;\
        exit (1);\
    }\
} while(0)

#define CHECK_EQ(x, y) CHECK_BINARY(==, x, y)