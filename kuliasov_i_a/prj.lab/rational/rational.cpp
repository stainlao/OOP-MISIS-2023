#include <rational/rational.hpp>
#include <iostream>
#include <string>
Rational::Rational(const int32_t num) noexcept
	: num_{ num }, den_{ 1 } {};

Rational::Rational(const int32_t num, const int32_t denom)
    : num_{ num }, den_{ denom } {
    if (den_ == 0) throw std::invalid_argument("Denominator cant be Zero!");
    normalize();
};

bool Rational::operator==(const Rational& rhs) const noexcept {
	return (num() == rhs.num() && denom() == rhs.denom());
};
bool Rational::operator!=(const Rational& rhs) const noexcept {
    return !(*this == rhs);
};
bool Rational::operator>(const Rational& rhs) const noexcept {
    return (num() * rhs.denom() > rhs.num() * denom());
};
bool Rational::operator<(const Rational& rhs) const noexcept {
    return (num() * rhs.denom() < rhs.num() * denom());
};
bool Rational::operator>=(const Rational& rhs) const noexcept {
    return (*this == rhs || *this > rhs);
};
bool Rational::operator<=(const Rational& rhs) const noexcept {
    return (*this == rhs || *this < rhs);
};

Rational Rational::operator-() const noexcept {
    return (Rational(-num(), denom()));
};
Rational Rational::operator+() const noexcept {
    return (Rational(num(), denom()));
};

Rational::operator bool() const noexcept {
    return (num() != 0);
};

Rational& Rational::operator*=(const Rational& rhs) noexcept {
    return (*this=Rational(num() * rhs.num(), denom() * rhs.denom()));
};
Rational& Rational::operator+=(const Rational& rhs) noexcept {
    return (*this = Rational(num() * rhs.denom() + denom()*rhs.num(), denom() * rhs.denom()));
};
Rational& Rational::operator-=(const Rational& rhs) noexcept {
    return (*this = Rational(num() * rhs.denom() - denom() * rhs.num(), denom() * rhs.denom()));
};
Rational& Rational::operator/=(const Rational& rhs){
    return (*this = Rational(num() * rhs.denom(), denom() * rhs.num()));
};

Rational Rational::operator++(int) noexcept {
    Rational tmp(*this);
    *this += 1;
    return tmp;
};
Rational& Rational::operator++() noexcept {
    return *this += 1;
}
Rational Rational::operator--(int) noexcept {
    Rational tmp(*this);
    *this -= 1;
    return tmp;
}
Rational& Rational::operator--() noexcept {
    return *this -= 1;
}

std::istream& Rational::read_from(std::istream& istrm) noexcept
{
    std::string temp;
    istrm >> temp;
    size_t pos_of_delimiter = temp.find('/');
    if (pos_of_delimiter == -1)
    {
        num_ = std::stoll(temp);
    }
    else
    {
        num_ = std::stoll(temp.substr(0, pos_of_delimiter));
        den_ = std::stoll(temp.substr(pos_of_delimiter+1,temp.length() - pos_of_delimiter - 1));
    }
    return istrm;
    
}
std::ostream& Rational::write_to(std::ostream& ostrm) const noexcept
{
    if (den_ != 1)
    {
        ostrm << num_ << delimiter_ << den_;
    }
    else ostrm << num_;
    return ostrm;
}

std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
    return rhs.read_from(istrm);
};
std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept
{
    return rhs.write_to(ostrm);
};

int Rational::gcd(int32_t a, int32_t b) const noexcept {
    if (b > a)
    {
        int32_t temp = b;
        b = a;
        a = temp;
    }
    return b ? gcd(b, a % b) : a;
};
void Rational::normalize() noexcept
{
    if (num_ < 0 && den_ < 0) {
        num_ = std::abs(num_);
        den_ = std::abs(den_);
    }
    else if (den_ < 0) {
        num_ *= -1;
        den_ = std::abs(den_);
    }
    int g = gcd(std::abs(num_), std::abs(den_));
    num_ /= g;
    den_ /= g;
};

