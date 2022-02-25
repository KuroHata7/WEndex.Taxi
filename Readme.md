# WEndex.Taxi

This is an implementation of a digital system for a service named ***WEndex.Taxi***  which allows users to order rides and accept orders. The system supports 2 types of users: `Passengers` and `Drivers` each of which having their own independent interface to interact with the system.
The system uses a database to keep track of user accounts, payment methods, receipts, addresses, etc.

## System Description

The `2` interfaces provided to interact with the system are:

***Passenger Gateway***: The gateway first provides a `register`/`login` menu which allows the users to have personal accounts in the system which are stored in the database along with their information.

The gateway then provides different functionalities for `Passengers`:
- View order history.
- View, add and replace payment methods.
- View, add and replace pinned addresses.
- Order a ride.
- Request current coordinates.

***Driver Gateway***: The gateway also provides `drivers` with a `register`/`login` menu for the users to enter their personal information and information about their `cars`.

The gateway provides `drivers` with functionalities to interact with orders placed by `passengers`:
- View order history.
- View car info.
- Update status.
- View available orders.

>P.S.: The system provides random and somewhat ambiguous coordinates, addresses, times and prices as they were not required according to the assignment description.

>P.S.: They system does not provide any testing in `main` and it does not exist. The interface was designed to make up for it, and for ease of use/testing.


## Code Structure

 `Passenger.h`, `PassengerGateway.cpp` and `PassengerGateway.h` provide the back-end and interface for the passengers' side of the system.

 `Driver.h`, `DriverGateway.cpp` and `DriverGateway.h` provide the back-end and interface for the drivers' side of the system.

`Order.h` the implementation of `Order` class which is used by both driver and passenger gateways.

`lib.h` contains header files for simplicity.

`database.sql` and `database.db`, the scheme and database used by the system for storage.


###### New functionalities:

- Added a 3rd interface for a new user type `Admins`. The admin interface contains the following functions:

  - View order history.
  - List `driver`/`passenger` usernames.
  - ***Ban / Unban*** a `driver`/`passenger`.
  - List all `cars`.
  - ***Validate*** ***new*** `cars` before the first ride.


- A driver can now have ***multiple cars***.

- A `car` should now be ***validated*** by an `admin` before its first ride.

###### New Files:

- `Admin.h`, `AdminGateway.cpp`, `AdminGateway.h` provide the back-end and interface for the admins' side of the system.

- `Car.h` was now required as a car was previously stored along with the driver. A separate entity along with storage for cars was ensued by the new functionalities.

## Dependencies

- Latest versions of `python3`, `g++` and `cmake`.

- `conan` and `Poco` (to be explained in the next section).

## Instructions

###### Compile:

Execute the following commands in your `linux terminal` after navigating to the project directory:
- Installing and configuring `conan`:

      pip install conan

      conan profile new default --detect

      conan profile update settings.compiler.libcxx=libstdc++11 default

      mkdir build

      cd build

      conan install .. --build=missing

- `cmake` commands:

      cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

      cmake --build .

- Moving binary files and navigating to the project directory:

      cp ./bin/passengergate ../

      cp ./bin/drivergate ../

      cp ./bin/admingate ../

      cd ../

###### Run:
- Execute `passengergate` to use the `passengers` interface:

      ./passengergate

- Execute `drivergate` to use the `drivers` interface:

      ./drivergate

- Execute `admingate` to use the `admins` interface:

      ./admingate

## Contact Info

>Name: Jaffar Totanji

>Email: jaafarti@gmail.com

>Telegram: @KuroHata7
