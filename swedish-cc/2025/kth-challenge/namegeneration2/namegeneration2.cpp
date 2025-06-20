#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <fstream>
using namespace std;

#define sz(c) ((int)c.size())

string vow = "eiauo";
string con = "xvyrjhcfwmtpnlqkgbzds";
string letters = vow + con;

vector<string> prod2(string s) {
  vector<string> ans;
  for (int i = 0; i < sz(s); i++) {
    for (int j = 0; j < sz(s); j++) {
      ans.push_back(string{s[i]} + s[j]);
      ans.push_back(string{s[j]} + s[i]);
    }
  }

  return ans;
}

int main() {
vector<bool> use(66150);
  vector<string> conv;
  map<string, int> conv2;
  __gnu_pbds::priority_queue<pair<int, int>> pq;
  vector<decltype(pq)::point_iterator> its(66150);

  int ind = 0;

  for (auto v : prod2(vow)) {
    for (auto c : prod2(con)) {
      for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
          string word = "    ";
          word[i] = v[0];
          word[j] = v[1];
          int l = 0;
          for (int k = 0; k < 4; k++) {
            if (k == i || k == j)
              continue;
            word[k] = c[l++];
          }

          if (conv2.count(word)) continue;

          conv2[word] = ind;
          conv.push_back(word);
          its[ind] = pq.push({-100, ind});
          ind++;
        }
      }
    }
  }

  cout << "Generated words" << endl;
  cout << sz(pq) << endl;

  vector<string> used;

  auto upd = [&](string s) {
    for (int i = 0; i < 4; i++) {
      for (auto j : letters) {
        string ns = s;
        ns[i] = j;

        int ind = conv2[ns];
        if (!use[ind] && its[ind] != pq.end()) {
          pq.modify(its[ind], {its[ind]->first + 1, its[ind]->second});
        }
      }
    }
  };

  while (sz(pq)) {
    auto [p, wordind] = pq.top();
    pq.pop();

    if (sz(pq) && pq.top().first == p && rand() % 2) {
      auto [t1, t2] = pq.top();
      its[wordind] = pq.push({p, wordind});
      tie(p, wordind) = tie(t1, t2);
    }

    p = -p;

    if (p < 0)
      continue;

    if (use[wordind])
      continue;

    used.push_back(conv[wordind]);
    use[wordind] = 1;

    for (int i = 0; i < 4; i++) {
      for (auto j : letters) {
        string nw = conv[wordind];
        nw[i] = j;

        int nwind = conv2[nw];

        if (its[nwind] == pq.end() || use[nwind])
          continue;

        use[nwind] = 1;

        upd(nw);
      }
    }
  }

  cout << sz(used) << '\n';

  ofstream out("./out.txt");
  for (auto i : used)
    out << i << '\n';
}
