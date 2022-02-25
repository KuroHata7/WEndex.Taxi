#include "Admin.h"
#include "Passenger.h"
class AdminGateway{
    Admin admin;
    bool logged_in = false;
public:
    AdminGateway(){}

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
                admin_login();
                if(logged_in)break;
            }
            else if(choice == 2) admin_register();
            else if(choice == 0) return;
            else cout<<"Invalid!\n";
        }
        while(true){
            cout<<"Welcome " + admin.username + " what would you like to do:\n"
                <<"(1) View order history\n"
                <<"(2) View driver list\n"
                <<"(3) View passenger list\n"
                <<"(4) Ban a driver\n"
                <<"(5) Unban a dirver\n"
                <<"(6) Ban a passenger\n"
                <<"(7) Unban a passenger\n"
                <<"(8) View all cars\n"
                <<"(9) Validate new cars\n"
                <<"(0) Logout\n";
            int choice;
            cin>>choice;
            if(choice == 1) view_order_history();
            else if(choice == 2) view_driver_list();
            else if(choice == 3) view_passenger_list();
            else if(choice == 4) ban_driver();
            else if(choice == 5) unban_driver();
            else if(choice == 6) ban_passenger();
            else if(choice == 7) unban_passenger();
            else if(choice == 8) view_all_cars();
            else if(choice == 9) view_new_cars();
            else if(choice == 0) {
                admin_logout();
                break;
            }
            else cout<<"Invalid\n";
        }
    }

    void admin_login(){
        while(true){
            cout<<"Please enter your username:\n";
            string user;
            cin>>user;
            cout<<"Please enter your password:\n";
            string pass;
            cin>>pass;
            if(Admin::admin_login_successful(user,pass)){
                admin = (*new Admin(user));
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

    void admin_register(){
        cout<<"Please enter your first and last name separated by a space:\n";
        string name;
        cin.ignore();
        getline(cin,name);
        string username;
        while(true){
            cout<<"Please enter your desired username (no spaces):\n";
            cin>>username;
            if(Admin::username_conflict(username)){
                cout<<"Username already exists. Please choose a different username:\n";
            }
            else {break;}
        }
        cout<<"Please enter your desired password (no spaces):\n";
        string password;
        cin>>password;
        admin = (*new Admin(name,username,password));
        cout<<"You have been successfully registered!\n";
        logged_in = true;
    }

    void admin_logout(){
        admin = (*new Admin());
        logged_in = false;
        cout<<"You have been successfully logged out\n";
        main_menu();
    }

    void view_order_history(){
        std::vector<Order>orders = admin.order_history();
        for(auto i : orders){
            cout<<i.order_info()<<endl;
        }
    }

    void view_driver_list(){
        std::vector<string>drivers = admin.driver_list();
        for(int i=0;i<drivers.size();i++){
            cout<<"DRIVER " + to_string(i+1) + " :" + drivers[i]<<endl;
        }
    }

    void view_passenger_list(){
        std::vector<string>passengers = admin.passenger_list();
        for(int i=0;i<passengers.size();i++){
            cout<<"PASSENGER " + to_string(i+1) + " :" + passengers[i]<<endl;
        }
    }

    void ban_driver(){
        while(true)
        {
            cout<<"Please enter the driver's username:\n";
            string user;
            cin>>user;
            if(Driver::username_conflict(user)){
                admin.ban_user(user);
                cout<<"User has been banned from taking orders.\n";
                break;
            }
            else{
                cout<<"Username does not exist. Please try again.\n";
            }
        }
    }

    void unban_driver(){
        while(true)
        {
            cout<<"Please enter the driver's username:\n";
            string user;
            cin>>user;
            if(Driver::username_conflict(user)){
                admin.unban_user(user);
                cout<<"User has been unbanned.\n";
                break;
            }
            else{
                cout<<"Username does not exist. Please try again.\n";
            }
        }
    }

    void ban_passenger(){
        while(true)
        {
            cout<<"Please enter the passenger's username:\n";
            string user;
            cin>>user;
            if(Passenger::username_conflict(user)){
                admin.ban_user(user);
                cout<<"User has been banned from placing orders.\n";
                break;
            }
            else{
                cout<<"Username does not exist. Please try again.\n";
            }
        }
    }

    void unban_passenger(){
        while(true)
        {
            cout<<"Please enter the passenger's username:\n";
            string user;
            cin>>user;
            if(Passenger::username_conflict(user)){
                admin.unban_user(user);
                cout<<"User has been unbanned.\n";
                break;
            }
            else{
                cout<<"Username does not exist. Please try again.\n";
            }
        }
    }

    void view_all_cars(){
        cout<<Car::list_all_cars();
    }

    void view_new_cars(){
        std::vector<int>ids = Car::all_car_ids();
        while(true){
            cout<<Car::list_new_cars()<<endl;
            cout<<"Please enter the ID of the car you wish to validate:\n";
            int id;
            cin>>id;
            if(find(ids.begin(),ids.end(),id) != ids.end()){
                admin.validate_car(id);
                cout<<"Car has been validated successfully.\n";
                break;
            }
            else{
                cout<<"Car ID does not exist. Please try again.\n";
            }
        }
    }
};