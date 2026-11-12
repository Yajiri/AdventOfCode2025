#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
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

vector<Pair> getShortest10(const vector<vector<int>>&points) {
        vector<Pair> pairs;

        for (int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++) {
                pairs.push_back({dist2(points[i], points[j]), i, j});
            }
        }
        sort(pairs.begin(), pairs.end(), [](const Pair& a, const Pair& b) {
        return a.distance < b.distance;
        });
        for (int k = 0; k < 10; k++) {
            const Pair& p = pairs[k];

            
            cout << points[p.i][0] << ","
                 << points[p.i][1] << ","
                 << points[p.i][2] << "<->"
                 << points[p.j][0] << ","
                 << points[p.j][1] << ","
                 << points[p.j][2] 
                 << " distance² = "
                 << p.distance << '\n';
        }
        return vector<Pair>(pairs.begin(), pairs.begin() + 10);
    }
    int solution(const vector<vector<int>>& points) {
        auto pairs = getShortest10(points);

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
    vector<vector<int>> points = {
        {162,817,812},
        {57,618,57},
        {906,360,560},
        {592,479,940},
        {352,342,300},
        {466,668,158},
        {542,29,236},
        {431,825,988},
        {739,650,466},
        {52,470,668},
        {216,146,977},
        {819,987,18},
        {117,168,530},
        {805,96,715},
        {346,949,466},
        {970,615,88},
        {941,993,340},
        {862,61,35},
        {984,92,344},
        {425,690,689}
    };

    cout << solution(points) << '\n';
}