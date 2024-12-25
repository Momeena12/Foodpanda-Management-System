#include <iostream>
#include <string>
#include <limits>
#include <cctype> // Required for isalpha and isdigit
#include <vector>
#include <algorithm> // Required for find and reverse
#define INF 1000 // Represents a large distance when no direct connection exists
#ifdef _WIN32
#else
#define CLEAR_SCREEN "clear" 
#endif
#define RESET        "\033[0m"       // Adding colours to the text at Run time. 
#define RED          "\033[31m"      
#define GREEN        "\033[32m"      
#define YELLOW       "\033[33m"      
#define BLUE         "\033[34m"     
#define MAGENTA      "\033[35m"      
#define CYAN         "\033[36m"      
#define WHITE        "\033[37m"      
#define GRAY         "\033[90m"      
#define LIGHT_RED    "\033[91m"      
#define LIGHT_GREEN  "\033[92m"      
#define LIGHT_YELLOW "\033[93m"      
#define LIGHT_BLUE   "\033[94m"      
#define LIGHT_MAGENTA "\033[95m"     
#define LIGHT_CYAN   "\033[96m"   
using namespace std;

// Graph to store distances (in kilometers)
int graph[7][7];
string sectors[7] = { "F7", "I9", "I8", "H8", "F8", "H6", "I10" };

// Linked list node for an order
struct Order {
    string customerName;
    string phone;
    string destination;
    vector<string> products;
    vector<int> prices;
    bool isDelivered = false;
    Order* next; // Pointer to the next order in the linked list
};

Order* head = nullptr; // Head of the linked list

void addEdge(int v1, int v2, int dist_km) {
    graph[v1][v2] = dist_km;
    graph[v2][v1] = dist_km;
}

void displayDistance(int source, string destination) {
    auto it = find(begin(sectors), end(sectors), destination);
    if (it == end(sectors)) {
        cout << RED << "Invalid destination entered. Please try again." << RESET << endl;
        return;
    }

    int destIdx = it - begin(sectors);

    // Directly show the distance to the destination
    if (graph[source][destIdx] != INF) {
        cout << BLUE << "Distance from " << sectors[source] << " to " << destination << ": " << graph[source][destIdx] << " km" << RESET << endl;
    }
    else {
        cout << RED << "No direct connection available from " << sectors[source] << " to " << destination << "." << RESET << endl;
    }
}

void displayMenu() {
    cout << MAGENTA << "\n***** FoodPanda Management System *****\n"<<RESET;
    cout << CYAN << "1. Purchase Product\n"<<RESET;
    cout << CYAN << "2. Check All Orders\n"<<RESET;
    cout << CYAN << "3. Check Bills\n"<<RESET;
    cout << CYAN << "4. Update Order\n"<<RESET;
    cout << CYAN << "5. Cancel Order\n"<<RESET;
    cout << CYAN << "6. Deliver Order\n"<<RESET;
    cout << CYAN << "7. Check Delivered Orders\n"<<RESET;
    cout << CYAN << "8. Check Previous Feedback\n"<<RESET;
    cout << CYAN << "9. Exit\n"<<RESET;
    cout << LIGHT_GREEN << "Enter choice: "<<RESET;
}

void displayProducts() {
    cout << MAGENTA<< "\n********* Available Products *********\n"<<RESET;
    cout << LIGHT_MAGENTA<< "1. Chicken-Burger: 200\n"<<RESET;
    cout << LIGHT_MAGENTA<< "2. Fries: 100\n"<<RESET;
    cout << LIGHT_MAGENTA<< "3. Coke: 120\n"<<RESET;
    cout << LIGHT_MAGENTA<< "4. Pizza: 400\n"<<RESET;
    cout << "\n";
}

void addOrderToList(Order* newOrder) {
    if (head == nullptr) {
        head = newOrder;
    }
    else {
        Order* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newOrder;
    }
}


void purchaseProduct() {
    Order* newOrder = new Order;
    int totalPrice = 0;

    // Validate Customer Name (Alphabets only)
    cout << YELLOW << "Enter your name (alphabets only): "<<RESET;
    while (true) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover input
        getline(cin, newOrder->customerName);

        bool validName = true;
        for (char c : newOrder->customerName) {
            if (!isalpha(c) && c != ' ') { // Check if each character is an alphabet or space
                validName = false;
                break;
            }
        }

        if (validName) break;
        else cout << RED << "Invalid name! Please use alphabets only: "<<RESET;
    }

    // Validate Phone Number (+92 followed by 10 digits)
    cout << BLUE << "Enter your phone number (+92XXXXXXXXXX): "<<RESET;
    while (true) {
        cin >> newOrder->phone;

        if (newOrder->phone.length() == 13 &&
            newOrder->phone.substr(0, 3) == "+92") {
            bool validPhone = true;
            for (int i = 3; i < 13; i++) { // Check if remaining digits are numbers
                if (!isdigit(newOrder->phone[i])) {
                    validPhone = false;
                    break;
                }
            }

            if (validPhone) break;
        }
        cout << RED << "Invalid phone number! Please enter in format +92XXXXXXXXXX: "<<RESET;
    }

    // Validate Destination
    cout << BLUE << "Enter your destination (F7/I9/I8/H8/F8/H6/I10): "<<RESET;
    cin >> newOrder->destination;

    // Show distance to destination
    int sourceIdx = 0; // Example source: F7
    displayDistance(sourceIdx, newOrder->destination);

    displayProducts();

    int choice;
    cout << BLUE << "Select products by entering the number (Press 0 to finish): \n"<<RESET;
    while (true) {
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1:
            newOrder->products.push_back("Chicken-Burger");
            newOrder->prices.push_back(200);
            totalPrice += 200;
            break;
        case 2:
            newOrder->products.push_back("Fries");
            newOrder->prices.push_back(100);
            totalPrice += 100;
            break;
        case 3:
            newOrder->products.push_back("Coke");
            newOrder->prices.push_back(120);
            totalPrice += 120;
            break;
        case 4:
            newOrder->products.push_back("Pizza");
            newOrder->prices.push_back(400);
            totalPrice += 400;
            break;
        default:
            cout << RED << "Invalid choice!" << RESET <<endl;
            break;
        }
    }

    addOrderToList(newOrder);
    cout << YELLOW << "Total bill: " << totalPrice << " PKR" << RESET <<endl;
}


void checkOrders() {
    if (head == nullptr) {
        cout << RED << "No orders available." << RESET << endl;
        return;
    }

    cout << BLUE << "\n***** All Orders *****\n" <<RESET;
    Order* temp = head;
    int orderNumber = 1;
    while (temp != nullptr) {
        cout << LIGHT_CYAN << "Order " << orderNumber << ":\n"<<RESET;
        cout << LIGHT_CYAN << "Customer Name: " << temp->customerName << "\n"<<RESET;
        cout << LIGHT_CYAN << "Phone: " << temp->phone << "\n"<<RESET;
        cout << LIGHT_CYAN << "Destination: " << temp->destination << "\n"<<RESET;
        cout << LIGHT_CYAN << "Products: "<<RESET;
        for (const auto& product : temp->products) {
            cout << GREEN << product << " "<<RESET;
        }
        cout << YELLOW << "\nPrice: "<<RESET;
        int totalPrice = 0;
        for (const auto& price : temp->prices) {
            totalPrice += price;
        }
        cout << LIGHT_BLUE << " PKR\n"<<RESET;
        cout << LIGHT_BLUE << "Delivered: " << (temp->isDelivered ? "Yes" : "No") << "\n"<<RESET;
        cout << LIGHT_BLUE << "--------------------------\n"<<RESET;
        temp = temp->next;
        orderNumber++;
    }
}

void checkBills() {
    if (head == nullptr) {
        cout << RED << "No orders available." << endl;
        return;
    }

    cout << BLUE << "\n***** All Bills *****\n" <<RESET;
    Order* temp = head;
    while (temp != nullptr) {
        cout << LIGHT_CYAN <<  "Order:\n"<<RESET;
        cout << LIGHT_CYAN << "Customer Name: " << temp->customerName << "\n"<<RESET;
        cout << LIGHT_CYAN <<  "Products: "<<RESET;
        for (const auto& product : temp->products) {
            cout << GREEN << product << " "<<RESET;
        }
        cout << YELLOW << "\nPrice: "<<RESET;
        int totalPrice = 0;
        for (const auto& price : temp->prices) {
            totalPrice += price;
        }
        cout << LIGHT_BLUE <<  totalPrice << " PKR\n"<<RESET;
        cout <<  LIGHT_BLUE << "--------------------------\n"<<RESET;
        temp = temp->next;
    }
}

void updateOrder() {
    int orderId;
    cout << "Enter order number to update: "<<RESET;
    cin >> orderId;

    if (orderId <= 0) {
        cout << RED << "Invalid order number!" << RESET <<endl;
        return;
    }

    Order* temp = head;
    int count = 1;
    while (temp != nullptr && count < orderId) {
        temp = temp->next;
        count++;
    }

    if (temp == nullptr) {
        cout << RED << "Invalid order number!" << RESET <<endl;
        return;
    }

    cout << BLUE << "Enter new product (1. Chicken-Burger, 2. Fries, 3. Coke, 4. Pizza): "<<RESET;
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        temp->products.push_back("Chicken-Burger");
        temp->prices.push_back(200);
        break;
    case 2:
        temp->products.push_back("Fries");
        temp->prices.push_back(100);
        break;
    case 3:
        temp->products.push_back("Coke");
        temp->prices.push_back(120);
        break;
    case 4:
        temp->products.push_back("Pizza");
        temp->prices.push_back(400);
        break;
    default:
        cout << RED << "Invalid choice!" << RESET <<endl;
        return;
    }

    cout << MAGENTA << "Order updated successfully!" << RESET <<endl;
}

void cancelOrder() {
    int orderId;
    cout << BLUE << "Enter order number to cancel: " << RESET;
    cin >> orderId;

    if (orderId <= 0) {
        cout << RED<< "Invalid order number!" << RESET <<endl;
        return;
    }

    Order* temp = head;
    Order* prev = nullptr;
    int count = 1;

    while (temp != nullptr && count < orderId) {
        prev = temp;
        temp = temp->next;
        count++;
    }

    if (temp == nullptr) {
        cout << RED << "Invalid order number!" << RESET <<endl;
        return;
    }

    if (prev == nullptr) {
        head = temp->next;
    }
    else {
        prev->next = temp->next;
    }

    delete temp;
    cout << LIGHT_BLUE << "Order canceled successfully!" << RESET <<endl;
}

void deliverOrder() {
    int orderId;
    cout << BLUE << "Enter order number to mark as delivered: " <<RESET;
    cin >> orderId;

    if (orderId <= 0) {
        cout << RED << "Invalid order number!" << RESET <<endl;
        return;
    }

    Order* temp = head;
    int count = 1;
    while (temp != nullptr && count < orderId) {
        temp = temp->next;
        count++;
    }

    if (temp == nullptr) {
        cout << RED << "Invalid order number!" << RESET <<endl;
        return;
    }

    temp->isDelivered = true;
    cout << MAGENTA << "Order marked as delivered!" << RESET <<endl;
}

void checkDeliveredOrders() {
    bool anyDelivered = false;
    cout << BLUE<< "\n***** Delivered Orders *****\n"<<RESET;
    Order* temp = head;

    if (temp == nullptr) {
        cout << RED << "No orders available.\n" <<RESET;
        return;
    }

    while (temp != nullptr) {
        if (temp->isDelivered) {
            cout << LIGHT_CYAN << "Order:\n" <<RESET;
            cout << LIGHT_CYAN << "Customer Name: " << temp->customerName << "\n" <<RESET;
            cout << LIGHT_CYAN << "Products: " <<RESET;
            for (const auto& product : temp->products) {
                cout << GREEN << product << " " <<RESET;
            }
            cout << YELLOW << "\nPrice: " <<RESET;
            int totalPrice = 0;
            for (const auto& price : temp->prices) {
                totalPrice += price;
            }
            cout << LIGHT_BLUE << totalPrice << " PKR\n" <<RESET;
            cout << LIGHT_BLUE << "--------------------------\n" <<RESET;
            anyDelivered = true;
        }
        temp = temp->next;
    }

    if (!anyDelivered) {
        cout << RED << "No delivered orders found.\n" <<RESET;
    }
}

int main() {
    // Initialize distances (in kilometers) with INF
    fill(&graph[0][0], &graph[0][0] + sizeof(graph) / sizeof(int), INF);

    // Set the distance from F7 to F7 as 0 and distances for other destinations
    addEdge(0, 0, 0);  // F7 to F7 (distance 0)
    addEdge(0, 1, 3);  // F7 to I9 (distance 3)
    addEdge(0, 2, 4);  // F7 to I8 (distance 4)
    addEdge(0, 3, 5);  // F7 to H8 (distance 5)
    addEdge(0, 4, 6);  // F7 to F8 (distance 6)
    addEdge(0, 5, 4);  // F7 to H6 (distance 4)
    addEdge(0, 6, 5);  // F7 to I10 (distance 5)

    int choice;
    do {
        displayMenu();

        if (!(cin >> choice)) { // Check if input is invalid
            cout << RED << "Invalid input! Please enter a number.\n" <<RESET;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue; // Restart the loop
        }

        switch (choice) {
        case 1:
            purchaseProduct();
            break;
        case 2:
            checkOrders();
            break;
        case 3:
            checkBills();
            break;
        case 4:
            updateOrder();
            break;
        case 5:
            cancelOrder();
            break;
        case 6:
            deliverOrder();
            break;
        case 7:
            checkDeliveredOrders();
            break;
        case 8:
            cout << BLUE << "Feedback:\n"<<RESET;
            cout << LIGHT_BLUE << "I have used this app, and they offer good customer service, and their delivery is very fast. I am satisfied.\n"<<RESET;
            break;
        case 9:
            cout << CYAN <<"Exiting...\n"<<RESET;
            break;
        default:
            cout << RED << "Invalid choice. Try again.\n"<<RESET;
        }
    } while (choice != 9);


    return 0;
}