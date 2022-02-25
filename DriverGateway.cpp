#include "DriverGateway.h"
int main(){
    Poco::Data::SQLite::Connector::registerConnector();
    srand(time(0));
    DriverGateway dd;
    dd.main_menu();
    return 0;
}