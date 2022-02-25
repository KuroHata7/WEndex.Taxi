#include "Order.h"
#include "Driver.h"
class Admin{
public:
    string name;
    string username;
    string password;

    Admin(){}

    Admin(string username){
        this->username = username;
        Session ses ("SQLite","database.db");
        ses<<"SELECT name, password FROM Admins WHERE username = ?",
        use(username), into(name), into(password), now;
    }

    Admin(string name, string username, string password){
        this->name = name;
        this->username = username;
        this->password = password;
        Session ses("SQLite","database.db");
        ses<<"INSERT INTO Admins (name, username, password) VALUES (?,?,?)",
        use(name), use(username), use(password), now;
    }

    void ban_user(string user){
        Session ses("SQLITE", "database.db");
        ses<<"INSERT INTO BannedUsers (username, bannedBy) VALUES (?,?)",
        use(user), use(username), now;
    }

    void unban_user(string user){
        Session ses("SQLite", "database.db");
        ses<<"DELETE FROM BannedUsers WHERE username = ?",
        use(user), now;
    }

    void validate_car(int id){
        Car temp = (*new Car(id));
        temp.validate();
    }

    std::vector<string> passenger_list(){
        std::vector<string>temp;
        Session ses("SQLite","database.db");
        ses<<"SELECT username FROM Passengers",
        into(temp), now;
        return temp;
    }

    std::vector<string> driver_list(){
        std::vector<string>temp;
        Session ses("SQLite","database.db");
        ses<<"SELECT username FROM Drivers",
        into(temp), now;
        return temp;
    }

    std::vector<Order> order_history(){
        return Order::all_orders();
    }

    /*static bool check_if_banned(string user){
        int banned = 0;
        Session ses("SQLite", "database.db");
        ses<<"SELECT 1 FROM BannedUsers WHERE username = ?",
        use(user), into(banned), now;
        return banned;
    }*/

    static bool username_conflict(string user){
        Session ses("SQLite","database.db");
        int found = 0;
        ses<<"SELECT 1 from Admins WHERE username = ?",
        use(user), into(found), now;
        return found;
    }

    static bool admin_login_successful(string user, string pass){
        Session ses("SQLite","database.db");
        int login_verdict = 0;
        ses<<"SELECT 1 from Admins WHERE username = ? and password = ?",
        use(user), use(pass), into(login_verdict), now;
        return login_verdict;
    }
};