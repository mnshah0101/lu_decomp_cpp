#pragma once

#include "DenseStorage.hpp"
#include <vector>
#include <stdexcept>
#include <sstream>
#include <string>
#include <algorithm>

template <typename T>
class Matrix;

template <class T>
struct LUResult
{
    Matrix<T> P, L, U;
};

enum class RowOpType
{
    Exchange,
    Sum,
    Scale
};

template <typename T>
struct RowOperation
{
    RowOpType type;
    size_t r1{}, r2{}, dest{};
    T scalar{};

    std::string to_string() const
    {
        std::ostringstream o;
        switch (type)
        {
        case RowOpType::Exchange:
            o << "Swap row " << r1 << " with " << r2;
            break;
        case RowOpType::Scale:
            o << "Scale row " << r1 << " by " << scalar;
            break;
        case RowOpType::Sum:
            o << "Add " << scalar << "*row " << r2
              << " into row " << dest;
            break;
        }
        return o.str();
    }
};

template <typename T>
class Matrix : public DenseStorage<T>{
    using Row = std::vector<T>;
    using size_type = std::size_t;
    using super = DenseStorage<T>;

    T m_det;
    std::vector<RowOperation<T>> m_operations;
 
public:
    Matrix() noexcept = default;
    Matrix(int rows, int cols) : DenseStorage<T> (rows, cols){
        m_det = 0;
    };

    Matrix(size_type rows, size_type cols, Row data): DenseStorage<T> (rows, cols, data)
    {
    };

    Matrix(Row data) : DenseStorage<T> (data) {};

    Matrix(size_t n)
        : DenseStorage<T>(n, n) 
    {
        // set 1's on the diagonal
        for (size_t i = 0; i < n; ++i)
        {
            this->setValue(i * n + i, T(1));
        }
    }

    void row_scale(T scalar, size_type row){
        if (row >= super::getRows())
        {
            throw std::runtime_error("Row doesn't exist!");
        }
        size_type start = super::getCols() * row;
        for (int i = 0; i < super::getCols(); i++)
        {
            super::scaleValue(start + i, scalar);
        }
    };

    void row_exchange(size_type a, size_type b){
        if (a >= super::getRows() || b >= super::getRows())
        {
            throw std::runtime_error("Row doesn't exist!");
        }
        size_type c = super::getCols();
        size_type start_a = c * a;
        size_type start_b = c * b;

        super::swapRanges(start_a, start_a + c, start_b, start_b+ c);
    }

    void row_sum(size_t row_a, size_t row_b, T scalar, size_t destination_row ){
        if (row_a >= super::getRows() || row_b >= super::getRows() || destination_row >= super::getRows())
        {
            throw std::runtime_error("Row doesn't exist!");
        }
        size_type c = super::getCols();
        size_type start_a = c * row_a;
        size_type start_b = c * row_b;
        size_type start_d = c * destination_row;
        super::sumRanges(start_a, start_a + c, start_b, start_b + c, start_d, start_d + c, scalar);
    }

    int is_non_zero_column(size_type col, size_type start_row)
    {
        auto c = super::getCols();
        auto r = super::getRows();

        for (int i = start_row; i < r; i++)
        {
            if (super::value(i, col) != 0)
            {
                return i;
            }
        }
        return -1;
    }

    LUResult<T> lu() {
        Matrix<T> copy{*this};
        size_type c {copy.getCols()};
        size_type r{copy.getRows()};
        std::vector<RowOperation<T>> operations{};
        std::vector<int> pivot_locations{};
        size_type next_row_id = 0;

        // Initialize L and P as identity
        Matrix<T> L(r, r, std::vector<T>(r*r, T(0)));
        Matrix<T> P(r, r, std::vector<T>(r*r, T(0)));
        for (size_type i = 0; i < r; ++i) {
            L.setValue(i*r + i, T(1));
            P.setValue(i*r + i, T(1));
        }

        //lets get the pivot positions
        for(size_type col = 0; col< c; col++){
            int nonzero_row_id = is_non_zero_column(col, next_row_id);
            if (nonzero_row_id < 0){
                pivot_locations.push_back(-1);
                continue;
            }
            if (nonzero_row_id != static_cast<int>(next_row_id))
            {
                copy.row_exchange(nonzero_row_id, next_row_id);
                // Swap rows in P as well
                P.row_exchange(nonzero_row_id, next_row_id);
                // Swap the rows in L for columns [0, col)
                for (size_type k = 0; k < col; ++k) {
                    T tmp = L.value(nonzero_row_id, k);
                    L.setValue(nonzero_row_id * r + k, L.value(next_row_id, k));
                    L.setValue(next_row_id * r + k, tmp);
                }
                RowOperation<T> op1{RowOpType::Exchange, 
                    static_cast<size_t>(nonzero_row_id), 
                    static_cast<size_t>(next_row_id)};
                operations.push_back(op1);
                nonzero_row_id = next_row_id;
            }
            pivot_locations.push_back(nonzero_row_id);

            for (size_type row = nonzero_row_id + 1; row < r; row++){
                if (copy.value(row,col) == 0){
                    continue;
                }
                T scalar = - 1 * copy.value(row, col) / copy.value(nonzero_row_id, col);
                copy.row_sum(row, nonzero_row_id, scalar, row);
                RowOperation<T> op3{RowOpType::Sum, 
                    row, 
                    static_cast<size_t>(nonzero_row_id), 
                    row, 
                    scalar};
                operations.push_back(op3);
                // Set L[row, nonzero_row_id] = -scalar
                L.setValue(row * r + nonzero_row_id, -scalar);
            }
            next_row_id++;
        }
        copy.m_operations = std::move(operations); 
        return  {P, L, copy};
    }

    std::vector<RowOperation<T>> &getOperations()
    {
        return m_operations;
    }
    const std::vector<RowOperation<T>> &getOperations() const
    {
        return m_operations;
    }

    // Matrix multiplication helper
    Matrix<T> matmul(const Matrix<T> &other) const {
        if (this->getCols() != other.getRows()) {
            throw std::runtime_error("Matrix multiplication dimension mismatch");
        }
        Matrix<T> result(this->getRows(), other.getCols());
        for (size_t i = 0; i < this->getRows(); ++i) {
            for (size_t j = 0; j < other.getCols(); ++j) {
                T sum = 0;
                for (size_t k = 0; k < this->getCols(); ++k) {
                    sum += this->value(i, k) * other.value(k, j);
                }
                result.setValue(i * other.getCols() + j, sum);
            }
        }
        return result;
    }
}; 