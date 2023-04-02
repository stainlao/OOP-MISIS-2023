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

    /**
     * \brief ���������� ������� ������� ��� ��������� {i, j}
     * \param[in] elem ������� ��������
     * \return ������� �������
     * \throw std::out_of_range ���� i ��� ��������� [0, m) ��� j ��� ��������� [0, n)
     */
    [[nodiscard]] int& at(const SizeType& elem);
    [[nodiscard]] const int& at(const SizeType& elem) const;
    [[nodiscard]] int& at(const std::ptrdiff_t i, const std::ptrdiff_t j);
    [[nodiscard]] const int& at(const std::ptrdiff_t i, const std::ptrdiff_t j) const;

    /**
     * \brief ��������� ������� �������
     * \param[in] new_size ����� ������ ������� {new_m, new_n}
     * \throw std::invalid_argument ���� new_m <= 0 ��� new_n <= 0
     */
    void resize(const SizeType& new_size);
    void resize(const std::ptrdiff_t i, const std::ptrdiff_t j);

    /**
     * \return ������� ������ ������� {m, n}
     */
    [[nodiscard]] const SizeType& ssize() const noexcept;

    /**
     * \return ���������� ����� � ������� (m)
     */
    [[nodiscard]] std::ptrdiff_t nRows() const noexcept;

    /**
     * \return ���������� �������� � ������� (n)
     */
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