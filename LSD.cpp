#include <iostream>
#include <algorithm>
#include <utility>
#include<cstdlib>
#include<vector>
#include<assert.h>
#include <string>
#include <set>

using namespace std;
bool cmp(int a, int b) { return a < b; }




void LSD(std::vector<long long>& ch1) {
    long long co = 1;
    vector<long long>ch;
    vector<pair<long long, long long>>AB[256];
    for (int i = 0; i < ch1.size(); i++)AB[0].push_back({ ch1[i],i });
    while (co < 9) {
        vector<pair<long long, long long>>ab[256];

        for (int j = 0; j < 256; j++) {
            for (auto i : AB[j])ab[i.first & 255].push_back({ i.first >> 8,i.second });
            while (AB[j].size() > 0)AB[j].pop_back();
        }

        for (int j = 0; j < 256; j++) {
            for (auto i : ab[j])AB[j].push_back(i);
        }
        co++;
    }
    for (int j = 0; j < 256; j++) {
        for (auto i : AB[j])ch.push_back(ch1[i.second]);
    }

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
    LSD(ch);
    for (auto i : ch)cout << i << " ";
}
