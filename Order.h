#include "lib.h"

string order_status_enum[] = {"Pending", "Ongoing", "Done"};
string _car_types[4] = {"Economy", "Comfort", "ComfortPlus", "Business"};

class Order{
public:
    string passengerUsername;
    string driverUsername;
    string addressFrom;
    string addressTo;
    int carType;
    float price;
    float timeTaken;
    int status;
    int id;

    Order(){}

    Order(int id){
        this->id = id;
        
        Session ses ("SQLite","database.db");
        ses<<"SELECT passengerUsername, driverUsername, addressFrom, addressTo, carType, price, timeTaken, status FROM Orders WHERE id = ?",
        into(passengerUsername), into(driverUsername), into(addressFrom), into(addressTo),
        into(carType), into(price), into(timeTaken), into(status), use(id), now;
    }

    Order(string passengerUsername, string addressFrom, string addressTo,
        int carType){
        this->passengerUsername = passengerUsername;
        this->driverUsername = "NULL";
        this->addressFrom = addressFrom;
        this->addressTo = addressTo;
        this->carType = carType;
        this->price = (rand()%10000)/100.0;
        this->timeTaken = (rand()%900)/30.0;
        this->status = 0;
        int last_id = get_max_id();
        this->id = ++last_id;
    }

    int get_max_id(){
        Session ses("SQLite","database.db");
        std::vector<int>ids;
        ses<<"SELECT id FROM Orders", into(ids), now;
        sort(ids.begin(),ids.end());
        if(!ids.size())return 0;
        else return ids.back();
    }

    void insert_into_database(){
        Session ses("SQLite","database.db");
        ses<<"INSERT INTO Orders (passengerUsername, driverUsername, addressFrom, addressTo, carType, price, timeTaken, status, id) VALUES (?,?,?,?,?,?,?,?,?)",
        use(passengerUsername), use(driverUsername), use(addressFrom), use(addressTo),
        use(carType), use(price), use(timeTaken), use(status), use(id), now;
    }

    string order_info(){
        string temp = "ORDER:\n";
                temp+= "Passenger: " + passengerUsername;
                temp+= "\nDriver: " + driverUsername; 
                temp+= "\nFrom: " + addressFrom; 
                temp+= "\nTo: " + addressTo; 
                temp+= "\nCar Type: " + _car_types[carType]; 
                temp+= "\nPrice: " + to_string(price);
                temp+= "\nTime Taken: " + to_string(timeTaken);
                temp+= "\nStatus: " + order_status_enum[status];
                temp+= "\nOrder ID: " + to_string(id);
        return temp;
    }

    void update_status(int new_status){
        this->status = new_status;
        Session ses("SQLite","database.db");
        ses<<"UPDATE Orders SET passengerUsername = ?, driverUsername = ?, addressFrom = ?, addressTo = ?, carType = ?, price = ?, timeTaken = ?, status = ? WHERE id = ?",
        use(passengerUsername), use(driverUsername), use(addressFrom), use(addressTo),
        use(carType), use(price), use(timeTaken), use(status), use(id), now;
    }

    static bool check_passenger_orders(string user){
        std::vector<int>status;
        Session ses("SQLite","database.db");
        ses<<"SELECT status from Orders WHERE passengerUsername = ?", use(user), into(status), now;
        for(int i=0;i<status.size();i++){
            if(status[i] == 0) return 1;
        }
        return 0;
    }

    static std::vector<Order> passenger_order_history(string user){
        std::vector<int> ids;
        std::vector<Order> order_history;

        Session ses ("SQLite","database.db");
        ses<<"SELECT id FROM Orders WHERE passengerUsername = ?", use(user), into(ids), now;
        for(int i=0;i<ids.size();i++)
        {
            order_history.push_back(Order(ids[i]));
        }
        return order_history;
    } 

    static std::vector<Order> driver_order_history(string user){
        std::vector<int> ids;
        std::vector<Order> order_history;

        Session ses ("SQLite","database.db");
        ses<<"SELECT id FROM Orders WHERE driverUsername = ?", use(user), into(ids), now;
        for(int i=0;i<ids.size();i++)
        {
            order_history.push_back(Order(ids[i]));
        }
        return order_history;
    }

    static std::vector<Order> available_orders(int car_type){
        std::vector<int> ids;
        std::vector<Order> order_history;
        int pending_status = 0;

        Session ses ("SQLite","database.db");
        ses<<"SELECT id FROM Orders WHERE status = ? and carType = ?", use(pending_status), use(car_type), into(ids), now;
        for(int i=0;i<ids.size();i++)
        {
            order_history.push_back(Order(ids[i]));
        }
        return order_history;
    }

    static std::vector<Order> all_orders(){
        std::vector<int> ids;
        std::vector<Order> order_history;

        Session ses ("SQLite","database.db");
        ses<<"SELECT id FROM Orders", into(ids), now;
        for(int i=0;i<ids.size();i++)
        {
            order_history.push_back(Order(ids[i]));
        }
        return order_history;
    }
};