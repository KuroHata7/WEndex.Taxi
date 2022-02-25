#include "Passenger.h"
#include "Order.h"

class passengerBannedException : public exception {
    const char* what() const throw() {
        cout<<"Passenger has been banned from placing orders\n";
    }
};

class PassengerGateway{
    Passenger passenger;
    bool logged_in = false;
public:
    PassengerGateway(){}

    void main_menu(){
        while(true){
            cout<<"Welcome to WEndex.Taxi!\n";
            cout<<"Would you like to:\n"
                <<"(1) Login\n"
                <<"(2) Register\n"
                <<"(0) Exit\n";
            int choice;
            cin>>choice;
            if(choice == 1){
                passenger_login();
                if(logged_in)break;
            }
            else if(choice == 2) passenger_register();
            else if(choice == 0) return;
            else cout<<"Invalid!\n";
        }
        while(true){
            cout<<"Welcome " + passenger.username + " what would you like to do:\n"
                <<"(1) View order history\n"
                <<"(2) View payment methods\n"
                <<"(3) Add payment method\n"
                <<"(4) Replace payment methods\n"
                <<"(5) View pinned addresses\n"
                <<"(6) Pin new address\n"
                <<"(7) Replace pinned addresses\n"
                <<"(8) Order a ride\n"
                <<"(9) Request current coordinates\n"
                <<"(0) Logout\n";
            int choice;
            cin>>choice;
            if(choice == 1) view_order_history();
            else if(choice == 2) view_payment_methods();
            else if(choice == 3) add_payment_method();
            else if(choice == 4) replace_payment_methods();
            else if(choice == 5) view_pinned_addresses();
            else if(choice == 6) pin_new_address();
            else if(choice == 7) replace_pinned_addresses();
            else if(choice == 8) place_order();
            else if(choice == 9) request_current_location();
            else if(choice == 0) {
                passenger_logout();
                break;
            }
            else cout<<"Invalid\n";
        }
    }

    void passenger_login(){
        while(true){
            cout<<"Please enter your username:\n";
            string user;
            cin>>user;
            cout<<"Please enter your password:\n";
            string pass;
            cin>>pass;
            if(Passenger::passenger_login_successful(user,pass)){
                passenger = (*new Passenger(user));
                cout<<"You have been successfully logged in!\n";
                logged_in = true;
                break;
            }
            else {
                cout<<"Invalid credentials. Would you like to:\n";
                cout<<"(1) Try again\n"
                    <<"(0) Back\n";
                int choice;
                cin>>choice;
                if(choice == 1) cout<<"Please try again:\n";
                else if(choice == 0)break;
                else cout<<"Invalid!\n";
            }
        }
    }

    void passenger_register(){
        cout<<"Please enter your first and last name separated by a space:\n";
        string name;
        cin.ignore();
        getline(cin,name);
        string username;
        while(true){
            cout<<"Please enter your desired username (no spaces):\n";
            cin>>username;
            if(Passenger::username_conflict(username)){
                cout<<"Username already exists. Please choose a different username:\n";
            }
            else {break;}
        }
        cout<<"Please enter your desired password (no spaces):\n";
        string password;
        cin>>password;
        cout<<"Please enter your rating of our app (float 0.0~5.0):\n";
        float rating;
        cin>>rating;
        passenger = (*new Passenger(name,username,password,rating));
        cout<<"You have been successfully registered!\n";
        logged_in = true;
    }

    void passenger_logout(){
        passenger = (*new Passenger());
        logged_in = false;
        cout<<"You have been successfully logged out\n";
        main_menu();
    }

    void view_order_history(){
        std::vector<Order>order_history = Order::passenger_order_history(passenger.username);
        if(!order_history.size()){
            cout<<"You have no previous orders\n";
        }
        for(auto order : order_history){
            cout<<order.order_info()<<endl;
        }
    }

    void view_payment_methods(){
        for(int i=0;i<passenger.payment_methods.size();i++){
            cout<<i+1<<"."<<passenger.payment_methods[i]<<endl;
        }
    }

    void add_payment_method(){
        cout<<"Please enter the name of your new payment method (string e.g. \"credit card\")\n";
        string method;
        cin.ignore();
        getline(cin,method);
        passenger.add_payment_method(method);
    }

    void replace_payment_methods(){
        cout<<"Please enter the number of new payment methods you would like to have:\n";
        cout<<"[Please note that \"Cash\" will remain in your payment methods by default]\n";
        std::vector<string>payment_methods;
        payment_methods.push_back("Cash");
        int num;
        cin>>num;
        cin.ignore();
        for(int i=0;i<num;i++){
            cout<<"Enter payment method:\n";
            string temp;
            getline(cin,temp);
            payment_methods.push_back(temp);
        }
        passenger.set_payment_methods(payment_methods);
    }

    void view_pinned_addresses(){
        for(int i=0;i<passenger.pinned_addresses.size();i++){
            cout<<i+1<<"."<<passenger.pinned_addresses[i]<<endl;
        }
    }

    void pin_new_address(){
        cout<<"Please enter the name of your new pinned address (string e.g. \"Work\")\n";
        string address;
        cin.ignore();
        getline(cin,address);
        passenger.pin_new_address(address);
    }

    void replace_pinned_addresses(){
        cout<<"Please enter the number of new pinned addresses you would like to have:\n";
        cout<<"[Please note that \"Home\" will remain in your pinned addresses by default]\n";
        std::vector<string>pinned_addresses;
        pinned_addresses.push_back("Home");
        int num;
        cin>>num;
        cin.ignore();
        for(int i=0;i<num;i++){
            cout<<"Enter address:\n";
            string temp;
            getline(cin,temp);
            pinned_addresses.push_back(temp);
        }
        passenger.set_pinned_addresses(pinned_addresses);
    }

    void place_order(){
        if(Passenger::check_if_banned(passenger.username)){
            throw passengerBannedException();
            return;
        }
        if(Order::check_passenger_orders(passenger.username)){
            cout<<"You already have a pending order. Please try again later.\n";
            return;
        }
        cout<<"Please specify where you would like to go (e.g University):\n";
        string addressTo;
        cin.ignore();
        getline(cin,addressTo);
        int carType = -1;
        while(true){
            cout<<"Please specify the type of the car you wish to take:\n"
                <<"(1) Economy\n"
                <<"(2) Comfort\n"
                <<"(3) ComfortPlus\n"
                <<"(4) Business\n";
            int choice;
            cin>>choice;
            if(choice == 1)carType = 0;
            else if(choice == 2)carType = 1;
            else if(choice == 3)carType = 2;
            else if(choice == 4)carType = 3;
            else cout<<"Invalid!\n";
            if(carType != -1)break;
        }
        Order potential_order = (*new Order(passenger.username, passenger.current_location(), addressTo, carType));
        int choice = -1;
        while(true){
            cout<<"Your ride will take " + to_string(potential_order.timeTaken) + " minutes and will cost " 
            + to_string(potential_order.price) + "\n Would you like to take it?\n";
            cout<<"(1) Yes\n";
            cout<<"(2) No\n";
            cin>>choice;
            if(choice != 1 && choice != 2)cout<<"Invalid\n";
            else break;
        }
        if(choice == 1){
            int payment;
            while(true){
                cout<<"Please choose your preferred payment method for this ride:\n";
                for(int i=0;i<passenger.payment_methods.size();i++){
                    cout<<"("<<i+1<<")"<<passenger.payment_methods[i]<<endl;
                }
                cin>>payment;
                if(payment < 1 || payment > passenger.payment_methods.size())cout<<"Invalid!\n";
                else break;
            }
            potential_order.insert_into_database();
            cout<<"Your order has been placed successfully!\n";
        }
        else {
            cout<<"Your order has been cancelled\n";
        }
    }

    void request_current_location(){
        float randomX, randomY, randomSign;
        randomSign = rand()%2 == 1? 1:-1;
        randomX = ((large_random()%1000000)/1000.0)*randomSign;
        randomY = ((large_random()%1000000)/1000.0)*randomSign;
        cout<<"Your current location is: " + passenger.current_location()<<endl;
        cout<<"At coordinates: " + to_string(randomX) + " , " +to_string(randomY) + "\n";
    }

    int large_random(){
        return rand() * rand();
    }
};
