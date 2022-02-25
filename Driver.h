#include "Car.h"

int car_rates[4] = {1, 2, 3, 4};

class Driver{
public:
    string name;
    string username;
    string password;
    float rating;
    bool status;
    pair<float,float>currentCoordinates;

    Driver(){};

    Driver(string username){
        this->username = username;
        Session ses("SQLite", "database.db");
        ses<<"SELECT name, password, rating, status, currentX, currentY FROM Drivers WHERE username = ?",
        into(name), into(password), into(rating), into(status), into(currentCoordinates.first),
        into(currentCoordinates.second), use(username), now;
    }

    Driver(string name, string username, string password, float rating){
                this->name = name;
                this->username = username;
                this->password = password;
                this->rating = rating;
                this->status = 0;
                this->currentCoordinates.first = 0.0;
                this->currentCoordinates.second = 0.0;

                Session ses("SQLite","database.db");
                ses<<"INSERT INTO Drivers (name, username, password, rating, status, currentX, currentY) VALUES (?,?,?,?,?,?,?)",
                use(name), use(username), use(password), use(rating), use(status), 
                use(currentCoordinates.first), use(currentCoordinates.second), now;

           }
    
    void update_driver_info(){
        Session ses("SQLite","database.db");
        ses<<"UPDATE Drivers SET name = ?, password = ?, rating = ?, status = ?, currentX = ?, currentY = ? WHERE username = ?",
        use(name), use(password), use(rating),
        use(status), use(currentCoordinates.first),
        use(currentCoordinates.second), use(username), now; 
    }

    void update_status(int status){
        this->status = status;
        update_driver_info();
    }

    void parkRightInFrontOfTheEntrance(){
        std::vector<int> ids = this->car_ids();
        bool business = 0;
        for(int i=0;i<ids.size();i++){
            Car temp_car = (*new Car(ids[i]));
            if(temp_car.carType == 3) business = 1;
        }
        if(!business) return;
        int randomSign = rand()%2 == 1? 1:-1;
        this->currentCoordinates.first = ((large_random()%1000000)/1000.0)*randomSign;
        this->currentCoordinates.second = ((large_random()%1000000)/1000.0)*randomSign;
        update_driver_info();
    }

    int large_random(){
        return rand() * rand();
    }
    
    std::vector<int> car_ids(){
        std::vector<int> temp;

        Session ses("SQLite","database.db");
        ses<<"SELECT id FROM Cars WHERE ownedBy = ?",
        use(username), into(temp), now;
        return temp;
    }

    string driver_car_info(){
        string info;
        std::vector<int> ids = this->car_ids();
        for(int i=0;i<ids.size();i++){
            info += "CAR :\n";
            Car temp_car = (*new Car(ids[i]));
            info += temp_car.car_info();
        }
        return info;
    }

    static bool username_conflict(string user){
        Session ses("SQLite","database.db");
        int found = 0;
        ses<<"SELECT 1 FROM Drivers WHERE username = ?",
        use(user), into(found), now;
        return found;
    }

    static bool check_if_banned(string user){
        int banned = 0;
        Session ses("SQLite", "database.db");
        ses<<"SELECT 1 FROM BannedUsers WHERE username = ?",
        use(user), into(banned), now;
        return banned;
    }

    static bool driver_login_successful(string user, string pass){
        Session ses("SQLite","database.db");
        int login_verdict = 0;
        ses<<"SELECT 1 from Drivers WHERE username = ? and password = ?",
        use(user), use(pass), into(login_verdict), now;
        return login_verdict;
    }
};