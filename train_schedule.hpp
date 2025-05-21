#ifndef TRAIN_SCHEDULE_H
#define TRAIN_SCHEDULE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <optional>

using namespace std;

class Train {
public:
    string name;
    vector<string> towns;

    Train() = default;
    Train(const string &trainName, const vector<string> &route);
};

class TrainSchedule {
private:
    unordered_map<string, Train> trains;

public:
    void createTrain(const string &name, const vector<string> &towns);
    void trainsForTown(const string &town) const;
    void townsForTrain(const string &trainName) const;
    void allTrains() const;
};

enum class Type {
    CREATE_TRAIN,
    TRAINS_FOR_TOWN,
    TOWNS_FOR_TRAIN,
    TRAINS,
    UNKNOWN
};

Type commandFromString(const string& command);

#endif
