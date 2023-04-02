#include <matrixs/matrixs.hpp>

#include <iostream>
#include <algorithm>

using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;

MatrixS::MatrixS(const SizeType& size) {
	if (std::get<0>(size) < 0 || std::get<1>(size) < 0) {
		throw std::invalid_argument("Size can't be less than 0");
	}
	else
	{
		m_row = std::get<0>(size);
		m_col = std::get<1>(size);
		m_size = std::make_tuple(m_row, m_col);
		m_row_capacity = m_row;
		m_col_capacity = m_col;
		if (m_row == 0 || m_col == 0) {
			m_data = nullptr;
		}
		else {
			m_data = new int[m_col_capacity * m_row_capacity];
			std::fill(m_data, m_data + m_col_capacity * m_row_capacity, 0);
		}
	}
}
MatrixS::MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n) {
	if (m < 0 || n < 0) {
		throw std::invalid_argument("Size can't be less than 0");
	}
	else
	{
		m_row = m;
		m_col = n;
		m_size = std::make_tuple(m,n);
		m_row_capacity = m_row;
		m_col_capacity = m_col;
		if (m_row == 0 || m_col == 0) {
			m_data = nullptr;
		}
		else {
			m_data = new int[m_col_capacity * m_row_capacity];
			std::fill(m_data, m_data + m_col_capacity * m_row_capacity, 0);
		}
	}
}
MatrixS::~MatrixS(){
	if (m_data) {
		delete[] m_data;
		m_data = nullptr;
	}
}

MatrixS::MatrixS(const MatrixS& other) {
	m_col = other.m_col;
	m_row = other.m_row;
	m_size = other.m_size;
	m_col_capacity = other.m_col_capacity;
	m_row_capacity = other.m_row_capacity;
	if (other.m_data) {
		m_data = new int[m_col_capacity * m_row_capacity];
		std::copy(other.m_data, other.m_data + other.m_col_capacity * other.m_row_capacity, m_data);
	}
	else {
		m_data = nullptr;
	}
}
MatrixS& MatrixS::operator=(const MatrixS& other) {
	if (m_data != other.m_data)
	{
		m_col = other.m_col;
		m_row = other.m_row;
		m_size = other.m_size;
		m_col_capacity = other.m_col_capacity;
		m_row_capacity = other.m_row_capacity;
		if (other.m_data) {
			m_data = new int[m_col_capacity * m_row_capacity];
			std::copy(other.m_data, other.m_data + other.m_col_capacity * other.m_row_capacity, m_data);
		}
		else {
			m_data = nullptr;
		}
	}	
	return *this;
}

int& MatrixS::at(const SizeType& elem){
	if (std::get<0>(elem) < 0 || std::get<0>(elem) >= m_row || std::get<1>(elem) < 0 || std::get<1>(elem) >= m_col) {
		throw std::out_of_range("index out of range");
	}
	else
	{
		return (m_data[std::get<0>(elem) * m_col_capacity + get<1>(elem)]);
	}
}
const int& MatrixS::at(const SizeType& elem) const{
	if (std::get<0>(elem) < 0 || std::get<0>(elem) >= m_row || std::get<1>(elem) < 0 || std::get<1>(elem) >= m_col) {
		throw std::out_of_range("index out of range");
	}
	else
	{
		return (m_data[std::get<0>(elem) * m_col_capacity + get<1>(elem)]);
	}
}
int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j){
	if (i < 0 || i >= m_row || j < 0 || j >= m_col) {
		throw std::out_of_range("index out of range");
	}
	else
	{
		return (m_data[i * m_col_capacity + j]);
	}
}
const int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const{
	if (i < 0 || i >= m_row || j < 0 || j >= m_col) {
		throw std::out_of_range("index out of range");
	}
	else
	{
		return (m_data[i * m_col_capacity + j]);
	}
}

void MatrixS::resize(const SizeType& new_size){
	if (std::get<0>(new_size) <= 0 || std::get<1>(new_size) <= 0) {
		throw std::invalid_argument("Size can't be less than 0");
	}
	else
	{
		const ptrdiff_t& new_row = std::get<0>(new_size);
		const ptrdiff_t& new_col = std::get<1>(new_size);
		if (new_row <= m_row_capacity && new_col <= m_col_capacity) {
			m_row = new_row;
			m_col = new_col;
			m_size = std::make_tuple(m_row, m_col);
		}
		else {
			ptrdiff_t new_row_capacity = std::max(m_row_capacity * 2, new_row);
			ptrdiff_t new_col_capacity = std::max(m_col_capacity * 2, new_col);
			int* new_data = new int[new_col_capacity * new_row_capacity];
			std::fill(new_data, new_data + new_col_capacity * new_row_capacity, 0);
			for (ptrdiff_t i = 0; i < m_row; ++i) {
				for (ptrdiff_t j = 0; j < m_col; ++j) {
					new_data[i * new_col_capacity + j] = m_data[i * m_col_capacity + j];
				}
			}
			delete[] m_data;
			m_data = new_data;
			m_row = new_row;
			m_col = new_col;
			m_size = std::make_tuple(m_row, m_col);
			m_row_capacity = new_row_capacity;
			m_col_capacity = new_col_capacity;
		}
	}
}
void MatrixS::resize(const std::ptrdiff_t i, const std::ptrdiff_t j){
	if (i <= 0 || j<= 0) {
		throw std::invalid_argument("Size can't be less than 0");
	}
	else
	{
		const ptrdiff_t& new_row = i;
		const ptrdiff_t& new_col = j;
		if (new_row <= m_row_capacity && new_col <= m_col_capacity) {
			m_row = new_row;
			m_col = new_col;
			m_size = std::make_tuple(m_row, m_col);
		}
		else {
			ptrdiff_t new_row_capacity = std::max(m_row_capacity * 2, new_row);
			ptrdiff_t new_col_capacity = std::max(m_col_capacity * 2, new_col);
			int* new_data = new int[new_col_capacity * new_row_capacity];
			std::fill(new_data, new_data + new_col_capacity * new_row_capacity, 0);
			for (ptrdiff_t i = 0; i < m_row && i<new_row_capacity; ++i) {
				for (ptrdiff_t j = 0; j < m_col && j<new_col_capacity; ++j) {
					new_data[i * new_col_capacity + j] = m_data[i * m_col_capacity + j];
				}
			}
			delete[] m_data;
			m_data = new_data;
			m_row = new_row;
			m_col = new_col;
			m_size = std::make_tuple(m_row, m_col);
			m_row_capacity = new_row_capacity;
			m_col_capacity = new_col_capacity;
		}
	}
}

const SizeType& MatrixS::ssize() const noexcept{
	return m_size;
}

std::ptrdiff_t MatrixS::nRows() const noexcept{
	return m_row;
}

std::ptrdiff_t MatrixS::nCols() const noexcept{
	return m_col;
}


