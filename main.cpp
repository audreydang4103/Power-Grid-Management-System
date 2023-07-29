#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct district {
    string name;
    string type;
    int num_resident;
    int power;
    bool has_power;
    int num_technician;
    string technicians[10];
};


void cut_power(string district_name, district districts[], int num_district) {
    for (int i = 0; i < num_district; i++) {
        if (districts[i].name == district_name) {
            districts[i].has_power = false;
            districts[i].power = 0;
            break;
        }
    }
}

void restore_power(string district_name, district districts[], int num_district) {
    for (int i = 0; i < num_district; i++) {
        if (districts[i].name == district_name) {
            districts[i].has_power = true;
            // Set the power back to the default value, you might need to change this value
            districts[i].power = districts[i].num_resident * 1; // Example: 1 MW per resident
            break;
        }
    }
}



void sort_districts(district districts[], int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - 1 - i; j++) {
            if (districts[j].num_resident > districts[j + 1].num_resident) {
                swap(districts[j], districts[j + 1]);
            }
        }
    }
}

void load(string fname, district districts[], int &num, int &power) {
    ifstream file(fname);

    if (file.is_open()) {
        file >> power;
        file >> num;
        file.ignore();

        for (int i = 0; i < num; i++) {
            getline(file, districts[i].name);
            getline(file, districts[i].type);
            file >> districts[i].num_resident;
            file >> districts[i].power;
            file >> districts[i].has_power;
            file >> districts[i].num_technician;
            file.ignore();

            for (int j = 0; j < districts[i].num_technician; j++) {
                getline(file, districts[i].technicians[j]);
            }
        }

        file.close();
    }
    sort_districts(districts, num);

}

void save(string fname, district districts[], int num, int power) {
    ofstream file(fname);

    if (!file.is_open()) {
        cerr << "Error: Unable to open the file!" << endl;
        return;
    }

    file << power << endl;
    file << num << endl;

    for (int i = 0; i < num; i++) {
        file << districts[i].name << endl;
        file << districts[i].type << endl;
        file << districts[i].num_resident << endl;
        file << districts[i].power << endl;
        file << districts[i].has_power << endl;
        file << districts[i].num_technician << endl;

        for (int j = 0; j < districts[i].num_technician; j++) {
            file << districts[i].technicians[j] << endl;
        }
    }

    file.close();
}


void print_all(district districts[], int num, int power) {
    int total_power_demand = 0;

    cout << "The current power supply is " << power << "MW." << endl;

    for (int i = 0; i < num; i++) {
        cout << districts[i].name << endl;
        cout << "District type: " << districts[i].type << endl;
        cout << "Number of residents: " << districts[i].num_resident << endl;
        if (districts[i].has_power == 1) {
            cout << "Power use: " << districts[i].power << "MW" << endl;
        } else {cout << "Power use: 0MW" << endl;}
        cout << "Has power: " << (districts[i].has_power ? "1" : "0") << endl;

        if (districts[i].num_technician > 0) {
            cout << "Technicians: ";
            for (int j = 0; j < districts[i].num_technician; j++) {
                cout << districts[i].technicians[j];
                if (j < districts[i].num_technician - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }

        cout << "---" << endl;
        if (districts[i].has_power==1) {
            total_power_demand += districts[i].power;
        }
    }

    if (power < total_power_demand) {
        cout << "Critical Error! The current power supply of " << power << "MW is insufficient to supply " << total_power_demand << "MW of power demand. Please shut off one or more districts." << endl;
        cout << "---" << endl;
    }
}

void assign_technician(string tech_name, string district_name, district districts[], int num_district) {
    bool district_found = false;

    for (int i = 0; i < num_district; i++) {
        if (districts[i].name == district_name) {
            district_found = true;

            if (districts[i].num_technician < 10) {
                districts[i].technicians[districts[i].num_technician] = tech_name;
                districts[i].num_technician++;
                cout << "Technician assigned!" << endl;
            } else {
                cout << "Error! Maximum number of technicians reached for this district." << endl;
            }
            break;
        }
    }

    if (!district_found) {
        cout << "Error! The district with that name doesn't exist." << endl;
    }
}

int main() {
    string filename;
    int num_districts = 0;
    int total_power_supply = 0;
    district districts[100];

    cout << "Please enter the name of the file to load:" << endl;
    cin >> filename;
    cin.ignore();
    load(filename, districts, num_districts, total_power_supply);
    print_all(districts, num_districts, total_power_supply);

    int choice;
    while (true) {
        cout << "Main Menu" << endl;
        cout << "1- Status" << endl;
        cout << "2- Set Power Supply" << endl;
        cout << "3- Shutoff Power" << endl;
        cout << "4- Restore Power" << endl;
        cout << "5- Assign Technician" << endl;
        cout << "6- Save" << endl;
        cout << "7- Load" << endl;
        cout << "8- Exit" << endl;
        cout << "Please enter your choice:" << endl;
        void cut_power(string district_name, district districts[], int num_district);
        void restore_power(string district_name, district districts[], int num_district);

        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            print_all(districts, num_districts, total_power_supply);
        } else if (choice == 2) {
            cout << "Enter the updated power supply in megawatts:" << endl;
            cin >> total_power_supply;
            cin.ignore();
        } else if (choice == 3 || choice == 4) {
            string district_name;
            cout << "Enter the name of the district:" << endl;
            getline(cin, district_name);


            bool district_found = false;
            for (int i = 0; i < num_districts; i++) {
                if (districts[i].name == district_name) {
                    district_found = true;
                    districts[i].has_power = (choice == 4);

                    if (choice == 4) {
                        cout << "The district's power has been successfully turned back on." << endl;

                    } else {
                        cout << "The district's power has been successfully turned off." << endl;
                    }
                    if (choice == 3) {
                        districts[i].has_power=0;
                    }
                    break;
                }
            }

            if (!district_found) {
                cout << "Error! The district with that name doesn't exist." << endl;
            }
        } else if (choice == 5) {
            string technician_name, district_name;
            cout << "Enter the name of the technician:" << endl;
            getline(cin, technician_name);
            cout << "Enter the name of the district to assign them to:" << endl;
            getline(cin, district_name);
            assign_technician(technician_name, district_name, districts, num_districts);
        } else if (choice == 6) {
            cout << "Enter the file name to save to:" << endl;
            cin >> filename;
            cin.ignore();
            save(filename, districts, num_districts, total_power_supply);
        } else if (choice == 7) {
            cout << "Enter the file name to load from:" << endl;
            cin >> filename;
            cin.ignore();
            load(filename, districts, num_districts, total_power_supply);
        } else if (choice == 8) {
            break;
        } else {
            cout << "Invalid option!" << endl;
        }
    }

    return 0;

}

