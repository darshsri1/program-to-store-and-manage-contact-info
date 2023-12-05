#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<limits>
#include<algorithm>
using namespace std;

struct Contact {
    string name;
    string phoneNumber;
    string emailAddress;
};

// Trim function to remove leading and trailing whitespaces
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
        return str;

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Function to add a new contact
void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Enter Name: ";
    getline(cin >> ws, newContact.name);
    cout << "Enter Phone Number: ";
    getline(cin, newContact.phoneNumber);
    cout << "Enter Email Address: ";
    getline(cin, newContact.emailAddress);

    contacts.push_back(newContact);
    cout << "Contact added successfully!" << endl;
}

// Function to view all contacts
void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts found." << endl;
    } else {
        cout << "Contacts:" << endl;
        for (const auto& contact : contacts) {
            cout << "Name: " << contact.name << "\tPhone: " << contact.phoneNumber << "\tEmail: " << contact.emailAddress << endl;
        }
    }
}

// Function to edit an existing contact
void editContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts found." << endl;
        return;
    }

    cout << "Enter the name of the contact to edit: ";
    string targetName;
    getline(cin >> ws, targetName);

    for (auto& contact : contacts) {
        if (contact.name == targetName) {
            cout << "Enter new phone number: ";
            getline(cin, contact.phoneNumber);
            cout << "Enter new email address: ";
            getline(cin, contact.emailAddress);
            cout << "Contact edited successfully!" << endl;
            return;
        }
    }

    cout << "Contact not found." << endl;
}

// Function to delete an existing contact
void deleteContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts found." << endl;
        return;
    }

    cout << "Enter the name of the contact to delete: ";
    string targetName;
    getline(cin >> ws, targetName);

    auto it = std::remove_if(contacts.begin(), contacts.end(),
                             [targetName](const Contact& contact) {
                                 return contact.name == targetName;
                             });

    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        cout << "Contact deleted successfully!" << endl;
    } else {
        cout << "Contact not found." << endl;
    }
}

// Function to save contacts to a file
void saveContactsToFile(const vector<Contact>& contacts, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& contact : contacts) {
            file << contact.name << "," << contact.phoneNumber << "," << contact.emailAddress << "\n";
        }
        cout << "Contacts saved to file successfully!" << endl;
    } else {
        cout << "Error opening file for saving contacts." << endl;
    }
}

// Function to load contacts from a file
void loadContactsFromFile(vector<Contact>& contacts, const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        contacts.clear();

        string line;
        while (getline(file, line)) {
            size_t comma1 = line.find(',');
            size_t comma2 = line.find(',', comma1 + 1);

            Contact loadedContact;
            loadedContact.name = trim(line.substr(0, comma1));
            loadedContact.phoneNumber = trim(line.substr(comma1 + 1, comma2 - comma1 - 1));
            loadedContact.emailAddress = trim(line.substr(comma2 + 1));

            contacts.push_back(loadedContact);
        }

        cout << "Contacts loaded from file successfully!" << endl;
    } else {
        cout << "Error opening file for loading contacts." << endl;
    }
}

int main() {
    vector<Contact> contacts;
    const string filename = "contacts.txt"; // Change the filename as needed

    int choice;
    do {
        cout << "\nContact Management Program\n";
        cout << "1. Add a new contact\n";
        cout << "2. View contacts\n";
        cout << "3. Edit a contact\n";
        cout << "4. Delete a contact\n";
        cout << "5. Save contacts to file\n";
        cout << "6. Load contacts from file\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        // Input validation
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number: ";
        }

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts(contacts);
                break;
            case 3:
                editContact(contacts);
                break;
            case 4:
                deleteContact(contacts);
                break;
            case 5:
                saveContactsToFile(contacts, filename);
                break;
            case 6:
                loadContactsFromFile(contacts, filename);
                break;
            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
