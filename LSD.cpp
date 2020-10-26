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




void LSD(std::vector<long long>& ch1) {
    long long co = 1;
    vector<long long>ch;
    vector<pair<long long, long long>>AB[2];
    for (int i = 0; i < ch1.size(); i++)AB[0].push_back({ ch1[i],i });
    while (co < 65) {
        vector<pair<long long, long long>>ab[2];
        for (auto i : AB[0])ab[i.first % 2].push_back({ i.first / 2,i.second });
        while (AB[0].size() > 0)AB[0].pop_back();
        for (auto i : AB[1])ab[i.first % 2].push_back({ i.first / 2,i.second });
        while (AB[1].size() > 0)AB[1].pop_back();

        for (auto i : ab[0])AB[0].push_back(i);
        for (auto i : ab[1])AB[1].push_back(i);
        co++;
    }
    for (auto i : AB[0])ch.push_back(ch1[i.second]);
    for (auto i : AB[1])ch.push_back(ch1[i.second]);

    for (int i = 0; i < ch.size(); i++)ch1[i] = ch[i];
}




int main()
{
    std::vector<long long> ch;

    long long k, m, n, co = 0;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> m;
        ch.push_back(m);
    }
    long long temp = 4 << 2;
    LSD(ch);
    for (auto i : ch)cout << i << " ";
}