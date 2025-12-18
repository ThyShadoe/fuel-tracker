#include "FuelEntryManager.h"

void clrscr() {
#ifdef _WIN32
  COORD tl = {0, 0};
  CONSOLE_SCREEN_BUFFER_INFO s;
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(console, &s);
  DWORD written, cells = s.dwSize.X * s.dwSize.Y;
  FillConsoleOutputCharacter(console, ' ', cells, tl, &written);
  FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
  SetConsoleCursorPosition(console, tl);
#else
  cout << "\033[2J\033[H" << flush;
#endif
}

class FuelTracker {
public:
  void displayMenu() {
    cout << "╭────────────────────────────────╮\n"
         << "│    FUEL EFFICIENCY TRACKER    │\n"
         << "├────────────────────────────────┤\n"
         << "│ [1]  Record Entry             │\n"
         << "│ [2] 󰁨 Manage Entries           │\n"
         << "│ [3] 󰈙 View Report              │\n"
         << "│ [4]  Settings                 │\n"
         << "├────────────────────────────────┤\n"
         << "│ [0] 󰈆 Exit Program             │\n"
         << "╰────────────────────────────────╯\n";
  }

  void run() {

    const int MAX_CHOICE = 4;
    int choice;
    do {
      while (true) {
        clrscr();
        displayMenu();
        cout << "Select Menu Option: ";
        cin >> choice;
        if (cin.fail() || choice > MAX_CHOICE) {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          continue;
        } else {
          break;
        }
      }
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      switch (choice) {
      case 0:
        cout << "Exiting Program.\n";
        break;
      case 1:
        clrscr();
        fuelEntryMgr.AddFuelEntry();
        break;
      case 2:
        clrscr();
        fuelEntryMgr.ManageFuelEntries();
        break;
      case 3:
        clrscr();
        fuelEntryMgr.GenerateReport();
        break;
      }

    } while (choice != 0);
  }

private:
  FuelEntryManager fuelEntryMgr;
};

int main(int argc, char *argv[]) {

  clrscr();
  FuelTracker fueltracker;
  fueltracker.run();

  return 0;
}
