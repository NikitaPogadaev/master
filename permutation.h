#include <cstring>
#include <iostream>
class Permutation {
private:
    int size = 1;
    int* perm = new int[size];
    void Perm_swap(Permutation& a) {
        std::swap(size, a.size);
        std::swap(perm, a.perm);
    }
public:
    void print() {
        for (int i = 0; i < size; i++)std::cerr << perm[i];
        std::cerr << '\n';
    }
    void print() const {
        for (int i = 0; i < size; i++)std::cerr << perm[i];
        std::cerr << '\n';
    }
    Permutation(unsigned int  n) {
        if (size)
            delete[]perm;
        size = n;
        perm = new int[size];
        for (int i = 0; i < size; i++) {
            perm[i] = i;
        }
    }
    Permutation(unsigned int n, const int* a) {
        if (size)
            delete[]perm;
        size = n;
        perm = new int[size];
        for (int i = 0; i < size; i++) {
            perm[i] = a[i];
        }
    }
    int length() { return size; }
    int length()const { return size; }
    int operator [](int i) {
        int temp = perm[i];
        return temp;
    }
    int operator [](int i)const {
        int temp = perm[i];
        return temp;
    }
    Permutation(const Permutation& a) {
        perm = new int[a.size];
        size = a.size;
        for (int i = 0; i < size; i++)perm[i] = a[i];
    }
    Permutation& operator=(const Permutation& a) {
        if (size)delete[]perm;
        perm = new int[a.size];
        size = a.size;
        for (int i = 0; i < size; i++)perm[i] = a.perm[i];
        return *this;
    }


    ~Permutation() {
        if (perm)
            delete[]perm;
    }



    Permutation& operator*=(const Permutation& x) {
        Permutation temp(size, perm);
        for (int i = 0; i < size; ++i)
            perm[i] = temp[x[i]];
        return*this;
    }
    friend Permutation operator*(const  Permutation&, const  Permutation&);

    Permutation inverse() {
        int* temp = new int[size];
        for (int i = 0; i < size; ++i)
            temp[perm[i]] = i;
        Permutation t(size, temp);
        delete[]temp;
        return t;
    }
    Permutation inverse()const {
        int* temp = new int[size];
        for (int i = 0; i < size; ++i)
            temp[perm[i]] = i;
        Permutation t(size, temp);
        delete[]temp;
        return t;
    }
    void operator()(int* a) {
        int* temp = new int[size];
        for (int i = 0; i < size; ++i)
            temp[perm[i]] = a[i];
        for (int i = 0; i < size; ++i)
            a[i] = temp[i];
        delete[]temp;

    }
    Permutation& operator++() {
        int k = -1;
        for (int i = size - 1; i >= 0; i--) {
            if (perm[i] < k) {
                for (int j = i + 1; j < size; j++) {
                    if (perm[i] > perm[j]) {
                        std::swap(perm[i], perm[j - 1]); j = size;
                    }
                    if (j == size - 1)std::swap(perm[i], perm[j]);
                }
                int g = i + 1;
                for (int j = g; j <= (g + size - 1) / 2; j++)
                    std::swap(perm[j], perm[size - 1 + g - j]);
                return *this;
            }
            k = perm[i];
        }
        for (int j = 0; j <= (size - 1) / 2; j++)
            std::swap(perm[j], perm[size - 1 - j]);

        return *this;

    }
    Permutation& operator--() {
        int k = size;
        for (int i = size - 1; i >= 0; i--) {
            if (perm[i] > k) {
                for (int j = i + 1; j < size; j++) {
                    if (perm[i] < perm[j]) {
                        std::swap(perm[i], perm[j - 1]); j = size;
                    }
                    if (j == size - 1)std::swap(perm[i], perm[j]);
                }
                int g = i + 1;
                for (int j = g; j <= (g + size - 1) / 2; j++)
                    std::swap(perm[j], perm[size - 1 + g - j]);
                return *this;
            }
            k = perm[i];
        }
        for (int j = 0; j <= (size - 1) / 2; j++)
            std::swap(perm[j], perm[size - 1 - j]);
        return *this;

    }
    Permutation operator++(int) {
        Permutation temp(size, perm);
        ++(*this);
        return temp;
    }
    Permutation operator--(int) {
        Permutation temp(size, perm);
        --(*this);
        return temp;
    }
    Permutation next() {
        Permutation temp(size, perm);
        ++temp;
        return temp;
    }
    Permutation next() const {
        Permutation temp(size, perm);
        ++temp;
        return temp;
    }
    Permutation previous() {
        Permutation temp(size, perm);
        --temp;
        return temp;
    }
    Permutation previous() const {
        Permutation temp(size, perm);
        --temp;
        return temp;
    }
    bool isOdd() {
        int co = 0;
        int* temp = new int[size];
        for (int i = 0; i < size; ++i)
            temp[i] = perm[i];
        for (int i = 0; i < size; ++i)
            while (temp[i] != i) {
                co++;
                int g = temp[i];
                std::swap(temp[i], temp[g]);
            }

        delete[]temp;
        return(co % 2 != 0);
    }
    bool isEven() {
        return(!isOdd());
    }
    bool isOdd()const {
        int co = 0;
        int* temp = new int[size];
        for (int i = 0; i < size; ++i)
            temp[i] = perm[i];
        for (int i = 0; i < size; ++i)
            while (temp[i] != i) {
                co++;
                int g = temp[i];
                std::swap(temp[i], temp[g]);
            }
        delete[]temp;
        return(co % 2 != 0);
    }
    bool isEven()const {
        return(!isOdd());
    }

    Permutation pow(int degree) {
        bool* mark = new bool[size];
        for (int i = 0; i < size; ++i)
            mark[i] = true;
        int* temp = new int[size];
        for (int i = 0; i < size; ++i)
            if (mark[i]) {
                mark[i] = false;
                int co = 1, g = i;
                while (i != perm[g]) {
                    co++;
                    g = perm[g];
                    mark[g] = false;
                }
                int* buf = new int[co];
                g = i;
                co = 0;
                while (i != perm[g]) {
                    buf[co] = g;
                    co++;
                    g = perm[g];
                }
                buf[co] = g;
                int coef = ((degree % (co + 1)) + co + 1) % (co + 1);
                for (int j = 0; j <= co; j++) {
                    temp[buf[j]] = buf[(j + coef) % (co + 1)];
                }
                delete[]buf;
            }
        Permutation t(size, temp);
        delete[]temp;
        delete[]mark;
        return t;

    }






    friend bool operator==(const Permutation&, const Permutation&);
    friend bool operator!=(const Permutation&, const Permutation&);
    friend bool operator>=(const Permutation&, const Permutation&);
    friend bool operator<=(const Permutation&, const Permutation&);
    friend bool operator>(const Permutation&, const Permutation&);
    friend bool operator<(const Permutation&, const Permutation&);
};


Permutation operator*(const Permutation& a, const Permutation& b) {
    Permutation temp(a.length(), a.perm);
    temp *= b;
    return temp;
}


bool operator==(const Permutation& x, const Permutation& y) {
    \
        if (x.length() != y.length())return false;
        else {
            for (int i = 0; i < x.length(); i++) {
                if (x[i] != y[i])return false;
            }
            return true;
        }
}
bool operator!=(const Permutation& x, const Permutation& y) {
    return !(x == y);
}
bool operator>=(const Permutation& x, const Permutation& y) {
    for (int i = 0; i < std::min(x.length(), y.length()); i++) {
        if (x[i] > y[i])return true;
        else if (x[i] < y[i])return false;
    }
    return (x.length() >= y.length());
}
bool operator<=(const Permutation& x, const Permutation& y) {
    for (int i = 0; i < std::min(x.length(), y.length()); i++) {
        if (x[i] < y[i])return true;
        else if (x[i] > y[i])return false;
    }
    return (x.length() <= y.length());
}
bool operator<(const Permutation& x, const Permutation& y) {
    return(x <= y) && (x != y);
}
bool operator>(const Permutation& x, const Permutation& y) {
    return(x >= y) && (x != y);
}


