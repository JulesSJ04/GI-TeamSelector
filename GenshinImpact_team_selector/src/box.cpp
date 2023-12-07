#include "box.h"
#include "character.h"

Box::Box()
{
    this->loadExistingCharacters();
    this->m_got_loaded = this->loadCharacters();
    this->getCharacterDifference();
}

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

bool Box::resetBox(){
    try {
        this->m_characters.clear();
        if (this->m_characters.empty() != true)
            throw std::runtime_error("Couldn't clear the box");
    }
    catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
        return false;
    }
    return true;
}

void Box::displayBox() const {
    if (this->m_characters.empty() != true){
        for (const auto& elem: this->m_characters){
            elem.second.displayCharacter();
        }
    } else {
        std::cout << "No characters have been loaded/created yet" << std::endl;
    }
}

void Box::displayExistingCharacters() const {
    std::cout << "All the existing characters are :" << std::endl;
    for (const auto &elem: this->m_existing_characters) {
        std::cout << "Character " << elem.first << " is " << elementToString(elem.second) << std::endl;
    }
}

void Box::displayNonAddedCharacters() const {
    std::cout << "Non added characters are : " << std::endl;
    for (const auto &elem: this->m_non_added_characters) {
        std::cout << elem << " # ";
    }
    std::cout << std::endl;
}

void Box::addCharacterToBox() {
    // Acquiring new character name
    std::string character_picked = "";
    int result = 0;
    this->displayNonAddedCharacters();
    if (this->m_non_added_characters.size() == 0) {
        std::cout << BG_RED <<"You already have all the caracters in your box" << RESET <<std::endl;
        return; 
    }
    std::cout << BG_YELLOW <<"Choose a character to add in this list :"<< RESET << std::endl;
    do {
        std::cin >> character_picked;
        result = this->m_non_added_characters.count(character_picked);
        if (result == 0)
            std::cout << BG_RED << "Please pick an existing character from the list" << RESET <<std::endl; 
    }while (result == 0);
    // Acquiring its role
    int role; 
    std::cout << BG_YELLOW << "Choose a role between those role :" << RESET <<std::endl
        << "0. " << roleToString(static_cast<Character_role>(0)) << std::endl
        << "1. " << roleToString(static_cast<Character_role>(1)) << std::endl
        << "2. " << roleToString(static_cast<Character_role>(2)) << std::endl
        << "3. " << roleToString(static_cast<Character_role>(3)) << std::endl;
    do {
        std::cin >> role;
        if ((role < 0) || (role > 3))
            std::cout << BG_RED << "Please pick an existing role from the list" << RESET <<std::endl; 
    } while((role < 0) || (role > 3));
    // Acquiring if he has build
    int has_build;
    std::cout << BG_YELLOW << "Has he build ? 0. No 1. Yes" << RESET <<std::endl;
    do {
        std::cin >> has_build;
        if ((has_build != 0) && (has_build != 1))
            std::cout << BG_RED << "Please pick an existing option from the list" << RESET << std::endl; 
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
    std::cout << "Successfully added " << character_picked << " to the list" << std::endl;
}

void Box::getCharacterDifference() {
    // Iter over characters and check if it is stored in the collection or not
    for (const auto &elem: this->m_existing_characters) {
        // If not in the list, add its name to the vector
        if(this->m_characters.find(elem.first) == this->m_characters.end()){
            m_non_added_characters.insert(elem.first);
        }
    }
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
            std::cout << "Character added to file (" << line << ")" << std::endl; 
        }
    } catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
    }
    
}

Character Box::getCharacterByName(std::string name) {
    return this->m_characters.at(name);
}

bool Box::hasCharacter(std::string name, int build) {
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

void Box::removeCharacterFromMyBox(std::string name) {
    const std::string filename = "./datas/my_characters.txt";

    // Read the file into a vector of strings
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
}

bool Box::characterExist(std::string name) {
    std::unordered_map<std::string,Element>::const_iterator got = this->m_existing_characters.find(name);
    if(got == this->m_existing_characters.end()) 
        return false;
    return true;
}
