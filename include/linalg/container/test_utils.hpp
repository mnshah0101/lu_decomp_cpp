#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"
#include <iostream>
#include <iomanip>

template<typename T>
void print_matrix(const DenseStorage<T>& mat, const std::string& name) {
    std::cout << name << ":\n";
    for (size_t i = 0; i < mat.getRows(); ++i) {
        for (size_t j = 0; j < mat.getCols(); ++j) {
            std::cout << std::setw(8) << std::setprecision(4) << mat.value(i, j) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

template<typename T>
void print_row_operations(const std::vector<RowOperation<T>>& operations) {
    std::cout << "Row operations performed:\n";
    for (const auto& op : operations) {
        std::cout << op.to_string() << "\n";
    }
    std::cout << "\n";
}

template<typename T>
void verify_lu_decomposition(const Matrix<T>& A, const LUResult<T>& result) {
    std::cout << "Verifying PA = LU:\n";
    Matrix<T> PA = result.P.matmul(A);
    Matrix<T> LU = result.L.matmul(result.U);
    
    print_matrix(PA, "PA");
    print_matrix(LU, "LU");
    
    // Calculate and print the difference
    std::cout << "Maximum difference between PA and LU: ";
    T max_diff = 0;
    for (size_t i = 0; i < PA.getRows(); ++i) {
        for (size_t j = 0; j < PA.getCols(); ++j) {
            T diff = std::abs(PA.value(i, j) - LU.value(i, j));
            max_diff = std::max(max_diff, diff);
        }
    }
    std::cout << max_diff << "\n\n";
} 