//เพิ่มให้ใส่วันที่ได้แล้ว แต่มันเอาวันที่บวกกันเป็นจำนวนเงิน นอย

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Donation {
private:
    string name;
    string phoneNumber;
    double amount;
    string donationDate;

public:
    Donation(string n, string phone, double amt, string date)
        : name(n), phoneNumber(phone), amount(amt), donationDate(date) {}

    void saveToFile() {
        ofstream outFile("donations7.txt", ios::app);
        if (outFile.is_open()) {
            outFile << name << "," << phoneNumber << "," << amount << "," << donationDate << endl;
            outFile.close();
            cout << "Donation details saved to file." << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    static double getTotalDonations() {
        double total = 0.0;
        ifstream inFile("donations7.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                size_t pos = line.find_last_of(",");
                total += stod(line.substr(pos + 1));
                // double amt = stod(line.substr(pos + 1));
                // total += amt;
            }
            inFile.close();
        } else {
            cout << "Unable to open file." << endl;
        }
        return total;
    }
};

int main() {
    string name, phoneNumber, donationDate;
    double amount;

    char choice;
    do {
        cout << "Enter donor's name: ";
        getline(cin, name);
        cout << "Enter donor's phone number: ";
        getline(cin, phoneNumber);
        cout << "Enter donation amount: ";
        cin >> amount;
        cin.ignore(); // Clear newline character from input buffer
        cout << "Enter donation date (MM/DD/YYYY): ";
        getline(cin, donationDate);

        Donation donation(name, phoneNumber, amount, donationDate);
        donation.saveToFile();

        cout << "Do you want to make another donation? (Y/N): ";
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer
    } while (choice == 'Y' || choice == 'y');

    //cout << "Total donations received: $" << Donation::getTotalDonations() << endl;
    double totalDonations = Donation::getTotalDonations();
    cout << "Total donations received: " << totalDonations << endl;
    cout << "Thank you for your donations!" << endl;

    return 0;
}
