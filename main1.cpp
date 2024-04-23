#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// สร้างโครงสร้างข้อมูลสำหรับเก็บข้อมูลการบริจาค
struct DonationRecord {
    string name;
    string phoneNumber;
    int amount;
};

// สร้างคลาสสำหรับการบันทึกและแสดงข้อมูลการบริจาค
class DonationTracker {
private:
    static const int MAX_RECORDS = 100; // กำหนดขนาดสูงสุดของอาร์เรย์
    DonationRecord records[MAX_RECORDS]; // เก็บข้อมูลการบริจาค
    int numRecords = 0; // เก็บจำนวนข้อมูลการบริจาคที่มีอยู่

public:
    // เมธอดสำหรับบันทึกข้อมูลการบริจาค
    void recordDonation(const string& name, const string& phoneNumber, int amount) {
        bool found = false;
        // ตรวจสอบเบอร์โทรซ้ำ
        for (int i = 0; i < numRecords; ++i) {
            if (records[i].phoneNumber == phoneNumber) {
                records[i].amount += amount;
                found = true;
                break;
            }
        }
        // ถ้าไม่มีเบอร์โทรซ้ำให้เพิ่มข้อมูลใหม่
        if (!found) {
            records[numRecords++] = {name, phoneNumber, amount};
        }
    }

    // เมธอดสำหรับบันทึกข้อมูลลงในไฟล์
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < numRecords; ++i) {
                file << records[i].name << "," << records[i].phoneNumber << "," << records[i].amount << endl;
            }
            file.close();
            cout << "The information has been successfully recorded in " << filename << endl;
        } else {
            cout << "Unable to open file " << filename << " to record information" << endl;
        }
    }

    // เมธอดสำหรับแสดงผู้บริจาคมากสุด 5 คน
    void displayTopDonors() {
        // คัดเลือกข้อมูล 5 คนแรก
        sort(records, records + numRecords, [](const DonationRecord& a, const DonationRecord& b) {
            return a.amount > b.amount;
        });

        cout << "Top 5 donors:" << endl;
        for (int i = 0; i < min(5, numRecords); ++i) {
            cout << "Name: " << records[i].name << ", Phone number: " << records[i].phoneNumber << ", Donation amount: " << records[i].amount << endl;
        }
    }
};

int main() {
    DonationTracker tracker;

    int numDonations;
    cout << "Enter the number of donors: ";
    cin >> numDonations;

    for (int i = 0; i < numDonations; ++i) {
        string name, phoneNumber;
        int amount;
        cout << "Donate times " << i+1 << ":" << endl;
        cout << "Enter donor name: ";
        cin >> name;
        cout << "Enter donor phone number: ";
        cin >> phoneNumber;
        cout << "Enter donation amount: ";
        cin >> amount;

        tracker.recordDonation(name, phoneNumber, amount);
    }

    tracker.saveToFile("donation_records.txt");
    tracker.displayTopDonors();

    return 0;
}
