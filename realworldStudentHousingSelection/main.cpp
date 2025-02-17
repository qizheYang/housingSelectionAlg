#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Home.h"

using namespace std;

unordered_map<string, Home> homes;  // Hash table storing homes by name
vector<pair<int, Home> > rankedHomes; // Vector for sorting homes by score
string filename;  // CSV file location

// Function to check if a file exists
bool fileExists(const string& path) {
    ifstream file(path);
    return file.good();
}

// Function to rank homes based on score
void rankHomes() {
    rankedHomes.clear();
    for (auto& pair : homes) {
        int score = pair.second.calculateFactors();
        rankedHomes.emplace_back(score, pair.second);
    }

    // Sort homes by descending score
    sort(rankedHomes.begin(), rankedHomes.end(), [](const pair<int, Home>& a, const pair<int, Home>& b) {
        return a.first > b.first;
    });
}

// Function to save homes to a CSV file
void saveHomesToCSV() {
    ofstream file(filename);
    if (!file) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }

    // Write CSV header
    file << "Rank,Score,Name,OwnerRating,HouseType,RoomType,Location,WalkingTime,Price,CheckinTimeFlex,Furnished,HaveGate,HaveSecurity,Utilities,Bath,SizeOfBedroom,PrivateWasherDryer,AdditionalFactors,DPS\n";

    // Rank and save homes
    rankHomes();
    int rank = 1;
    for (const auto& entry : rankedHomes) {
        const Home& home = entry.second;
        int score = entry.first;

        file << rank << "," << score << ","
             << home.getName() << "," << home.getOwnerRating() << ","
             << home.getHouseType() << "," << home.getRoomType() << ","
             << home.getLocation() << "," << home.getWalkingTimeToTaperHall() << ","
             << home.getPrice() << "," << home.isCheckinTimeFlexible() << ","
             << home.isFurnished() << "," << home.hasGate() << ","
             << home.hasSecurity() << "," << home.includesUtilities() << ","
             << home.hasBath() << "," << home.getSizeOfBedroom() << ","
             << home.hasPrivateWasherDryer() << "," << home.getAdditionalFactors() << ","
             << home.inDps() << "\n";

        rank++;
    }

    file.close();
    cout << "Homes saved to " << filename << " successfully.\n";
}

// Function to load homes from a CSV file
void loadHomesFromCSV() {
    if (!fileExists(filename)) {
        ofstream newFile(filename);
        newFile << "";  // Create empty file
        newFile.close();
        cout << "No existing file found. Created new file: " << filename << "\n";
        return;
    }

    ifstream file(filename);
    if (!file) {
        cout << "Error: Could not open file for reading.\n";
        return;
    }

    string line;
    getline(file, line);  // Skip header line

    while (getline(file, line)) {
        stringstream ss(line);
        string name, roomType, location;
        int rank, score, ownerRating, houseType, walkingTime, price, sizeOfBedroom, additionalFactors;
        bool checkinTimeFlex, furnished, haveGate, haveSecurity, utilities, bath, privateWasherDryer, dps;

        // Parse CSV row
        ss >> rank; ss.ignore();
        ss >> score; ss.ignore();
        getline(ss, name, ',');
        ss >> ownerRating; ss.ignore();
        ss >> houseType; ss.ignore();
        getline(ss, roomType, ',');
        getline(ss, location, ',');
        ss >> walkingTime; ss.ignore();
        ss >> price; ss.ignore();
        ss >> checkinTimeFlex; ss.ignore();
        ss >> furnished; ss.ignore();
        ss >> haveGate; ss.ignore();
        ss >> haveSecurity; ss.ignore();
        ss >> utilities; ss.ignore();
        ss >> bath; ss.ignore();
        ss >> sizeOfBedroom; ss.ignore();
        ss >> privateWasherDryer; ss.ignore();
        ss >> additionalFactors; ss.ignore();
        ss >> dps;

        Home home(name, ownerRating, houseType, roomType, location, walkingTime, price,
                  checkinTimeFlex, furnished, haveGate, haveSecurity, utilities, bath,
                  sizeOfBedroom, privateWasherDryer, additionalFactors, dps);

        homes[name] = home;
    }

    file.close();
}

// Function to add a new home
void addNewHome() {
    string name, roomType, location;
    int ownerRating, houseType, time, price, sizeOfBedroom, additionalFactors;
    bool checkinTimeFlex, furnished, haveGate, haveSecurity, utilities, bath, privateWasherDryer, dps;

    cout << "Enter home name: ";
    getline(cin, name);

    if (homes.find(name) != homes.end()) {
        cout << "Error: A home with this name already exists!\n";
        return;
    }

    cout << "Enter owner rating (0-10): ";
    cin >> ownerRating;

    cout << "Enter house type (0=Apartment, 1=Townhouse, 2=Villa): ";
    cin >> houseType;
    cin.ignore();  // Ignore newline for getline

    cout << "Enter room type: ";
    getline(cin, roomType);

    cout << "Enter location: ";
    getline(cin, location);

    cout << "Enter walking time to Taper Hall (minutes): ";
    cin >> time;

    cout << "Enter price: ";
    cin >> price;

    cout << "Is check-in time flexible? (1 for Yes, 0 for No): ";
    cin >> checkinTimeFlex;

    cout << "Is the home furnished? (1 for Yes, 0 for No): ";
    cin >> furnished;

    cout << "Does the home have a gate? (1 for Yes, 0 for No): ";
    cin >> haveGate;

    cout << "Does the home have security? (1 for Yes, 0 for No): ";
    cin >> haveSecurity;

    cout << "Are water, electricity, and internet included? (1 for Yes, 0 for No): ";
    cin >> utilities;

    cout << "Does the home have a private bathroom? (1 for Yes, 0 for No): ";
    cin >> bath;

    cout << "Enter the size of the bedroom (sqft): ";
    cin >> sizeOfBedroom;

    cout << "Does the home have a private washer/dryer? (1 for Yes, 0 for No): ";
    cin >> privateWasherDryer;

    cout << "Enter additional factors (positive or negative): ";
    cin >> additionalFactors;

    cout << "Is it inside of DPS: ";
    cin >> dps;

    homes[name] = Home(name, ownerRating, houseType, roomType, location, time, price,
                       checkinTimeFlex, furnished, haveGate, haveSecurity, utilities, bath,
                       sizeOfBedroom, privateWasherDryer, additionalFactors, dps);

    cout << "Home added successfully!\n";
}

int main() {
    cout << "Enter CSV file location (e.g., homes.csv): ";
    getline(cin, filename);

    loadHomesFromCSV();

    while (true) {
        cout << "\n----- Student Housing Selection -----\n";
        cout << "1. Add a new home\n";
        cout << "2. View stored homes\n";
        cout << "3. Save and Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();  // Prevent issues with getline

        if (choice == 1) {
            addNewHome();
        } else if (choice == 2) {
            rankHomes();
            for (size_t i = 0; i < rankedHomes.size(); ++i) {
                std::string type;
                if (rankedHomes[i].second.getHouseType() == 0) {
                    type = "Studio";
                } else {
                    type = "1B1B";
                }
                cout << (i + 1) << ". " << rankedHomes[i].second.getName() << " | Room type: " << type << " | House type: " << rankedHomes[i].second.getRoomType() << " | Score: " << rankedHomes[i].first << " | Price: " << rankedHomes[i].second.getPrice() << "\n";
            }
        } else if (choice == 3) {
            saveHomesToCSV();
            cout << "Homes saved. Exiting...\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}