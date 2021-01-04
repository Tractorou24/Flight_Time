#include <string>
#include <fstream>
#include <filesystem>
#include "../seeOptionsWindow/database.h"
#include <QComboBox>
#include "programSettings.h"

std::string getSelectedDatabase()
{
    std::ifstream file;
    std::string line;
    file.open("config/preferences.txt");
    if (file.is_open())
    {
        int lineCounter = 0;
        while (std::getline(file, line))
        {
            lineCounter++;
            if (lineCounter == 3)
            {
                break;
            }
        }
    }
    file.close();
    line = line.substr(20, line.length() - 20);
    
    database db;
    if (db.dbExist(line))
    {
        return line;
    }
    return "DATABASE DO NOT EXIST";
}

std::string setSelectedDatabase(std::string str)
{
    std::string line;
    std::ifstream file("config/preferences.txt");
    std::ofstream file2("temp/preferences.txt");

    if (!file.is_open() && !file2.is_open())
    {
        return "ERROR OPENING FILE";
    }

    while (std::getline(file, line))
    {
        if (line.substr(0, 20) == "selected_database = ")
        {
            file2 << "selected_database = " + str << std::endl;
        }
        else {
            file2 << line << std::endl;
        }
    }
    file.close();
    file2.close();

    remove("config/preferences.txt");
    std::filesystem::copy_file("temp/preferences.txt", "config/preferences.txt");
    remove("temp/preferences.txt");

    return "OK";
}
