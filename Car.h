#include "lib.h"
string car_types[4] = {"Economy", "Comfort", "ComfortPlus", "Business"};

class Car{
public:
    string carModel;
    string carNumber;
    string carColor;
    int carType;
    int waterBottleCount;
    string ownedBy;
    int validated;
    int id;

    Car(int in_id){
        this->id = in_id;

        Session ses("SQLite","database.db");
        ses<<"SELECT carModel, carNumber, carColor, carType, waterBottleCount, ownedBy, validated, id FROM Cars WHERE id = ?",
        into(carModel), into(carNumber), into(carColor), into(carType), into(waterBottleCount),
        into(ownedBy), into(validated), into(id), use(in_id), now;
    }

    Car(string carModel, string carNumber, string carColor, int carType, string ownedBy){
            this->carModel = carModel;
            this->carNumber = carNumber;
            this->carColor = carColor;
            this->carType = carType;
            if(carType == 1)this->waterBottleCount = rand()%10;
            else this->waterBottleCount = 0;
            this->ownedBy = ownedBy;
            this->validated = 0;
            int last_id = get_max_id();
            this->id = ++last_id;
        
        Session ses("SQLite","database.db");
        ses<<"INSERT INTO Cars (carModel, carNumber, carType, carColor, waterBottleCount, ownedBy, validated, id) VALUES (?,?,?,?,?,?,?,?)",
        use(carModel), use(carNumber), use(carType), use(carColor), use(waterBottleCount),
        use(ownedBy), use(validated), use(id), now;
    }

    void update_car_info(){
        Session ses("SQLite","database.db");
        ses<<"UPDATE Cars SET carModel = ?, carNumber = ?, carType = ?, carColor = ?, waterBottleCount = ?, ownedBy = ?, validated = ? WHERE id = ?",
        use(carModel), use(carNumber), use(carType), use(carColor), use(waterBottleCount),
        use(ownedBy), use(validated), use(id), now;
    }

    int get_max_id(){
        Session ses("SQLite","database.db");
        std::vector<int>ids;
        ses<<"SELECT id FROM Cars", into(ids), now;
        sort(ids.begin(),ids.end());
        if(!ids.size())return 0;
        else return ids.back();
    }

    string car_info(){
        string info = "Model: " + carModel 
                    + "\nNumber: " + carNumber
                    + "\nColor: " + carColor
                    + "\nType: " + car_types[carType] 
                    + "\nWater Bottles: " + to_string(waterBottleCount)
                    + "\nOwner: " + ownedBy
                    + "\nValidated: " + (validated?"Yes":"No")
                    + "\nID:" + to_string(id) + "\n";
        return info;
    }

    void drink_water(){
        waterBottleCount-=(rand()%10);
        waterBottleCount = max(0,waterBottleCount);
        update_car_info();
    }

    void validate(){
        this->validated = 1;
        update_car_info();
    }

    static string list_all_cars(){
        std::vector<int>ids;
        string info;
        Session ses("SQLite","database.db");
        ses<<"SELECT id FROM Cars", into(ids), now;
        for(int i=0;i<ids.size();i++){
            Car temp = (*new Car(ids[i]));
            info += "CAR:\n";
            info += temp.car_info();
        }
        return info;
    }

    static string list_new_cars(){
        std::vector<int>ids;
        string info;
        int f = 0;
        Session ses("SQLite","database.db");
        ses<<"SELECT id FROM Cars WHERE validated = ?", use(f), into(ids), now;
        for(int i=0;i<ids.size();i++){
            Car temp = (*new Car(ids[i]));
            info += "CAR:\n";
            info += temp.car_info();
        }
        return info;
    }

    static std::vector<int> all_car_ids(){
        std::vector<int>ids;
        Session ses("SQLite","database.db");
        ses<<"SELECT id FROM Cars", into(ids), now;
        return ids;
    }
};