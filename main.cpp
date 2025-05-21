#include "train_schedule.hpp"
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    TrainSchedule schedule;
    string commandLine;

    while (getline(cin, commandLine)) {
        istringstream iss(commandLine);
        string commandStr;
        iss >> commandStr;

        Type command = commandFromString(commandStr);

        switch (command) {
            case Type::CREATE_TRAIN: {
                string trainName, town;
                vector<string> towns;
                iss >> trainName;
                while (iss >> town) {
                    towns.push_back(town);
                }
                schedule.createTrain(trainName, towns);
                break;
            }
            case Type::TRAINS_FOR_TOWN: {
                string town;
                iss >> town;
                schedule.trainsForTown(town);
                break;
            }
            case Type::TOWNS_FOR_TRAIN: {
                string trainName;
                iss >> trainName;
                schedule.townsForTrain(trainName);
                break;
            }
            case Type::TRAINS: {
                schedule.allTrains();
                break;
            }
            case Type::UNKNOWN:
            default:
                cout << "Неизвестная команда!" << endl;
                break;
        }
    }

    return 0;
}
