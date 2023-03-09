#pragma once
#ifndef ARRAYD_ARRAYD_HPP_20230308
#define ARRAYD_ARRAYD_HPP_20230308

#include <iosfwd>
//#include <cstdint>

class ArrayD{
public:
	ArrayD() = default;
	ArrayD(const ArrayD&);
	ArrayD(size_t);
	ArrayD& operator=(const ArrayD&);
	~ArrayD();

	void resize(const size_t) noexcept;
	void push_back(const double) noexcept;
	ptrdiff_t ssize() const noexcept;

	double& operator[](const ptrdiff_t);
	const double& operator[](const ptrdiff_t) const;



private:
	ptrdiff_t size_ = 0;
	size_t capacity_ = 0;
	double* dater_ = nullptr;
};

#endif