#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

void addFriend(unordered_map<string, unordered_set<string>> &friends, const string &i, const string &j) {
    friends[i].insert(j);
    friends[j].insert(i);
}

int countFriends(const unordered_map<string, unordered_set<string>> &friends, const string &i) {
    auto it = friends.find(i);
    if (it != friends.end()) {
        return it->second.size();
    }
    return 0;
}

bool areFriends(const unordered_map<string, unordered_set<string>> &friends, const string &i, const string &j) {
    auto it = friends.find(i);
    if (it != friends.end() && it->second.find(j) != it->second.end()) {
        return true;
    }
    return false;
}

int main() {
    int N;
    cin >> N;

    unordered_map<string, unordered_set<string>> friends;

    string query;
    string person1, person2;

    for (int i = 0; i < N; ++i) {
        cin >> query;

        if (query == "FRIENDS") {
            cin >> person1 >> person2;
            addFriend(friends, person1, person2);
        }
        else if (query == "COUNT") {
            cin >> person1;
            cout << countFriends(friends, person1) << endl;
        }
        else if (query == "QUESTION") {
            cin >> person1 >> person2;
            cout << (areFriends(friends, person1, person2) ? "YES" : "NO") << endl;
        }
    }

    return 0;
}

