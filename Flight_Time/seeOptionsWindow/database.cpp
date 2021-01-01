#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include "database.h"

std::vector<std::string> database::getAllAvailableDatabases()
{
    std::vector<std::string> dbList;
    std::string path = "config/databases";
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        std::string str = entry.path().u8string();
        str = str.substr(17, str.size() - 21);
        dbList.push_back(str);
    }
    return dbList;
}

std::string database::addDatabase(std::string dbName)
{
    const std::string backupPath = "config/blank_files/blank_database.txt";
    const std::string newPath = "config/databases/" + dbName + ".txt";
    if (dbExist(dbName))
    {
        return "Database already exist !";
    }
    std::filesystem::copy_file(backupPath, newPath);
    return "OK";
}

std::string database::deleteDatabase(std::string dbName)
{
    if (!dbExist(dbName))
    {
        return "Database do not exist.";
    }
    std::string str = "config/databases/" + dbName + ".txt";
    remove(str.c_str());
    return "OK";
}

bool database::dbExist(const std::string name) {
    const std::string path = "config/databases/" + name + ".txt";
    if (FILE* file = fopen(path.c_str(), "r")) {
        fclose(file);
        return true;
    }
    return false;
}

std::string database::addPlayerToDatabase(std::string databaseName, std::string playerName, std::vector<std::string> playerInformations)
{
    if (checkIfPlayerExistInDatabase(databaseName, playerName))
    {
        return "ERROR PLAYER ALREADY EXIST IN DATABASE";
    }

    std::ofstream file;
    file.open(("config/databases/" + databaseName + ".txt").c_str(), std::ios::app);
    if (!file.is_open())
    {
        return ("ERROR OPENING DATABASE " + databaseName + ".");
    }

    file << playerName + " {" << std::endl;
    file << "   informations {" << std::endl;
    for (int i = 0; i < playerInformations.size(); i++)
    {
        file << "       " + (playerInformations[i]) << std::endl;
    }
    file << "   }" << std::endl;
    file << "   caseIDeparture = " << std::endl;
    file << "   caseII / IIIDeparture = " << std::endl;
    file << "   caseIArrival = " << std::endl;
    file << "   caseII / IIIArrival = " << std::endl;
    file << "   bvr = " << std::endl;
    file << "   bfm = " << std::endl;
    file << "   A/AGuns = " << std::endl;
    file << "   intercept = " << std::endl;
    file << "   dayAAR = " << std::endl;
    file << "   night AAR = " << std::endl;
    file << "   laserGuidedBombs = " << std::endl;
    file << "   unguidedBombs = " << std::endl;
    file << "   tald = " << std::endl;
    file << "   rockets = " << std::endl;
    file << "   A/GGuns = " << std::endl;
    file << "   tacturn = " << std::endl;
    file << "   training = " << std::endl;
    file << "   missions = " << std::endl;
    file << "}" << std::endl << std::endl;;
    file.close();

    return "OK";
}

std::string database::removePlayerFromDatabase(std::string databaseName, std::string playerName)
{
    if (!checkIfPlayerExistInDatabase(databaseName, playerName))
    {
        return "ERROR PLAYER IS NOT IN DATABASE";
    }

    std::ifstream file;
    file.open(("config/databases/" + databaseName + ".txt").c_str());
    if (!file.is_open())
    {
        return ("ERROR CAN'T OPEN DATABASE " + databaseName + ".");
    }

    std::string line;
    std::ofstream outfile("temp/tempDB.txt");
    bool stopDeleting = true;
    while (std::getline(file, line))
    {
        if (line != (playerName + " {") && stopDeleting == true)
        {
            outfile << line << std::endl;
            std::cout << line << std::endl;
        }
        else {
            stopDeleting = false;
            if (line == "")
            {
                stopDeleting = true;
            }
        }
    }
    file.close();
    outfile.close();

    const std::string backupPath = "temp/tempDB.txt";
    const std::string newPath = "config/databases/VF84.txt";
    std::remove(newPath.c_str());
    std::filesystem::copy_file(backupPath, newPath);
    std::remove(backupPath.c_str());

    return "OK";
}

bool database::checkIfPlayerExistInDatabase(std::string databaseName, std::string playerName)
{
    std::ifstream file;
    file.open(("config/databases/" + databaseName + ".txt").c_str());
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line == (playerName + " {"))
            {
                return true;
            }
        }
    }
    return false;
}
