#include "AdminGateway.h"
int main(){
    Poco::Data::SQLite::Connector::registerConnector();
    AdminGateway aa;
    aa.main_menu();
    return 0;
}