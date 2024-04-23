//ok แล้ว อยากเพิ่มวันที่ด้วย

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Donation {
private:
    string name;
    string phoneNumber;
    double amount;

public:
    // Constructor
    Donation(string n, string phone, double amt) : name(n), phoneNumber(phone), amount(amt) {}

    // Save donation to file
    void saveToFile() {
        ofstream file("donations6.txt", ios::app);
        if (file.is_open()) {
            file << name << "," << phoneNumber << "," << amount << endl;
            file.close();
            cout << "Donation saved successfully." << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    // Static method to calculate total donations from file
    static double getTotalDonations() {
        double total = 0.0;
        ifstream file("donations6.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t pos = line.find_last_of(",");
                total += stod(line.substr(pos + 1));
            }
            file.close();
        } else {
            cout << "Unable to open file." << endl;
        }
        return total;
    }
};

int main() {
    string name, phoneNumber;
    double amount;

    cout << "Enter donor's name: ";
    getline(cin, name);
    cout << "Enter donor's phone number: ";
    getline(cin, phoneNumber);
    cout << "Enter donation amount: ";
    cin >> amount;

    Donation donor(name, phoneNumber, amount);
    donor.saveToFile();

    double totalDonations = Donation::getTotalDonations();
    cout << "Total donations received: " << totalDonations << endl;
    cout << "Thank you for your donation!" << endl;

    return 0;
}
