#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
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
    if (dbExist(dbName))
    {
        return "Database already exist !";
    }

    const std::string backupPath = "config/blank_files/blank_database.txt";
    const std::string newPath = "config/databases/" + dbName + ".txt";
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
    if (dbExist(databaseName))
    {
        if (checkIfPlayerExistInDatabase(databaseName, playerName))
        {
            return "ERROR PLAYER IS ALREADY IN DATABASE";
        }
    }
    else {
        return "NO DATABASE.";
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

    file << "   heures { " << std::endl;
    file << "       allTime = " << std::endl;
    file << "       dayTime = " << std::endl;
    file << "       nightTime = " << std::endl;
    file << "       totalAA = " << std::endl;
    file << "       totalAG = " << std::endl;
    file << "   }" << std::endl;

    file << "   caseIDeparture = " << std::endl;
    file << "   caseIIorIIIDeparture = " << std::endl;
    file << "   caseIArrival = " << std::endl;
    file << "   caseIIorIIIArrival = " << std::endl;
    file << "   bvr = " << std::endl;
    file << "   bfm = " << std::endl;
    file << "   AAGuns = " << std::endl;
    file << "   intercept = " << std::endl;
    file << "   dayAAR = " << std::endl;
    file << "   nightAAR = " << std::endl;
    file << "   laserGuidedBombs = " << std::endl;
    file << "   unguidedBombs = " << std::endl;
    file << "   tald = " << std::endl;
    file << "   rockets = " << std::endl;
    file << "   AGGuns = " << std::endl;
    file << "   tacturn = " << std::endl;
    file << "   training = " << std::endl;
    file << "   missions = " << std::endl;
    file << "}" << std::endl << std::endl;;
    file.close();

    return "OK";
}

std::string database::removePlayerFromDatabase(std::string databaseName, std::string playerName)
{
    if (dbExist(databaseName))
    {
        if (!checkIfPlayerExistInDatabase(databaseName, playerName))
        {
            return "ERROR PLAYER IS NOT IN DATABASE";
        }
    }
    else {
        return "NO DATABASE.";
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

std::string database::loadPlayer(std::string databaseName, std::string playerName)
{
    if (dbExist(databaseName))
    {
        if (!checkIfPlayerExistInDatabase(databaseName, playerName))
        {
            return "ERROR PLAYER IS NOT IN DATABASE";
        }
    }
    else {
        return "NO DATABASE.";
    }

    std::ifstream file;
    file.open(("config/databases/" + databaseName + ".txt").c_str());
    if (!file.is_open())
    {
        return ("ERROR CAN'T OPEN DATABASE " + databaseName + ".");
    }

    std::string line;
    bool playerFound = false;
    int playerLineCounter = 0;
    int endLineOfInformations = 0;
    
    while (std::getline(file, line))
    {
        if (playerFound == false && (line == playerName + " {"))
        {
            playerFound = true;
        }
        if (playerFound)
        {
            playerLineCounter++;
            if (line == "   }")
            {
                endLineOfInformations = playerLineCounter;
                endLineOfInformations++;
                break;
            }
        }
    }
    
    playerLineCounter = 0;
    file.close();
    file.open(("config/databases/" + databaseName + ".txt").c_str());

    while (std::getline(file, line))
    {
        if (playerFound == false && (line == playerName + " {"))
        {
            playerFound = true;
        }
        if (playerFound)
        {
            std::cout << line << " " << playerLineCounter << std::endl;

            if (playerLineCounter > 3 && playerLineCounter < endLineOfInformations) // Aditionnal informations
            {
                player.informations.push_back(line.substr(7, line.length() - 7));
            }
            if (playerLineCounter == endLineOfInformations + 2) { // allTime
                player.allTime = stod(line.substr(17, line.length() - 17));
            }
            else if (playerLineCounter == endLineOfInformations + 3) { // dayTime
                player.dayTime = stod(line.substr(17, line.length() - 17));
            }
            else if (playerLineCounter == endLineOfInformations + 4) { // nightTime
                player.nightTime = stod(line.substr(19, line.length() - 19));
            }
            else if (playerLineCounter == endLineOfInformations + 5) { // totalAA
                player.totalAA = stod(line.substr(17, line.length() - 17));
            }
            else if (playerLineCounter == endLineOfInformations + 6) { // totalAG
                player.totalAG = stod(line.substr(17, line.length() - 17));
            }
            else if (playerLineCounter == endLineOfInformations + 8) { // caseIDeparture
                player.caseIDeparture = line.substr(21, line.length() - 21);
            }
            else if (playerLineCounter == endLineOfInformations + 9) { // caseIIorIIIDeparture
                player.caseIIorIIIDeparture = line.substr(27, line.length() - 27);
            }
            else if (playerLineCounter == endLineOfInformations + 10) { // caseIArrival
                player.caseIArrival = line.substr(19, line.length() - 19);
            }
            else if (playerLineCounter == endLineOfInformations + 11) { // caseIIorIIIArrival
                player.caseIIorIIIArrival = line.substr(25, line.length() - 25);
            }
            else if (playerLineCounter == endLineOfInformations + 12) { // bvr
                player.bvr = line.substr(10, line.length() - 10);
            }
            else if (playerLineCounter == endLineOfInformations +13) { // bfm
                player.bfm = line.substr(10, line.length() - 10);
            }
            else if (playerLineCounter == endLineOfInformations + 14) { // AAGuns
                player.AAGuns = line.substr(13, line.length() - 13);
            }
            else if (playerLineCounter == endLineOfInformations + 15) { // intercept
                player.intercept = line.substr(16, line.length() - 16);
            }
            else if (playerLineCounter == endLineOfInformations + 16) { // dayAAR
                player.dayAAR = line.substr(13, line.length() - 13);
            }
            else if (playerLineCounter == endLineOfInformations + 17) { // nightAAR
                player.nightAAR = line.substr(15, line.length() - 15);
            }
            else if (playerLineCounter == endLineOfInformations + 18) { // laserGuidedBombs
                player.laserGuidedBombs = line.substr(23, line.length() - 23);
            }
            else if (playerLineCounter == endLineOfInformations + 19) { // unguidedBombs
                player.unguidedBombs = line.substr(20, line.length() - 20);
            }
            else if (playerLineCounter == endLineOfInformations + 20) { // tald
                player.tald = line.substr(11, line.length() - 11);
            }
            else if (playerLineCounter == endLineOfInformations + 21) { // rockets
                player.rockets = line.substr(14, line.length() - 14);
            }
            else if (playerLineCounter == endLineOfInformations + 22) { // AGGuns
                player.AGGuns = line.substr(13, line.length() - 13);
            }
            else if (playerLineCounter == endLineOfInformations + 23) { // tacturn
                player.tacturn = line.substr(14, line.length() - 14);
            }
            else if (playerLineCounter == endLineOfInformations + 24) { // training
                player.training = line.substr(15, line.length() - 15);
            }
            else if (playerLineCounter == endLineOfInformations + 25) { // missions
                player.missions = line.substr(15, line.length() - 15);
            }
            playerLineCounter++;
        }
        if (line == "}")
        {
            playerFound = false;
            break;
        }
    }
    file.close();
    return "OK";
}

bool database::checkIfPlayerExistInDatabase(std::string databaseName, std::string playerName)
{
    if (!dbExist(databaseName))
    {
        return "NO DATABASE.";
    }
    
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
                break;
            }
        }
    }
    return false;
}

std::string database::addAnHourInDatabase(std::string databaseName, std::string playerName, std::string parameter, int nbHour)
{
    if (dbExist(databaseName))
    {
        if (!checkIfPlayerExistInDatabase(databaseName, playerName))
        {
            return "ERROR PLAYER IS NOT IN DATABASE";
        }
    }
    else {
        return "NO DATABASE.";
    }
    
    std::string test = loadPlayer(databaseName, playerName);
    std::cout << test << std::endl;

    return "OK";
}

std::string database::getNewDate()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    return std::to_string(ltm->tm_mday) + "/" + std::to_string(ltm->tm_mon + 1) + "/" + std::to_string(1900 + ltm->tm_year);
}