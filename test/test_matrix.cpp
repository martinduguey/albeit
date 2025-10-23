#include "../albeit-code/structures/albeit_matrix.hpp"

#include <vector>

//Tests
static void test_init_albeit_matrix() {
    AlbeitMatrix M(int nb_rows = 8, int nb_columns = 12);
}

//Runner
static void run(const char * name, void (*f)()) {
    printf("%s ", name);
    fflush(stdout);
    f();
    printf("PASSED\n");
}

//Main
int main(){
    run("test_init_albeit_matrix", test_init_albeit_matrix);
    return EXIT_SUCCESS;
}