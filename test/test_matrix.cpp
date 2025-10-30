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
    //
    std::vector<double> test_values2 = {1.0, 1.0, 1.0, 1.0};
    AlbeitFlatMatrix testQ(2, 2, test_values2);
    testQ(0,1) = 2.0;
    CHECK_EQ(testQ.getValue(0,0), 1.0);
    CHECK_EQ(testQ.getValue(0,1), 2.0);
    //
    testQ(0,1) += 1.0;
    CHECK_EQ(testQ.getValue(0,1), 3.0);
}

static void test_operation_albeit_flat_matrix() {

    std::vector<double> values1 = {1.0, 1.0, 1.0, 1.0};
    std::vector<double> values2 = {2.0, 2.0, 2.0, 2.0};
    AlbeitFlatMatrix M(2, 2, values1);
    AlbeitFlatMatrix N(2, 2, values2);
    AlbeitFlatMatrix P = M + N;
    CHECK_EQ(P.getValue(0,0), 3.0);
    CHECK_EQ(P.getValue(0,1), 3.0);
    CHECK_EQ(P.getValue(1,0), 3.0);
    CHECK_EQ(P.getValue(1,1), 3.0);
    //
    AlbeitFlatMatrix Q = N + M;
    bool assert1 = (P == Q);
    CHECK_EQ(assert1, true);
    //
    AlbeitFlatMatrix R = Q;
    R(1,1) += 1.0;
    bool assert2 = (Q == R);
    CHECK_EQ(assert2, false);
    //
    std::vector<double> values3 = {3.0, 3.0, 3.0, 4.0};
    AlbeitFlatMatrix S(2, 2, values3);
    bool assert3 = (R == S);
    CHECK_EQ(assert3, true);
    //
    AlbeitFlatMatrix T = M - N;
    AlbeitFlatMatrix U = N - M;
    std::vector<double> values4 = {1.0, 1.0, 1.0, 1.0};
    std::vector<double> values5 = {-1.0, -1.0, -1.0, -1.0};
    AlbeitFlatMatrix V(2, 2, values4);
    AlbeitFlatMatrix W(2, 2, values5);
    bool assert4 = (T == W);
    bool assert5 = (U == V);
    CHECK_EQ(assert4, true);
    CHECK_EQ(assert5, true);
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
    run("test_operation_albeit_flat_matrix", test_operation_albeit_flat_matrix);
    return EXIT_SUCCESS;
}