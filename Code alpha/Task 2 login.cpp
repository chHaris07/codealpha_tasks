#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

bool usernameExists(const string& username) {
    string filename = username + ".txt";
    ifstream file(filename);
    bool exists = file.is_open();
    if (exists) {
        file.close();
    }
    return exists;
}

void registerUser() {
    string username, password;

    cout << "\n--- User Registration ---" << endl;
    cout << "Enter desired username: ";
    cin >> username;

    if (username.find(' ') != string::npos) {
        cout << "Username cannot contain spaces. Please try again." << endl;
        return;
    }

    if (usernameExists(username)) {
        cout << "Username '" << username << "' already exists. Please choose another." << endl;
        return;
    }

    cout << "Enter desired password: ";
    cin >> password;

    if (password.length() < 5) {
        cout << "Password must be at least 5 characters long. Please try again." << endl;
        return;
    }
    if (password.find(' ') != string::npos) {
        cout << "Password cannot contain spaces. Please try again." << endl;
        return;
    }

    string filename = username + ".txt";
    ofstream file(filename);

    if (file.is_open()) {
        file << username << endl;
        file << password << endl;
        file.close();
        cout << "Registration successful for user: " << username << endl;
    } else {
        cout << "Error: Could not create user file. Registration failed." << endl;
    }
}

void loginUser() {
    string username, password;

    cout << "\n--- User Login ---" << endl;
    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    if (!usernameExists(username)) {
        cout << "Login failed: Username '" << username << "' not found." << endl;
        return;
    }

    string filename = username + ".txt";
    ifstream file(filename);

    if (file.is_open()) {
        string storedUsername, storedPassword;
        getline(file, storedUsername);
        getline(file, storedPassword);
        file.close();

        if (username == storedUsername && password == storedPassword) {
            cout << "Login successful! Welcome, " << username << "!" << endl;
        } else {
            cout << "Login failed: Incorrect password." << endl;
        }
    } else {
        cout << "Error: Could not open user file. Login failed." << endl;
    }
}

int main() {
    cout << "------------------------------------------" << endl;
    cout << "    Login and Registration System         " << endl;
    cout << "------------------------------------------" << endl;

    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        while (cin.fail() || (choice < 1 || choice > 3)) {
            cout << "Invalid input. Please enter 1, 2, or 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    cout << "\nLogin and Registration System task completed." << endl;

    return 0;
}
