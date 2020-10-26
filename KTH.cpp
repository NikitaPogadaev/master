#include <iostream>
#include <algorithm>
#include <utility>
#include<cstdlib>
#include<vector>
#include<assert.h>
#include <string>
#include <set>

const long long DBS = 1000000;
using namespace std;
bool cmp(int a, int b) { return a < b; }

template<class T>
class IsLess {
public:
    bool operator()(const T& left, const T& right) const {
        return left < right;
    }
private:
};

template<class T, class Compare = IsLess<T>>
int pivot(std::vector<T>& ch, int nach, int kon, Compare isless = IsLess<T>()) {
    int mid = (nach + kon) / 2;
    swap(ch[mid], ch[nach + 1]);
    if (isless(ch[kon], ch[nach])) swap(ch[kon], ch[nach]);
    if (isless(ch[kon], ch[nach + 1])) swap(ch[kon], ch[nach + 1]);
    if (isless(ch[nach + 1], ch[nach]))swap(ch[nach + 1], ch[nach]);
    int l = nach + 1, r = kon, piv = ch[nach + 1];
    while (true) {
        while (ch[++l] < piv);
        while (ch[--r] > piv);
        if (l > r)
            break;
        std::swap(ch[l], ch[r]);
    }
    swap(ch[nach + 1], ch[r]);
    return r;
}



template<class T, class Compare = IsLess<T>>
int cth(std::vector<T>ch, int k, Compare isless = IsLess<T>()) {
    int l = 0, r = ch.size() - 1;
    while (r - l > 1) {
        int temp = pivot(ch, l, r);
        if (temp == k)break;
        else if (temp > k)r = temp;
        else l = temp;
    }
    if (r - l > 1)return ch[k];
    else {
        if (r == l + 1 && ch[r] < ch[l])
            swap(ch[l], ch[r]);
        return ch[k];
    }


}




int main()
{
    std::vector<int> ch;

    int k, m, n, co = 0;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin >> n >> k;
    for (int i = 0; i < n; i++) {
        std::cin >> m;
        ch.push_back(m);
    }
    std::cout << cth(ch, k);
