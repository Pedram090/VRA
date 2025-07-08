#include <iostream>
#include <string>
#include <conio.h>
#include <limits>
using namespace std;

class Vehicle {
protected:
    string model;
    int year;
    double pricePerDay;
    bool isRented;
public:
    Vehicle() : isRented(false) {}
    Vehicle(string m, int y, double p) :
        model(m), year(y), pricePerDay(p), isRented(false) {}

    virtual void showDetails() const {
        cout << "Model: " << model << endl
             << "Year: " << year << endl
             << "Price/day: $" << pricePerDay << endl
             << "Status: " << (isRented ? "Rented" : "Available") << endl;
    }

    string getModel() const {
         return model;
         }
    double getPrice() const {
         return pricePerDay;
         }
    bool getIsRented() const {
         return isRented;
         }
    void rent() {
         isRented = true;
         }
};

class Car : public Vehicle {
    int seats;
public:
    Car() {}
    Car(string m, int y, double p, int s) :
        Vehicle(m, y, p), seats(s) {}

    void showDetails() const override {
        cout << "[CAR] ";
        Vehicle::showDetails();
        cout << "Seats: " << seats << endl;
    }
};

class Motorcycle : public Vehicle {
    bool hasCarrier;
public:
    Motorcycle() {}
    Motorcycle(string m, int y, double p, bool c) :
        Vehicle(m, y, p), hasCarrier(c) {}

    void showDetails() const override {
        cout << "[MOTORCYCLE] ";
        Vehicle::showDetails();
        cout << "Carrier: " << (hasCarrier ? "Yes" : "No") << endl;
    }
};

class User {
    string username;
    string password;
public:
    User() {}
    User(string u, string p) : username(u), password(p) {}

    string getUsername() const { return username; }
    bool checkPassword(const string& p) const { return password == p; }
};

User users[100];
int userCount = 0;

Car cars[100];
int carCount = 0;
Motorcycle motos[100];
int motoCount = 0;

void printReceipt(const Vehicle& v, int days);
string getHiddenPassword();
void adminAddVehicle();
void initData();
void signup();
int login();
void userMenu();
void adminMenu();
void showAvailableVehicles();

int main() {
    initData();
    while (true) {
        cout << "1. Sign Up\n2. Log In\n3. Exit\nChoice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            signup();
        } else if (choice == 2) {
            int userIndex = login();
            if (userIndex >= 0) {
                if (users[userIndex].getUsername() == "admin") {
                    adminMenu();
                } else {
                    userMenu();
                }
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}

string getHiddenPassword() {
    string pass;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!pass.empty()) {
                pass.pop_back();
                cout << "\b \b";
            }
        } else {
            pass += ch;
            cout << '*';
        }
    }
    cout << endl;
    return pass;
}

void signup() {
    if (userCount >= 100) {
        cout << "User limit reached!\n";
        return;
    }

    string username, password;
    cout << "Enter username: ";
    getline(cin, username);

    for (int i = 0; i < userCount; i++) {
        if (users[i].getUsername() == username) {
            cout << "Username already exists!\n";
            return;
        }
    }

    cout << "Enter password: ";
    password = getHiddenPassword();

    users[userCount++] = User(username, password);
    cout << "Signup successful!\n";
}

int login() {
    string username, password;
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    password = getHiddenPassword();

    for (int i = 0; i < userCount; i++) {
        if (users[i].getUsername() == username && users[i].checkPassword(password)) {
            cout << "Login successful!\n";
            return i;
        }
    }
    cout << "Invalid credentials!\n";
    return -1;
}

void adminMenu() {
    while (true) {
        cout << "\nADMIN MENU\n1. Add Vehicle\n2. Logout\nChoice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            adminAddVehicle();
        } else if (choice == 2) {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }
}

void userMenu() {
    while (true) {
        cout << "\nUSER MENU\n1. Rent Vehicle\n2. Logout\nChoice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            showAvailableVehicles();
        } else if (choice == 2) {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }
}

void showAvailableVehicles() {
    while (true) {
        cout << "\n1. Cars\n2. Motorcycles\n3. Back\nChoice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            cout << "\nAvailable Cars:\n";
            for (int i = 0; i < carCount; i++) {
                if (!cars[i].getIsRented()) {
                    cout << i+1 << ". " << cars[i].getModel() << endl;
                }
            }
            cout << "Select car (0 to cancel): ";
            int sel;
            cin >> sel;
            if (sel > 0 && sel <= carCount) {
                if (!cars[sel-1].getIsRented()) {
                    cars[sel-1].showDetails();
                    cout << "Enter rental days: ";
                    int days;
                    cin >> days;
                    cars[sel-1].rent();
                    printReceipt(cars[sel-1], days);
                } else {
                    cout << "Car already rented!\n";
                }
            }
        } else if (choice == 2) {
            cout << "\nAvailable Motorcycles:\n";
            for (int i = 0; i < motoCount; i++) {
                if (!motos[i].getIsRented()) {
                    cout << i+1 << ". " << motos[i].getModel() << endl;
                }
            }
            cout << "Select motorcycle (0 to cancel): ";
            int sel;
            cin >> sel;
            if (sel > 0 && sel <= motoCount) {
                if (!motos[sel-1].getIsRented()) {
                    motos[sel-1].showDetails();
                    cout << "Enter rental days: ";
                    int days;
                    cin >> days;
                    motos[sel-1].rent();
                    printReceipt(motos[sel-1], days);
                } else {
                    cout << "Motorcycle already rented!\n";
                }
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }
}

void adminAddVehicle() {
    cout << "Vehicle type (1=Car, 2=Motorcycle): ";
    int type;
    cin >> type;
    cin.ignore();

    string model;
    int year;
    double price;

    cout << "Model: ";
    getline(cin, model);
    cout << "Year: ";
    cin >> year;
    cout << "Price/day: $";
    cin >> price;

    if (type == 1) {
        int seats;
        cout << "Seats: ";
        cin >> seats;
        cars[carCount++] = Car(model, year, price, seats);
    } else {
        bool carrier;
        cout << "Carrier? (1=Yes, 0=No): ";
        cin >> carrier;
        motos[motoCount++] = Motorcycle(model, year, price, carrier);
    }
    cout << "Vehicle added!\n";
}

void printReceipt(const Vehicle& v, int days) {
    cout << "\n=== RECEIPT ===\n"
         << "Model: " << v.getModel() << "\n"
         << "Daily rate: $" << v.getPrice() << "\n"
         << "Days: " << days << "\n"
         << "Total: $" << v.getPrice() * days << "\n"
         << "===============\n";
}

void initData() {
    users[userCount++] = User("admin", "admin123");

    cars[carCount++] = Car("Toyota Corolla", 2020, 35.0, 5);
    cars[carCount++] = Car("Honda Civic", 2019, 30.0, 5);
    cars[carCount++] = Car("Ford Mustang", 2021, 55.0, 4);
    cars[carCount++] = Car("Chevrolet Impala", 2018, 40.0, 5);
    cars[carCount++] = Car("BMW 3 Series", 2022, 65.0, 5);

    motos[motoCount++] = Motorcycle("Kawasaki Ninja", 2020, 30.0, true);
    motos[motoCount++] = Motorcycle("Yamaha YZF-R3", 2021, 25.0, false);
    motos[motoCount++] = Motorcycle("Harley Davidson", 2019, 50.0, true);
    motos[motoCount++] = Motorcycle("Ducati Monster", 2022, 45.0, false);
    motos[motoCount++] = Motorcycle("BMW G310", 2021, 35.0, true);
}
