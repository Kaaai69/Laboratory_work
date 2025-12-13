#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <pqxx/pqxx>
#include <memory>
#include <string>
#include <fstream>

class DatabaseManager {
private:
    std::unique_ptr<pqxx::connection> conn;
    std::ofstream logFile;

    DatabaseManager();

public:

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;


    static DatabaseManager& getInstance();


    bool connect(const std::string& connStr = "host=localhost port=5432 dbname=sales_db user=postgres password=MyNewStrongPass123");


    pqxx::connection& getConnection();


    void logOperation(const std::string& operation, const std::string& details = "");


    bool initializeDatabase();

    ~DatabaseManager();
};

#endif