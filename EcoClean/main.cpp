// ECO-CLEAN LAUNDRY SYSTEM - MODULARIZED
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Include modules in specific order
#include "data.cpp"
#include "functions.cpp"
#include "file_handler.cpp"
#include "users.cpp"
#include "customers.cpp"
#include "orders.cpp"
#include "auth.cpp"

int main() {
    // Load data from files at startup
    loadCustomers();
    loadOrders();

    // Perform login
    bool loggedIn = false;
    while(!loggedIn) {
        if(login()) {
            loggedIn = true;
        } else {
            printHeader("Access Denied! Invalid credentials.");
            cout << "\n";
            center("1. Try Again");
            center("2. Exit Program");
            cout << "\n";
            center("--------------------------------------------------");

            int retryChoice = getChoice();
            if(retryChoice == 2) {
                return 0;
            }
        }
    }

    // Main Menu Loop
    while(true) {
        printHeader("ECO - CLEAN LAUNDRY SYSTEM");

        string roleStr;
        if(isAdmin) {
            roleStr = " (ADMIN)";
        } else {
            roleStr = " (EMPLOYEE)";
        }

        center("Logged in as: " + currentUser + roleStr);
        cout << "\n";

        center("1. View Services");
        center("2. Manage Customers");
        center("3. View Customers");
        center("4. Place Order");
        center("5. View Orders");
        center("6. Update Order Status");

        if(isAdmin) {
            center("7. Manage Users");
        }

        // Adjust menu numbers based on role
        if(isAdmin) {
            center("8. Logout");
            center("9. Exit");
        } else {
            center("7. Logout");
            center("8. Exit");
        }

        cout << "\n";
        center("==================================================");

        int choice = getChoice();

        if(choice == 1) {
            viewServices();
        }
        else if(choice == 2) {
            manageCustomers();
        }
        else if(choice == 3) {
            viewCustomers();
        }
        else if(choice == 4) {
            placeOrder();
        }
        else if(choice == 5) {
            viewOrders();
        }
        else if(choice == 6) {
            updateStatus();
        }
        else if(isAdmin && choice == 7) {
            manageUsers();
        }
        else if(choice == (isAdmin ? 8 : 7)) {
            // Logout
            center("Logged out successfully!");
            currentUser = "";
            isAdmin = false;
            wait();

            // Ask for login again
            if(!login()) {
                printHeader("Access Denied!");
                cout << "\n\n\t\t\tPress Enter to exit...";
                cin.get();
                return 0;
            }
        }
        else if(choice == (isAdmin ? 9 : 8)) {
            // Exit
            center("Thank you for using EcoClean! Goodbye!");
            wait();
            return 0;
        }
        else {
            center("Invalid choice! Please try again.");
            wait();
        }
    }
    return 0;
}
