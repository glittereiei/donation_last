#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Donation {
public:
    string name;
    string phoneNumber;
    double amount;
    Donation* next;

    Donation(string n, string phone, double amt) : name(n), phoneNumber(phone), amount(amt), next(nullptr) {}
};

class DonationList {
private:
    Donation* head;
public:
    DonationList() : head(nullptr) {}

    void addDonation(string name, string phoneNumber, double amount) {
        if (head == nullptr) {
            head = new Donation(name, phoneNumber, amount);
            return;
        }

        Donation* current = head;
        while (current != nullptr) {
            if (current->phoneNumber == phoneNumber) {
                current->amount += amount;
                return;
            }
            if (current->next == nullptr)
                break;
            current = current->next;
        }

        current->next = new Donation(name, phoneNumber, amount);
    }

    double getTotalDonationAmount() {
        double totalAmount = 0.0;
        Donation* current = head;
        while (current != nullptr) {
            totalAmount += current->amount;
            current = current->next;
        }
        return totalAmount;
    }

    void saveToFile() {
        ofstream file("donations4.txt", ios::app);
        if (!file) {
            cout << "Error: Unable to open file!" << endl;
            return;
        }

        Donation* current = head;
        while (current != nullptr) {
            file << current->name << "," << current->phoneNumber << "," << current->amount << endl;
            current = current->next;
        }

        file.close();
    }

    ~DonationList() {
        Donation* current = head;
        while (current != nullptr) {
            Donation* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    DonationList donationList;

    string name, phoneNumber;
    double amount;

    char choice;
    do {
        cout << "Enter donor's name: ";
        cin >> name;
        cout << "Enter donor's phone number: ";
        cin >> phoneNumber;
        cout << "Enter donation amount: ";
        cin >> amount;

        donationList.addDonation(name, phoneNumber, amount);

        cout << "Do you want to add another donation? (Y/N): ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    donationList.saveToFile();

    double totalDonation = donationList.getTotalDonationAmount();
    cout << "Total donation amount: " << totalDonation << endl;

    return 0;
}
