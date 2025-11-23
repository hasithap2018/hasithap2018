#include <iostream>
#include <string>

using namespace std;

// ===================== LOGIN SYSTEM =====================

// Function to handle user login
bool login() {
    // Load users from file first
    loadUsers();

    printHeader("ECO-CLEAN LAUNDRY SYSTEM - LOGIN");

    string inputUsername;
    string inputPassword;

    cout << "\n\n";
    cout << string(30,' ') << "Username: ";
    cin >> inputUsername;

    cout << string(30,' ') << "Password: ";
    cin >> inputPassword;

    // Check credentials against loaded users
    for(int i = 0; i < userCnt; i++) {
        if(users[i].username == inputUsername && users[i].password == inputPassword) {
            // Login successful
            currentUser = users[i].username;
            isAdmin = users[i].isAdmin;

            // cls() removed as requested
            center("Welcome, " + currentUser + "!");
            wait();
            return true;
        }
    }

    return false; // No match found
}
