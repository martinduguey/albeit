#include "../header/albeit_matrix.hpp"
#include "../header/albeit_flat_matrix.hpp"
#include "../utils/utils_comp.hpp"

#include <vector>

//Tests
static void test_init_albeit_matrix() {
    AlbeitMatrix testM(8, 12);
    CHECK_EQ(testM.getNbRows(), 8);
    CHECK_EQ(testM.getNbColumns(), 12);
}

static void test_init_albeit_flat_matrix() {
    AlbeitFlatMatrix testM(8, 12);
    CHECK_EQ(testM.getNbRows(), 8);
    CHECK_EQ(testM.getNbColumns(), 12);
    CHECK_EQ(testM.getValue(0,0), 0);
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
    run("test_init_albeit_flat_matrix", test_init_albeit_flat_matrix);
    return EXIT_SUCCESS;
}