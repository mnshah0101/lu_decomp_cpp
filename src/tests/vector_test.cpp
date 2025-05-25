#include "linalg/container/Vector.hpp"
#include "linalg/container/test_utils.hpp"
#include <iostream>

void test_vector_addition() {
    std::cout << "\n=== Testing Vector Addition ===\n";
    Vector<double> v1({1.0, 2.0, 3.0});
    Vector<double> v2({4.0, 5.0, 6.0});
    
    print_matrix(v1, "Vector 1");
    print_matrix(v2, "Vector 2");
    
    auto result = v1 + v2;
    print_matrix(result, "Vector 1 + Vector 2");
}

void test_vector_subtraction() {
    std::cout << "\n=== Testing Vector Subtraction ===\n";
    Vector<double> v1({1.0, 2.0, 3.0});
    Vector<double> v2({4.0, 5.0, 6.0});
    
    print_matrix(v1, "Vector 1");
    print_matrix(v2, "Vector 2");
    
    auto result = v1 - v2;
    print_matrix(result, "Vector 1 - Vector 2");
}

void test_vector_negation() {
    std::cout << "\n=== Testing Vector Negation ===\n";
    Vector<double> v({1.0, 2.0, 3.0});
    
    print_matrix(v, "Original Vector");
    auto result = -v;
    print_matrix(result, "Negated Vector");
}

void test_vector_multiplication() {
    std::cout << "\n=== Testing Vector Multiplication ===\n";
    Vector<double> v1({1.0, 2.0, 3.0});
    Vector<double> v2({4.0, 5.0, 6.0});
    
    print_matrix(v1, "Vector 1");
    print_matrix(v2, "Vector 2");
    
    auto result = v1 * v2;
    print_matrix(result, "Vector 1 * Vector 2");
}

int main() {
    test_vector_addition();
    test_vector_subtraction();
    test_vector_negation();
    test_vector_multiplication();
    return 0;
} 