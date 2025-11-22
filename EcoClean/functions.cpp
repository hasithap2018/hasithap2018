#include <iostream>
#include <string>

using namespace std;

// ===================== HELPER FUNCTIONS =====================

// Function to center text on the screen
void center(const string& text) {
    int width = 80; // Assuming console width is 80
    int len = text.length();
    int padding = (width - len) / 2;

    if (padding < 0) {
        padding = 0;
    }

    // Print spaces for padding
    for(int i = 0; i < padding; i++) {
        cout << " ";
    }
    cout << text << endl;
}

// Clears the input buffer to avoid skipping inputs
void clearInputBuffer() {
    cin.ignore(1000, '\n');
}

// Pauses the program until user presses Enter
void wait() {
    cout << "\n\n\t\t\tPress Enter to continue...";
    // Only ignore if there is something to ignore (e.g. from previous cin >>)
    // But we need to be careful. The safest way for a simple console app
    // that mixes cin >> and getline is to just use getline here.

    // Check if previous input left a newline
    if (cin.peek() == '\n') {
        cin.ignore();
    }

    // Wait for user to press Enter
    cin.get();
}

// Prints a standardized header
void printHeader(string title) {
    // cls() was removed
    center("==================================================");
    center(title);
    center("==================================================");
    cout << "\n";
}

// Gets a valid integer choice from the user
int getChoice() {
    int choice;
    cout << "                              Your choice: "; // Manual spacing
    cin >> choice;

    // Check if input was not a number
    if (cin.fail()) {
        cin.clear(); // Clear error flag
        clearInputBuffer(); // Discard bad input
        return -1; // Return error code
    }
    return choice;
}
