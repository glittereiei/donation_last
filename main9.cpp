
//รับค่าชื่อ เบอร์โทร จำนวนเงิน วันที่ที่บริจาค 
//แสดงจำนวนเงินสะสมรวม พอพิมพ์บริจาคเสร็จออกจากโปรแกรมเลย
//อยากให้มีถามอีกรอบว่าแน่ใจมั้ยว่าจะบริจาคเท่านี้ แต่ขกนอย

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
    // Constructor
    Donation(string n, string ph, double amt, string date) {
        name = n;
        phoneNumber = ph;
        amount = amt;
        donationDate = date;
    }

    // Function to save donation details to file
    void saveToFile() {
        ofstream outFile("donations9.txt", ios::app);
        if (outFile.is_open()) {
            outFile << name << "," << phoneNumber << "," << amount << "," << donationDate << endl;
            outFile.close();
        } else {
            cout << "Unable to open file for saving donation." << endl;
        }
    }

    // Static function to calculate total donation amount
    static double getTotalDonation() {
        ifstream inFile("donations9.txt");
        double total = 0.0;
        string line;
        while (getline(inFile, line)) {
            // Split line into tokens
            size_t pos = 0;
            string token;
            int count = 0;
            while ((pos = line.find(",")) != string::npos) {
                token = line.substr(0, pos);
                if (count == 2) {
                    total += stod(token); // Convert string to double and add to total
                }
                line.erase(0, pos + 1);
                count++;
            }
        }
        inFile.close();
        return total;
    }
};

int main() {
    string name, phoneNumber, donationDate;
    double amount;

    //while (true) {
        cout << "Enter donor's name (or type 'quit' to exit): ";
        getline(cin, name);
        // if (name == "quit") {
        //     break;
        // }

        cout << "Enter donor's phone number: ";
        getline(cin, phoneNumber);

        cout << "Enter donation amount: ";
        cin >> amount;
        cin.ignore(); // Ignore newline character
        // Validate amount
        if (amount <= 0) {
            cout << "Invalid donation amount. Please enter a positive value." << endl;
            //continue;
        }

        cout << "Enter donation date (DD-MM-YYYY): ";
        getline(cin, donationDate);

        // Create Donation object
        Donation donation(name, phoneNumber, amount, donationDate);

        // Save donation details to file
        donation.saveToFile();

        cout << "Thank you for your donation!" << endl;
    //}

    // Display total donation amount
    cout << "Total donation amount received: " << Donation::getTotalDonation() << endl;

    //cout << "Program ended. Thank you!" << endl;

    return 0;
}
