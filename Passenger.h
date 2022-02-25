#include "lib.h"

string location_enum[5] = {"Home", "Work", "University", "Restaurant", "Park"};

class Passenger{
public:
    string name;
    string username;
    string password;
    std::vector<string>payment_methods;
    std::vector<string>pinned_addresses;
    float rating;

    Passenger(){}

    Passenger(string username){
        this->username = username;
        Session ses("SQLite","database.db");
        ses<<"SELECT name, password, rating FROM Passengers WHERE username = ?",
        use(username), into(name), into(password), into(rating), now;
        ses<<"SELECT method FROM PaymentMethods WHERE username = ?",
        use(username), into(payment_methods), now;
        ses<<"SELECT address FROM PinnedAddresses WHERE username = ?",
        use(username), into(pinned_addresses), now;
    }

    Passenger(string name, string username, string password, float rating){
        this->name = name;
        this->username = username;
        this->password = password;
        this->rating = rating;
        payment_methods.push_back("Cash");
        pinned_addresses.push_back("Home");
        Session ses("SQLite","database.db");
        ses<<"INSERT INTO Passengers (name, username, password, rating) VALUES (?, ?, ?, ?)",
        use(name), use(username), use(password), use(rating), now;
        ses<<"INSERT INTO PaymentMethods (username,method) VALUES (?, ?)",
        use(username), use(payment_methods), now;
        ses<<"INSERT INTO PinnedAddresses (username,address) VALUES (?, ?)",
        use(username), use(pinned_addresses), now;
    }

    void update_payment_methods(){
        Session ses("SQLite","database.db");
        ses<<"DELETE FROM PaymentMethods WHERE username = ?",
         use(username), now;
        for(auto method : payment_methods){
            ses<<"INSERT INTO PaymentMethods (username, method) VALUES (?, ?)",
            use(username), use(method), now;
        }
    }

    string current_location(){
        int random_location = rand()%5;
        return location_enum[random_location];
    }

    void set_payment_methods(std::vector<string> added_payment_methods){
        payment_methods.clear();
        payment_methods = added_payment_methods;
        update_payment_methods();
    }

    void add_payment_method(string method){
        payment_methods.push_back(method);
        update_payment_methods();
    }

    void update_pinned_addresses(){
        Session ses("SQLite","database.db");
        ses<<"DELETE FROM PinnedAddresses WHERE username = ?",
         use(username), now;
        for(auto address : pinned_addresses){
            ses<<"INSERT INTO PinnedAddresses (username, address) VALUES (?, ?)",
            use(username), use(address), now;
        }
    }

    void set_pinned_addresses(std::vector<string> added_pinned_addresses){
        pinned_addresses.clear();
        pinned_addresses = added_pinned_addresses;
        update_pinned_addresses();
    }

    void pin_new_address(string address){
        pinned_addresses.push_back(address);
        update_pinned_addresses();
    }

    static bool username_conflict(string user){
        Session ses("SQLite","database.db");
        int found = 0;
        ses<<"SELECT 1 from Passengers WHERE username = ?",
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

    static bool passenger_login_successful(string user, string pass){
        Session ses("SQLite","database.db");
        int login_verdict = 0;
        ses<<"SELECT 1 from Passengers WHERE username = ? and password = ?",
        use(user), use(pass), into(login_verdict), now;
        return login_verdict;
    }
};