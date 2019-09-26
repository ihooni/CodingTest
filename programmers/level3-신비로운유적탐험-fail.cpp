/**
 * Time complexity of `calcMax` is n factorial.
 * This function should be improved.
 */

#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct pair_hash
{
  template <class T1, class T2>
  size_t operator() (const pair<T1, T2> &pair) const
  {
    return hash<T1>()(pair.first) ^ hash<T2>()(pair.second);
  }
};

unordered_map<pair<int, int>, int, pair_hash> maxCounts;

vector<vector<vector<int>>> sortByLevel(vector<vector<int>> g1, vector<vector<int>> g2) {
  vector<vector<vector<int>>> result;
  result.push_back(vector<vector<int>>(2, vector<int>(1, 1)));

  int i = 0;
  vector<vector<int>>::iterator iter;
  while (!g1.empty() && !g2.empty()) {
    result.push_back(vector<vector<int>>(2));

    // g1
    for (int parent : result[i][0]) {
      for (iter = g1.begin(); iter != g1.end();) {
        if ((*iter)[0] == parent) {
          result[i + 1][0].push_back((*iter)[1]);
          iter = g1.erase(iter);
        } else if ((*iter)[1] == parent) {
          result[i + 1][0].push_back((*iter)[0]);
          iter = g1.erase(iter);
        } else {
          iter++;
        }
      }
    }

    // g2
    for (int parent : result[i][1]) {
      for (iter = g2.begin(); iter != g2.end();) {
        if ((*iter)[0] == parent) {
          result[i + 1][1].push_back((*iter)[1]);
          iter = g2.erase(iter);
        } else if ((*iter)[1] == parent) {
          result[i + 1][1].push_back((*iter)[0]);
          iter = g2.erase(iter);
        } else {
          iter++;
        }
      }
    }

    i++;
  }

  reverse(result.begin(), result.end());

  return result;
}

vector<int> getChilds(vector<vector<int>> g, int node, vector<int> lowLevelNodes) {
  vector<int> adjacencyNodes;
  vector<int> childs;

  for (auto info : g) {
    if (info[0] == node) {
      adjacencyNodes.push_back(info[1]);
    } else if (info[1] == node) {
      adjacencyNodes.push_back(info[0]);
    }
  }

  sort(adjacencyNodes.begin(), adjacencyNodes.end());
  sort(lowLevelNodes.begin(), lowLevelNodes.end());
  set_intersection(adjacencyNodes.begin(), adjacencyNodes.end(),
                   lowLevelNodes.begin(), lowLevelNodes.end(),
                   back_inserter(childs));

  return childs;
}

int calcMax(vector<int> children1, vector<int> children2) {
  if (children1.empty() || children2.empty()) {
    return 0;
  }

  int max = 0;
  int temp = 0;
  vector<int> updatedChildren2;

  int currChild1 = *(children1.begin());
  children1.erase(children1.begin());

  for (auto iter = children2.begin(); iter != children2.end(); iter++) {
    updatedChildren2.clear();
    updatedChildren2.assign(children2.begin(), children2.end());
    updatedChildren2.erase(iter - children2.begin() + updatedChildren2.begin());

    temp = maxCounts.find(make_pair(currChild1, *iter))->second + calcMax(children1, updatedChildren2);
    if (temp > max) {
      max = temp;
    }
  }

  return max;
}

int solution(int n1, vector<vector<int>> g1, int n2, vector<vector<int>> g2) {
  vector<vector<vector<int>>> sortedNodes = sortByLevel(g1, g2);

  // lowest level
  for (auto g1Node : sortedNodes[0][0]) {
    for (auto g2Node : sortedNodes[0][1]) {
      maxCounts.emplace(make_pair(g1Node, g2Node), 1);
    }
  }

  int i;
  int currCount = 0;
  for (i = 1; i < sortedNodes.size(); i++) {
    for (auto g1Node : sortedNodes[i][0]) {
      for (auto g2Node : sortedNodes[i][1]) {
        currCount = 1 + calcMax(getChilds(g1, g1Node, sortedNodes[i - 1][0]), getChilds(g2, g2Node, sortedNodes[i - 1][1]));
        maxCounts.emplace(make_pair(g1Node, g2Node), currCount);
      }
    }
  }

  return maxCounts.find(make_pair(1, 1))->second;
}

int main() {
  vector<vector<int>> g1 = {{3, 1}, {5, 7}, {8, 7}, {2, 3}, {3, 6}, {1, 5}, {4, 3}};

  vector<vector<int>> g2 = {{1, 5}, {5, 6}, {3, 7}, {3, 1}, {7, 4}, {7, 2}, {9, 8}, {5, 9}};

  printf("%d\n", solution(8, g1, 9, g2));
  for (auto it = maxCounts.begin(); it != maxCounts.end(); it++) {
    printf("%d %d: %d\n", it->first.first, it->first.second, it->second);
  }

  return 0;
}