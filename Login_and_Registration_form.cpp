
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


string hashPassword(const string &password) {
    int hash = 0;
    for (char c : password) {
        hash = (hash * 31 + c) % 1000000007;
    }
    return to_string(hash);
}

void registerUser() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username.empty() || password.empty()) {
        cout << "Error: Username and password cannot be empty.\n";
        return;
    }

    ifstream infile("users.txt");
    string u, p;

    while (infile >> u >> p) {
        if (u == username) {
            cout << "Error: Username already exists!\n";
            infile.close();
            return;
        }
    }
    infile.close();

    ofstream outfile("users.txt", ios::app);
    outfile << username << " " << hashPassword(password) << endl;
    outfile.close();

    cout << "Registration successful!\n";
}

void loginUser() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream infile("users.txt");
    if (!infile) {
        cout << "Error: No registered users found.\n";
        return;
    }

    string u, p;
    string hashed = hashPassword(password);

    while (infile >> u >> p) {
        if (u == username) {
            if (p == hashed) {
                cout << "Login successful! Welcome, " << username << "!\n";
            } else {
                cout << "Error: Incorrect password.\n";
            }
            infile.close();
            return;
        }
    }

    infile.close();
    cout << "Error: Username not found.\n";
}

int main() {
    int choice;

    while (true) {
        cout << "\n1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: 
                cout << "Exiting..."; 
                return 0;
            default: 
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
