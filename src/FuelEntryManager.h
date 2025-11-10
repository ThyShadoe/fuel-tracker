#include <chrono>
#include <cstdlib>
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
  FuelEntry(const string &entryDate, double odometer, double amount,
            double price)
      : date(entryDate), odometerReading(odometer), fuelAmount(amount),
        fuelPrice(price) {}

  // Getters
  string getDate() const { return date; }
  double getOdometerReading() const { return odometerReading; }
  double getFuelAmount() const { return fuelAmount; }
  double getFuelPrice() const { return fuelPrice; }

  // Setters
  void setDate(const string &date) { this->date = date; }
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
         << "| Fuel Price       : " << "₱" << fuelPrice << "/L" << endl
         << "+------------------+--------------+\n";
  }

private:
  string date;
  double odometerReading;
  double fuelAmount;
  double fuelPrice;
};

class FuelEntryManager {
public:
  void AddFuelEntry() {
    string date;
    double odometerReading, fuelAmount, fuelPrice;

    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, date);

    cout << "Enter odometer reading (km): ";
    cin >> odometerReading;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Input and validate fuel amount
    while (true) {
      cout << "Enter fuel amount (liters): ";
      cin >> fuelAmount;

      if (fuelAmount < 1) {
        cout << "Amount cannot be zero or lower.\n";
        this_thread::sleep_for(chrono::seconds(1));
        continue;

      } else if (fuelAmount > tankCapacity) {
        cout << "Amount cannot be higher than tank capacity.\n"
             << "Current tank capacity: " << fixed << setprecision(2)
             << tankCapacity << "L\n";
        this_thread::sleep_for(chrono::seconds(1));

      } else {
        break;
      }
    }
    cout << "Enter fuel price (₱/liter): ";
    cin >> fuelPrice;

    // Add fuel amount to tank state
    tankState += fuelAmount;

    // Place all user input into fuel entry
    entries.emplace_back(date, odometerReading, fuelAmount, fuelPrice);
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
           << "| FUEL ENTRY NO. " << i + 1 << endl
           << "+------------+--------------------+\n"
           << "| Entry Date : " << entries[i].getDate() << endl
           << "+------------+--------------------+\n";
    }
    cout << "Enter Entry number you would like to remove: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
         << "| Total Expenses  : " << "₱" << totalExpenses << endl
         << "+-----------------+---------------+\n";

    cout << "Press Enter to Continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  void ConfigureSettings() {
    int choice;
    do {
      system("clear");
      cout << "+---------------------------------+\n"
           << "| CONFIGURE SETTINGS              |\n"
           << "+-----------------------+---------+\n"
           << "| Current Tank Capacity : " << tankCapacity << "L\n"
           << "| Current Tank State    : " << tankState << "L\n"
           << "+-----------------------+---------+\n"
           << "| [1] Edit Tank Capacity          |\n"
           << "| [2] Reset Tank State            |\n"
           << "+---------------------------------+\n"
           << "| [0] Exit                        |\n"
           << "+---------------------------------+\n";
      cout << "Select menu option (0-2): ";
      cin >> choice;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      switch (choice) {
      case 0:
        break;
      case 1:
        while (true) {
          system("clear");
          cout << "Enter new tank capacity (current: " << tankCapacity
               << "L): ";
          cin >> tankCapacity;
          if (tankCapacity < 1) {
            cout << "Tank capacity cannot be zero or below.\n";
            return;
          } else {
            system("clear");
            cout << "Tank capacity was changed to: " << tankCapacity << "L\n";
            this_thread::sleep_for(chrono::seconds(2));
            break;
          }
        }
        break;
      case 2:
        system("clear");
        tankState = 0.0;
        cout << "Tank state was reset.\n";
        this_thread::sleep_for(chrono::seconds(2));
        break;
      }
    } while (choice != 0);
  }

private:
  double tankState = 0.0;
  double tankCapacity = 55.0;
  vector<FuelEntry> entries;
};
