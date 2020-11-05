#include <iostream>
#include <algorithm>
#include <utility>
#include<cstdlib>
#include<vector>
#include<assert.h>
#include <string>

const long long DBS = 1000000;

class Heapmax {
public:
    Heapmax();
    Heapmax(std::vector<long long>);
    ~Heapmax();
    void insert(long long x);
    void extract();
    long long get();
private:
    std::pair<long long, long long>* HeapArray = new std::pair<long long, long long>[DBS];
    long long* time = new long long[1000001];
    long long BS = DBS;
    long long size = 0;
    long long counter = 1;
    void growHeap();
    void siftUp(long long i);
    void siftDown(long long i);

    Heapmax(const Heapmax&) = delete;
    void operator=(const Heapmax&) = delete;
};
Heapmax::Heapmax() {

}
Heapmax::Heapmax(std::vector<long long> ch) {
    while(BS<ch.size())growHeap();
    for (int i = 0; i < ch.size(); i++) {
        HeapArray[i] = { ch[i],i };
    }
    for (int i = size / 2; i >= 0; i--)
    {
        siftDown(ch[i]);
    }
}
Heapmax::~Heapmax() {
    delete[] HeapArray;
    delete[] time;
}
void Heapmax::growHeap()
{
    BS *= 2;
    std::pair<long long, long long>* newB = new std::pair<long long, long long>[BS];
    for (long long i = 0; i < size; ++i) {
        newB[i] = HeapArray[i];
    }
    delete[] HeapArray;
    HeapArray = newB;

}


void Heapmax::insert(long long x) {
    if (size == BS)growHeap();
    HeapArray[size] = { x,counter };

    time[counter] = size;
    siftUp(size);
    counter++;
    size++;
}
long long Heapmax::get() {
    counter++;
    return HeapArray[0].first;
}

void Heapmax::extract() {
    size--;
    HeapArray[0] = HeapArray[size];
    time[HeapArray[0].second] = 0;
    siftDown(0);
    counter++;
}

void Heapmax::siftUp(long long x) {
    if ((x != 0) && (HeapArray[((x + 1) / 2) - 1].first < HeapArray[x].first)) {
        swap(HeapArray[((x + 1) / 2) - 1], HeapArray[x]);
        time[HeapArray[((x + 1) / 2) - 1].second] = ((x + 1) / 2) - 1;
        time[HeapArray[x].second] = x;
        siftUp(((x + 1) / 2) - 1);
    }
}
void Heapmax::siftDown(long long x) {
    long long x1 = x + 1;
    long long x2 = 2 * x1, x3 = 2 * x1 + 1;

    if (x2 - 1 < size)
        if (x3 - 1 < size) {
            if (HeapArray[x2 - 1].first >= HeapArray[x3 - 1].first) {
                if (HeapArray[x].first < HeapArray[x2 - 1].first) {
                    swap(HeapArray[x], HeapArray[x2 - 1]);
                    time[HeapArray[x2 - 1].second] = x2 - 1;
                    time[HeapArray[x].second] = x;
                    siftDown(x2 - 1);
                }
            }
            else if (HeapArray[x].first < HeapArray[x3 - 1].first) {
                swap(HeapArray[x], HeapArray[x3 - 1]);
                time[HeapArray[x].second] = x;
                time[HeapArray[x3 - 1].second] = x3 - 1;
                siftDown(x3 - 1);
            }
        }
        else if (HeapArray[x].first < HeapArray[x2 - 1].first) {
            swap(HeapArray[x], HeapArray[x2 - 1]);
            time[HeapArray[x].second] = x;
            time[HeapArray[x2 - 1].second] = x2 - 1;
            siftDown(x2 - 1);
        }

}


int main()
{
    Heapmax B;
    long long k, m, n;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin >> n >> k;
    std::vector<long long> ch;
    std::string s;
    for (int i = 0; i < k; i++) {
        std::cin >> m;
        B.insert(m);
    }

    for (int i = k; i < n; i++) {
        std::cin >> m;
        B.insert(m);
        B.extract();
    }
    for (int i = 0; i < k; i++) {
        ch.push_back(B.get());
        B.extract();
    }

    for (int i = k - 1; i >= 0; i--) {
        std::cout << ch[i] << " ";
    }

}
