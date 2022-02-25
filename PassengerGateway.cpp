#include "PassengerGateway.h"
int main(){
    Poco::Data::SQLite::Connector::registerConnector();
    PassengerGateway pp;
    pp.main_menu();
    return 0;
}