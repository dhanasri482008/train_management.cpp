#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Train {
    int trainNo;
    string trainName;
    string source;
    string destination;
    int seats;
    float price;
};

struct Booking {
    string passengerName;
    int trainNo;
    int seatsBooked;
};

vector<Train> trains;
vector<Booking> bookings;

void addTrain() {
    Train t;

    cout << "\nEnter Train Number: ";
    cin >> t.trainNo;

    cin.ignore();

    cout << "Enter Train Name: ";
    getline(cin, t.trainName);

    cout << "Enter Source: ";
    getline(cin, t.source);

    cout << "Enter Destination: ";
    getline(cin, t.destination);

    cout << "Enter Total Seats: ";
    cin >> t.seats;

    cout << "Enter Ticket Price: ";
    cin >> t.price;

    trains.push_back(t);

    cout << "\nTrain Added Successfully!\n";
}


void viewTrains() {

    if(trains.empty()) {
        cout << "\nNo Trains Available!\n";
        return;
    }

    cout << "\n================ TRAIN LIST ================\n";

    cout << left
         << setw(10) << "No"
         << setw(20) << "Name"
         << setw(15) << "Source"
         << setw(15) << "Destination"
         << setw(10) << "Seats"
         << setw(10) << "Price"
         << endl;

    for(auto t : trains) {
        cout << left
             << setw(10) << t.trainNo
             << setw(20) << t.trainName
             << setw(15) << t.source
             << setw(15) << t.destination
             << setw(10) << t.seats
             << setw(10) << t.price
             << endl;
    }
}


void searchTrain() {

    int number;
    bool found = false;

    cout << "\nEnter Train Number to Search: ";
    cin >> number;

    for(auto t : trains) {

        if(t.trainNo == number) {

            cout << "\nTrain Found!\n";

            cout << "Train Name : " << t.trainName << endl;
            cout << "Source     : " << t.source << endl;
            cout << "Destination: " << t.destination << endl;
            cout << "Seats      : " << t.seats << endl;
            cout << "Price      : " << t.price << endl;

            found = true;
        }
    }

    if(!found) {
        cout << "\nTrain Not Found!\n";
    }
}


void bookTicket() {

    int number;
    bool found = false;

    cout << "\nEnter Train Number: ";
    cin >> number;

    for(auto &t : trains) {

        if(t.trainNo == number) {

            found = true;

            int seats;

            cout << "Enter Number of Seats: ";
            cin >> seats;

            if(seats > t.seats) {
                cout << "\nNot Enough Seats Available!\n";
                return;
            }

            Booking b;

            cin.ignore();

            cout << "Enter Passenger Name: ";
            getline(cin, b.passengerName);

            b.trainNo = number;
            b.seatsBooked = seats;

            bookings.push_back(b);

            t.seats -= seats;

            cout << "\n===== TICKET BOOKED SUCCESSFULLY =====\n";
            cout << "Passenger Name : " << b.passengerName << endl;
            cout << "Train Name     : " << t.trainName << endl;
            cout << "Seats Booked   : " << seats << endl;
            cout << "Total Price    : " << seats * t.price << endl;

            ofstream file("tickets.txt", ios::app);

            file << b.passengerName << " "
                 << b.trainNo << " "
                 << b.seatsBooked << endl;

            file.close();

            return;
        }
    }

    if(!found) {
        cout << "\nTrain Not Found!\n";
    }
}


void cancelTicket() {

    string name;
    bool found = false;

    cin.ignore();

    cout << "\nEnter Passenger Name: ";
    getline(cin, name);

    for(int i = 0; i < bookings.size(); i++) {

        if(bookings[i].passengerName == name) {

            int trainNo = bookings[i].trainNo;
            int seats = bookings[i].seatsBooked;

            for(auto &t : trains) {

                if(t.trainNo == trainNo) {
                    t.seats += seats;
                }
            }

            bookings.erase(bookings.begin() + i);

            cout << "\nTicket Cancelled Successfully!\n";

            found = true;
            break;
        }
    }

    if(!found) {
        cout << "\nBooking Not Found!\n";
    }
}


bool login() {

    string username, password;

    cout << "\n===== ADMIN LOGIN =====\n";

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    if(username == "admin" && password == "1234") {
        cout << "\nLogin Successful!\n";
        return true;
    }

    cout << "\nInvalid Username or Password!\n";
    return false;
}


int main() {

    int choice;

    while(true) {

        cout << "\n=====================================\n";
        cout << "      TRAIN MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";

        cout << "1. Admin Login\n";
        cout << "2. Add Train\n";
        cout << "3. View Trains\n";
        cout << "4. Search Train\n";
        cout << "5. Book Ticket\n";
        cout << "6. Cancel Ticket\n";
        cout << "7. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                login();
                break;

            case 2:
                addTrain();
                break;

            case 3:
                viewTrains();
                break;

            case 4:
                searchTrain();
                break;

            case 5:
                bookTicket();
                break;

            case 6:
                cancelTicket();
                break;

            case 7:
                cout << "\nThank You!\n";
                return 0;

            default:
                cout << "\nInvalid Choice!\n";
        }
    }

    return 0;
}