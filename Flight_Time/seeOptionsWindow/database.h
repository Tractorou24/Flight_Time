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
	std::string addAnHourInDatabase(std::string databaseName, std::string playerName, std::string parameter, int nbHour);

private:
	bool dbExist(const std::string name);
	bool checkIfPlayerExistInDatabase(std::string databaseName, std::string playerName);
	std::string loadPlayer(std::string databaseName, std::string playerName);
	//std::string getParameterLineNumber(std::string databaseName, std::string playerName, std::string parameter);
	std::string getNewDate();

	struct playerInformations {
		std::vector<std::string> informations;

		double allTime;
		double dayTime;
		double nightTime;
		double totalAA;
		double totalAG;

		std::string caseIDeparture;
		std::string caseIIorIIIDeparture;
		std::string caseIArrival;
		std::string caseIIorIIIArrival;
		std::string bvr;
		std::string bfm;
		std::string AAGuns;
		std::string intercept;
		std::string dayAAR;
		std::string nightAAR;
		std::string laserGuidedBombs;
		std::string unguidedBombs;
		std::string tald;
		std::string rockets;
		std::string AGGuns;
		std::string tacturn;
		std::string training;
		std::string missions;
	};

	std::string modifyPlayerName;
	struct playerInformations player;
};

#endif
