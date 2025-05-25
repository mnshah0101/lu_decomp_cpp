#include <cstddef>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <type_traits>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>
#include "linalg/container/Matrix.hpp"
#include "linalg/container/Vector.hpp"
#include "linalg/container/test_utils.hpp"



template<typename T>
void print_matrix(const Matrix<T>& mat, const std::string& name) {
    std::cout << name << ":\n";
    for (size_t i = 0; i < mat.getRows(); ++i) {
        for (size_t j = 0; j < mat.getCols(); ++j) {
            std::cout << std::setw(8) << std::setprecision(4) << mat.value(i, j) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    std::cout << "Matrix Library Example\n";
    std::cout << "=====================\n\n";

    std::cout << "Example 1: LU Decomposition\n";
    std::cout << "-------------------------\n";
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

    std::cout << "\nExample 2: Vector Operations\n";
    std::cout << "-------------------------\n";
    Vector<double> v1({1.0, 2.0, 3.0});
    Vector<double> v2({4.0, 5.0, 6.0});
    
    print_matrix(v1, "Vector 1");
    print_matrix(v2, "Vector 2");
    
    auto sum = v1 + v2;
    print_matrix(sum, "Vector 1 + Vector 2");
    
    auto diff = v1 - v2;
    print_matrix(diff, "Vector 1 - Vector 2");
    
    auto neg = -v1;
    print_matrix(neg, "-Vector 1");
    
    auto prod = v1 * v2;
    print_matrix(prod, "Vector 1 * Vector 2");

    return 0;
}
