#include <iostream>

double my_max(double lhs, double rhs) {
    return (rhs - lhs > 0 ? rhs : lhs);
}

double my_min(double lhs, double rhs) {
    return (rhs - lhs > 0 ? lhs : rhs);
}

double my_abs(double lhs) {
    return (lhs >= 0 ? lhs : (-1) * lhs);
}

namespace geo2d {
    namespace orto {
        class Quad {
        public:
            virtual ~Quad() = 0;
            virtual Quad* Scale(const double parametr)const = 0;
            virtual Quad* Intersection(const Quad& rhs)const = 0;
            virtual Quad* Union(const Quad& rhs) const = 0;
            virtual std::pair<double, double> GetCoordinates() const = 0;
            virtual double GetXlength() const = 0;
            virtual double GetYlength() const = 0;
        };

        Quad::~Quad() {};

        class Rect : public Quad {
        public:
            Rect(Rect&& anoth) noexcept {
                x_center_ = std::move(anoth.x_center_);
                y_center_ = std::move(anoth.y_center_);
                x_length_ = std::move(anoth.x_length_);
                y_length_ = std::move(anoth.y_length_);
                std::cout << "good";
            }
            Rect(double x_center, double y_center, double x_length, double y_length)
                : x_center_(x_center), y_center_(y_center), x_length_(x_length),
                y_length_(y_length) {};

            Quad* Scale(const double parametr) const override {
                Rect* r = new Rect(x_center_, y_center_, x_length_ * std::sqrt(parametr),
                    y_length_ * std::sqrt(parametr));
                return r;
            }
            Quad* Union(const Quad& rhs) const override {
                std::pair<double, double>lhs1 = { x_center_ + (x_length_ / 2),y_center_ + (y_length_ / 2) };
                std::pair<double, double>lhs3 = { x_center_ - (x_length_ / 2),y_center_ - (y_length_ / 2) };
                double rhs_x_center = rhs.GetCoordinates().first;
                double rhs_y_center = rhs.GetCoordinates().second;
                double rhs_x_length = rhs.GetXlength();
                double rhs_y_length = rhs.GetYlength();
                std::pair<double, double> rhs1 = { rhs_x_center + (rhs_x_length / 2),rhs_y_center + (rhs_y_length / 2) };
                std::pair<double, double> rhs3 = { rhs_x_center - (rhs_x_length / 2),rhs_y_center - (rhs_y_length / 2) };
                std::pair<double, double> new1 = { my_max(lhs1.first, rhs1.first),my_max(lhs1.second,rhs1.second) };
                std::pair<double, double> new3 = { my_min(lhs3.first, rhs3.first),my_min(lhs3.second,rhs3.second) };

                double new_x_length = my_abs(new1.first - new3.first);
                double new_y_length = my_abs(new1.second - new3.second);
                double new_x_center = (new1.first + new3.first) / 2;
                double new_y_center = (new1.second + new3.second) / 2;
                Rect* r = new Rect(new_x_center, new_y_center, new_x_length, new_y_length);
                return r;
            }
            Quad* Intersection(const Quad& rhs) const override {
                std::pair<double, double>lhs1 = { x_center_ + (x_length_ / 2),y_center_ + (y_length_ / 2) };
                std::pair<double, double>lhs3 = { x_center_ - (x_length_ / 2),y_center_ - (y_length_ / 2) };
                double rhs_x_center = rhs.GetCoordinates().first;
                double rhs_y_center = rhs.GetCoordinates().second;
                double rhs_x_length = rhs.GetXlength();
                double rhs_y_length = rhs.GetYlength();
                std::pair<double, double> rhs1 = { rhs_x_center + (rhs_x_length / 2),rhs_y_center + (rhs_y_length / 2) };
                std::pair<double, double> rhs3 = { rhs_x_center - (rhs_x_length / 2),rhs_y_center - (rhs_y_length / 2) };
                std::pair<double, double> new1 = { my_min(lhs1.first, rhs1.first),my_min(lhs1.second,rhs1.second) };
                std::pair<double, double> new3 = { my_max(lhs3.first, rhs3.first),my_max(lhs3.second,rhs3.second) };
                double new_x_length = my_abs(new1.first - new3.first);
                double new_y_length = my_abs(new1.second - new3.second);
                double new_x_center = (new1.first + new3.first) / 2;
                double new_y_center = (new1.second + new3.second) / 2;
                Quad&& a = Rect(new_x_center, new_y_center, new_x_length, new_y_length);
                //Rect* r = new Rect(new_x_center, new_y_center, new_x_length, new_y_length);
                return &a;
            }
            std::pair<double, double> GetCoordinates() const {
                return { x_center_,y_center_ };
            }
            double GetXlength() const override {
                return x_length_;
            }
            double GetYlength() const override {
                return x_length_;
            }
            ~Rect() override {};
        private:
            double x_center_ = 0;
            double y_center_ = 0;
            double x_length_ = 0;
            double y_length_ = 0;
        };
    }
}


int main() {

    geo2d::orto::Rect a2(-2, -1, 2, 2);
    geo2d::orto::Rect a1(1, 1, 6, 4);
    auto a3 = a1.Union(a2);
    std::cout << a3->GetCoordinates().first << ' ' << a3->GetCoordinates().second << ' '
        << a3->GetXlength() << ' ' << a3->GetYlength() << std::endl;
}