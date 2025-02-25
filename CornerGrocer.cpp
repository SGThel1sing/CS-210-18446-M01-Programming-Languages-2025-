#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

// Function to read a file and count the frequency of each item
map<string, int> ReadFile(const string& filename) {
    map<string, int> itemFrequency;
    ifstream inputFile(filename);
    string item;

    if (!inputFile) {
        cerr << "Error: Could not open file " << filename << endl;
        return itemFrequency;
    }

    while (inputFile >> item) {
        itemFrequency[item]++;
    }
    inputFile.close();
    return itemFrequency;
}

// Function to save data to a backup file
void SaveToFile(const map<string, int>& data, const string& filename) {
    ofstream outFile(filename);
    for (const auto& pair : data) {
        outFile << pair.first << " " << pair.second << endl;
    }
    outFile.close();
}

// Function to print a list of all items with their frequency
void PrintItemList(const map<string, int>& data) {
    for (const auto& pair : data) {
        cout << pair.first << " " << pair.second << endl;
    }
}

// Function to print a histogram representation of item frequencies
void PrintHistogram(const map<string, int>& data) {
    for (const auto& pair : data) {
        cout << pair.first << " ";
        for (int i = 0; i < pair.second; i++) {
            cout << "*";
        }
        cout << endl;
    }
}

int main() {
    string inputFile = "CS210_Project_Three_Input_File.txt";
    string backupFile = "frequency.dat";

    // Read data from file and store item frequencies
    map<string, int> itemData = ReadFile(inputFile);
    // Save data to a backup file
    SaveToFile(itemData, backupFile);

    int choice;
    string searchItem;

    do {
        // Display menu options
        cout << "\nMenu:" << endl;
        cout << "1. Search for an item" << endl;
        cout << "2. Display item list" << endl;
        cout << "3. Display histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Select an option: ";

        if (!(cin >> choice)) { // Check if input is valid
            cout << "Error: Invalid input. Please enter a number." << endl;
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue; // Restart loop
        }

        switch (choice) {
        case 1:
            // Search for an item and display its frequency
            cout << "Enter item name: ";
            cin >> searchItem;
            if (itemData.find(searchItem) != itemData.end()) {
                cout << "Item " << searchItem << " was purchased " << itemData[searchItem] << " times." << endl;
            }
            else {
                cout << "Item not found." << endl;
            }
            break;
        case 2:
            // Display all items with their frequencies
            PrintItemList(itemData);
            break;
        case 3:
            // Display histogram representation of item frequencies
            PrintHistogram(itemData);
            break;
        case 4:
            // Exit the program
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Error: Invalid input. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}