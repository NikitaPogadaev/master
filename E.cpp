#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Struct_of_set {

public:

    Struct_of_set();
    Struct_of_set(long long);
    ~Struct_of_set();
    void Add(long long, long long);
    void Delete(long long, long long);
    void Clear(long long);


    vector < set<long long>> v;
    map <long long, set<long long>> g;

public:
    /*long long sz(long long a) {
        return v[a].size();
    }
    long long multi_count(long long a) {
        return g[a].size();
    }*/

};

Struct_of_set::Struct_of_set() {
    v.resize(100001);
}

Struct_of_set::Struct_of_set(long long sz) {
    v.resize(sz + 1);
}

Struct_of_set::~Struct_of_set() {

    v.clear();
    g.clear();

}

void Struct_of_set::Add(long long a, long long b) {
    v[b].insert(a);
    g[a].insert(b);
}

void Struct_of_set::Delete(long long a, long long b) {
    v[b].erase(a);
    g[a].erase(b);
}

void Struct_of_set::Clear(long long s) {
    for (auto i : v[s])g[i].erase(s);
    v[s].clear();
}

int main() {

    string t;
    long long n, m, k, e, s;

    cin >> n >> m >> k;
    Struct_of_set st(m+1);

    for (long long j = 0; j < k; ++j) {

        cin >> t;
        if (t == "ADD") {
            cin >> e >> s;
            st.Add(e, s);
        }
        else if (t == "DELETE") {
            cin >> e >> s;
            st.Delete(e, s);
        }
        else if (t == "CLEAR") {

            cin >> s;
            st.Clear(s);

        }
        else if (t == "LISTSET") {
            cin >> s; 
            if (st.v[s].size() > 0) {
                for (auto i : st.v[s]) {
                    cout << i << ' ';
                }
            }
            else
                cout << -1;
            cout << endl;
        }
        else if (t == "LISTSETSOF") {
            cin >> e;
            if (st.g[e].size() > 0) {
                for (auto i : st.g[e]) {
                    cout << i << ' ';
                }
            }
            else
                cout << -1;
            cout << endl;
        }

    }

    return 0;

}