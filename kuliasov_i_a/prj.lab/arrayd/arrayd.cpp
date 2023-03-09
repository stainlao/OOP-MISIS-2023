#include <arrayd/arrayd.hpp>
#include <iostream>
#include <algorithm>


ArrayD::ArrayD(const ArrayD& a)
{
	size_ = a.size_;
	capacity_ = a.capacity_;
	dater_ = nullptr;
	if (size_ != 0){
		dater_ = new double[size_];
	}
	else dater_ = 0;
	for (ptrdiff_t i = 0; i < size_; ++i){
		dater_[i] = a.dater_[i];
	}
}
ArrayD::ArrayD(size_t size)
{
	size_ = size;
	capacity_ = size;
	if (size_ != 0){
		dater_ = new double[size_];
	}
	else dater_ = 0;
}
ArrayD& ArrayD::operator=(const ArrayD& a){
	size_ = a.size_;
	capacity_ = a.capacity_;
	dater_ = nullptr;
	if (size_ != 0) {
		dater_ = new double[size_];
	}
	else dater_ = 0;
	for (ptrdiff_t i = 0; i < size_; ++i) {
		dater_[i] = a.dater_[i];
	}
	return *this;
}
ArrayD::~ArrayD()
{
	if (dater_) delete[] dater_;
}

void ArrayD::resize(const size_t size) noexcept
{
	if (size > capacity_)
	{
		long long new_size = size;
		size_t new_capacity = std::max(new_size, size_ * 2);
		double* new_dater = new double[new_capacity];
		for (ptrdiff_t i = 0; i < size_; ++i){
			new_dater[i] = dater_[i];
		}
		delete[] dater_;
		dater_ = new_dater;
		capacity_ = new_capacity;
	}
	size_ = size;
}

void ArrayD::push_back(const double val) noexcept{
	resize(size_ + 1);
	dater_[size_ - 1] = val;
}

ptrdiff_t ArrayD::ssize() const noexcept{
	return size_;
}

double& ArrayD::operator[](const ptrdiff_t i){
	if (i < size_) {
		return dater_[i];
	}
	else throw std::invalid_argument("Element index greater than array size!");
	
}

const double& ArrayD::operator[](const ptrdiff_t i) const{
	if (i < size_) {
		return dater_[i];
	}
	else throw std::invalid_argument("Element index greater than array size!");
}
