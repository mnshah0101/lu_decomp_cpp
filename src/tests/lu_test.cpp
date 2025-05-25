#include "linalg/container/test_utils.hpp"
#include <iostream>

void test_tridiagonal_matrix() {
    std::cout << "\n=== Testing Tridiagonal Matrix ===\n";
    Matrix<double> A(3, 3, {
        2, -1, 0,
        -1, 2, -1,
        0, -1, 2
    });

    print_matrix(A, "Original matrix A");
    auto result = A.lu();
    
    print_matrix(result.P, "P");
    print_matrix(result.L, "L");
    print_matrix(result.U, "U");
    
    verify_lu_decomposition(A, result);
    print_row_operations(result.U.getOperations());
}

void test_singular_matrix() {
    std::cout << "\n=== Testing Singular Matrix ===\n";
    Matrix<double> A(3, 3, {
        1, 2, 3,
        2, 4, 6,
        3, 6, 9
    });

    print_matrix(A, "Original matrix A");
    auto result = A.lu();
    
    print_matrix(result.P, "P");
    print_matrix(result.L, "L");
    print_matrix(result.U, "U");
    
    verify_lu_decomposition(A, result);
    print_row_operations(result.U.getOperations());
}

void test_identity_matrix() {
    std::cout << "\n=== Testing Identity Matrix ===\n";
    Matrix<double> A(3);  // Creates 3x3 identity matrix

    print_matrix(A, "Original matrix A");
    auto result = A.lu();
    
    print_matrix(result.P, "P");
    print_matrix(result.L, "L");
    print_matrix(result.U, "U");
    
    verify_lu_decomposition(A, result);
    print_row_operations(result.U.getOperations());
}

void test_rectangular_matrix() {
    std::cout << "\n=== Testing Rectangular Matrix ===\n";
    Matrix<double> A(3, 4, {
        1, 2, 3, 4,
        2, 4, 6, 8,
        3, 6, 9, 12
    });

    print_matrix(A, "Original matrix A");
    auto result = A.lu();
    
    print_matrix(result.P, "P");
    print_matrix(result.L, "L");
    print_matrix(result.U, "U");
    
    verify_lu_decomposition(A, result);
    print_row_operations(result.U.getOperations());
}

int main() {
    test_tridiagonal_matrix();
    test_singular_matrix();
    test_identity_matrix();
    test_rectangular_matrix();
    return 0;
} 