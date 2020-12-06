#include <string>
#include <vector>
#include <iostream>
using namespace std;


class BigInteger {
private:
	vector <int> v;
	void swap(BigInteger& s) {
		std::swap(s.v, v);
	}
	void zero_destroy() {
		reverse(v.begin(), v.end());
		while (v.size() > 1 && v.back() == 0)v.pop_back();
		reverse(v.begin(), v.end());
	}

	BigInteger operator^ (const int& b) {
		BigInteger temp;
		if ((b == 0) || (*this == 0)) {
			BigInteger a = 0;
			return a;
		}
		size_t buff = 0;
		for (size_t i = v.size(); i > 0; i--) {
			temp.v.push_back((v[i - 1] * b + buff) % 10);
			buff = (v[i - 1] * b + buff) / 10;
		}
		if (buff != 0) {
			temp.v.push_back(buff % 10);
			if (buff / 10 > 0)
				temp.v.push_back(buff / 10);
		}
		reverse(temp.v.begin(), temp.v.end());
		return temp;
	}
public:
	BigInteger() {}

	string toString();
	string toString() const;
	BigInteger(int a) {
		if (a == 0)
			v.push_back(0);
		else {
			bool g = false;
			if (a < 0) {
				a *= -1;
				g = true;
			}
			while (a) {
				v.push_back(a % 10);
				a /= 10;
			}
			reverse(v.begin(), v.end());
			if (g)v[0] *= -1;
		}
	}

	friend std::ostream& operator <<(std::ostream& out, const BigInteger& s);
	friend std::istream& operator >>(std::istream& in, BigInteger& s);
	friend bool operator==(const BigInteger&, const BigInteger&);
	friend bool operator!=(const BigInteger&, const BigInteger&);
	friend bool operator<=(const BigInteger&, const BigInteger&);
	friend bool operator>=(const BigInteger&, const BigInteger&);
	friend bool operator<(const BigInteger&, const BigInteger&);
	friend bool operator>(const BigInteger&, const BigInteger&);
	friend bool operator==(const BigInteger&, const int&);
	friend bool operator!=(const BigInteger&, const int&);
	friend bool operator<=(const BigInteger&, const int&);
	friend bool operator>=(const BigInteger&, const int&);
	friend bool operator<(const BigInteger&, const int&);
	friend bool operator>(const BigInteger&, const int&);
	friend bool operator==(const int&, const BigInteger&);
	friend bool operator!=(const int&, const BigInteger&);
	friend bool operator<=(const int&, const BigInteger&);
	friend bool operator>=(const int&, const BigInteger&);
	friend bool operator<(const int&, const BigInteger&);
	friend bool operator>(const int&, const BigInteger&);

	BigInteger& operator=(BigInteger a) {
		reverse(a.v.begin(), a.v.end());
		while (a.v.size() > 1 && a.v.back() == 0)a.v.pop_back();
		reverse(a.v.begin(), a.v.end());
		swap(a);
		return *this;
	}

	BigInteger& operator=(int a) {
		BigInteger b(a);
		swap(b);
		return *this;
	}

	BigInteger& operator-=(const BigInteger& a) {
		if (a.v[0] < 0) {
			BigInteger c = a;
			c.v[0] *= -1;
			*this += c;
			return *this;
		}
		else if (v[0] < 0) {
			BigInteger c = a;
			v[0] *= -1;
			c += *this;
			*this = -c;
			return *this;
		}
		else {
			BigInteger itog;
			BigInteger c = a;
			BigInteger b = *this;
			reverse(c.v.begin(), c.v.end());
			reverse(b.v.begin(), b.v.end());
			if (c.v.size() > b.v.size()) {
				c.v.push_back(0);
				while (c.v.size() > b.v.size()) {
					b.v.push_back(0);
				}
			}
			else {
				b.v.push_back(0);
				while (c.v.size() < b.v.size()) {
					c.v.push_back(0);
				}
			}
			int d = 0;
			if (*this > a) {
				int e = 0;
				for (size_t i = 0; i < b.v.size(); ++i) {
					if (b.v[i] - d - c.v[i] < 0) {
						b.v[i] += 10 - d;
						d = 1;
						e = b.v[i] - c.v[i];
					}
					else {
						e = b.v[i] - c.v[i] - d;
						d = 0;
					}
					itog.v.push_back(e);
				}
				reverse(itog.v.begin(), itog.v.end());
				*this = itog;
			}
			else {
				int e = 0;
				for (size_t i = 0; i < b.v.size(); ++i) {
					if (c.v[i] - d - b.v[i] < 0) {
						c.v[i] += 10 - d;
						d = 1;
						e = c.v[i] - b.v[i];
					}
					else {
						e = c.v[i] - b.v[i] - d;
						d = 0;
					}
					itog.v.push_back(e);
				}
				reverse(itog.v.begin(), itog.v.end());
				*this = -itog;
			}
			return *this;
		}
	}

	BigInteger& operator+=(const BigInteger& a) {
		if (a.v[0] < 0) {
			BigInteger c = a;
			c.v[0] *= -1;
			*this -= c;
			return *this;
		}
		else if (v[0] < 0) {
			BigInteger c = a;
			v[0] *= -1;
			c -= *this;
			*this = c;
			return *this;
		}
		else {
			BigInteger itog;
			BigInteger c = a;
			BigInteger b = *this;
			reverse(c.v.begin(), c.v.end());
			reverse(b.v.begin(), b.v.end());
			if (c.v.size() > b.v.size()) {
				c.v.push_back(0);
				while (c.v.size() > b.v.size()) {
					b.v.push_back(0);
				}
			}
			else {
				b.v.push_back(0);
				while (c.v.size() < b.v.size()) {
					c.v.push_back(0);
				}
			}
			int d = 0;
			for (size_t i = 0; i < b.v.size(); ++i) {
				int e = b.v[i] + c.v[i] + d;
				itog.v.push_back(e % 10);
				d = e / 10;
			}
			reverse(itog.v.begin(), itog.v.end());
			*this = itog;
			return *this;
		}
	}

	BigInteger& operator*=(const BigInteger& b) {
		BigInteger sum = 0;
		size_t g = 1;
		if (v[0] < 0) {
			v[0] *= -1;
			g *= -1;
		}
		if (b.v[0] < 0)g *= -1;
		for (size_t i = b.v.size(); i > 0; i--) {
			BigInteger temp = (*this) ^ abs(b.v[i - 1]);
			sum += temp;
			v.push_back(0);
		}
		sum.v[0] *= g;
		*this = sum;
		return *this;
	}

	BigInteger& operator/=(const BigInteger& a) {
		bool z = true;
		if (v[0] < 0) {
			v[0] = -v[0];
			z = false;
		}
		BigInteger t = a;
		bool y = true;
		if (a.v[0] < 0) {
			t.v[0] = -t.v[0];
			y = false;
		}
		BigInteger temp;
		BigInteger b = 0;
		vector<int> itogult;
		if (t > * this) {
			*this = 0;
			return *this;
		}
		else {
			for (size_t i = 0; i < t.v.size(); ++i)
				temp.v.push_back(v[i]);
			int j = 0;
			for (j = 0; j < 10; ++j) {
				if (temp < b) {
					if (!(j == 1 && itogult.size() == 0))
						itogult.push_back(j - 1);
					for (int l = 0; l < j - 1; ++l) {
						temp -= t;
					}
					break;
				}
				b += t;
			}
			if (j == 10) {
				itogult.push_back(j - 1);
				for (int l = 0; l < j - 1; ++l) {
					temp -= t;
				}
			}
			for (size_t i = t.v.size(); i < v.size(); ++i) {
				temp.v.push_back(0);
				temp += v[i];
				int j = 0;
				b = 0;
				for (j = 0; j < 10; ++j) {
					if (temp < b) {
						if (!(j == 1 && itogult.size() == 0))
							itogult.push_back(j - 1);
						for (int l = 0; l < j - 1; ++l) {
							temp -= t;
						}
						break;
					}
					b += t;
				}
				if (j == 10) {
					itogult.push_back(j - 1);
					for (int l = 0; l < j - 1; ++l) {
						temp -= t;
					}
				}
			}
			v.clear();
			v = itogult;
			if ((!y && z) || (!z && y)) return -*this;
			return *this;
		}
	}

	BigInteger& operator%=(const BigInteger& a) {
		BigInteger temp = *this;
		temp /= a;
		temp *= a;
		*this -= temp;
		return *this;
	}

	BigInteger& operator+=(const int& b) {
		BigInteger b1 = BigInteger(b);
		*this += b1;
		return *this;
	}

	BigInteger& operator-=(const int& b) {
		BigInteger b1 = BigInteger(b);
		*this -= b1;
		return *this;
	}

	BigInteger& operator*=(const int& b) {
		BigInteger b1 = BigInteger(b);
		*this *= b1;
		return *this;
	}

	BigInteger& operator/=(const int& b) {
		BigInteger b1 = BigInteger(b);
		*this /= b1;
		return *this;
	}

	BigInteger& operator%=(const int& b) {
		BigInteger b1 = BigInteger(b);
		*this %= b1;
		return *this;
	}

	BigInteger& operator-() {
		zero_destroy();
		v[0] *= -1;
		return *this;
	}

	operator bool() {
		if (v.size() == 0)return 0;
		return v[0];
	}

	BigInteger& operator++() {
		*this += BigInteger(1);
		return *this;
	}

	BigInteger operator++(int) {
		BigInteger temp = *this;
		++(*this);
		return temp;
	}

	BigInteger& operator--() {
		*this -= BigInteger(1);
		return *this;
	}

	BigInteger operator--(int) {
		BigInteger temp = *this;
		--(*this);
		return temp;
	}
};


string BigInteger::toString() {
	string s = "";
	for (size_t i = 0; i < (*this).v.size(); i++) {
		if ((*this).v[i] < 0) {
			s += '-';
			s += char(48 - (*this).v[i]);
		}
		else s += char(48 + (*this).v[i]);
	}
	return s;
}

string BigInteger::toString() const {
	string s = "";
	for (size_t i = 0; i < (*this).v.size(); i++) {
		if ((*this).v[i] < 0) {
			s += '-';
			s += char(48 - (*this).v[i]);
		}
		else s += char(48 + (*this).v[i]);
	}
	return s;
}

std::ostream& operator <<(std::ostream& out, const BigInteger& s) {
	for (auto i : s.v) {
		out << i;
	}
	return out;
}

std::istream& operator >> (std::istream& in, BigInteger& s) {
	char c;
	bool less = false;
	s = 0;
	do {
		c = in.get();
	} while (isspace(c));
	while (!in.eof() && !isspace(c)) {
		if (c != '-') {
			if (s)s *= 10;
			s += BigInteger(int(c) - 48);
		}
		else less = true;
		c = in.get();
	}
	if (less)s.v[0] *= -1;
	return in;
}

bool operator==(const BigInteger& a, const BigInteger& b) {
	if (a.v.size() != b.v.size())return false;
	for (size_t i = 0; i < a.v.size(); i++)if (a.v[i] != b.v[i])return false;
	return true;
}

bool operator!=(const BigInteger& a, const BigInteger& b) {
	return !(a == b);
}

bool operator<=(const BigInteger& a, const BigInteger& b) {
	if (a.v[0] <= 0 && b.v[0] >= 0)return true;
	if (a.v[0] >= 0 && b.v[0] <= 0)return false;
	bool f = false;
	if (a.v[0] <= 0 && b.v[0] <= 0)f = true;
	if (a.v.size() < b.v.size()) {
		if (!f)return true;
		return false;
	}
	if (a.v.size() > b.v.size()) {
		if (!f)return false;
		return true;
	}
	for (size_t i = 0; i < a.v.size(); i++) {
		if (a.v[i] < b.v[i]) {
			if (!f)return true;
			return false;
		}
		if (a.v[i] > b.v[i]) {
			if (!f)return false;
			return true;
		}
	}
	return true;
}

bool operator>=(const BigInteger& a, const BigInteger& b) {
	if (a.v[0] <= 0 && b.v[0] >= 0)return false;
	if (a.v[0] >= 0 && b.v[0] <= 0)return true;
	bool f = false;
	if (a.v[0] <= 0 && b.v[0] <= 0)f = true;
	if (a.v.size() < b.v.size()) {
		if (f)return true;
		return false;
	}
	if (a.v.size() > b.v.size()) {
		if (f)return false;
		return true;
	}
	for (size_t i = 0; i < a.v.size(); i++) {
		if (a.v[i] < b.v[i]) {
			if (f)return true;
			return false;
		}
		if (a.v[i] > b.v[i]) {
			if (f)return false;
			return true;
		}
	}
	return true;
}

bool operator<(const BigInteger& a, const BigInteger& b) {
	return (a <= b && a != b);
}

bool operator>(const BigInteger& a, const BigInteger& b) {
	return (a >= b && a != b);
}

bool operator==(const BigInteger& a, const int& b) {
	const BigInteger b1 = BigInteger(b);
	if (a.v.size() != b1.v.size())return false;
	for (size_t i = 0; i < a.v.size(); i++)if (a.v[i] != b1.v[i])return false;
	return true;
}

bool operator!=(const BigInteger& a, const int& b) {
	const BigInteger b1 = BigInteger(b);
	return !(a == b1);
}

bool operator<=(const BigInteger& a, const int& b) {
	const BigInteger b1 = BigInteger(b);
	if (a.v.size() < b1.v.size())return true;
	if (a.v.size() > b1.v.size())return false;
	for (size_t i = 0; i < a.v.size(); i++) {
		if (a.v[i] < b1.v[i])return true;
		if (a.v[i] > b1.v[i])return false;
	}
	return true;
}

bool operator>=(const BigInteger& a, const int& b) {
	const BigInteger b1 = BigInteger(b);
	if (a.v.size() > b1.v.size())return true;
	if (a.v.size() < b1.v.size())return false;
	for (size_t i = 0; i < a.v.size(); i++) {
		if (a.v[i] > b1.v[i])return true;
		if (a.v[i] < b1.v[i])return false;
	}
	return true;
}

bool operator<(const BigInteger& a, const int& b) {
	const BigInteger b1 = BigInteger(b);
	return (a <= b1 && a != b1);
}

bool operator>(const BigInteger& a, const int& b) {
	const BigInteger b1 = BigInteger(b);
	return (a >= b1 && a != b1);
}

bool operator==(const int& a, const BigInteger& b) {
	BigInteger a1 = BigInteger(a);
	if (a1.v.size() != b.v.size())return false;
	for (size_t i = 0; i < a1.v.size(); i++)if (a1.v[i] != b.v[i])return false;
	return true;
}

bool operator!=(const int& a, const BigInteger& b) {
	BigInteger a1 = BigInteger(a);
	return !(a1 == b);
}

bool operator<=(const int& a, const BigInteger& b) {
	BigInteger a1 = BigInteger(a);
	if (a1.v.size() < b.v.size())return true;
	if (a1.v.size() > b.v.size())return false;
	for (size_t i = 0; i < a1.v.size(); i++) {
		if (a1.v[i] < b.v[i])return true;
		if (a1.v[i] > b.v[i])return false;
	}
	return true;
}

bool operator>=(const int& a, const BigInteger& b) {
	BigInteger a1 = BigInteger(a);
	if (a1.v.size() > b.v.size())return true;
	if (a1.v.size() < b.v.size())return false;
	for (size_t i = 0; i < a1.v.size(); i++) {
		if (a1.v[i] > b.v[i])return true;
		if (a1.v[i] < b.v[i])return false;
	}
	return true;
}

bool operator<(const int& a, const BigInteger& b) {
	BigInteger a1 = BigInteger(a);
	return (a1 <= b && a1 != b);
}

bool operator>(const int& a, const BigInteger& b) {
	BigInteger a1 = BigInteger(a);
	return (a1 >= b && a1 != b);
}

BigInteger operator+(const BigInteger& a, const BigInteger& b) {
	BigInteger temp = a;
	temp += b;
	return temp;
}

BigInteger operator-(const BigInteger& a, const BigInteger& b) {
	BigInteger temp = a;
	temp -= b;
	return temp;
}

BigInteger operator*(const BigInteger& a, const BigInteger& b) {
	BigInteger temp = a;
	temp *= b;
	return temp;
}

BigInteger operator/(const BigInteger& a, const BigInteger& b) {
	BigInteger temp = a;
	temp /= b;
	return temp;
}

BigInteger operator%(const BigInteger& a, const BigInteger& b) {
	BigInteger temp = a;
	temp %= b;
	return temp;
}

BigInteger operator+(const int& a, const BigInteger& b) {
	BigInteger temp = BigInteger(a);
	temp += b;
	return temp;
}

BigInteger operator-(const int& a, const BigInteger& b) {
	BigInteger temp = BigInteger(a);
	temp -= b;
	return temp;
}

BigInteger operator*(const int& a, const BigInteger& b) {
	BigInteger temp = BigInteger(a);
	temp *= b;
	return temp;
}

BigInteger operator/(const int& a, const BigInteger& b) {
	BigInteger temp = BigInteger(a);
	temp /= b;
	return temp;
}

BigInteger operator%(const int& a, const BigInteger& b) {
	BigInteger temp = BigInteger(a);
	temp %= b;
	return temp;
}

BigInteger operator+(const BigInteger& a, const int& b) {
	BigInteger temp = BigInteger(b);
	temp += a;
	return temp;
}

BigInteger operator-(const BigInteger& a, const int& b) {
	BigInteger temp = a;
	temp -= BigInteger(b);
	return temp;
}

BigInteger operator*(const BigInteger& a, const int& b) {
	BigInteger temp = BigInteger(b);
	temp *= a;
	return temp;
}

BigInteger operator/(const BigInteger& a, const int& b) {
	BigInteger temp = a;
	temp /= BigInteger(b);
	return temp;
}

BigInteger operator%(const BigInteger& a, const int& b) {
	BigInteger temp = a;
	temp %= BigInteger(b);
	return temp;
}

BigInteger GCD(BigInteger a, BigInteger b) {
	if (a < 0) {
		a *= -1;
	}
	if (b < 0) {
		b *= -1;
	}
	while (a && b) {
		if (a > b)a %= b;
		else b %= a;
	}
	a += b;
	return a;
}

BigInteger operator ""_bi(unsigned long long a) {
	return BigInteger(a);
}

class Rational {
private:
	BigInteger num = 0;
	BigInteger dim = 1;

public:

	Rational();
	~Rational();
	Rational(const BigInteger& a) {
		num = a;
		dim = 1;
	}
	Rational(const int& a) {
		num = a;
		dim = 1;
	}

	friend bool operator>=(const Rational&, const Rational&);
	friend bool operator>=(const Rational&, const BigInteger&);
	friend bool operator>=(const Rational&, const int&);
	friend bool operator>=(const BigInteger&, const Rational&);
	friend bool operator>=(const int&, const Rational&);
	friend bool operator>(const Rational&, const Rational&);
	friend bool operator>(const Rational&, const BigInteger&);
	friend bool operator>(const Rational&, const int&);
	friend bool operator>(const BigInteger&, const Rational&);
	friend bool operator>(const int&, const Rational&);
	friend bool operator!=(const Rational&, const Rational&);
	friend bool operator!=(const Rational&, const BigInteger&);
	friend bool operator!=(const Rational&, const int&);
	friend bool operator!=(const BigInteger&, const Rational&);
	friend bool operator!=(const int&, const Rational&);
	friend bool operator==(const Rational&, const Rational&);
	friend bool operator==(const Rational&, const BigInteger&);
	friend bool operator==(const Rational&, const int&);
	friend bool operator==(const BigInteger&, const Rational&);
	friend bool operator==(const int&, const Rational&);
	friend bool operator<(const Rational&, const Rational&);
	friend bool operator<(const Rational&, const BigInteger&);
	friend bool operator<(const Rational&, const int&);
	friend bool operator<(const BigInteger&, const Rational&);
	friend bool operator<(const int&, const Rational&);
	friend bool operator<=(const Rational&, const Rational&);
	friend bool operator<=(const Rational&, const BigInteger&);
	friend bool operator<=(const Rational&, const int&);
	friend bool operator<=(const BigInteger&, const Rational&);
	friend bool operator<=(const int&, const Rational&);

	friend Rational operator/(const Rational&, const Rational&);
	friend Rational operator/(const Rational&, const BigInteger&);
	friend Rational operator/(const Rational&, const int&);
	friend Rational operator/(const BigInteger&, const Rational&);
	friend Rational operator/(const int&, const Rational&);



	Rational& operator=(const Rational a) {
		num = a.num;
		dim = a.dim;
		return *this;
	}
	Rational& operator=(const BigInteger a) {
		num = a;
		dim = 1;
		return *this;
	}
	Rational& operator=(const int a) {
		num = a;
		dim = 1;
		return *this;
	}

	Rational& operator+=(const Rational& a) {
		num = num * a.dim + dim * a.num;
		dim = dim * a.dim;
		BigInteger Nod = GCD(dim, num);
		num = num / Nod;
		dim = dim / Nod;
		if (dim < 0) {
			num *= -1;
			dim *= -1;
		}
		return *this;
	}
	Rational& operator+=(const BigInteger& a) {
		num = num + dim * a;
		BigInteger Nod = GCD(dim, num);
		num = num / Nod;
		dim = dim / Nod;
		if (dim < 0) {
			num *= -1;
			dim *= -1;
		}
		return *this;
	}
	Rational& operator+=(const int& a) {
		num = num + dim * a;
		BigInteger Nod = GCD(dim, num);
		num = num / Nod;
		dim = dim / Nod;
		if (dim < 0) {
			num *= -1;
			dim *= -1;
		}
		return *this;
	}

	Rational& operator-=(const Rational& a) {
		num = num * a.dim - dim * a.num;
		dim = dim * a.dim;
		BigInteger Nod = GCD(dim, num);
		num = num / Nod;
		dim = dim / Nod;
		if (dim < 0) {
			num *= -1;
			dim *= -1;
		}
		return *this;
	}
	Rational& operator-=(const BigInteger& a) {
		num = num - dim * a;
		BigInteger Nod = GCD(dim, num);
		num = num / Nod;
		dim = dim / Nod;
		if (dim < 0) {
			num *= -1;
			dim *= -1;
		}
		return *this;
	}
	Rational& operator-=(const int& a) {
		num = num - dim * a;
		BigInteger Nod = GCD(dim, num);
		num = num / Nod;
		dim = dim / Nod;
		if (dim < 0) {
			num *= -1;
			dim *= -1;
		}
		return *this;
	}

	Rational& operator*=(const Rational& a) {
		num = num * a.num;
		dim = dim * a.dim;
		BigInteger Nod = GCD(dim, num);
		num = num / Nod;
		dim = dim / Nod;
		if (dim < 0) {
			num *= -1;
			dim *= -1;
		}
		return *this;
	}
	Rational& operator*=(const BigInteger& a) {
		num = num * a;
		BigInteger Nod = GCD(dim, num);
		num = num / Nod;
		dim = dim / Nod;
		if (dim < 0) {
			num *= -1;
			dim *= -1;
		}
		return *this;
	}
	Rational& operator*=(const int& a) {
		num = num * a;
		BigInteger Nod = GCD(dim, num);
		num = num / Nod;
		dim = dim / Nod;
		if (dim < 0) {
			num *= -1;
			dim *= -1;
		}
		return *this;
	}

	Rational& operator/=(const Rational& a) {
		num = num * a.dim;
		dim = dim * a.num;
		BigInteger Nod = GCD(dim, num);
		num = num / Nod;
		dim = dim / Nod;
		if (dim < 0) {
			num *= -1;
			dim *= -1;
		}
		return *this;
	}
	Rational& operator/=(const BigInteger& a) {
		dim = dim * a;
		BigInteger Nod = GCD(dim, num);
		num = num / Nod;
		dim = dim / Nod;
		if (dim < 0) {
			num *= -1;
			dim *= -1;
		}
		return *this;
	}
	Rational& operator/=(const int& a) {
		dim = dim * a;
		BigInteger Nod = GCD(dim, num);
		num = num / Nod;
		dim = dim / Nod;
		if (dim < 0) {
			num *= -1;
			dim *= -1;
		}
		return *this;
	}

	string toString() {
		string temp;
		BigInteger x = num;
		if (x < 0) {
			temp += "-";
			x *= -1;
		}
		if (x == 0) {
			temp += "0";
			return temp;
		}
		else {
			string str = x.toString();
			temp += str;
			if (dim == 1) {
				return temp;
			}
			else {
				BigInteger x = dim;
				temp += "/";
				string str = x.toString();
				temp += str;
				return temp;
			}
		}
	}

	string toString() const {
		string temp;
		BigInteger x = num;
		if (x < 0) {
			temp += "-";
			x *= -1;
		}
		if (x == 0) {
			temp += "0";
			return temp;
		}
		else {
			string str = x.toString();
			temp += str;
			if (dim == 1) {
				return temp;
			}
			else {
				BigInteger x = dim;
				temp += "/";
				string str = x.toString();
				temp += str;
				return temp;
			}
		}
	}

	string asDecimal(size_t precision = 0) {
		BigInteger a = num / dim;
		BigInteger b = num % dim;
		BigInteger c = dim;
		string temp;
		if (num < 0) temp = "-"; else temp = "";
		string ttemp = a.toString();
		if (num < 0) temp = "-"; else temp = "";
		temp += ttemp;
		if (precision == 0) {
			cerr << temp << " " << precision << endl;
			return temp;
		}
		else {
			precision++;
			temp += ".";
			for (size_t i = 0; i < precision; ++i) {
				a = b * 10;
				b = a % c;
				a /= c;
				if (a < 0) a *= -1;
				for (int g = 0; g < 10; g++) {
					if (a == g) {
						temp.push_back(char(g + 48));
						g = 10;
					}
				}
			}
			if (int(temp.back()) - 48 >= 5) {
				temp.pop_back();
				int i = temp.size() - 1;
				while (true) {
					if (temp[i] != '9') {
						temp[i] = char(int(temp[i]) + 1);
						break;
					}
					temp[i] = '0';
					i--;
					if (temp[i] == '.')break;
				}
				if (temp[i] == '.')temp = (num / dim + 1).toString();
				cerr << temp << " " << precision << endl;
				return temp;
			}
			else {
				temp.pop_back();
				cerr << temp << " " << precision << endl;
				return temp;
			}
		}
	}

	string asDecimal(size_t precision = 0) const {
		BigInteger a = num / dim;
		BigInteger b = num % dim;
		BigInteger c = dim;
		string temp;
		if (num < 0) temp = "-"; else temp = "";
		string ttemp = a.toString();
		if (num < 0) temp = "-"; else temp = "";
		temp += ttemp;
		if (precision == 0) {
			return temp;
		}
		else {
			precision++;
			temp += ".";
			for (size_t i = 0; i < precision; ++i) {
				a = b * 10;
				b = a % c;
				a /= c;
				if (a < 0) a *= -1;
				for (int g = 0; g < 10; g++) {
					if (a == g) {
						temp.push_back(char(g + 48));
						g = 10;
					}
				}

			}
			if (int(temp.back()) - 48 >= 5) {
				temp.pop_back();
				int i = temp.size() - 1;
				while (true) {
					if (temp[i] != '9') {
						temp[i] = char(int(temp[i]) + 1);
						break;
					}
					temp[i] = '0';
					i--;
					if (temp[i] == '.')break;
				}
				if (temp[i] == '.')temp = (num / dim + 1).toString();
				return temp;
			}
			else {
				temp.pop_back();
				return temp;
			}
		}
	}

	Rational& operator-() {
		num *= -1;
		return *this;
	}

	explicit operator double() {
		string temp = asDecimal(310);
		size_t nach = temp.find(".");
		double k = 1, sum = 0;
		for (int i = nach - 1; i >= 0; i--) {
			char c = temp[i];
			double x = int(c) - 48;
			sum = sum + x * k;
			k = k * 10;
		}
		k = 0.1;
		for (size_t i = nach + 1; i <= 307; i++) {
			char c = temp[i];
			double x = int(c) - 48;
			sum = sum + x * k;
			k = k / 10;
		}
		return sum;
	}

};

Rational::Rational() {
	num = 0;
	dim = 1;
}

Rational::~Rational() {

}

Rational operator+(const Rational& a, const Rational& b) {
	Rational temp = a;
	temp += b;
	return temp;
}
Rational operator+(const Rational& a, const BigInteger& b) {
	Rational temp = a;
	temp += b;
	return temp;
}
Rational operator+(const Rational& a, const int& b) {
	Rational temp = a;
	temp += b;
	return temp;
}

Rational operator+(const BigInteger& b, const Rational& a) {
	Rational temp = a;
	temp += b;
	return temp;
}

Rational operator+(const int& b, const Rational& a) {
	Rational temp = a;
	temp += b;
	return temp;
}

Rational operator-(const Rational& a, const Rational& b) {
	Rational temp = a;
	temp -= b;
	return temp;
}

Rational operator-(const Rational& a, const BigInteger& b) {
	Rational temp = a;
	temp -= b;
	return temp;
}

Rational operator-(const Rational& a, const int& b) {
	Rational temp = a;
	temp -= b;
	return temp;
}

Rational operator-(const BigInteger& b, const Rational& a) {
	Rational temp = a;
	temp *= -1;
	temp += b;
	return temp;
}
Rational operator-(const int& b, const Rational& a) {
	Rational temp = a;
	temp *= -1;
	temp += b;
	return temp;
}

Rational operator*(const Rational& a, const Rational& b) {
	Rational temp = a;
	temp *= b;
	return temp;
}
Rational operator*(const Rational& a, const BigInteger& b) {
	Rational temp = a;
	temp *= b;
	return temp;
}

Rational operator*(const Rational& a, const int& b) {
	Rational temp = a;
	temp *= b;
	return temp;
}

Rational operator*(const BigInteger& b, const Rational& a) {
	Rational temp = a;
	temp *= b;
	return temp;
}

Rational operator*(const int& b, const Rational& a) {
	Rational temp = a;
	temp *= b;
	return temp;
}

Rational operator/(const Rational& a, const Rational& b) {
	Rational temp = a;
	temp /= b;
	return temp;
}
Rational operator/(const Rational& a, const BigInteger& b) {
	Rational temp = a;
	temp /= b;
	return temp;
}
Rational operator/(const Rational& a, const int& b) {
	Rational temp = a;
	temp /= b;
	return temp;
}
Rational operator/(const BigInteger& b, const Rational& a) {
	Rational temp;
	temp.num = a.dim;
	temp.dim = a.num;
	temp *= b;
	BigInteger Nod = GCD(temp.dim, temp.num);
	temp.num /= Nod;
	temp.dim /= Nod;
	return temp;
}

Rational operator/(const int& b, const Rational& a) {
	Rational temp;
	temp.num = a.dim;
	temp.dim = a.num;
	temp *= b;
	BigInteger Nod = GCD(temp.dim, temp.num);
	temp.num /= Nod;
	temp.dim /= Nod;
	return temp;
}

bool operator==(const Rational& a, const Rational& b) {
	return (a.num == b.num && a.dim == b.dim);
}
bool operator==(const Rational& a, const BigInteger& b) {
	return (a.num == b && a.dim == 1);
}
bool operator==(const Rational& a, const int& b) {
	return (a.num == b && a.dim == 1);
}
bool operator==(const BigInteger& b, const Rational& a) {
	return (a.num == b && a.dim == 1);
}
bool operator==(const int& b, const Rational& a) {
	return (a.num == b && a.dim == 1);
}

bool operator!=(const Rational& a, const Rational& b) {
	return !(a.num == b.num && a.dim == b.dim);
}
bool operator!=(const Rational& a, const BigInteger& b) {
	return !(a.num == b && a.dim == 1);
}
bool operator!=(const Rational& a, const int& b) {
	return !(a.num == b && a.dim == 1);
}
bool operator!=(const BigInteger& b, const Rational& a) {
	return !(a.num == b && a.dim == 1);
}
bool operator!=(const int& b, const Rational& a) {

	return !(a.num == b && a.dim == 1);
}

bool operator>(const Rational& a, const Rational& b) {

	return (a.num * b.dim > a.dim * b.num);
}
bool operator>(const Rational& a, const BigInteger& b) {

	return (a.num > a.dim * b);
}

bool operator>(const Rational& a, const int& b) {
	return (a.num > a.dim * b);
}

bool operator>(const BigInteger& b, const Rational& a) {
	return (a.num < a.dim* b);
}

bool operator>(const int& b, const Rational& a) {

	return (a.num < a.dim* b);
}

bool operator<(const Rational& a, const Rational& b) {
	return (a.num * b.dim < a.dim* b.num);
}
bool operator<(const Rational& a, const BigInteger& b) {

	return (a.num < a.dim* b);
}
bool operator<(const Rational& a, const int& b) {
	return (a.num < a.dim* b);
}
bool operator<(const BigInteger& b, const Rational& a) {
	return (a.num > a.dim * b);
}
bool operator<(const int& b, const Rational& a) {
	return (a.num > a.dim * b);
}

bool operator>=(const Rational& a, const Rational& b) {
	return (a.num * b.dim >= a.dim * b.num);
}
bool operator>=(const Rational& a, const BigInteger& b) {
	return (a.num >= a.dim * b);
}
bool operator>=(const Rational& a, const int& b) {
	return (a.num >= a.dim * b);
}
bool operator>=(const BigInteger& b, const Rational& a) {
	return (a.num <= a.dim * b);
}
bool operator>=(const int& b, const Rational& a) {
	return (a.num <= a.dim * b);
}

bool operator<=(const Rational& a, const Rational& b) {
	return (a.num * b.dim <= a.dim * b.num);
}
bool operator<=(const Rational& a, const BigInteger& b) {
	return (a.num <= a.dim * b);
}
bool operator<=(const Rational& a, const int& b) {
	return (a.num <= a.dim * b);
}
bool operator<=(const BigInteger& b, const Rational& a) {
	return (a.num >= a.dim * b);
}

bool operator<=(const int& b, const Rational& a) {
	return (a.num >= a.dim * b);
}