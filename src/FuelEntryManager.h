#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

using namespace std;

// TODO: Add file saving support (either txt or csv)
// TODO: Add a validation function for user input (separate class prob)

class FuelEntry {
public:
  // Constructor
  FuelEntry(const string &entryDate, const string &type, double odometer,
            double amount, double price)
      : date(entryDate), fuelType(type), odometerReading(odometer),
        fuelAmount(amount), fuelPrice(price) {}

  // Getters
  string getDate() const { return date; }
  string getFuelType() const { return fuelType; }
  double getOdometerReading() const { return odometerReading; }
  double getFuelAmount() const { return fuelAmount; }
  double getFuelPrice() const { return fuelPrice; }

  // Setters
  void setDate(const string &date) { this->date = date; }
  void setFuelType(const string &fuelType) { this->fuelType = fuelType; }
  void setOdometerReading(const double odometerReading) {
    this->odometerReading = odometerReading;
  }
  void setFuelAmount(const double fuelAmount) { this->fuelAmount = fuelAmount; }
  void setFuelPrice(const double fuelPrice) { this->fuelPrice = fuelPrice; }

  // Display Full Entry
  void displayEntry() const {
    cout << fixed << setprecision(2);
    cout << "+------------------+--------------+\n"
         << "| Entry Date       : " << date << endl
         << "| Odometer Reading : " << odometerReading << "km" << endl
         << "| Fuel Amount      : " << fuelAmount << "L" << endl
         << "| Fuel Price       : " << "$" << fuelPrice << "/L" << endl
         << "| Fuel Type        : " << fuelType << endl
         << "+------------------+--------------+\n";
  }

private:
  string date;
  string fuelType;
  double odometerReading;
  double fuelAmount;
  double fuelPrice;
};

class FuelEntryManager {
public:
  void AddFuelEntry() {
    string date, fuelType;
    double odometerReading, fuelAmount, fuelPrice;
    int fuelTypeChoice;

    cout << "Enter date: ";
    getline(cin, date);

    cout << "Enter odometer reading (km): ";
    cin >> odometerReading;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter fuel amount (liters): ";
    cin >> fuelAmount;

    cout << "Enter fuel price ($/liter): ";
    cin >> fuelPrice;

    cout << "Select fuel type:\n"
         << "1. Gasoline\n"
         << "2. Diesel\n"
         << "3. Electric\n"
         << "4. Hybrid\n"
         << "Enter your choice (1-4): ";
    cin >> fuelTypeChoice;

    switch (fuelTypeChoice) {
    case 1:
      fuelType = "Gasoline";
      break;
    case 2:
      fuelType = "Diesel";
      break;
    case 3:
      fuelType = "Electric";
      break;
    case 4:
      fuelType = "Hybrid";
      break;
    default:
      cout << "Invalid option: Defauting to Gasoline.\n";
      fuelType = "Gasoline";
      break;
    }

    entries.emplace_back(date, fuelType, odometerReading, fuelAmount,
                         fuelPrice);
    cout << "Fuel entry was recorded successfully!\n";
    this_thread::sleep_for(chrono::seconds(2));
  }

  void RemoveFuelEntry() {
    int choice;
    if (entries.empty()) {
      cout << "No entries are currently recorded.\n";
      this_thread::sleep_for(chrono::seconds(2));
      return;
    }
    for (int i = 0; i < entries.size(); i++) {
      cout << "+---------------------------------+\n"
           << "| FUEL ENTRY NO. " << i + 1 << endl;
      entries[i].displayEntry();
    }
    cout << "Enter Entry number you would like to remove: ";
    cin >> choice;
    cin.ignore();

    if (choice >= 1 && choice <= entries.size()) {
      entries.erase(entries.begin() + choice - 1);
      cout << "Entry was removed successfully.\n";
      this_thread::sleep_for(chrono::seconds(2));
    } else {
      cout << "Invalid number: Could not remove the entry.\n";
      this_thread::sleep_for(chrono::seconds(2));
    }
  }

  void GenerateReport() {
    if (entries.empty()) {
      cout << "No entries are currently recorded.\n";
      this_thread::sleep_for(chrono::seconds(2));
      return;
    }
    for (int i = 0; i < entries.size(); i++) {
      cout << "+---------------------------------+\n"
           << "| FUEL ENTRY NO. " << i + 1 << endl;
      entries[i].displayEntry();
    }

    cout << "Press Enter to Continue...";
    cin.ignore();
  }
  void CalculateEfficiency() {
    if (entries.size() < 2) {
      cout << "Not enough entries: requires 2 minimum entries.\n";
      this_thread::sleep_for(chrono::seconds(2));
      return;
    }

    double totalDistance = 0.0;
    double totalFuelUsed = 0.0;
    double totalExpenses = 0.0;

    for (int i = 1; i < entries.size(); i++) {
      double distance =
          entries[i].getOdometerReading() - entries[i - 1].getOdometerReading();
      double fuelUsed = entries[i].getFuelAmount();
      double pricePerLiter = entries[i].getFuelPrice();

      totalDistance += distance;
      totalFuelUsed += fuelUsed;
      totalExpenses += fuelUsed * pricePerLiter;
    }

    if (totalFuelUsed == 0) {
      cout << "Total fuel used cannot be zero.";
      this_thread::sleep_for(chrono::seconds(2));
      return;
    }

    double efficiency = totalDistance / totalFuelUsed;
    cout << "+---------------------------------+\n"
         << "| CALCULATED FUEL EFFICIENCY       \n"
         << "|-----------------+---------------+\n"
         << "| Fuel Efficiency : " << efficiency << "km/L" << endl
         << "| Total Expenses  : " << "$" << totalExpenses << endl
         << "+---------------------------------+\n";

    cout << "Press Enter to Continue...";
    cin.ignore();
  }

private:
  vector<FuelEntry> entries;
};
