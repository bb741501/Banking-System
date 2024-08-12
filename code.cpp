// bank_system.cpp
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class User {
private:
    string username;
    string password;
    double balance;

public:
    // Constructor
    User(string user, string pass, double bal) : username(user), password(pass), balance(bal) {}

    // Getter methods
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    double getBalance() const { return balance; }

    // Methods to modify balance
    void deposit(double amount) { balance += amount; }
    bool withdraw(double amount) {
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        return true;
    }
};

class Bank {
private:
    unordered_map<string, User> users;

public:
    // Method to add a new user
    bool addUser(const string& username, const string& password, double initialBalance) {
        if (users.find(username) != users.end()) {
            return false; // User already exists
        }
        users.emplace(username, User(username, password, initialBalance));
        return true;
    }

    // Method to authenticate a user
    User* authenticate(const string& username, const string& password) {
        auto it = users.find(username);
        if (it != users.end() && it->second.getPassword() == password) {
            return &it->second;
        }
        return nullptr;
    }

    // Method to transfer money from one user to another
    bool transfer(User* fromUser, const string& toUsername, double amount) {
        if (!fromUser) return false;

        auto it = users.find(toUsername);
        if (it == users.end()) return false;

        User* toUser = &it->second;
        if (fromUser->withdraw(amount)) {
            toUser->deposit(amount);
            return true;
        }
        return false;
    }

    // Method to get the balance of a user
    double getBalance(User* user) {
        if (user) return user->getBalance();
        return -1; // Error code
    }
};

// Example main function to show how it could be used (for testing only)
int main() {
    Bank bank;
    bank.addUser("user1", "pass1", 1000.0);
    bank.addUser("user2", "pass2", 500.0);

    User* user = bank.authenticate("user1", "pass1");
    if (user) {
        cout << "User authenticated. Balance: $" << bank.getBalance(user) << endl;
        if (bank.transfer(user, "user2", 200.0)) {
            cout << "Transferred $200 to user2. New balance: $" << bank.getBalance(user) << endl;
        } else {
            cout << "Transfer failed!" << endl;
        }
    } else {
        cout << "Authentication failed!" << endl;
    }

    return 0;
}
