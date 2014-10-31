#include <iostream>
#include <vector>
#include <list>
#include <cassert>
using namespace std;


class Solution {
  public:
    int cal(const vector<int> &vec) {
      if (vec.empty()) return 0;

      list<pair<int, int> > pos(1, make_pair(-1, -1));
      list<pair<int, int> >::iterator iter = pos.begin();

      int sum = 0;
      for (size_t i = 0; i < vec.size(); ++i) {

        if (vec[i] == 1) {
          sum += 1;
          list<pair<int, int> >::iterator tmp = iter;
          if (++tmp == pos.end()) {
            pos.push_back(make_pair(i, i));
            ++iter;
          } else {
            ++iter;
            iter->second = i;
          }

        } else { // vec[i] == -1
          sum -= 1;
          if (iter == pos.begin()) {
            pos.push_front(make_pair(i, i));
            --iter;
          } else {
            --iter;
            iter->second = i;
          }
        }

      }

      int maxdiff = 0;
      for (iter = pos.begin(); iter != pos.end(); ++iter) {
        int diff = iter->second - iter->first;
        maxdiff = diff > maxdiff ? diff : maxdiff;
      }

      return maxdiff;
    }
};



int main() {

  Solution sln;
  {
    const int N = 10;
    int arr[N] = {0, 1, 1, 0, 1, 0, 1, 1, 1, 0};
    vector<int> vec(arr, arr+N);
    assert(sln.cal(vec) == 6);
  }
  {
    const int N = 1;
    int arr[N] = {0};
    vector<int> vec(arr, arr+N);
    assert(sln.cal(vec) == 0);
  }
  {
    const int N = 2;
    int arr[N] = {0, 0};
    vector<int> vec(arr, arr+N);
    assert(sln.cal(vec) == 0);
  }
  {
    const int N = 2;
    int arr[N] = {0, 1};
    vector<int> vec(arr, arr+N);
    assert(sln.cal(vec) == 2);
  }

}
