#include "../header/albeit_matrix.hpp"
#include "../header/albeit_flat_matrix.hpp"
#include "../header/albeit_sparse_matrix.hpp"
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

static void test_sum_sub_albeit_flat_matrix() {

    std::vector<double> values1 = {1.0, 1.0, 1.0, 1.0};
    std::vector<double> values2 = {2.0, 2.0, 2.0, 2.0};
    AlbeitFlatMatrix testM(2, 2, values1);
    AlbeitFlatMatrix testN(2, 2, values2);
    AlbeitFlatMatrix testP = testM + testN;
    CHECK_EQ(testP.getValue(0,0), 3.0);
    CHECK_EQ(testP.getValue(0,1), 3.0);
    CHECK_EQ(testP.getValue(1,0), 3.0);
    CHECK_EQ(testP.getValue(1,1), 3.0);
    //
    AlbeitFlatMatrix testQ = testN + testM;
    bool assert1 = (testP == testQ);
    CHECK_EQ(assert1, true);
    //
    AlbeitFlatMatrix testR = testQ;
    testR(1,1) += 1.0;
    bool assert2 = (testQ == testR);
    CHECK_EQ(assert2, false);
    //
    std::vector<double> values3 = {3.0, 3.0, 3.0, 4.0};
    AlbeitFlatMatrix testS(2, 2, values3);
    bool assert3 = (testR == testS);
    CHECK_EQ(assert3, true);
    //
    AlbeitFlatMatrix testT = testM - testN;
    AlbeitFlatMatrix testU = testN - testM;
    std::vector<double> values4 = {1.0, 1.0, 1.0, 1.0};
    std::vector<double> values5 = {-1.0, -1.0, -1.0, -1.0};
    AlbeitFlatMatrix testV(2, 2, values4);
    AlbeitFlatMatrix testW(2, 2, values5);
    bool assert4 = (testT == testW);
    bool assert5 = (testU == testV);
    CHECK_EQ(assert4, true);
    CHECK_EQ(assert5, true);
}

static void test_product_albeit_flat_matrix() {

    std::vector<double> values1 = {2.0, 2.0, 2.0, 2.0};
    std::vector<double> values2 = {8.0, 8.0, 8.0, 8.0};
    AlbeitFlatMatrix testA(2, 2, values1);
    AlbeitFlatMatrix testRef(2, 2, values2);
    AlbeitFlatMatrix testB = testA * testA;
    bool assert1 = (testB == testRef);
    CHECK_EQ(assert1, true);
}

static void test_init_albeit_sparse_matrix() {

    AlbeitSparseMatrix testM(8, 12);
    CHECK_EQ(testM.getNbRows(), 8);
    CHECK_EQ(testM.getNbColumns(), 12);
    CHECK_EQ(testM.getValue(0,0), 1);
    CHECK_EQ(testM.getValue(1,1), 0);
    //
    // testN
    // [1.0 0.0 0.0]
    // [0.0 2.0 0.0]
    // [0.0 0.0 0.0]
    std::vector<double> test_values = {1.0, 2.0};
    std::vector<unsigned int> test_row_index = {0, 1};
    std::vector<unsigned int> test_column_ptr = {0, 1, 2, 2};
    std::vector<unsigned int> test_column_nnz = {1, 1, 0};
    AlbeitSparseMatrix testN(
        3,
        3,
        test_row_index,
        test_column_ptr,
        test_column_nnz,
        test_values
    );
    CHECK_EQ(testN.getNbRows(), 3);
    CHECK_EQ(testN.getNbColumns(), 3);
    CHECK_EQ(testN.getValue(0,0), 1.0);
    CHECK_EQ(testN.getValue(1,1), 2.0);
    CHECK_EQ(testN.getValue(2,2), 0.0);
    //
    AlbeitSparseMatrix testP = testN;
    CHECK_EQ(testP.getNbRows(), 3);
    CHECK_EQ(testP.getNbColumns(), 3);
    CHECK_EQ(testP.getValue(1,0), 0.0);
    //
    // testQ
    // [1.0 0.0 0.0 0.0 0.0]
    // [0.0 2.0 0.0 0.0 0.0]
    // [0.0 0.0 0.0 0.0 0.0]
    // [0.0 0.0 0.0 0.0 0.0]
    // [0.0 0.0 0.0 0.0 0.0]
    // [0.0 0.0 0.0 0.0 0.0]
    // [0.0 0.0 0.0 0.0 0.0]
    // [0.0 0.0 0.0 0.0 0.0]
    std::vector<double> test_values2 = {1.0, 2.0};
    std::vector<unsigned int> test_row_index2 = {0, 1};
    std::vector<unsigned int> test_column_ptr2 = {0, 1, 2, 2, 2, 2};
    std::vector<unsigned int> test_column_nnz2 = {1, 1, 0, 0, 0};
    AlbeitSparseMatrix testQ(
        8,
        5,
        test_row_index2,
        test_column_ptr2,
        test_column_nnz2,
        test_values2
    );
    //
    testQ(0, 0) = 3.0;
    testQ(7, 4) = 36.0;
    CHECK_EQ(testQ.getValue(0,0), 3.0);
    CHECK_EQ(testQ.getValue(7,4), 36.0);
    testQ(7, 4) += 6.0;
    CHECK_EQ(testQ.getValue(7,4), 42.0);
    AlbeitSparseMatrix testR = testQ;
    bool assert1 = (testR == testQ);
    CHECK_EQ(assert1, true);
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
    run("test_sum_sub_albeit_flat_matrix", test_sum_sub_albeit_flat_matrix);
    run("test_product_albeit_flat_matrix", test_product_albeit_flat_matrix);
    run("test_init_albeit_sparse_matrix", test_init_albeit_sparse_matrix);
    return EXIT_SUCCESS;
}