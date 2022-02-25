CREATE TABLE IF NOT EXISTS Passengers(
    name TEXT NOT NULL,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL,
    rating REAL DEFAULT 3.0
);

CREATE TABLE IF NOT EXISTS PinnedAddresses(
    username TEXT NOT NULL,
    address TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS PaymentMethods(
    username TEXT NOT NULL,
    method TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS Orders(
    passengerUsername TEXT NOT NULL,
    driverUsername TEXT NOT NULL,
    addressFrom TEXT NOT NULL,
    addressTo TEXT NOT NULL,
    carType INT,
    price REAL DEFAULT 0.0,
    timeTaken REAL DEFAULT 0.0,
    status INT DEFAULT 0,
    id INT
);

CREATE TABLE IF NOT EXISTS Drivers(
    name TEXT NOT NULL,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL,
    rating REAL DEFAULT 3.0,
    status INT DEFAULT 0,
    currentX REAL DEFAULT 0.0,
    currentY REAL DEFAULT 0.0
);

CREATE TABLE IF NOT EXISTS Cars(
    carModel TEXT NOT NULL,
    carNumber TEXT NOT NULL,
    carColor TEXT NOT NULL,
    carType INT,
    waterBottleCount INT DEFAULT 0,
    ownedBy TEXT NOT NULL,
    validated INT,
    id INT
);

CREATE TABLE IF NOT EXISTS Admins(
    name TEXT NOT NULL,
    username TEXT NOT NULL,
    password TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS BannedUsers(
    username TEXT NOT NULL,
    bannedBy TEXT NOT NULL
);