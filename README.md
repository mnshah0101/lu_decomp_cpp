# Matrix Library

A C++ library for linear algebra operations, featuring matrix and vector operations with LU decomposition support.

## Features

- Matrix operations:
  - LU decomposition with partial pivoting
  - Matrix multiplication
  - Row operations (exchange, scale, sum)
- Vector operations:
  - Addition
  - Subtraction
  - Negation
  - Element-wise multiplication
- Efficient storage using dense matrix format
- Comprehensive test suite

## Project Structure

```
.
├── include/
│   └── linalg/
│       └── container/
│           ├── DenseStorage.hpp  # Base class for matrix storage
│           ├── Matrix.hpp        # Matrix class with LU decomposition
│           ├── Vector.hpp        # Vector class with operations
│           └── test_utils.hpp    # Testing utilities
├── src/
│   ├── tests/
│   │   ├── lu_test.cpp          # LU decomposition tests
│   │   └── vector_test.cpp      # Vector operation tests
│   └── main.cpp                 # Example usage
└── CMakeLists.txt              # Build configuration
```

## Building the Project

### Prerequisites

- CMake (version 3.10 or higher)
- C++17 compatible compiler

### Build Steps

```bash
# Create and enter build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Run tests
./lu_test
./vector_test
./matrix_test
```

## Usage Examples

### Matrix LU Decomposition

```cpp
#include "linalg/container/Matrix.hpp"

// Create a matrix
Matrix<double> A(3, 3, {
    2, -1, 0,
    -1, 2, -1,
    0, -1, 2
});

// Perform LU decomposition
auto result = A.lu();

// Access P, L, and U matrices
Matrix<double> P = result.P;
Matrix<double> L = result.L;
Matrix<double> U = result.U;
```

### Vector Operations

```cpp
#include "linalg/container/Vector.hpp"

// Create vectors
Vector<double> v1({1.0, 2.0, 3.0});
Vector<double> v2({4.0, 5.0, 6.0});

// Vector operations
auto sum = v1 + v2;      // Addition
auto diff = v1 - v2;     // Subtraction
auto neg = -v1;          // Negation
auto prod = v1 * v2;     // Element-wise multiplication
```

## Testing

The project includes comprehensive tests for both matrix and vector operations:

- `lu_test.cpp`: Tests LU decomposition with various matrix types:
  - Tridiagonal matrices
  - Singular matrices
  - Identity matrices
  - Rectangular matrices

- `vector_test.cpp`: Tests vector operations:
  - Addition
  - Subtraction
  - Negation
  - Element-wise multiplication

## Error Handling

The library includes error checking for:
- Matrix dimension mismatches
- Invalid row/column indices
- Overlapping ranges in row operations
- Size mismatches in vector operations

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details. # lu_decomp_cpp
