#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Donation {
public:
    string name;
    string phoneNumber;
    int amount;
    Donation* next;

    // Constructor
    Donation(string n, string phone, int amt) {
        name = n;
        phoneNumber = phone;
        amount = amt;
        next = nullptr;
    }
};

class DonationList {
private:
    Donation* head;
    int totalDonations;

public:
    // Constructor
    DonationList() {
        head = nullptr;
        totalDonations = 0;
    }

    void addDonation(string name, string phone, int amount) {
        Donation* newDonation = new Donation(name, phone, amount);

        if (head == nullptr) {
            head = newDonation;
        } else {
            Donation* current = head;
            //เชคเบอร์โทร
            while (current->next != nullptr) {
                if (current->phoneNumber == phone) {
                    //เบอร์เดียวกันบวก?
                    current->amount += amount;
                    delete newDonation;
                    return;
                }
                current = current->next;
            }
            current->next = newDonation;
        }
        totalDonations += amount;
    }

    void displayDonations() {
        Donation* current = head;
        while (current != nullptr) {
            cout << "Name: " << current->name << ", Phone: " << current->phoneNumber << ", Amount: " << current->amount << endl;
            current = current->next;
        }
        cout << "Total Donations: " << totalDonations << endl;
    }

    void saveToFile(string filename) {
        ofstream outFile(filename);

        if (!outFile) {
            cerr << "Cannot open the file: " << filename << endl;
            return;
        }

        Donation* current = head;
        while (current != nullptr) {
            outFile << current->name << "," << current->phoneNumber << "," << current->amount << endl;
            current = current->next;
        }

        outFile.close();
    }
};

int main() {
    DonationList donations;

    string name, phone;
    int amount;
    char choice;
    do {
        cout << "Enter donor's name: ";
        cin >> name;
        cout << "Enter donor's phone number: ";
        cin >> phone;
        cout << "Enter donation amount: ";
        cin >> amount;

        donations.addDonation(name, phone, amount);

        cout << "Do you want to add another donation? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "All Donations: " << endl;
    donations.displayDonations();

    donations.saveToFile("donations3.txt");

    return 0;
}
