#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <random>

using namespace std;

struct Visitor {
    string ticket;
    int duration;
};


string generate_ticket() {
    vector<int> ticket_pool;
    int ticket_index = 0;
    for (int i = 100; i <= 999; ++i)
        ticket_pool.push_back(i);
    shuffle(ticket_pool.begin(), ticket_pool.end(), mt19937(random_device{}()));

    return "T" + to_string(ticket_pool[ticket_index++]);
}


int best_makespan = INT_MAX;
vector<vector<Visitor>> best_distribution;

void backtrack(int idx, vector<int> &times, vector<vector<Visitor>> &curr_dist, const vector<Visitor> &visitors, int window_count) {
    if (idx == visitors.size()) {
        int current_makespan = *max_element(times.begin(), times.end());
        if (current_makespan < best_makespan) {
            best_makespan = current_makespan;
            best_distribution = curr_dist;
        }
        return;
    }

    const Visitor &v = visitors[idx];
    for (int i = 0; i < window_count; ++i) {
        times[i] += v.duration;
        curr_dist[i].push_back(v);

        if (*max_element(times.begin(), times.end()) < best_makespan) {
            backtrack(idx + 1, times, curr_dist, visitors, window_count);
        }

        times[i] -= v.duration;
        curr_dist[i].pop_back();
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int n;
    cout << "Введите количество окон: ";
    cin >> n;

    vector<Visitor> visitors;
    string cmd;
    while (cin >> cmd && cmd != "DISTRIBUTE") {
        if (cmd == "ENQUEUE") {
            int dur;
            cin >> dur;
            string ticket = generate_ticket();
            cout << ticket << endl;
            visitors.push_back({ ticket, dur });
        }
    }

    vector<int> times(n, 0);
    vector<vector<Visitor>> current_distribution(n);

    backtrack(0, times, current_distribution, visitors, n);

    for (int i = 0; i < n; ++i) {
        int total = 0;
        for (const auto &v : best_distribution[i])
            total += v.duration;

        cout << "Окно " << (i + 1) << " (" << total << " минут): ";
        for (size_t j = 0; j < best_distribution[i].size(); ++j) {
            cout << best_distribution[i][j].ticket;
            if (j + 1 < best_distribution[i].size()) cout << ", ";
        }
        cout << endl;
    }

    return 0;
}
