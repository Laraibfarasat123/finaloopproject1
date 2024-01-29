#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

class hotel
{
public:
    virtual void inputInfo() = 0;
    virtual void displayInfo() const = 0;
    virtual void saveInfoToFile(ofstream &file) const = 0;
    virtual void loadInfoFromFile(ifstream &file) = 0;
};

class User : public hotel
{
private:
    string username;
    string email;
    string password;
    int phoneNumber;
    int idCardNumber;
    string city;

public:
    User() : username(""), email(""), password(""), phoneNumber(0), idCardNumber(0), city("") {}

    void inputInfo() override
    {
        cout << "Enter Username: ";
        cin >> username;

        cout << "Enter Email: ";
        cin >> email;

        cout << "Enter Password: ";
        cin >> password;

        cout << "Enter Phone Number: ";
        cin >> phoneNumber;

        cout << "Enter ID Card Number: ";
        cin >> idCardNumber;

        cout << "Enter City: ";
        cin >> city;

        ofstream outFile("hotel.txt", ios::app);
        if (!outFile.is_open())
        {
            cerr << "Error opening file for writing.\n";
            return;
        }

        saveInfoToFile(outFile);

        outFile.close();
    }

    bool logIn()
    {
        string inputUsername, inputPassword;
        cout << "Enter Username: ";
        cin >> inputUsername;

        cout << "Enter Password: ";
        cin >> inputPassword;

        return (inputUsername == username && inputPassword == password);
    }

    void displayInfo() const override
    {
        cout << "Username: " << username << endl;
        cout << "Email: " << email << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "ID Card Number: " << idCardNumber << endl;
        cout << "City: " << city << endl;
    }

    void saveInfoToFile(ofstream &file) const override
    {
        file << "User " << username << ' ' << email << ' ' << password << ' ' << phoneNumber << ' ' << idCardNumber << ' ' << city << '\n';
    }

    void loadInfoFromFile(ifstream &file) override
    {
        file >> username >> email >> password >> phoneNumber >> idCardNumber >> city;
    }
};

class Room : public hotel
{
private:
    static map<int, Room> roomData;

    int roomNumber;
    bool isOccupied;
    int roomRate;
    bool isAC;
    bool isLuxurious;
    char roomType;

public:
    Room() : roomNumber(0), isOccupied(false), roomRate(0), isAC(false), isLuxurious(false), roomType('s') {}

    void inputInfo() override
    {
        cout << "Enter Room Number: ";
        cin >> roomNumber;

        auto it = roomData.find(roomNumber);

        if (it != roomData.end())
        {
            *this = it->second;

            cout << "Room details already exist. Displaying existing details:\n";

            displayInfo();

            return;
        }

        cout << "Is Room Occupied? (1 for Yes, 0 for No): ";
        cin >> isOccupied;

        cout << "Enter Room Type ('s' for Single, 'd' for Double, 'm' for Master): ";
        cin >> roomType;

        cout << "Is AC? (1 for Yes, 0 for No): ";
        cin >> isAC;

        cout << "Is Luxurious? (1 for Yes, 0 for No): ";
        cin >> isLuxurious;

        
        roomData[roomNumber] = *this;

        ofstream outFile("hotel.txt", ios::app);
        if (!outFile.is_open())
        {
            cerr << "Error opening file for writing.\n";
            return;
        }

        saveInfoToFile(outFile);

        outFile.close();
    }

    void displayInfo() const override
    {
        cout << "Room Number: " << roomNumber << endl;
        cout << "Occupied: " << (isOccupied ? "Yes" : "No") << endl;
        cout << "Room Type: " << roomType << endl;
        cout << "AC: " << (isAC ? "Yes" : "No") << endl;
        cout << "Luxurious: " << (isLuxurious ? "Yes" : "No") << endl;
    
    }

    void saveInfoToFile(ofstream &file) const override
    {
        file << "Room " << roomNumber << ' ' << (isOccupied ? 1 : 0) << ' ' << roomType << ' ' << (isAC ? 1 : 0) << ' ' << (isLuxurious ? 1 : 0) <<'\n';
    }
    void loadInfoFromFile(ifstream &file) override
    {
        file >> roomNumber >> isOccupied >> roomType >> isAC >> isLuxurious ;
        roomData[roomNumber] = *this;
    }

    double calculateTotalCost(int quantity, int numOfDays) const
    {
        double baseCost = 0.0;

        switch (roomType)
        {
        case 's':
            baseCost = 5000.0;
            break;
        case 'd':
            baseCost = 7000.0;
            break;
        case 'm':
            baseCost = 10000.0;
            break;
        }

        return baseCost * quantity * numOfDays;
    }
    void searchRoom(int roomNumber)
    {

        if (this->roomNumber == roomNumber)
        {
            cout << "Room found!\n";
            this->displayInfo();
        }
        else
        {
            cout << "Room not found.\n";
        }
    }
};

map<int, Room> Room::roomData;

class Customer : public hotel
{
private:
    string name;
    string address;
    string phone;
    int bookingID;
    string checkInDate;
    string checkOutDate;

public:
    Customer() : name(""), address(""), phone(""), bookingID(0),checkInDate(""), checkOutDate("") {}

    void inputInfo() override
    {
        cout << "Enter Customer Name: ";
        cin >> name;

        cout << "Enter Address: ";
        cin >> address;

        cout << "Enter Phone Number: ";
        cin >> phone;

        cout << "Enter Booking ID: ";
        cin >> bookingID;

        cout << "Enter Check-In Date: ";
        cin >> checkInDate;

        cout << "Enter Check-Out Date: ";
        cin >> checkOutDate;

        ofstream outFile("hotel.txt", ios::app);
        if (!outFile.is_open())
        {
            cerr << "Error opening file for writing.\n";
            return;
        }

        saveInfoToFile(outFile);

        outFile.close();
    }

    void displayInfo() const override
    {
        cout << "Customer Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Phone Number: " << phone << endl;
        cout << "Booking ID: " << bookingID << endl;
        cout << "Check-In Date: " << checkInDate << endl;
        cout << "Check-Out Date: " << checkOutDate << endl;
    }

    void saveInfoToFile(ofstream &file) const override
    {
        file << "customer " << name << ' ' << address << ' ' << phone << ' ' << bookingID << ' ' << checkInDate << ' ' << checkOutDate <<  '\n';
    }

    void loadInfoFromFile(ifstream &file) override
    {
        file >> name >> address >> phone >> bookingID>> checkInDate >> checkOutDate;
    }
};

class DiscountPlan : public hotel
{
private:
    string discountType;
    double discountPercentage;
    int discountedAmount;
    int totalAmount;

public:
    DiscountPlan() : discountType(""), discountPercentage(0.0) {}

    void inputInfo() override
    {
        cout << "Select Discount Type (silver/gold/platinum): ";
        cin >> discountType;

        while (discountType != "silver" && discountType != "gold" && discountType != "platinum")
        {
            cout << "Invalid discount type. Please enter silver, gold, or platinum: ";
            cin >> discountType;
        }

        if (discountType == "silver")
        {
            discountPercentage = 10.0;
        }
        else if (discountType == "gold")
        {
            discountPercentage = 20.0;
        }
        else if (discountType == "platinum")
        {
            discountPercentage = 25.0;
        }

        cout << "Enter Total Amount: ";
        cin >> totalAmount;

        double discountAmount = (discountPercentage / 100) * totalAmount;
        discountedAmount = totalAmount - discountAmount;

        ofstream outFile("hotel.txt", ios::app);
        if (!outFile.is_open())
        {
            cerr << "Error opening file for writing.\n";
            return;
        }

        saveInfoToFile(outFile);

        outFile.close();
    }

    void displayInfo() const override
    {
        cout << "Discount Type: " << discountType << endl;
        cout << "Discount Percentage: " << discountPercentage << "%" << endl;
        cout << "Total Amount: " << totalAmount << endl;
        cout << "Discounted Amount: " << discountedAmount << endl;
    }

    void saveInfoToFile(ofstream &file) const override
    {
        file << "discount plan " << discountType << ' ' << discountPercentage << '\n';
    }

    void loadInfoFromFile(ifstream &file) override
    {
        file >> discountType >> discountPercentage;
    }
};

void displayAllDetails(const Room& room, const Customer& customer, const DiscountPlan& discountPlan)
{
    cout << "\n-----------------------\n";
    cout << "\n|      ALL DETAILS     |\n";
    cout << "\n-----------------------\n";

    cout << "\nRoom Information:\n";
    room.displayInfo();

    cout << "\nCustomer Information:\n";
    customer.displayInfo();

    cout << "\nDiscount Plan Information:\n";
    discountPlan.displayInfo();

}


void printWelcomeMessage()
{
    cout << "***********************************************\n";
    cout << "*            WELCOME TO THE HOTEL             *\n";
    cout << "*                                             *\n";
    cout << "*   Explore luxury and comfort at our hotel   *\n";
    cout << "*                                             *\n";
    cout << "***********************************************\n";
}
int main()
{
    User user;
    Room room;
    Customer customer;
    DiscountPlan discountPlan;

    int option;
    string fileName = "hotel.txt";

    ofstream outFile(fileName);
    ifstream inFile(fileName);

    if (!outFile.is_open())
    {
        cerr << "Error opening file for writing.\n";
        return 1;
    }

    if (!inFile.is_open())
    {
        cerr << "Error opening file for reading.\n";
        return 1;
    }

    printWelcomeMessage();

    cout << "Press enter key to continue...";
    cin.ignore();
    cin.get();
    
    do
    {
        cout << "***********************************************\n";
        cout << "*                  MAIN MENU                  *\n";
        cout << "***********************************************\n";
        cout << "1. Reservation \n";
        cout << "2. search room\n";
        cout << "3. Check discount plan \n";
        cout << "4. see all details\n";
        cout << "5. Save Data to File\n";
        cout << "6. Load Data from File\n";
        cout << "7. Exit\n";
        cout << "Enter option: ";
        cin >> option;

        switch (option)
        {
        case 1:

            int onlineOption;
            cout << "\n   ONLINE REGISTRATION  \n";
            cout << "\n1. Sign Up\n";
            cout << "2. Log In\n";
            cout << "Enter option: ";
            cin >> onlineOption;

            switch (onlineOption)
            {
            case 1:
                // Sign Up
                user.inputInfo();
                cout << "Account created successfully!\n";
                break;

            case 2:
                // Log In
                if (user.logIn())
                {
                    cout << "Log in successful!\n";

                    // Room Options
                    int roomOption;
                    do

                    {
                        cout << "\n OPTIONS\n";
                        cout << "1. check in room\n";
                        cout << "2. Back to Main Menu\n";
                        cout << "Enter option: ";
                        cin >> roomOption;

                        switch (roomOption)
                        {
                        case 1:
                            cout << "\nEnter Room Information:\n";
                            room.inputInfo();

                            int quantity;
                            cout << "Enter the quantity of rooms needed: ";
                            cin >> quantity;

                            int numOfDays;
                            cout << "for how many days : ";
                            cin >> numOfDays;

                            cout << "\n------------------------\n";
                            cout << "\n|   ROOM INFORMATION   |\n";
                            cout << "\n------------------------\n";

                            room.displayInfo();

                            cout << "\n   Enter Customer Information:  \n";
                            customer.inputInfo();

                            cout << "\n-----------------------\n";
                            cout << "\n|     CUSTOMER INFO   |\n";
                            cout << "\n-----------------------\n";
                            customer.displayInfo();
                            customer.saveInfoToFile(outFile);

                            cout << "room reserved successfully\n";

                            cout << " single room : pkr5000\n";
                            cout << " double room : pkr7000\n";
                            cout << " master room : pkr10000\n";

                            cout << "\n--------------------------\n";
                            cout << "\n|    your total bill is :  |\n";
                            cout << "\n--------------------------\n";
                            cout << "Total Cost: PKR " << room.calculateTotalCost(quantity, numOfDays) << endl;
                            room.saveInfoToFile(outFile);

            
                            int discountOption;
                            cout << "\nDo you want a discount plan? (1 for Yes, 0 for No): ";
                            cin >> discountOption;

                            if (discountOption == 1)
                            {
                                cout << "\nEnter Discount Plan Information:\n";
                                discountPlan.inputInfo();

                                discountPlan.saveInfoToFile(outFile);

                                cout << "\n---------------------------\n";
                                cout << "\n|    FINAL BILL DETAILS   |\n";
                                cout << "\n---------------------------\n";
                                discountPlan.displayInfo();
                            }
                            else
                            {
                                cout << "\n---------------------------\n";
                                cout << "\n|    FINAL BILL DETAILS   |\n";
                                cout << "\n---------------------------\n";
                                cout << "Total Cost: PKR " << room.calculateTotalCost(quantity, numOfDays) << endl;
                            }
                            break;

                        case 2:
                            cout << "Returning to Main Menu.\n";
                            break;

                        default:
                            cout << "Invalid . Please try again.\n";
                        }
                    } while (roomOption != 2);
                }
                else
                {
                    cout << "Invalid username or password. Please try again.\n";
                }
                break;

            default:
                cout << "Invalid online option. Please try again.\n";
            }
            break;

        case 2:
            
            int searchRoomNum;
            cout << "Enter Room Number to search: ";
            cin >> searchRoomNum;
            room.searchRoom(searchRoomNum);
            break;

        case 3:

            cout << "\nEnter Discount Plan Information:\n";
            discountPlan.inputInfo();

            cout << "\n-----------------------\n";
            cout << "\n|     DISCOUNT INFO   |\n";
            cout << "\n-----------------------\n";
            discountPlan.displayInfo();
            discountPlan.saveInfoToFile(outFile);
            break;

        case 4: 
                displayAllDetails(room, customer, discountPlan);
                break;


        case 5:
            int subOption;

            cout << "\n1. Save Room Details\n";
            cout << "2. Save Customer Details\n";
            cout << "3. Save discount Details\n";
            cout << "4. Back to Main Menu\n";
            cout << "Enter sub-option: ";
            cin >> subOption;

            switch (subOption)
            {
            case 1:
                cout << "\nEnter Room Information:\n";
                room.inputInfo();
                room.displayInfo();
                room.saveInfoToFile(outFile);
                break;

            case 2:
                cout << "\nEnter Customer Information:\n";
                customer.inputInfo();
                customer.displayInfo();
                customer.saveInfoToFile(outFile);
                break;
            
            case 3:
                cout << "\nEnter Discount Plan Information:\n";
                discountPlan.inputInfo();
                discountPlan.displayInfo();
                discountPlan.saveInfoToFile(outFile);
                break;

            default:
                cout << "Invalid sub-option. Please try again.\n";
            }

            outFile << flush;
            cout << "Data saved to file.\n";
            break;
        
        
        case 6:
            inFile.clear();
            inFile.seekg(0);

            room.loadInfoFromFile(inFile);
            cout << "\nRoom Information:\n";
            room.displayInfo();

            customer.loadInfoFromFile(inFile);
            cout << "\ncustomerInformation:\n";
            customer.displayInfo();

            discountPlan.loadInfoFromFile(inFile);
            cout << "\ndiscountPlan Information:\n";
            discountPlan.displayInfo();

            break;

    
        case 7:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid option. Please try again.\n";
        }

    } while (option != 7);

    outFile.close();
    inFile.close();

    return 0;
}


