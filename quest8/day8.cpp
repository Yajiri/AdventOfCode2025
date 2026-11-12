#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <fstream>
#include <sstream>
#include <windows.h> //This allowes me to run the SetConsoleOutputCP(CP_UTF8); in order to get my print distance² instead of distance^2

using namespace std;

struct Pair {
    long long distance;
    int i;
    int j;
};

long long dist2(const vector<int>& a, const vector<int>& b) {
    long long dx = a[0] - b[0];
    long long dy = a[1] - b[1];
    long long dz = a[2] - b[2];

    return dx * dx + dy * dy + dz * dz;
}

vector<Pair> getShortest1000(const vector<vector<int>>&points) {
        vector<Pair> pairs;

        for (int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++) {
                pairs.push_back({dist2(points[i], points[j]), i, j});
            }
        }
        sort(pairs.begin(), pairs.end(), [](const Pair& a, const Pair& b) {
        return a.distance < b.distance;
        });
        for (int k = 0; k < 1000; k++) {
            const Pair& p = pairs[k];
            
            /*cout << points[p.i][0] << ","
                 << points[p.i][1] << ","
                 << points[p.i][2] << "<->"
                 << points[p.j][0] << ","
                 << points[p.j][1] << ","
                 << points[p.j][2] 
                 << " distance² = "
                 << p.distance << '\n';*/
        }
        return vector<Pair>(pairs.begin(), pairs.begin() + 1000);
    }
    int solution(const vector<vector<int>>& points) {
        auto pairs = getShortest1000(points);

        vector<vector<int>> graph(points.size());

        for (const Pair& p : pairs) {
            graph[p.i].push_back(p.j);
            graph[p.j].push_back(p.i);
        }
        unordered_set<int> visited;
        vector<int> sizes;

        for (int start = 0; start < points.size(); start++) {
            if (visited.count(start))
                continue;
            stack<int> st;
            st.push(start);

            int size = 0;

            while (!st.empty()) {
                int node = st.top();
                st.pop();

                if (visited.count(node))
                    continue;

                    visited.insert(node);
                    size++;

                    for (int neighbor : graph[node]) {
                        if (!visited.count(neighbor)) {
                            st.push(neighbor);
                    }
                }
            }
            sizes.push_back(size);
        }
        sort(sizes.begin(), sizes.end(), greater<int>());
        return sizes[0] * sizes[1] * sizes [2]; 
    }

int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<vector<int>> points;
    ifstream file("input.txt");
    if (!file) {
        cout << "could not open the file";
        return 1;
    }
    string line;
    
    while (getline(file, line)) {
        vector<int> point;
        stringstream ss(line);
        string value;

        while (getline(ss, value, ',')) {
            point.push_back(stoi(value));
        }
    points.push_back(point);
    }

    cout << solution(points) << '\n';
}