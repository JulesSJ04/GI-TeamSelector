#include "box.h"
#include "character.h"

Box::Box()
{
    this->loadExistingCharacters();
    this->m_got_loaded = this->loadCharacters();
    this->getCharacterDifference();
}

/******************************************************************************************************************************
* FILE MANIPULATION
******************************************************************************************************************************/

void Box::loadExistingCharacters(){
    std::string file_path = "./datas/global_characters.txt";
    // Ouvrir le fichier
    try {
        std::ifstream input_file;
        input_file.open(file_path);
        if (!input_file.is_open()) {
            throw std::runtime_error("Unable to open file.");
        }
        // Variables à récupérer
        std::string line;
        std::string name;
        Element element;
        while (std::getline(input_file, line)) {
            std::istringstream iss(line);
            std::string data;
            // Name
            std::getline(iss, data, ',');
            name = data;
            // Element
            std::getline(iss, data, ',');
            element = static_cast<Element>(std::stoi(data));
            // Ajouter le character à la map
            m_existing_characters[name] = element;
        }
        input_file.close();
        
        std::cout << std::to_string(this->m_existing_characters.size()) 
            <<" characters successfully loaded into database" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
    }
}

bool Box::loadCharacters(){
    // Récupérer le chemin actuel du fichier
    std::string file_path = "./datas/my_characters.txt";
    // Ouvrir le fichier
    try {
        std::ifstream input_file;
        input_file.open(file_path);
        if (!input_file.is_open()) {
            throw std::runtime_error("Unable to open file.");
        }
        // Variables à récupérer
        std::string line;
        std::string name;
        Element element;
        Character_role role;
        bool has_stuff;
        
        while (std::getline(input_file, line)) {
            std::istringstream iss(line);
            std::string data;
            // Name
            std::getline(iss, data, ',');
            name = data;
            // Role
            std::getline(iss, data, ',');
            role = static_cast<Character_role>(std::stoi(data));
            // Element
            std::getline(iss, data, ',');
            element = static_cast<Element>(std::stoi(data));
            // Has_stuff
            std::getline(iss, data, ',');
            has_stuff = ToF(std::stoi(data));
            // Ajouter le character à la map
            this->m_characters[name] = Character(name, role, element, has_stuff);
        }
        input_file.close();
        
        std::cout << std::to_string(this->m_characters.size()) 
            <<" characters successfully loaded" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
        return false;
    }
    return false;
}

void Box::writeToFile(Character c) {
    std::string file_path = "./datas/my_characters.txt";
    try {
        std::ofstream outputFile(file_path, std::ios::app);
        if(!outputFile.is_open()) {
            throw std::runtime_error("Unable to open file.");
        }
        else {
            std::string name = c.getName();
            std::string element = std::to_string(static_cast<int>(c.getElement()));
            std::string role = std::to_string(static_cast<int>(c.getRole()));
            std::string build = std::to_string(int(c.hasBuild()));
            std::string line = name + "," + role + "," + element + "," + build;
            outputFile << line << std::endl;
            outputFile.close();
        }
    } catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
    }  
}

void Box::writeMultipleCharacterToFile() {
    std::string file_path = "./datas/my_characters.txt";
    try {
        std::ofstream outputFile(file_path, std::ios::app);
        if(!outputFile.is_open()) {
            throw std::runtime_error("Unable to open file.");
        }
        else {
            for (auto elem: this->m_characters) {
                std::string name = elem.second.getName();
                std::string element = std::to_string(static_cast<int>(elem.second.getElement()));
                std::string role = std::to_string(static_cast<int>(elem.second.getRole()));
                std::string build = std::to_string(int(elem.second.hasBuild()));
                std::string line = name + "," + role + "," + element + "," + build;
                outputFile << line << std::endl;
            }
            outputFile.close();
        }
    } catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
    }
}

bool Box::resetCharacterFile() {
    std::string file_path = "./datas/my_characters.txt";
    try {
        std::ofstream outputFile(file_path, std::ios::trunc);
        if (!outputFile.is_open()) {
            throw std::runtime_error("Unable to open file for reset.");
        } else {
            outputFile.close();
            printSystem("File reset successfully.");
            return true;
        }
    } catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
        return false;
    }
    return false;
}

void Box::removeCharacterFromMyBox() {
    const std::string filename = "./datas/my_characters.txt";

    // Read the file into a vector of strings
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
}

void Box::updateFileData() {
    // Reset le file
    bool is_reset = this->resetCharacterFile();
    if (!is_reset) {
        printRestriction(" Update failed ");
        return;
    }
    // Ecrire tous les personnages de nouveau
    this->writeMultipleCharacterToFile();
}

/******************************************************************************************************************************
* DISPLAYS
******************************************************************************************************************************/

void Box::displayBox() const {
    if (this->m_characters.empty() != true){
        for (const auto& elem: this->m_characters){
            elem.second.displayCharacter();
        }
    } else {
        printRestriction<std::string>("No characters have been loaded/created yet");
        return;
    }
    printMessage<std::string>(std::to_string(this->m_characters.size()) + " / " + std::to_string(this->m_existing_characters.size()) +" characters are in your box");
}

void Box::displayExistingCharacters() const {
    std::cout << "All the existing characters are :" << std::endl;
    for (const auto &elem: this->m_existing_characters) {
        std::cout << "Character " << elem.first << " is " << elementToString(elem.second) << std::endl;
    }
}

void Box::displayNonAddedCharacters() const {
    printMessage<std::string>(" Non added characters are : ");
    for (const auto &elem: this->m_non_added_characters) {
        std::cout << elem << " # ";
    }
    std::cout << std::endl;
}

void Box::displayPossibleRole() const {
    std::cout << "0. " << roleToString(static_cast<Character_role>(0)) << std::endl
        << "1. " << roleToString(static_cast<Character_role>(1)) << std::endl
        << "2. " << roleToString(static_cast<Character_role>(2)) << std::endl
        << "3. " << roleToString(static_cast<Character_role>(3)) << std::endl;
}

/******************************************************************************************************************************
* BOX MANIPULATION
******************************************************************************************************************************/

void Box::addCharacterToBox() {
    // Acquiring new character name
    
    this->displayNonAddedCharacters();
    if (this->m_non_added_characters.size() == 0) {
        printRestriction<std::string>("You already have all the caracters in your box");
        return; 
    }

    std::string character_picked = "";
    int result = 0;
    do {
        character_picked = inputUser<std::string, std::string>("Choose a character to add in this list :");
        result = this->m_non_added_characters.count(character_picked);
        if (result == 0)
            printRestriction<std::string>("Please pick an existing character from the list");
    }while (result == 0);
    // Acquiring its role
    int role = -1; 
    printMessage<std::string>("Here are the different roles :");
    this->displayPossibleRole();
    do {
        role = inputUser<std::string, int>("Pick an existing role from the list :");
    } while((role < 0) || (role > 3));
    // Acquiring if he has build
    int has_build;
    do {
        has_build = inputUser<std::string, int>("Has he build ? 0. No 1. Yes" ); 
    } while((has_build != 0) && (has_build != 1));
    // Append character to the list
    Character_role r = static_cast<Character_role>(role);
    bool hs = ToF(has_build);
    Element el = this->m_existing_characters[character_picked];
    Character charact = Character(character_picked, r, el, hs);
    this->m_characters[character_picked] = charact;
    // Update file
    this->writeToFile(charact);
    //Remove it from non_added characters
    this->m_non_added_characters.erase(character_picked);
    printMessage<std::string>("Successfully added " + character_picked + " to the list ");
}

void Box::resetBox(){
    // Verify
    int check = -1; 
    do {
        check = inputUser<std::string, int>("Are you sure you want to delete your box ? 0. No 1. Yes");
    } while((check != 0) || (check !=1));
    if (check == 0)     
        return;
    try {
        this->m_characters.clear();
        if (this->m_characters.empty() != true)
            throw std::runtime_error("Couldn't clear the box");
    }
    catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
        return;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
        return;
    }
    bool delete_file = this->resetCharacterFile();
    if (delete_file)
        printRestriction<std::string>("All the characters were deleted from your box");        
}

void Box::updateCharacterData(int rank) {
    // Ask for the character to be modified
    std::string char_name = inputUser<std::string, std::string>("Pick a character to be modified");
    bool has_character = this->hasCharacter(char_name, 0);
    if (!has_character) {
        printRestriction("You don't have the specified character in your box");
        return;
    }
    if (rank == 0) {
        // Remove it from box
        this->m_characters.erase(char_name);
        this->updateFileData();
        this->m_non_added_characters.insert(char_name);
        printMessage(char_name + " was successfully removed from your box");
    } else if (rank == 1) {
        // Role manipulation
        this->displayPossibleRole();
        int new_role = -1;
        do {
            new_role = inputUser<std::string, int>("Choose a new role for your character : ");
        } while ((new_role < 0) || (new_role > 3));
        this->m_characters.at(char_name).setRole(static_cast<Character_role>(new_role));
        this->updateFileData();
        printMessage(char_name + " role was successfully updated from your box");     
    } else if (rank == 3) {
        // Build manipulation
        int has_build;
        do {
            has_build = inputUser<std::string, int>("Has he build ? 0. No 1. Yes" ); 
        } while((has_build != 0) && (has_build != 1));
        this->m_characters.at(char_name).setHasBuild(ToF(has_build));
        this->updateFileData();
        printMessage(char_name + " build was successfully updated from your box");
    } else {
        printRestriction<std::string>("No matching option");
    }
}


/******************************************************************************************************************************
* GETTERS AND SETTERS
******************************************************************************************************************************/

void Box::getCharacterDifference() {
    // Iter over characters and check if it is stored in the collection or not
    for (const auto &elem: this->m_existing_characters) {
        // If not in the list, add its name to the vector
        if(this->m_characters.find(elem.first) == this->m_characters.end()){
            m_non_added_characters.insert(elem.first);
        }
    }
}

Character Box::getCharacterByName(std::string name) {
    return this->m_characters.at(name);
}

/******************************************************************************************************************************
* DATA CHECK
******************************************************************************************************************************/

bool Box::hasCharacter(std::string name, int build) {
    // 0 = no build, 1 = build needed
    bool name_presence = ToF(this->m_characters.count(name));
    if (build == 1) {
        if (name_presence) {
            bool build_possession = this->m_characters[name].hasBuild();
            return build_possession ;
        }
    } else {
        return name_presence;
    }
    return false;
}

bool Box::characterExist(std::string name) {
    std::unordered_map<std::string,Element>::const_iterator got = this->m_existing_characters.find(name);
    if(got == this->m_existing_characters.end()) 
        return false;
    return true;
}

