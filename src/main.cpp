#include "FuelEntryManager.h"

class FuelTracker {
public:
  void displayMenu() {
    cout << "+---------------------------------+\n"
         << "| VEHICLE FUEL EFFICIENCY TRACKER |\n"
         << "+---------------------------------+\n"
         << "| [1] Add Fuel Entry              |\n"
         << "| [2] Manage Entries              |\n"
         << "| [3] Generate Report             |\n"
         << "+---------------------------------+\n"
         << "| [0] Exit Program                |\n"
         << "+---------------------------------+\n";
  }

  void run() {

    int choice;
    do {
      system("clear");
      displayMenu();
      cout << "Select Menu Option: ";
      cin >> choice;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      switch (choice) {
      case 0:
        cout << "Exiting Program.\n";
        break;
      case 1:
        system("clear");
        fuelEntryMgr.AddFuelEntry();
        break;
      case 2:
        system("clear");
        fuelEntryMgr.ManageFuelEntries();
        break;
      case 3:
        system("clear");
        fuelEntryMgr.GenerateReport();
        break;
      default:
        system("clear");
        cout << "Invalid Option: Select 1-3 or 0 to exit.\n";
        this_thread::sleep_for(chrono::seconds(2));
        break;
      }

    } while (choice != 0);
  }

private:
  FuelEntryManager fuelEntryMgr;
};

int main(int argc, char *argv[]) {

  system("clear");
  FuelTracker fueltracker;
  fueltracker.run();

  return 0;
}
