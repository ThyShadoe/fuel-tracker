#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include <thread>
#include <vector>

#ifndef FUEL_ENTRY_MANAGER_H
#define FUEL_ENTRY_MANAGER_H

#ifdef _WIN32
#include <Windows.h>
#endif
void clrscr();

#endif

using namespace std;

// TODO: Add comments for better documentation
// TODO: Add support for saving and loading data from file

class FuelEntry {
public:
  // Constructor
  FuelEntry(const string &entryDate, const double distance, const double amount,
            const double price)
      : date(entryDate), distanceDriven(distance), fuelConsumed(amount),
        fuelPrice(price) {}

  // Getters to return the specific value of a variable
  string getEntryDate() const { return date; }
  double getDistanceDriven() const { return distanceDriven; }
  double getFuelConsumed() const { return fuelConsumed; }
  double getFuelPrice() const { return fuelPrice; }

  // Setters to set a specific value to a variable
  void setEntryDate(const string &date) { this->date = date; }
  void setDistanceDriven(const double kilometersDriven) {
    this->distanceDriven = kilometersDriven;
  }
  void setFuelConsumed(const double litersUsed) {
    this->fuelConsumed = litersUsed;
  }
  void setFuelPrice(const double costPerLiter) {
    this->fuelPrice = costPerLiter;
  }

  // Function to display fuel entry
  void displayEntry() {
    cout << fixed << setprecision(2);
    cout << "+-----------------+---------------+\n"
         << "| Entry Date      : " << date << endl
         << "| Distance Driven : " << distanceDriven << "km\n"
         << "| Fuel Used       : " << fuelConsumed << "L\n"
         << "| Cost Per Liter  : " << "₱" << fuelPrice << endl
         << "+-----------------+---------------+\n";
  }

private:
  string date;
  double distanceDriven;
  double fuelConsumed;
  double fuelPrice;
};

class FuelEntryManager {
public:
  void AddFuelEntry() {
    string date;
    double distanceDriven, fuelConsumed, fuelPrice;
    // TODO: Add validation for date input
    while (true) {
      regex date_format;
      cout << "Enter entry date (YYYY-MM-DD): ";
      getline(cin, date);
      break;
    }

    // Input and validate distance driven
    while (true) {
      cout << "Enter distance driven (km): ";
      cin >> distanceDriven;
      if (cin.fail() || distanceDriven < 1) {
        cout << "Invalid input: Enter a valid number above zero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        this_thread::sleep_for(chrono::seconds(1));
        continue;
      } else {
        break;
      }
    }

    // Input and validate fuel consumed
    while (true) {
      cout << "Enter amount of fuel used (L): ";
      cin >> fuelConsumed;
      if (cin.fail() || fuelConsumed < 1) {
        cout << "Invalid input: Enter a valid number above zero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        this_thread::sleep_for(chrono::seconds(1));
        continue;
      } else {
        break;
      }
    }

    // Input and validate fuel price
    while (true) {
      cout << "Enter cost per liter (₱/L): ";
      cin >> fuelPrice;
      if (cin.fail() || fuelPrice < 0) {
        cout << "Invalid input: Enter a valid number above zero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        this_thread::sleep_for(chrono::seconds(1));
        continue;
      } else {
        break;
      }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    entries.emplace_back(date, distanceDriven, fuelConsumed, fuelPrice);

    clrscr();
    // clrscr();
    cout << "Trip entry was recorded successfully!\n";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  void ViewAllEntries() {
    for (int i = 0; i < entries.size(); i++) {
      cout << "+---------------------------------+\n"
           << "| TRIP ENTRY NO. " << i + 1 << endl;
      entries[i].displayEntry();
    }
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  // TODO: Add functionality to edit entries
  void EditEntry() {
    int choice;
    for (int i = 0; i < entries.size(); i++) {
      cout << "+---------------------------------+\n"
           << "| TRIP ENTRY NO. " << i + 1 << endl
           << "+------------+--------------------+\n"
           << "| Entry Date : " << entries[i].getEntryDate() << endl
           << "+---------------------------------+\n";
    }
    cout << "Which entry would you like to edit? ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (choice >= 1 && choice <= entries.size()) {
      cout << "WORK IN PROGRESS\n";
      cout << "This entry was edited successfully.\n";
    }
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  void DeleteEntry() {
    int choice;
    for (int i = 0; i < entries.size(); i++) {
      cout << "+---------------------------------+\n"
           << "| TRIP ENTRY NO. " << i + 1 << endl
           << "+------------+--------------------+\n"
           << "| Entry Date : " << entries[i].getEntryDate() << endl
           << "+------------+--------------------+\n";
    }
    cout << "Which entry would you like to delete? ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (choice >= 1 && choice <= entries.size()) {
      entries.erase(entries.begin() + choice - 1);
      cout << "This entry was removed successfully.\n";
    }
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  void ManageFuelEntries() {
    if (entries.empty()) {
      cout << "There are no recorded entries yet.\n";
      this_thread::sleep_for(chrono::seconds(1));
      cout << "\nPress Enter to continue...";
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return;
    }
    int choice;
    cout << "+---------------------------------+\n"
         << "| MANAGE ENTRIES                  |\n"
         << "+---------------------------------+\n"
         << "| [1] View All Entries            |\n"
         << "| [2] Edit An Entry               |\n"
         << "| [3] Delete An Entry             |\n"
         << "+---------------------------------+\n"
         << "| [0] Exit                        |\n"
         << "+---------------------------------+\n";
    while (true) {
      cout << "Select Menu Option: ";
      cin >> choice;
      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
      } else {
        break;
      }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
    case 1:
      clrscr();
      ViewAllEntries();
      break;
    case 2:
      clrscr();
      EditEntry();
      break;
    case 3:
      clrscr();
      DeleteEntry();
      break;
    case 0:
      break;
    default:
      cout << "Invalid Menu Option: Select 1-3 or 0 to exit.";
      this_thread::sleep_for(chrono::seconds(2));
    }
  }

  void GenerateReport() {
    if (entries.empty()) {
      cout << "There are no recorded entries yet.\n";
      this_thread::sleep_for(chrono::seconds(1));
      cout << "\nPress Enter to continue...";
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return;
    }

    double totalDistance = 0.0, totalFuelConsumed = 0.0, totalFuelPrice = 0.0,
           totalExpenses = 0.0, fuelEfficiency = 0.0;
    for (int i = 0; i < entries.size(); i++) {
      totalDistance += entries[i].getDistanceDriven();
      totalFuelConsumed += entries[i].getFuelConsumed();
      totalFuelPrice = entries[i].getFuelConsumed() * entries[i].getFuelPrice();
      totalExpenses += totalFuelPrice;
    }

    fuelEfficiency = totalDistance / totalFuelConsumed;

    cout << fixed << setprecision(2);
    cout << "+---------------------------------+\n"
         << "| EFFICIENCY REPORT                \n"
         << "+---------------------+-----------+\n"
         << "| Total Distance      : " << totalDistance << "km\n"
         << "| Total Fuel Consumed : " << totalFuelConsumed << "L\n"
         << "| Fuel Efficiency     : " << fuelEfficiency << "km/L\n"
         << "| Total Expenses      : " << "₱" << totalExpenses << endl
         << "+---------------------+-----------+\n";

    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

private:
  vector<FuelEntry> entries;
};
