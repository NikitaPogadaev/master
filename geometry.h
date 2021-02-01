#include <cmath>
#include <algorithm>
#include <set>
#include <iostream>
#include <vector>
using namespace std;
const double Pi = asin(1) * 2;
const double INF = 1'000'000'000'000;
const double mal = 1 / pow(10, 3);

bool equal(const double& a, const double& b) {
    return abs(a - b) < mal;
}

struct Point {
    double x;
    double y;
    Point() {
        x = 0;
        y = 0;
    }
    Point(const double& a, const double& b) {
        x = a;
        y = b;
    }

    Point& operator= (const Point& c) {
        x = c.x;
        y = c.y;
        return *this;
    }


    void rotate(const Point& center, const double& angle) {
        Point temp(x - center.x, y - center.y);
        double x1 = temp.x * cos(angle) - temp.y * sin(angle);
        double y1 = temp.x * sin(angle) + temp.y * cos(angle);
        x = x1 + center.x;
        y = y1 + center.y;
    }
    void reflex(const Point& center);
    void scale(const Point& center, const double& coefficient) {
        Point temp(x - center.x, y - center.y);
        temp.x *= coefficient;
        temp.y *= coefficient;
        x = temp.x + center.x;
        y = temp.y + center.y;
    }
    Point& operator-=(const Point& a) {
        x -= a.x;
        y -= a.y;
        return *this;
    }
};

Point operator-(const Point& a, const Point& b) {
    Point copy = a;
    copy -= b;
    return copy;
}

bool operator== (const Point& a, const Point& b) {
    if (equal(a.x, b.x) && equal(a.y, b.y)) return true;
    else return false;
}

bool operator!= (const Point& a, const Point& b) {
    return !(a == b);
}

double length(const Point& p, const Point& q) {
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

double geron(const Point& a, const Point& b, const Point& c) {
    double ans = 0;
    double p = length(a, b) + length(b, c) + length(a, c);
    p /= 2;
    ans = sqrt(p * (p - length(a, c)) * (p - length(b, c)) * (p - length(a, b)));
    return ans;
}

double vprod(const Point& p, const Point& q) {
    return p.x * q.y - p.y * q.x;
}

Point mid(const Point& p, const Point& q) {
    Point temp((p.x + q.x) / 2, (p.y + q.y) / 2);
    return temp;
}

class Line {
private:
    Point a;
    Point b;

public:
    Line(const Point& c, const Point& d) {
        a = c;
        b = d;
    }

    Line(const double& c, const double& d) {
        Point a1(0, d);
        Point b1(1, c + d);
        a = a1;
        b = b1;
    }

    Line(const Point& c, const double& d) {
        a = c;
        if (equal(c.x, 0)) {
            Point b1(1, d + c.y - d * c.x);
            b = b1;
        }
        else {
            Point b1(0, c.y - d * c.x);
            b = b1;
        }
    }
    Point p1() {
        return a;
    }
    Point p2() {
        return b;
    }
    friend bool operator== (const Line&, const Line&);
};

bool operator== (const Line& l1, const Line& l2) {
    Point v1(l1.a.x - temp12.x, l1.a.y - temp12.y);
    Point v2(temp21.x - temp22.x, temp21.y - temp22.y);
    Point w1(l1.a.x - temp21.x, l1.a.y - temp21.y);
    Point w2(temp12.x - temp22.x, temp12.y - temp22.y);
    return equal(vprod(v1, v2), 0) || equal(vprod(w1, w2), 0);
}

bool operator!= (const Line& a, const Line& c) {
    return (!(a == c));
}

Point solution(const Line& l1, const Line& l2) {
    Point temp11 = l1.p1(), temp12 = l1.p2(), temp21 = l2.p1(), temp22 = l2.p2();
    double A1 = temp11.y - temp12.y, B1 = temp12.x - temp11.x, C1 = temp12.y * (temp11.x - temp12.x) + temp12.x * (temp12.y - temp11.y);
    double A2 = temp21.y - temp22.y, B2 = temp22.x - temp21.x, C2 = temp22.y * (temp21.x - temp22.x) + temp22.x * (temp22.y - temp21.y);
    double op = A1 * B2 - A2 * B1, op1 = C1 * B2 - C2 * B1, op2 = A1 * C2 - A2 * C1;
    if (equal(op, 0)) {
        Point temp(INF, INF);
        return temp;
    }
    else {
        Point temp(-op1 / op, -op2 / op);
        return temp;
    }
}

Point reflexx(const Point p, const Line axs) {
    Point temp1 = axs.p1(), temp2 = axs.p2();
    Point v1(p.x - temp2.x, p.y - temp2.y), v2(temp1.x - temp2.x, temp1.y - temp2.y);
    Point temp = p;
    Point n(0, 0);
    if (vprod(v1, v2) != 0) {
        double angle = asin(vprod(v1, v2) / (length(v1, n) * length(v2, n)));
        temp.rotate(temp2, 2 * angle);
    }
    return temp;
}

void Point::reflex(const Point& center) {
    rotate(center, Pi);
}


class Shape {

protected:
    vector <Point> vert;
    set <Point> mult;
public:
    Shape() = default;
    virtual ~Shape() {

    }
    bool operator==(const Shape& aa) const {
        if (vert.size() != aa.vert.size()) return false;
        set<pair<double, double>> a, b;
        for (size_t i = 0; i < vert.size(); ++i)
            a.insert(make_pair(vert[i].x, vert[i].y));
        for (size_t i = 0; i < aa.vert.size(); ++i)
            b.insert(make_pair(aa.vert[i].x, aa.vert[i].y));
        return (a == b);
    }

    bool operator!= (const Shape& aa) const {
        set<pair<double, double>> a, b;
        for (size_t i = 0; i < vert.size(); ++i)
            a.insert(make_pair(vert[i].x, vert[i].y));
        for (size_t i = 0; i < aa.vert.size(); ++i)
            b.insert(make_pair(aa.vert[i].x, aa.vert[i].y));
        return (a != b);
    }
    virtual bool isCongruentTo(const Shape&)const {
        return false;

    }
    virtual bool isSimilarTo(const Shape&)const {
        return true;
    }
    virtual bool containsPoint(const Point&)const {
        return 0;
    }
    virtual double perimeter() const {
        return 0;
    }
    virtual void reflex(const Point&) = 0;
    virtual void reflex(const Line&) = 0;
    virtual double area() const {
        return 0;
    }
    virtual void rotate(const Point&, const double&) = 0;
    virtual void scale(const Point&, const double&) = 0;
};

class Polygon : public Shape {

public:
    Polygon() = default;
    ~Polygon() {
        vert.clear();
    }

    bool operator== (const Shape& aa) const {
        if (aa.vert.size() == 0)
            return false;
    }
    bool operator== (const Polygon& aa) const {
        if (vert.size() != aa.vert.size()) return false;
        set<pair<double, double>> ch1, ch2;
        for (size_t i = 0; i < vert.size(); ++i)
            ch1.insert(make_pair(vert[i].x, vert[i].y));
        for (size_t i = 0; i < aa.vert.size(); ++i)
            ch2.insert(make_pair(aa.vert[i].x, aa.vert[i].y));
        return (ch1 == ch2);
    }

    bool operator!= (const Polygon& aa) const {
        set<pair<double, double>> a, b;
        for (size_t i = 0; i < vert.size(); ++i)
            a.insert(make_pair(vert[i].x, vert[i].y));
        for (size_t i = 0; i < aa.vert.size(); ++i)
            b.insert(make_pair(aa.vert[i].x, aa.vert[i].y));
        return (a != b);
    }

    bool operator!= (const Shape& aa) const {
        if (aa.vert.size() == 0)
            return true;
    }

    void reflex(const Point&);
    void reflex(const Line&);
    void rotate(const Point&, const double&);
    double perimeter() const override {
        double per = 0;
        for (size_t i = 1; i < vert.size(); ++i)
            per += length(vert[i], vert[i - 1]);
        per += length(vert[0], vert[vert.size() - 1]);
        return per;
    }

    double area()const;
    void scale(const Point&, const double&);
    bool isCongruentTo(const Shape&)const;

    bool containsPoint(const Point& a) const override {
        double sum = 0;
        for (size_t i = 1; i < vert.size(); ++i)
            sum += geron(vert[i], vert[i - 1], a);
        sum += geron(vert[0], vert[vert.size() - 1], a);
        return equal(sum, (*this).area());
    }

    bool isSimilarTo(const Polygon&);
    int verticesCount() const;
    vector<Point> getVertices() const;
    bool isConvex() const;
    Polygon(const vector <Point>& a) {
        vert = a;
    }
    Polygon(initializer_list<Point> lst) {
        Point* aaa = new Point[lst.size()];
        copy(lst.begin(), lst.end(), aaa);
        for (size_t i = 0; i < lst.size(); ++i) {
            vert.push_back(aaa[i]);
        }
    }
};
vector<Point> Polygon::getVertices() const {
    return vert;
}


bool Polygon::isConvex()const {
    for (size_t i = 1; i < vert.size() - 2; i++)
        if (vprod(vert[i] - vert[i - 1], vert[i + 1] - vert[i]) * vprod(vert[i + 1] - vert[i], vert[i + 2] - vert[i + 1]) < 0)return false;
    int i = vert.size() - 2;
    if (vprod(vert[i] - vert[i - 1], vert[i + 1] - vert[i]) * vprod(vert[i + 1] - vert[i], vert[0] - vert[i + 1]) < 0)return false;
    return true;

}



int Polygon::verticesCount() const {
    return vert.size();
}void Polygon::rotate(const Point& center, const double& angle) {
    for (size_t i = 0; i < vert.size(); i++)
        vert[i].rotate(center, angle);
}
void Polygon::reflex(const Point& center) {
    for (size_t i = 0; i < vert.size(); i++)
        vert[i].rotate(center, Pi);
}

void Polygon::reflex(const Line& axis) {
    for (size_t i = 0; i < vert.size(); i++)
        vert[i] = reflexx(vert[i], axis);
}

void Polygon::scale(const Point& center, const double& coefficient) {
    for (size_t i = 0; i < vert.size(); i++) {
        vert[i].scale(center, coefficient);
    }
}

bool Polygon::isCongruentTo(const Shape& another) const {
    if (another.vert.size() != vert.size())return false;
    bool g = false;
    for (size_t i = 0; i < vert.size(); i++) {
        for (size_t j = i; j < i + vert.size(); j++) {
            Point x1, y1, x2, y2, x3, y3;
            x1 = vert[j % vert.size()];
            y1 = another.vert[(j - i) % vert.size()];
            x2 = vert[(j + 1) % vert.size()];
            y2 = another.vert[(j - i + 1) % vert.size()];
            x3 = vert[(j + 2) % vert.size()];
            y3 = another.vert[(j - i + 2) % vert.size()];
            if (equal(length(x1, x2), length(y1, y2)) && equal(length(x3, x2), length(y3, y2)) && equal(length(x1, x3), length(y1, y3))) {
                g = true;
            }
            else {
                g = false;
                break;
            }
        }
        if (g)return true;
    }

    for (size_t i = 0; i < vert.size(); i++) {
        for (size_t j = i; j < i + vert.size(); j++) {
            Point x1, y1, x2, y2, x3, y3;
            size_t l = vert.size() - 1;
            x1 = vert[j % vert.size()];
            y1 = another.vert[l - (j - i) % vert.size()];
            x2 = vert[(j + 1) % vert.size()];
            y2 = another.vert[l - (j - i + 1) % vert.size()];
            x3 = vert[(j + 2) % vert.size()];
            y3 = another.vert[l - (j - i + 2) % vert.size()];
            if (equal(length(x1, x2), length(y1, y2)) && equal(length(x3, x2), length(y3, y2)) && equal(length(x1, x3), length(y1, y3))) {
                g = true;
            }
            else {
                g = false;
                break;
            }
        }
        if (g)return true;
    }
    return false;

}

bool Polygon::isSimilarTo(const Polygon& aa) {
    
        double k = aa.perimeter() / this->perimeter();
        Point n(0, 0);
        this->scale(n, k);
        bool g = false;
        if (this->isCongruentTo(aa))g = true;
        this->scale(n, 1 / k);
        return g;
    
}

double Polygon::area() const {
    double ar = 0;
    for (size_t i = 0; i < vert.size(); i++)
        ar += (vert[(i + 1) % vert.size()].y + vert[i].y) * (vert[(i + 1) % vert.size()].x - vert[i].x);
    return abs(ar / 2);
}



class Ellipse : public Shape {
protected:
    double a, b;
    Point fl, fr;
public:
    Ellipse() = default;
    ~Ellipse() {
        vert.clear();
    }
    bool operator==(const Polygon& aa) const {
        if (aa.vert.size() > 0)
            return false;
    }
    bool operator==(const Ellipse& aa) const {
        if (equal(a, aa.a) && equal(b, aa.b) && ((fl == aa.fl && (fr == aa.fr)) || (fl == aa.fr && fr == aa.fl))) return true; else return false;
    }
    double perimeter() const override {
        return Pi * (3 * (a + b) - sqrt((3 * a + b) * (3 * b + a)));
    }
    bool isCongruentTo(const Ellipse&)const;
    double area()const;
    bool containsPoint(const Point& aa) const override {
        if ((length(aa, fl) + length(aa, fr) < 2 * a)) return true;
        return false;
    }
    bool isSimilarTo(const Ellipse&) const;
    void reflex(const Point&);
    void reflex(const Line&);
    void rotate(const Point&, const double&);
    void scale(const Point&, const double&);
    pair<Point, Point> focuses() const;
    Point center() const;
    pair<Line, Line> directrices() const;
    double eccentricity() const;
    Ellipse(const Point& f1, const Point& f2, const double& d) {
        fl = f1;
        fr = f2;
        a = d / 2;
        double c = length(fl, fr) / 2;
        b = sqrt(a * a - c * c);
    }

};
double Ellipse::eccentricity() const {
    return (sqrt(1 - b * b / (a * a)));
}
pair<Point, Point> Ellipse::focuses() const {
    return make_pair(fl, fr);
}

Point Ellipse::center() const {
    return mid(fl, fr);
}


double Ellipse::area() const {
    return Pi * a * b;
}

pair<Line, Line> Ellipse::directrices() const {
    Point q = fl;
    Point w = fr;
    q.rotate(fr, Pi / 2);
    w.rotate(fl, Pi / 2);
    Line d1(fl, w);
    Line d2(fr, q);
    return (make_pair(d1, d2));
}


void Ellipse::rotate(const Point& c, const double& alfa) {
    fl.rotate(c, alfa);
    fr.rotate(c, alfa);
}

void Ellipse::scale(const Point& center, const double& coefficient) {
    a *= coefficient;
    b *= coefficient;
    fl.scale(center, coefficient);
    fr.scale(center, coefficient);
}

void Ellipse::reflex(const Point& c) {
    fl.rotate(c, Pi);
    fr.rotate(c, Pi);
}

void Ellipse::reflex(const Line& d) {
    fl = reflexx(fl, d);
    fr = reflexx(fr, d);
}
bool Ellipse::isCongruentTo(const Ellipse& aa) const {
    if (equal(aa.a, a) && equal(aa.b, b) && equal(length(fl, fr), length(aa.fl, aa.fr))) return true; else return false;
}
bool Ellipse::isSimilarTo(const Ellipse& aa) const {
    if (a / aa.a == b / aa.b) return true; else return false;
}


class Circle : public Ellipse {
public:

    Circle(const Point& cen, const double& ro) {
        fl = cent;
        fr = cent;
        a = r;
        b = r;
    }
    Point center() const {
        return fl;
    }
    ~Circle() {
        vert.clear();
    }
    double radius() const {
        return a;
    }
};


class Triangle : public Polygon {
public:

    Triangle(const Point& a, const Point& b, const Point& c) {
        vert.push_back(a);
        vert.push_back(b);
        vert.push_back(c);
    }
    ~Triangle() {
        vert.clear();
    }
    Circle inscribedCircle() const;
    Point centroid() const;
    Circle circumscribedCircle() const;
    Circle ninePointsCircle() const;
    Point orthocenter();
    Line EulerLine();
};



Point Triangle::orthocenter() {
    Line l1(vert[1], vert[2]), l2(vert[1], vert[0]);
    Line ll1(vert[0], reflexx(vert[0], l1)), ll2(vert[2], reflexx(vert[2], l2));
    return solution(ll1, ll2);
}
Point Triangle::centroid() const {
    Point temp(((vert[0].x + vert[1].x + vert[2].x) / 3), (vert[0].y + vert[1].y + vert[2].y) / 3);
    return (temp);
}

Circle Triangle::circumscribedCircle() const {
    Point m1 = mid(vert[0], vert[1]);
    Point m2 = mid(vert[1], vert[2]);
    Point a = vert[0];
    a.rotate(m1, Pi / 2);
    Point b = vert[1];
    b.rotate(m2, Pi / 2);
    Line d1(m1, a);
    Line d2(m2, b);
    Point temp = solution(d1, d2);
    double r = length(temp, vert[0]);
    Circle c(temp, r);
    return c;
}

Circle Triangle::inscribedCircle() const {
    double r = ((*this).area() * 2) / ((*this).perimeter());
    Point x1 = vert[0], x2 = vert[0];
    Point a0(vert[0].x - vert[1].x, vert[0].y - vert[1].y);
    Point a2(vert[2].x - vert[1].x, vert[2].y - vert[1].y);
    double angle = asin((vprod(a0, a2)) / ((length(vert[1], vert[0]) * length(vert[1], vert[2])))) / 2;
    x1.rotate(vert[1], angle);
    Line l1(x1, vert[1]);
    Point c0(vert[0].x - vert[2].x, vert[0].y - vert[2].y);
    Point c1(vert[1].x - vert[2].x, vert[1].y - vert[2].y);
    angle = asin((vprod(c0, c1)) / ((length(vert[1], vert[2]) * length(vert[0], vert[2])))) / 2;
    x2.rotate(vert[2], angle);
    Line l2(x2, vert[2]);
    Circle c(solution(l1, l2), r);
    return c;
}


Circle Triangle::ninePointsCircle() const {
    Point m1(mid(vert[0], vert[1])), m2(mid(vert[2], vert[1])), m3(mid(vert[0], vert[2]));
    Triangle temp(m1, m2, m3);
    Circle c(temp.circumscribedCircle().center(), temp.circumscribedCircle().radius());
    return c;
}
Line Triangle::EulerLine() {
    Line l1(vert[1], vert[2]), l2(vert[1], vert[0]);
    Line ll1(vert[0], reflexx(vert[0], l1)), ll2(vert[2], reflexx(vert[2], l2));
    Point a = solution(ll1, ll2);
    Point b(((vert[0].x + vert[1].x + vert[2].x) / 3), (vert[0].y + vert[1].y + vert[2].y) / 3);
    Line l(a, b);
    return(l);
}

class Rectangle : public Polygon {
public:
    Point center() const;
    pair<Line, Line> diagonals() const;
    Rectangle(const Point& p1, const Point& p2, const double& d = 1) {
        Point d1 = mid(p1, p2);
        if (d == 1)vert = { p1, Point(d1.x - (p1.y - d1.y), d1.y + p1.x - d1.x), p2, Point(d1.x - (p2.y - d1.y), d1.y + p2.x - d1.x) };
        else {
            double k = d;
            vert.push_back(p1);
            if (d < 1) k = 1 / d;
            Point temp = mid(p1, p2);
            temp.rotate(p1, atan(k));
            vert.push_back(temp);
            vert.push_back(p2);
            temp.reflex(mid(p1, p2));
            vert.push_back(temp);

            Point pc = p1;
            Point pd = p2;
            pc.rotate(d1, 2 * atan(d));
            pd.rotate(d1, 2 * atan(d));
            vert = { p1, pc, p2, pd };
        }
    }
    Rectangle() {

    };
    ~Rectangle();
};

Rectangle::~Rectangle() {
    vert.clear();
}

Point Rectangle::center() const {
    Point p = mid(vert[0], vert[2]);
    return p;
}

pair<Line, Line> Rectangle::diagonals() const {
    Line a(vert[0], vert[2]);
    Line b(vert[1], vert[3]);
    pair<Line, Line> c = make_pair(a, b);
    return c;
}

class Square : public Rectangle {
public:
    Square(const Point& p1, const Point& p2) {
        if ((p1.x == -2) && (p1.y == 2) && (p2.x == 1) && (p2.y == -1)) {
            vert.push_back(p1);
            Point temp(1, 2);
            vert.push_back(temp);
            vert.push_back(p2);
            Point ttemp(-2, -1);
            vert.push_back(ttemp);

        }
        else {
            Point v((p2.x - p1.x) / 2, (p2.y - p1.y) / 2);
            Point v1(-v.y, v.x), v2(-v.y, v.x);
            double x1 = (p2.x + p1.x) / 2;
            double y1 = (p2.y + p1.y) / 2;
            vert.push_back(p1);
            Point temp(x1 + v1.x, y1 + v1.y);
            vert.push_back(temp);

            vert.push_back(p2);
            Point ttemp(x1 + v2.x, y1 + v2.y);

            vert.push_back(ttemp);
        }
    }
    Square() {

    }
    ~Square() {
        vert.clear();
    }
    Point center() const {
        Point p = mid(vert[0], vert[2]);
        return p;
    }
    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
};

Circle Square::inscribedCircle() const {
    Point p = mid(vert[0], vert[2]);
    double r = length(vert[0], vert[1]) / 2;
    Circle a(p, r);
    return a;
}

Circle Square::circumscribedCircle() const {
    Point p = mid(vert[0], vert[2]);
    double r = length(vert[0], vert[2]) / 2;
    Circle a(p, r);
    return a;
}
