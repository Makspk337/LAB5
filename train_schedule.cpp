#include "train_schedule.hpp"
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

Train::Train(const string &trainName, const vector<string> &route)
    : name(trainName), towns(route) {}

void TrainSchedule::createTrain(const string &name, const vector<string> &towns) {
    if (trains.count(name)) {
        cout << "Поезд " << name << " уже существует!" << endl;
        return;
    }

    if (towns.size() < 2) {
        cout << "Нельзя создать поезд с менее чем двумя остановками!" << endl;
        return;
    }

    unordered_set<string> uniqueTowns(towns.begin(), towns.end());
    if (uniqueTowns.size() != towns.size()) {
        cout << "Нельзя создать поезд с повторяющимися остановками!" << endl;
        return;
    }

    trains[name] = Train(name, towns);
}

void TrainSchedule::trainsForTown(const string &town) const {
    bool found = false;
    for (const auto &[trainName, train] : trains) {
        if (find(train.towns.begin(), train.towns.end(), town) != train.towns.end()) {
            cout << trainName << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "В городе " << town << " нет поездов!" << endl;
    }
}

void TrainSchedule::townsForTrain(const string &trainName) const {
    auto it = trains.find(trainName);
    if (it == trains.end()) {
        cout << "Такого поезда не существует!" << endl;
        return;
    }

    const Train &train = it->second;
    for (const string &town : train.towns) {
        cout << "Помимо поезда " << trainName << " город " << town << " проезжают поезда ";
        for (const auto &[otherTrainName, otherTrain] : trains) {
            if (otherTrainName != trainName &&
                find(otherTrain.towns.begin(), otherTrain.towns.end(), town) != otherTrain.towns.end()) {
                cout << otherTrainName << " ";
            }
        }
        cout << endl;
    }
}

void TrainSchedule::allTrains() const {
    if (trains.empty()) {
        cout << "Поездов нет!" << endl;
        return;
    }

    for (const auto &[trainName, train] : trains) {
        cout << "Поезд " << trainName << " останавливается в городах ";
        for (const string &town : train.towns) {
            cout << town << " ";
        }
        cout << endl;
    }
}

Type commandFromString(const string& command) {
    if (command == "CREATE_TRAIN") return Type::CREATE_TRAIN;
    if (command == "TRAINS_FOR_TOWN") return Type::TRAINS_FOR_TOWN;
    if (command == "TOWNS_FOR_TRAIN") return Type::TOWNS_FOR_TRAIN;
    if (command == "TRAINS") return Type::TRAINS;
    return Type::UNKNOWN;
}
