#include <iostream>
#include <vector>
#include <cassert>
using namespace std;


class Solution {
  private:
    class Pos {
      public:
      Pos(int l, int r) : 
          left(l), right(r) {}
      Pos(){}
      int left;
      int right;
    };

    void deal(int sum, int i, 
              vector<Pos> &zero,
              vector<Pos> &positive, 
              vector<Pos> &negative) {
      if (sum == 0) {
        if (zero.empty()) {
          zero.push_back(Pos(-1, i));
        } else {
          zero[0].right = i;
        }
      } else if (sum > 0) {
        if (sum >= positive.size()) {
          positive.push_back(Pos(i, i));
        } else {
          positive[sum].right = i;
        }
      } else {
        if (-sum >= negative.size()) {
          negative.push_back(Pos(i, i));
        } else {
          negative[-sum].right = i;
        }
      }
    }
    
  public:
    int cal(const vector<int> &vec) {
      if (vec.empty()) return 0;

      vector<Pos> zero;
      vector<Pos> positive(1, Pos()); 
      vector<Pos> negative(1, Pos());

      int sum = 0;
      for (size_t i = 0; i < vec.size(); ++i) {
        sum += (vec[i] == 1 ? 1 : -1);
        deal(sum, i, zero, positive, negative);
      }

      int maxdis = 0;
      for (size_t i = 0; i < zero.size(); ++i) {
        int diff = zero[i].right - zero[i].left;
        maxdis = diff > maxdis ? diff : maxdis;
      }
      for (size_t i = 1; i < positive.size(); ++i) {
        int diff = positive[i].right - positive[i].left;
        maxdis = diff > maxdis ? diff : maxdis;
      }
      for (size_t i = 1; i < negative.size(); ++i) {
        int diff = negative[i].right - negative[i].left;
        maxdis = diff > maxdis ? diff : maxdis;
      }
      return maxdis;
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
