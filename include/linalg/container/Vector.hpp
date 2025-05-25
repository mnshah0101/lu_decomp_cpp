#pragma once

#include "DenseStorage.hpp"
#include <cmath>
#include <type_traits>

template <typename T>
class Vector : public DenseStorage<T>
{
    using size_type = std::size_t;
    using Row = std::vector<T>;
    double m_norm;

public:
    Vector(const Row &init) : DenseStorage<T>(init)
    {
        T total = 0;
        for (T number : init)
        {
            total += number * number;
        }
        m_norm = std::sqrt(static_cast<double>(total));
    }

    Vector(size_type rows) : DenseStorage<T>(rows, 1), m_norm(0) {}

    template <typename F, typename H>
    friend Vector<std::common_type_t<F, H>> operator+(const Vector<F> &a, const Vector<H> &b)
    {
        if (a.getRows() != b.getRows())
        {
            throw std::runtime_error("Cannot add two vectors of differing sizes");
        }

        using R = std::common_type_t<F, H>;
        Vector<R> result{a.getRows()};

        for (size_t i = 0; i < a.getRows(); i++)
        {
            result.setValue(i, static_cast<R>(a.value(i) + b.value(i)));
        }

        return result;
    }

    template <typename F, typename H>
    friend Vector<std::common_type_t<F, H>> operator-(const Vector<F> &a, const Vector<H> &b)
    {
        if (a.getRows() != b.getRows())
        {
            throw std::runtime_error("Cannot subtract two vectors of differing sizes");
        }

        using R = std::common_type_t<F, H>;
        Vector<R> result{a.getRows()};

        for (size_t i = 0; i < a.getRows(); i++)
        {
            result.setValue(i, static_cast<R>(a.value(i) - b.value(i)));
        }

        return result;
    }

    template <typename F>
    friend Vector<F> operator-(const Vector<F> &a)
    {
        Vector<F> result{a.getRows()};

        for (size_t i = 0; i < a.getRows(); i++)
        {
            result.setValue(i, static_cast<F>(-1 * a.value(i)));
        }

        return result;
    }

    template <typename F, typename H>
    friend Vector<std::common_type_t<F, H>> operator*(const Vector<F> &a, const Vector<H> &b)
    {
        if (a.getRows() != b.getRows())
        {
            throw std::runtime_error("Cannot multiply two vectors of differing sizes");
        }

        using R = std::common_type_t<F, H>;
        Vector<R> result{a.getRows()};

        for (size_t i = 0; i < a.getRows(); i++)
        {
            result.setValue(i, static_cast<R>(a.value(i) * b.value(i)));
        }

        return result;
    }
}; 