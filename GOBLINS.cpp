#include <iostream>
#include <deque>



class GQueue {
public:
    GQueue();

    void push(int u);
    void push_mid(int u);
    int pop();
private:
    std::deque<int>q1;
    std::deque<int>q2;
};
GQueue::GQueue() {

}

void GQueue::push(int u) {

    int siz = (q1.size() + q2.size()) % 2;
    if (siz == 1)q2.push_back(u);
    else
        if (q2.size() != 0) {
            q1.push_back(q2[0]);
            q2.pop_front();
            q2.push_back(u);
        }
        else q1.push_back(u);
}
void GQueue::push_mid(int u) {
    int siz = (q1.size() + q2.size()) % 2;
    if (siz == 1)q2.push_front(u);
    else q1.push_back(u);
}
int GQueue::pop() {
    int siz = (q1.size() + q2.size()) % 2;
    if (siz == 1) {
        int temp = q1[0];
        q1.pop_front();
        return temp;
    }
    else {
        int temp = q1[0];
        q1.pop_front();
        q1.push_back(q2[0]);
        q2.pop_front();
        return temp;
    }
}


int main()
{
    int n;
    std::cin >> n;

    GQueue A;
    char c;
    for (int i = 0; i < n; i++) {
        std::cin >> c;
        if (c == '+') {
            int u;
            std::cin >> u;
            A.push(u);

        }
        else if (c == '*') {
            int u;
            std::cin >> u;
            A.push_mid(u);
        }
        else if (c == '-') {
            int temp = A.pop();
            std::cout << temp << std::endl;
        }
    }
}