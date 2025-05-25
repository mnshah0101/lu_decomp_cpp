#pragma once

#include <vector>
#include <stdexcept>
#include <sstream>
#include <string>
#include <algorithm>

template <typename T>
class DenseStorage
{
    using size_type = std::size_t;
    using Row = std::vector<T>;

    size_type m_rows{0};
    size_type m_cols{0};
    Row m_data;
    size_type m_size{0};

public:
    DenseStorage() noexcept = default;

    DenseStorage(const Row &init)
        : m_rows(init.size()), m_cols(1), m_data(init) {};

    DenseStorage(size_type rows, size_type cols, Row d)
        : m_rows(rows),
          m_cols(cols),
          m_data(d),
          m_size(rows * cols)
    {
        if (rows * cols != d.size())
        {
            throw std::runtime_error("Size is wrong!");
        }
    };

    DenseStorage(size_type rows, size_type cols)
        : m_rows(rows), m_cols(cols), m_data(Row(rows * cols, {})) {
            if (rows <= 0 || cols <= 0){
                throw std::runtime_error("row and col must be greater than 0");
            }
        };

    size_type getRows() const { return m_rows; };
    size_type getCols() const { return m_cols; }
    const Row &getData() const { return m_data; };
    T value(size_type idx) const { return m_data[idx]; };
    T value(size_type row, size_type col) const { return m_data[row*m_cols + col]; };
    void setValue(size_type idx, T val) { m_data[idx] = val; };
    void scaleValue(size_type idx, T val) { m_data[idx] = m_data[idx] *val; };
    void swapRanges(size_type start_a, size_type end_a,  size_type start_b, size_type end_b){
        bool overlap = std::max(start_a, start_b) < std::min(end_a, end_b);

        if (overlap){
            throw std::runtime_error("Error! cannot swap overlapping ranges");
        }
        std::swap_ranges(m_data.begin() + start_a, m_data.begin() + end_a, m_data.begin() + start_b);
    }
  
    void sumRanges(size_type start_a, size_type end_a, size_type start_b, size_type end_b, size_type start_d, size_type end_d,T scalar) {
        bool overlap = std::max(start_a, start_b) < std::min(end_a, end_b);
        if (overlap)
        {
            throw std::runtime_error("Error! cannot swap overlapping ranges");
        }
        if (end_a - start_a != end_b - start_b || end_d - start_d != end_b - start_b){
            throw std::runtime_error("Error! cannot swap unequally sized ranges");
        }
        for(int i = 0; i < end_d - start_d; i++){
            m_data[start_d + i] = m_data[start_a + i] + m_data[start_b + i] * scalar;
        }
    }
    std::string to_string() const
    {
        std::ostringstream oss;
        oss << "DenseStorage (" << m_rows << "x" << m_cols << "):\n";

        for (size_type i = 0; i < m_rows; ++i)
        {
            oss << "[ ";
            for (size_type j = 0; j < m_cols; ++j)
            {
                oss << value(i, j);
                if (j != m_cols - 1)
                    oss << ", ";
            }
            oss << " ]\n";
        }

        return oss.str();
    }
};
