#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

class FuelEntry {
public:
  FuelEntry(const string &entryDate, double odometer, double amount,
            double price)
      : date(entryDate), odometerReading(odometer), fuelAmount(amount),
        fuelPrice(price) {}

private:
  string date;
  double odometerReading;
  double fuelAmount;
  double fuelPrice;
};

class FuelEntryManager {
public:
  void AddFuelEntry() { cout << "AddFuelEntry\n"; }
  void RemoveFuelEntry() { cout << "RemoveFuelEntry\n"; }
  void GenerateReport() { cout << "GenerateReport\n"; }
  void CalculateEfficiency() { cout << "CalculateEfficiency\n"; }

private:
  vector<FuelEntry> entries;
};
