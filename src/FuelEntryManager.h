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

class FuelEntry {
public:
  // Constructor
  FuelEntry(const string &entryDate, const double distance, const double amount,
            const double price)
      : date(entryDate), distanceDriven(distance), fuelConsumed(amount),
        fuelPrice(price) {}

  // Getters to return the specific value of a variable.
  string getEntryDate() const { return date; }
  double getDistanceDriven() const { return distanceDriven; }
  double getFuelConsumed() const { return fuelConsumed; }
  double getFuelPrice() const { return fuelPrice; }

  // Setters to set a specific value to a variable.
  void setEntryDate(const string &date) { this->date = date; }
  void setDistanceDriven(const double distanceDriven) {
    this->distanceDriven = distanceDriven;
  }
  void setFuelConsumed(const double fuelConsumed) {
    this->fuelConsumed = fuelConsumed;
  }
  void setFuelPrice(const double fuelPrice) { this->fuelPrice = fuelPrice; }

  // Function to display fuel entry.
  void displayEntry() {
    cout << fixed << setprecision(2);
    cout << "├───┬─────────────────┬───────────\n"
         << "│  │ Entry Date      │ " << date << endl
         << "│ 󰑢 │ Distance Driven │ " << distanceDriven << "km\n"
         << "│ 󰟊 │ Fuel Consumed   │ " << fuelConsumed << "L\n"
         << "│  │ Fuel Cost       │ " << "₱" << fuelPrice << endl
         << "╰───┴─────────────────┴───────────\n";
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

    // Input and validate date string.
    while (true) {
      const regex dateFormat(
          R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$)");
      cout << "Enter entry date (YYYY-MM-DD): ";
      getline(cin, date);
      if (!regex_match(date, dateFormat)) {
        cout << "Invalid format: Enter a valid date with YYYY-MM-DD format.\n";
        this_thread::sleep_for(chrono::seconds(1));
        continue;
      } else {
        break;
      }
    }

    // Input and validate distance driven.
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

    // Input and validate fuel consumed.
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

    // Input and validate fuel price.
    while (true) {
      cout << "Enter cost per liter (₱/L): ";
      cin >> fuelPrice;
      if (cin.fail() || fuelPrice < 1) {
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

    // Return these values to the FuelEntry class.
    entries.emplace_back(date, distanceDriven, fuelConsumed, fuelPrice);

    clrscr();
    cout << "Trip entry was recorded successfully!\n";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  void ViewAllEntries() {
    for (int i = 0; i < entries.size(); i++) {
      cout << "╭─────────────────────────────────\n"
           << "│ 󰈙 TRIP ENTRY NO. " << i + 1 << endl;
      entries[i].displayEntry();
    }
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  void EditEntry() {
    string date;
    double distanceDriven, fuelConsumed, fuelPrice;
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
      FuelEntry &entry = entries[choice - 1];

      // Input and validate date string.
      while (true) {
        const regex dateFormat(
            R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$)");
        cout << "Current: " << entry.getEntryDate() << endl;
        cout << "Enter entry date (YYYY-MM-DD): ";
        getline(cin, date);
        if (!regex_match(date, dateFormat)) {
          cout
              << "Invalid format: Enter a valid date with YYYY-MM-DD format.\n";
          this_thread::sleep_for(chrono::seconds(1));
          continue;
        } else {
          break;
        }
      }

      // Input and validate distance driven.
      while (true) {
        cout << "Current: " << entry.getDistanceDriven() << endl;
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

      // Input and validate fuel consumed.
      while (true) {
        cout << "Current: " << entry.getFuelConsumed() << endl;
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

      // Input and validate fuel price.
      while (true) {
        cout << "Current: " << entry.getFuelPrice() << endl;
        cout << "Enter cost per liter (₱/L): ";
        cin >> fuelPrice;
        if (cin.fail() || fuelPrice < 1) {
          cout << "Invalid input: Enter a valid number above zero.\n";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          this_thread::sleep_for(chrono::seconds(1));
          continue;
        } else {
          break;
        }
      }

      // Set the new values for the specified entry earlier.
      entry.setEntryDate(date);
      entry.setDistanceDriven(distanceDriven);
      entry.setFuelConsumed(fuelConsumed);
      entry.setFuelPrice(fuelPrice);

      cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    // Returns user to the main menu if there are no recorded entries.
    if (entries.empty()) {
      cout << "There are no recorded entries yet.\n";
      this_thread::sleep_for(chrono::seconds(1));
      cout << "\nPress Enter to continue...";
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return;
    }

    int choice;
    while (true) {
      clrscr();
      cout << "╭────────────────────────────────╮\n"
           << "│  󰁨  MANAGE ENTRIES             │\n"
           << "├────────────────────────────────┤\n"
           << "│ [1] 󰈈 View Entries             │\n"
           << "│ [2] 󰷈 Edit Entry               │\n"
           << "│ [3] 󰩹 Delete Entry             │\n"
           << "├────────────────────────────────┤\n"
           << "│ [0] 󰈆 Return                   │\n"
           << "╰────────────────────────────────╯\n";
      cout << "Select Menu Option: ";
      cin >> choice;
      if (cin.fail() || choice > 3) {
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
    // Returns user to the main menu if there are no recorded entries.
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
