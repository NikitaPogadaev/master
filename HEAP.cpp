#include <iostream>
#include <algorithm>
#include <utility>
#include<cstdlib>
#include<assert.h>
#include <string>

const long long DBS = 1000000;

class Heap {
public:
    Heap();
    ~Heap();
    void insert(long long x);
    void extract();
    long long get();
    void decKey(long long y, long long d);
private:
    std::pair<long long, long long>* HeapArray = new std::pair<long long, long long>[DBS];
    long long* time = new long long[1000001];
    long long BS = DBS;
    long long size = 0;
    long long counter = 1;
    void growHeap();
    void siftUp(long long i);
    void siftDown(long long i);

    Heap(const Heap&) = delete;
    void operator=(const Heap&) = delete;
};
Heap::Heap() {

}
Heap::~Heap() {
    delete[] HeapArray;
    delete[] time;
}
void Heap::growHeap()
{
    BS *= 2;
    std::pair<long long, long long>* newB = new std::pair<long long, long long>[BS];
    for (long long i = 0; i < size; ++i) {
        newB[i] = HeapArray[i];
    }
    delete[] HeapArray;
    HeapArray = newB;

}


void Heap::insert(long long x) {
    if (size == BS)growHeap();
    HeapArray[size] = { x,counter };

    time[counter] = size;
    siftUp(size);
    counter++;
    size++;
}
long long Heap::get() {
    counter++;
    return HeapArray[0].first;
}

void Heap::extract() {
    size--;
    HeapArray[0] = HeapArray[size];
    time[HeapArray[0].second] = 0;
    siftDown(0);
    counter++;
}

void Heap::siftUp(long long x) {
    if ((x != 0) && (HeapArray[((x + 1) / 2) - 1].first > HeapArray[x].first)) {
        swap(HeapArray[((x + 1) / 2) - 1], HeapArray[x]);
        time[HeapArray[((x + 1) / 2) - 1].second] = ((x + 1) / 2) - 1;
        time[HeapArray[x].second] = x;
        siftUp(((x + 1) / 2) - 1);
    }
}
void Heap::siftDown(long long x) {
    long long x1 = x + 1;
    long long x2 = 2 * x1, x3 = 2 * x1 + 1;

    if (x2 - 1 < size)
        if (x3 - 1 < size) {
            if (HeapArray[x2 - 1].first <= HeapArray[x3 - 1].first) {
                if (HeapArray[x].first > HeapArray[x2 - 1].first) {
                    swap(HeapArray[x], HeapArray[x2 - 1]);
                    time[HeapArray[x2 - 1].second] = x2 - 1;
                    time[HeapArray[x].second] = x;
                    siftDown(x2 - 1);
                }
            }
            else if (HeapArray[x].first > HeapArray[x3 - 1].first) {
                swap(HeapArray[x], HeapArray[x3 - 1]);
                time[HeapArray[x].second] = x;
                time[HeapArray[x3 - 1].second] = x3 - 1;
                siftDown(x3 - 1);
            }
        }
        else if (HeapArray[x].first > HeapArray[x2 - 1].first) {
            swap(HeapArray[x], HeapArray[x2 - 1]);
            time[HeapArray[x].second] = x;
            time[HeapArray[x2 - 1].second] = x2 - 1;
            siftDown(x2 - 1);
        }

}
void Heap::decKey(long long y, long long d) {
    HeapArray[time[y]].first -= d;
    siftUp(time[y]);
    counter++;
}


int main()
{
    Heap A;
    long long q;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin >> q;
    std::string s;
    while (q > 0) {
        std::cin >> s;
        if (s == "getMin") {
            long long temp = A.get();
            std::cout << temp << '\n';
        }
        if (s == "extractMin")
            A.extract();
        else if (s == "decreaseKey") {
            long long a;
            long long b;
            std::cin >> a >> b;
            A.decKey(a, b);
        }
        else if (s == "insert") {
            long long v;
            std::cin >> v;
            A.insert(v);

        }

        q--;


    }

}