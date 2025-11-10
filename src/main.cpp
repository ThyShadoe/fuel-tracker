#include "FuelEntryManager.h"
#include <cstdlib>

class FuelTrackerMain {
public:
  void displayMenu() {
    cout << "+---------------------------------+\n"
         << "| VEHICLE FUEL EFFICIENCY TRACKER |\n"
         << "|---------------------------------|\n"
         << "| [1] Enter Fuel Entry            |\n"
         << "| [2] Remove Fuel Entry           |\n"
         << "| [3] Generate Report             |\n"
         << "| [4] Calculate Fuel Efficiency   |\n"
         << "| [5] Configure Settings          |\n"
         << "|---------------------------------|\n"
         << "| [0] Exit Program                |\n"
         << "+---------------------------------+\n";
  }

  void run() {
    int choice;

    do {
      system("clear");
      displayMenu();
      cout << "Select Menu Option (0-5): ";
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
        fuelEntryMgr.RemoveFuelEntry();
        break;
      case 3:
        system("clear");
        fuelEntryMgr.GenerateReport();
        break;
      case 4:
        system("clear");
        fuelEntryMgr.CalculateEfficiency();
        break;
      case 5:
        system("clear");
        fuelEntryMgr.ConfigureSettings();
        break;
      default:
        system("clear");
        cout << "Invalid Option: Select 0-5.\n";
        this_thread::sleep_for(chrono::seconds(2));
        break;
      }

    } while (choice != 0);
  }

private:
  FuelEntryManager fuelEntryMgr;
};

int main(int argc, char *argv[]) {

  // clears the console before starting the function
  system("clear");
  FuelTrackerMain main;
  main.run();

  return 0;
}
