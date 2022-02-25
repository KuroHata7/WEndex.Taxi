#include "Driver.h"
#include "Order.h"
string driver_status_enum[2] = {"Vacant","Busy"};

class driverBannedException : public exception {
    const char* what() const throw() {
        cout<<"Driver has been banned from taking orders\n";
    }
};

class DriverGateway {
    Driver driver;
    bool logged_in = 0;
public:
    DriverGateway(){}

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
                driver_login();
                if(logged_in)break;
            }
            else if(choice == 2) driver_register();
            else if(choice == 0) return;
            else cout<<"Invalid!\n";
        }
        while(true){
            cout<<"Welcome " + driver.username + " what would you like to do:\n"
                <<"(1) View order history\n"
                <<"(2) View car info\n"
                <<"(3) Update status\n"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
                <<"(4) View available orders\n"
                <<"(5) Add new car\n"
                <<"(0) Logout\n";
            int choice;
            cin>>choice;
            if(choice == 1) view_order_history();
            else if(choice == 2) view_car_info();
            else if(choice == 3) update_status();
            else if(choice == 4) view_available_orders();
            else if(choice == 5) add_new_car();
            else if(choice == 0) {
                driver_logout();
                break;
            }
            else cout<<"Invalid\n";
        }
    }

    void driver_login(){
        while(true){
            cout<<"Please enter your username:\n";
            string user;
            cin>>user;
            cout<<"Please enter your password:\n";
            string pass;
            cin>>pass;
            if(Driver::driver_login_successful(user,pass)){
                driver = (*new Driver(user));
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

    void driver_register(){
        cout<<"Please enter your first and last name separated by a space:\n";
        string name;
        cin.ignore();
        getline(cin,name);
        string username;
        while(true){
            cout<<"Please enter your desired username (no spaces):\n";
            cin>>username;
            if(Driver::username_conflict(username)){
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
        cout<<"Please enter your car model (e.g. \"Tesla\"):\n";
        string carModel;
        cin.ignore();
        getline(cin,carModel);
        cout<<"Please enter your car number (e.g. \"F12D34K\"):\n";
        string carNumber;
        getline(cin,carNumber);
        cout<<"Please enter your car color (e.g. \"Blue\"):\n";
        string carColor;
        getline(cin,carColor);
        int carType = -1;
        while(true){
            cout<<"Please specify your car type:\n"
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
        driver = (*new Driver(name, username, password, rating));
        Car car = (*new Car (carModel, carNumber, carColor, carType, username));
        cout<<"You have been successfully registered!\n";
        logged_in = true;
    }

    void driver_logout(){
        driver = (*new Driver());
        logged_in = false;
        cout<<"You have been successfully logged out\n";
        main_menu();
    }

    void view_order_history(){
        std::vector<Order>order_history = Order::driver_order_history(driver.username);
        if(!order_history.size()){
            cout<<"You have no previous orders\n";
        }
        for(auto order : order_history){
            cout<<order.order_info()<<endl;
        }
    }

    void view_car_info(){
        cout<<driver.driver_car_info();
    }

    void update_status(){
        cout<<"Your current status are: " + driver_status_enum[driver.status] + "\n";
        while(true)
        {
            cout<<"Would you like to change it?\n";
            cout<<"(1) Yes\n"
                <<"(2) No\n";
            int choice; 
            cin>>choice;
            if(choice == 1){driver.update_status(!driver.status);break;}
            else if(choice == 2){driver.update_status(driver.status);break;}
            else cout<<"Invalid!\n";
        }
        cout<<"Your status is now: " + driver_status_enum[driver.status] + "\n";
    }

    void view_available_orders(){
        if(Driver::check_if_banned(driver.username)){
            throw driverBannedException();
            return;
        }
        bool check_order[100005];
        memset(check_order, 0 , sizeof check_order);
        std::vector<int>car_ids = driver.car_ids();
        int car_id;
        while(true){
            cout<<"Please enter the id of the car you would like to use\n";
            cout<<driver.driver_car_info();
            cin>>car_id;
            if(find(car_ids.begin(),car_ids.end(),car_id) != car_ids.end()){
                break;
            }
            else cout<<"Invalid!\n";
        }
        Car current_car = (*new Car(car_id));
        if(!current_car.validated){
            cout<<"You car has not been validated yet. Please contanct an Admin to validate it\n";
            return;
        }
        cout<<"Here are the available orders for this car\n";
        std::vector<Order>available_orders = Order::available_orders(current_car.carType);
        for(auto order : available_orders){
            check_order[order.id] = 1;
            cout<<order.order_info()<<endl;
        }
        while(true){
            cout<<"What would you like to do:\n";
            cout<<"(1) Pick an order\n";
            cout<<"(0) Back\n";
            int choice;
            cin>>choice;
            if(choice == 1){
                if(driver.status == 1){
                    cout<<"Your status is set to \"Busy\". Please change it to \"Vacant\" before taking an order\n";
                    break;
                }
                int id;
                while(true){
                    cout<<"Please enter the ID of the order you would like to pick or \"0\" to exit:\n";
                    cin>>id;
                    if(id == 0)break;
                    if(id < 0 || !check_order[id])
                    {
                        cout<<"Invalid ID. Please try again.\n";
                    }
                    else break;
                }
                cout<<id<<endl;
                Order picked_order = (*new Order(id));
                picked_order.driverUsername = driver.username;
                picked_order.update_status(2);
                cout<<"Order has been taken successfully. Here is the bill:\n";
                cout<<picked_order.order_info()<<endl;
                if(current_car.carType == 1){
                    current_car.drink_water();
                }
                break;
            }
            else if(choice == 0)break;
            else cout<<"Invalid!\n";
        }
    }

    void add_new_car(){
        cout<<"Please enter your car model (e.g. \"Tesla\"):\n";
        string carModel;
        cin.ignore();
        getline(cin,carModel);
        cout<<"Please enter your car number (e.g. \"F12D34K\"):\n";
        string carNumber;
        getline(cin,carNumber);
        cout<<"Please enter your car color (e.g. \"Blue\"):\n";
        string carColor;
        getline(cin,carColor);
        int carType = -1;
        while(true){
            cout<<"Please specify your car type:\n"
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
        Car new_car = (*new Car (carModel, carNumber, carColor, carType, driver.username));
        cout<<"New car has been successfully added\n";
    }
};
