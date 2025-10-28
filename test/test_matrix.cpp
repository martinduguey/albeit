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
    //
    std::vector<double> test_values = {1.0, 1.0, 1.0, 1.0};
    AlbeitFlatMatrix testN(2, 2, test_values);
    CHECK_EQ(testN.getNbRows(), 2);
    CHECK_EQ(testN.getNbColumns(), 2);
    CHECK_EQ(testN.getValue(0,0), 1.0);
    //
    AlbeitFlatMatrix testP = testN;
    CHECK_EQ(testP.getNbRows(), 2);
    CHECK_EQ(testP.getNbColumns(), 2);
    CHECK_EQ(testP.getValue(0,0), 1.0);
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