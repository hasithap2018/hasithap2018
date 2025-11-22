#include <iostream>
#include <string>

using namespace std;

// --- CONSTANTS ---
const int MAX_CUST = 100;
const int MAX_ORD = 500;
const int MAX_USERS = 20;
const string CUST_FILE = "customers.txt";
const string ORD_FILE = "orders.txt";
const string USER_FILE = "users.txt";

// --- STRUCTURES ---
struct Customer {
    int id;
    string name;
    string phone;
    string address;
};

struct Order {
    int id;
    int custId;
    int service;
    string custName;
    string status;
    string date;
    double kg;
    double amount;
};

struct User {
    string username;
    string password;
    bool isAdmin;
};

struct Service {
    int code;
    string name;
    double price;
};

// --- EXTERN GLOBALS ---
extern Customer cust[MAX_CUST];
extern Order ord[MAX_ORD];
extern User users[MAX_USERS];
extern Service services[4];

extern int custCnt;
extern int ordCnt;
extern int userCnt;

extern int nextCustId;
extern int nextOrdId;

extern string currentUser;
extern bool isAdmin;

// --- FUNCTION PROTOTYPES ---
void printHeader(string title);
void center(const string& text);
void wait();
int getChoice();
void saveUsers();

// ===================== USER SYSTEM =====================

// Function to find a user by username
int findUser(const string& username) {
    for(int i = 0; i < userCnt; i++) {
        if(users[i].username == username) {
            return i; // Found the user, return index
        }
    }
    return -1; // User not found
}

// Function to display all registered users
void viewAllUsers() {
    printHeader("ALL USER ACCOUNTS");

    if(userCnt == 0) {
        center("No users found in the system.");
    } else {
        center("USERNAME             ROLE");
        center("---------------------------------------");

        for(int i = 0; i < userCnt; i++) {
            string role;
            if (users[i].isAdmin) {
                role = "ADMIN";
            } else {
                role = "EMPLOYEE";
            }

            string line = users[i].username;
            // Add padding for alignment (Username column width = 20)
            while(line.length() < 20) {
                line += " ";
            }

            // Add Role and pad to fixed width to ensure perfect centering
            // "ADMIN" is 5 chars, "EMPLOYEE" is 8 chars. Max is 8.
            // We want the row to be constant length.
            // Let's make the Role column 10 chars wide.
            string roleStr = role;
            while(roleStr.length() < 10) {
                roleStr += " ";
            }

            line += " " + roleStr;
            center(line);
        }
    }
    cout << "\n";
    center("Total Users: " + to_string(userCnt));
    wait();
}

// Function to manage users (Admin only)
void manageUsers() {
    // Security check
    if(!isAdmin) {
        printHeader("Access Denied!");
        center("Only administrators can access this menu.");
        wait();
        return;
    }

    while(true) {
        printHeader("MANAGE USERS (ADMIN ONLY)");
        center("1. Add New User");
        center("2. Change Password");
        center("3. Delete User");
        center("4. View All Users");
        center("5. Back");
        cout << "\n";
        center("--------------------------------------------------");

        int choice = getChoice();

        if(choice == 1) {
            // Add User
            if(userCnt >= MAX_USERS) {
                center("Error: Maximum number of users reached!");
                wait();
                continue;
            }

            string newUsername, newPassword;
            int isAdminChoice;

            printHeader("ADD USER");
            cout << string(25,' ') << "Username: ";
            cin >> newUsername;

            if(findUser(newUsername) != -1) {
                center("Error: Username already exists!");
                wait();
                continue;
            }

            cout << string(25,' ') << "Password: ";
            cin >> newPassword;
            cout << string(25,' ') << "Admin? (1=Yes, 0=No): ";
            cin >> isAdminChoice;

            // Add to array
            users[userCnt].username = newUsername;
            users[userCnt].password = newPassword;
            if (isAdminChoice == 1) {
                users[userCnt].isAdmin = true;
            } else {
                users[userCnt].isAdmin = false;
            }
            userCnt++;

            saveUsers();
            center("User added successfully!");
            wait();
        }
        else if(choice == 2) {
            // Change Password
            printHeader("CHANGE PASSWORD");
            string targetUser;
            cout << string(25,' ') << "Username: ";
            cin >> targetUser;

            int index = findUser(targetUser);
            if(index == -1) {
                center("User not found!");
                wait();
                continue;
            }

            cout << string(25,' ') << "New password: ";
            string newPass;
            cin >> newPass;

            users[index].password = newPass;
            saveUsers();
            center("Password changed successfully!");
            wait();
        }
        else if(choice == 3) {
            // Delete User
            printHeader("DELETE USER");
            string targetUser;
            cout << string(25,' ') << "Delete username: ";
            cin >> targetUser;

            // Prevent deleting self or the main admin
            if(targetUser == currentUser || targetUser == "admin") {
                center("Error: Cannot delete this user!");
                wait();
                continue;
            }

            int index = findUser(targetUser);
            if(index == -1) {
                center("User not found!");
                wait();
                continue;
            }

            // Shift array to remove user
            for(int j = index; j < userCnt - 1; j++) {
                users[j] = users[j+1];
            }
            userCnt--;

            saveUsers();
            center("User deleted successfully!");
            wait();
        }
        else if(choice == 4) {
            viewAllUsers();
        }
        else if(choice == 5) {
            return;
        }
        else {
            center("Invalid choice! Please try again.");
            wait();
        }
    }
}
