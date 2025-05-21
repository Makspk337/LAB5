#include <iostream>
#include <unordered_map>
#include <string>
#include <iomanip>
using namespace std;

const int ZONES = 2, SHELVES = 4, SECTIONS = 18, LEVELS = 5;
const int MAX_PER_CELL = 10, TOTAL_CAPACITY = 7200;

struct Cell {
    string product = "";
    int quantity = 0;
};

unordered_map<string, Cell> warehouse;

bool validAddress(const string &address) {
    if (address.size() < 4 || address.size() > 5) return false;
    if (address[0] < 'A' || address[0] > 'B') return false;
    int shelf = address[1] - '0';
    if (shelf < 1 || shelf > 4) return false;
    int section = 0;
    int level = 0;

    if (address.size() == 4) {
        section = address[2] - '0';
        level = address[3] - '0';

        if (section < 1 || section > 18) return false;
        if (level < 1 || level > 5) return false;
    }
    if (address.size() == 5) {
        section = (address[2] - '0') * 10 + (address[3] - '0');
        level = address[4] - '0';

        if (section < 1 || section > 18) return false;
        if (level < 1 || level > 5) return false;
    }
    return true;
}

void add(string name, int qty, string addr) {
    if (!validAddress(addr)) {
        cout << "Такой ячейки не может быть!\n";
        return;
    }
    auto &cell = warehouse[addr];
    if (!cell.product.empty() && cell.product != name)
        cout << "В ячейке другой товар!\n";
    else if (cell.quantity + qty > MAX_PER_CELL)
        cout << "В ячейке нет столько места!\n";
    else if (cell.quantity + qty < 1)
        cout << "Нельзя добавить меньше одного товара!\n";
    else {
        cell.product = name;
        cell.quantity += qty;
        cout << "Добавлено " << qty << "шт"<< name << "в" << addr << ".\n";
    }
}

void remove(string name, int qty, string addr) {
    if (!validAddress(addr)) {
        cout << "Такой ячейки не может быть!\n";
        return;
    }
    auto &cell = warehouse[addr];
    if (!cell.product.empty() && cell.product != name)
        cout << "В ячейке другой товар!\n";
    else if (cell.product != name || cell.quantity < qty)
        cout << "В ячейке нет столько товара!\n";
    else {
        cell.quantity -= qty;
        if (cell.quantity == 0) cell.product = "";
        cout << "Удалено " << qty << "шт" << name << "из" << addr << ".\n";
    }
}

void info() {
    int used = 0, zoneUsed[ZONES] = {};
    for (auto it = warehouse.begin(); it != warehouse.end(); ++it) {
        string addr = it->first;
        Cell &c = it->second;
        used += c.quantity;
        if (c.quantity) zoneUsed[addr[0] - 'A'] += c.quantity;
    }

    cout << fixed << setprecision(2);
    cout << "Склад: " << 100.0 * used / TOTAL_CAPACITY << "%\n";
    for (int i = 0; i < ZONES; ++i)
        cout << "Зона " << char('A' + i) << ": "
        << 100.0 * zoneUsed[i] / (SHELVES * SECTIONS * LEVELS * MAX_PER_CELL) << "%\n";

    for (auto it = warehouse.begin(); it != warehouse.end(); ++it)
        if (it->second.quantity)
            cout << it->first << ": " << it->second.product << " - " << it->second.quantity << "\n";
}

int main() {
    setlocale(LC_ALL, "rus");
    string cmd;
    while (cin >> cmd) {
        if (cmd == "EXIT") break;
        if (cmd == "ADD") {
            string name, addr; int qty;
            cin >> name >> qty >> addr;
            add(name, qty, addr);
        }
        else if (cmd == "REMOVE") {
            string name, addr; int qty;
            cin >> name >> qty >> addr;
            remove(name, qty, addr);
        }
        else if (cmd == "INFO") info();
        else cout << "Неизвестная команда.\n";
    }
    return 0;
}
