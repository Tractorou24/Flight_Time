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
    file << "       allTime = 0.0" << std::endl;
    file << "       dayTime = 0.0" << std::endl;
    file << "       nightTime = 0.0" << std::endl;
    file << "       totalAA = 0.0" << std::endl;
    file << "       totalAG = 0.0" << std::endl;
    file << "   }" << std::endl;

    file << "   caseIDeparture = 01/01/2000" << std::endl;
    file << "   caseIIorIIIDeparture = 01/01/2000" << std::endl;
    file << "   caseIArrival = 01/01/2000" << std::endl;
    file << "   caseIIorIIIArrival = 01/01/2000" << std::endl;
    file << "   bvr = 01/01/2000" << std::endl;
    file << "   bfm = 01/01/2000" << std::endl;
    file << "   AAGuns = 01/01/2000" << std::endl;
    file << "   intercept = 01/01/2000" << std::endl;
    file << "   dayAAR = 01/01/2000" << std::endl;
    file << "   nightAAR = 01/01/2000" << std::endl;
    file << "   laserGuidedBombs = 01/01/2000" << std::endl;
    file << "   unguidedBombs = 01/01/2000" << std::endl;
    file << "   tald = 01/01/2000" << std::endl;
    file << "   rockets = 01/01/2000" << std::endl;
    file << "   AGGuns = 01/01/2000" << std::endl;
    file << "   tacturn = 01/01/2000" << std::endl;
    file << "   training = 01/01/2000" << std::endl;
    file << "   missions = 01/01/2000" << std::endl;
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

std::string database::addAnHourInDatabase(std::string databaseName, std::string playerName, std::string parameter, double nbHour)
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

    loadPlayer(databaseName, playerName);
    if (parameter == "allTime")
    {
        player.allTime += nbHour;
    }
    else if (parameter == "dayTime")
    {
        player.dayTime += nbHour;
    }
    else if (parameter == "nightTime")
    {
        player.nightTime += nbHour;
    }
    else if (parameter == "totalAA")
    {
        player.totalAA += nbHour;
    }
    else if (parameter == "totalAG")
    {
        player.totalAG += nbHour;
    }
    updatePlayer(databaseName, playerName);

    return "OK";
}

std::string database::addADateInDatabase(std::string databaseName, std::string playerName, std::string parameter, std::string date)
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

    loadPlayer(databaseName, playerName);
    if (parameter == "caseIDeparture")
    {
        player.caseIDeparture = date;
    }
    else if (parameter == "caseIIorIIIDeparture")
    {
        player.caseIIorIIIDeparture = date;
    }
    else if (parameter == "caseIArrival")
    {
        player.caseIArrival = date;
    }
    else if (parameter == "caseIIorIIIArrival")
    {
        player.caseIIorIIIArrival = date;
    }
    else if (parameter == "bvr")
    {
        player.bvr = date;
    }
    else if (parameter == "bfm")
    {
        player.bfm = date;
    }
    else if (parameter == "AAGuns")
    {
        player.AAGuns = date;
    }
    else if (parameter == "intercept")
    {
        player.intercept = date;
    }
    else if (parameter == "dayAAR ")
    {
        player.dayAAR = date;
    }
    else if (parameter == "nightAAR ")
    {
        player.nightAAR = date;
    }
    else if (parameter == "laserGuidedBombs ")
    {
        player.laserGuidedBombs = date;
    }
    else if (parameter == "unguidedBombs ")
    {
        player.unguidedBombs = date;
    }
    else if (parameter == "tald ")
    {
        player.tald = date;
    }
    else if (parameter == "rockets ")
    {
        player.rockets = date;
    }
    else if (parameter == "AGGuns ")
    {
        player.AGGuns = date;
    }
    else if (parameter == "tacturn ")
    {
        player.tacturn = date;
    }
    else if (parameter == "training ")
    {
        player.training = date;
    }
    else if (parameter == "missions ")
    {
        player.missions = date;
    }
    updatePlayer(databaseName, playerName);

    return "OK";
}

std::string database::getNewDate()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    return std::to_string(ltm->tm_mday) + "/" + std::to_string(ltm->tm_mon + 1) + "/" + std::to_string(1900 + ltm->tm_year);
}




bool database::dbExist(const std::string name) {
    const std::string path = "config/databases/" + name + ".txt";
    if (FILE* file = fopen(path.c_str(), "r")) {
        fclose(file);
        return true;
    }
    return false;
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
                player.caseIDeparture = line.substr(20, line.length() - 20);
            }
            else if (playerLineCounter == endLineOfInformations + 9) { // caseIIorIIIDeparture
                player.caseIIorIIIDeparture = line.substr(26, line.length() - 26);
            }
            else if (playerLineCounter == endLineOfInformations + 10) { // caseIArrival
                player.caseIArrival = line.substr(18, line.length() - 18);
            }
            else if (playerLineCounter == endLineOfInformations + 11) { // caseIIorIIIArrival
                player.caseIIorIIIArrival = line.substr(24, line.length() - 24);
            }
            else if (playerLineCounter == endLineOfInformations + 12) { // bvr
                player.bvr = line.substr(9, line.length() - 9);
            }
            else if (playerLineCounter == endLineOfInformations +13) { // bfm
                player.bfm = line.substr(9, line.length() - 9);
            }
            else if (playerLineCounter == endLineOfInformations + 14) { // AAGuns
                player.AAGuns = line.substr(12, line.length() - 12);
            }
            else if (playerLineCounter == endLineOfInformations + 15) { // intercept
                player.intercept = line.substr(15, line.length() - 15);
            }
            else if (playerLineCounter == endLineOfInformations + 16) { // dayAAR
                player.dayAAR = line.substr(12, line.length() - 12);
            }
            else if (playerLineCounter == endLineOfInformations + 17) { // nightAAR
                player.nightAAR = line.substr(14, line.length() - 14);
            }
            else if (playerLineCounter == endLineOfInformations + 18) { // laserGuidedBombs
                player.laserGuidedBombs = line.substr(22, line.length() - 22);
            }
            else if (playerLineCounter == endLineOfInformations + 19) { // unguidedBombs
                player.unguidedBombs = line.substr(19, line.length() - 19);
            }
            else if (playerLineCounter == endLineOfInformations + 20) { // tald
                player.tald = line.substr(10, line.length() - 10);
            }
            else if (playerLineCounter == endLineOfInformations + 21) { // rockets
                player.rockets = line.substr(13, line.length() - 13);
            }
            else if (playerLineCounter == endLineOfInformations + 22) { // AGGuns
                player.AGGuns = line.substr(12, line.length() - 12);
            }
            else if (playerLineCounter == endLineOfInformations + 23) { // tacturn
                player.tacturn = line.substr(13, line.length() - 13);
            }
            else if (playerLineCounter == endLineOfInformations + 24) { // training
                player.training = line.substr(14, line.length() - 14);
            }
            else if (playerLineCounter == endLineOfInformations + 25) { // missions
                player.missions = line.substr(14, line.length() - 14);
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

std::string database::updatePlayer(std::string databaseName, std::string playerName)
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

    removePlayerFromDatabase(databaseName, playerName);

    std::ofstream file;
    file.open(("config/databases/" + databaseName + ".txt").c_str(), std::ios::app);
    if (!file.is_open())
    {
        return ("ERROR OPENING DATABASE " + databaseName + ".");
    }

    file << playerName + " {" << std::endl;
    file << "   informations {" << std::endl;
    for (int i = 0; i < player.informations.size(); i++)
    {
        file << "       " + (player.informations[i]) << std::endl;
    }
    file << "   }" << std::endl;

    file << "   heures { " << std::endl;
    file << "       allTime = " + std::to_string(player.allTime) << std::endl;
    file << "       dayTime = " + std::to_string(player.dayTime) << std::endl;
    file << "       nightTime = " + std::to_string(player.nightTime) << std::endl;
    file << "       totalAA = " + std::to_string(player.totalAA) << std::endl;
    file << "       totalAG = " + std::to_string(player.totalAG) << std::endl;
    file << "   }" << std::endl;

    file << "   caseIDeparture = " + player.caseIDeparture << std::endl;
    file << "   caseIIorIIIDeparture = " + player.caseIIorIIIDeparture << std::endl;
    file << "   caseIArrival = " + player.caseIArrival << std::endl;
    file << "   caseIIorIIIArrival = " + player.caseIIorIIIArrival << std::endl;
    file << "   bvr = " + player.bvr << std::endl;
    file << "   bfm = " + player.bfm << std::endl;
    file << "   AAGuns = " + player.AAGuns << std::endl;
    file << "   intercept = " + player.intercept << std::endl;
    file << "   dayAAR = " + player.dayAAR << std::endl;
    file << "   nightAAR = " + player.nightAAR << std::endl;
    file << "   laserGuidedBombs = " + player.laserGuidedBombs << std::endl;
    file << "   unguidedBombs = " + player.unguidedBombs << std::endl;
    file << "   tald = " + player.tald << std::endl;
    file << "   rockets = " + player.rockets << std::endl;
    file << "   AGGuns = " + player.AGGuns << std::endl;
    file << "   tacturn = " + player.tacturn << std::endl;
    file << "   training = " + player.training << std::endl;
    file << "   missions = " + player.missions << std::endl;
    file << "}" << std::endl << std::endl;;

    file.close();
    return "OK";
}
