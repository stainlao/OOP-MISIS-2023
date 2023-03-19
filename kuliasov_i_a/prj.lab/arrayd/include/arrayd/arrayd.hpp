#pragma once
#ifndef ARRAYD_ARRAYD_HPP_20230308
#define ARRAYD_ARRAYD_HPP_20230308

#include <iosfwd>

class ArrayD{
public:
	ArrayD();
	ArrayD(const ArrayD&);
	ArrayD(const ptrdiff_t);
	ArrayD& operator=(const ArrayD&);
	~ArrayD();

	double& operator[](const ptrdiff_t);
	const double& operator[](const ptrdiff_t) const;

	ptrdiff_t Ssize() const noexcept;
	void Resize(const ptrdiff_t);

	void Insert(const ptrdiff_t, const double);
	void Remove(const ptrdiff_t);
	
	void Push_back(const double) noexcept;

private:
	ptrdiff_t size_ = 0;
	ptrdiff_t capacity_ = 0;
	double* dater_ = nullptr;
};

#endif