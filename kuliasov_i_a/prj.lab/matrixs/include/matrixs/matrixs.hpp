#pragma once
#ifndef MATRIXS_MATRIXS_HPP_20230402
#define MATRIXS_MATRIXS_HPP_20230402

#include <tuple>

class MatrixS {
public:
    using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;

public:
    explicit MatrixS(const SizeType& size = { 0, 0 });
    MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n);
    ~MatrixS();

    MatrixS(const MatrixS& other);
    MatrixS& operator=(const MatrixS& other);

    [[nodiscard]] int& at(const SizeType& elem);
    [[nodiscard]] const int& at(const SizeType& elem) const;
    [[nodiscard]] int& at(const std::ptrdiff_t i, const std::ptrdiff_t j);
    [[nodiscard]] const int& at(const std::ptrdiff_t i, const std::ptrdiff_t j) const;

    void resize(const SizeType& new_size);
    void resize(const std::ptrdiff_t i, const std::ptrdiff_t j);

    [[nodiscard]] const SizeType& ssize() const noexcept;

    [[nodiscard]] std::ptrdiff_t nRows() const noexcept;

    [[nodiscard]] std::ptrdiff_t nCols() const noexcept;

private:
    std::ptrdiff_t m_col = 0;
    std::ptrdiff_t m_row = 0;
    std::ptrdiff_t m_col_capacity = 0;
    std::ptrdiff_t m_row_capacity = 0;
    SizeType m_size = std::make_tuple(m_col, m_row);
    int* m_data = nullptr;
};

#endif