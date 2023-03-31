#include <arrayd/arrayd.hpp>

#include <iostream>
#include <algorithm>


ArrayD::ArrayD(const ArrayD& a)
{
	size_ = a.size_;
	capacity_ = a.capacity_;
	dater_ = nullptr;
	if (size_ != 0){
		dater_ = new double[capacity_];
		for (ptrdiff_t i = 0; i < size_ && i<capacity_; ++i) {
			dater_[i] = a.dater_[i];
		}
	}
	else dater_ = 0;
}
ArrayD::ArrayD(const ptrdiff_t size)
{
	size_ = size;
	capacity_ = size;
	if (size_ != 0){
		dater_ = new double[capacity_];
		for (ptrdiff_t i = 0; i < size_; ++i) dater_[i] = 0.0;
	}
	else dater_ = 0;
}
ArrayD& ArrayD::operator=(const ArrayD& a){
	if (dater_ != a.dater_) {
		size_ = a.size_;
		capacity_ = a.capacity_;
		delete[] dater_;
		dater_ = nullptr;
		if (size_ != 0) {
			dater_ = new double[capacity_];
			for (ptrdiff_t i = 0; i < size_ && i < capacity_; ++i) {
				dater_[i] = a.dater_[i];
			}
		}
		else dater_ = 0;
	}	
	return *this;
}
ArrayD::~ArrayD()
{
	if (dater_) delete[] dater_;
}

double& ArrayD::operator[](const ptrdiff_t i) {
	if (i >= size_ || i < 0) throw std::out_of_range("Index out of range");
	else return dater_[i];
}
const double& ArrayD::operator[](const ptrdiff_t i) const {
	if (i >= size_ || i < 0) throw std::out_of_range("Index out of range");
	else return dater_[i];
}

ptrdiff_t ArrayD::ssize() const noexcept {
	return size_;
}
void ArrayD::resize(const ptrdiff_t size){
	if (size <= 0) {
		throw std::invalid_argument("New size can't be less than 0");
	}
	else{
		if (size > capacity_){
			ptrdiff_t new_size = size;
			ptrdiff_t new_capacity = std::max(new_size, size_ * 2);
			double* new_dater = new double[new_capacity];
			for (ptrdiff_t i = 0; i < size_ && i<new_capacity; ++i) {
				new_dater[i] = dater_[i];
			}
			delete[] dater_;
			dater_ = new_dater;
			capacity_ = new_capacity;
		}
		for (ptrdiff_t i = size_; i < size && i<capacity_; ++i) {
			dater_[i] = 0.0;
		}
		size_ = size;
	}
	
}

void ArrayD::insert(const ptrdiff_t i, const double value){
	if (i > size_ || i < 0) throw std::invalid_argument("invalid_argument");
	else
	{
		this->push_back(value);
		for (ptrdiff_t j = size_ - 1; j > i; --j)
		{
			std::swap(dater_[j], dater_[j - 1]);
		}
	}
}
void ArrayD::remove(const ptrdiff_t i)
{
	if (i >= size_ || i < 0) throw std::out_of_range("Index out of range");
	else{
		for (ptrdiff_t j = i; j < size_ - 1; ++j)
		{
			std::swap(dater_[j], dater_[j + 1]);
		}
		--size_;
	}
}
void ArrayD::push_back(const double val) noexcept{
	resize(size_ + 1);
	dater_[size_ - 1] = val;
}
