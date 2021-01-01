#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>

class database
{
public:
	std::vector<std::string> getAllAvailableDatabases();
	std::string addDatabase(std::string dbName);
	std::string deleteDatabase(std::string dbName);
	std::string addPlayerToDatabase(std::string databaseName, std::string playerName, std::vector<std::string> playerInformations);
	std::string removePlayerFromDatabase(std::string databaseName, std::string playerName);

private:
	bool dbExist(const std::string name);
	bool checkIfPlayerExistInDatabase(std::string databaseName, std::string playerName);
};

#endif
