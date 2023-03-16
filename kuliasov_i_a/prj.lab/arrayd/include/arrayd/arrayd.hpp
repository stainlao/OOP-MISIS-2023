#pragma once
#ifndef ARRAYD_ARRAYD_HPP_20230308
#define ARRAYD_ARRAYD_HPP_20230308

#include <iosfwd>

class ArrayD{
public:
	ArrayD() = default;
	ArrayD(const ArrayD&);
	ArrayD(const ptrdiff_t);
	ArrayD& operator=(const ArrayD&);
	~ArrayD();

	double& operator[](const ptrdiff_t);
	const double& operator[](const ptrdiff_t) const;

	ptrdiff_t ssize() const noexcept;
	void resize(const ptrdiff_t);

	void insert(const ptrdiff_t, const double);
	void remove(const ptrdiff_t);
	
	void push_back(const double) noexcept;

private:
	ptrdiff_t size_ = 0;
	ptrdiff_t capacity_ = 0;
	double* dater_ = nullptr;
};

#endif