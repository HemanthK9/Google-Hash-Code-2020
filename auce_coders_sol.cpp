#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pi;

int B, L, D;
vector<int> book_scores;
vector<int> numBooks;
vector<pair<int, int> > times;
vector<int> limit;

unordered_map<int, priority_queue<pair<int, int> > > lib_books;
// vector<int> seen;

bool comp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.first < b.first;
}

void input()
{
    cin >> B >> L >> D;
    book_scores.resize(B, 0);
    // seen.resize(B, 0);
    for (int i = 0; i < B; i++)
    {
        int temp;
        cin >> temp;
        book_scores[i] = temp;
    }
    numBooks.resize(L);
    // times.resize(L);
    limit.resize(L);
    int n, t, l;
    for (int i = 0; i < L; i++)
    {
        cin >> n >> t >> l;
        numBooks[i] = n;
        times.push_back(make_pair(t, i));
        limit[i] = l;
        for (int j = 0; j < n; j++)
        {
            int id;
            cin >> id;
            lib_books[i].push(make_pair(book_scores[id], id));
        }
    }
}
vector<pair<int, int> > getDays(vector<pair<int, int> > times)
{
    vector<pair<int, int> > res;
    int d = 0;
    int i = 0;
    while (d < D)
    {
        if (i >= L)
            break;
        d += times[i].first;
        if (d >= D)
            break;
        res.push_back(make_pair(times[i].second, d));
        i++;
    }
    return res;
}

int main()
{
    input();
    int sum = B;
    sort(times.begin(), times.end(), comp);
    vector<pair<int, int> > days = getDays(times);
    cout << days.size() << endl;
    for (auto it : days)
    {
        int count = 0;
        int id = it.first;
        int diff = D - it.second;
        // cout << id << endl;
        vector<int> seen(B, 0);
        vector<int> res;
        int lim = limit[id];
        auto pq = lib_books[id];
        // cout << diff << endl;
        for (int d = 0; d < diff; d++)
        {

            for (int l = 0; l < lim;)
            {
                if (pq.empty())
                    break;
                auto p = pq.top();
                pq.pop();
                if (seen[p.second] == 0)
                {
                    count++;
                    seen[p.second] = 1;
                    res.push_back(p.second);
                    l++;
                }
            }
            if (pq.empty())
                break;
        }
        cout << id << " " << count << endl;
        for (int i : res)
            cout << i << " ";
        cout << endl;
    }
    // auto pq = lib_books[1];
    // while(!pq.empty()) {
    //     auto p = pq.top();
    //     pq.pop();
    //     cout << p.second << " " << p.first << endl;
    // }

    return 0;
}
