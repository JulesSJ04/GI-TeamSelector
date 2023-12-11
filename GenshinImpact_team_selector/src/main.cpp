/**************************************************
 * 
 * Project named : Genshin Impact Team Selector
 * Author : Jules SOUFLI-JUMEL
 * 
***************************************************/

#include "general.h"
#include "box.h"
#include "team_list.h"

void menuModify(Box * box) {
    std::vector<std::string> menu_options = {
        "Quit                                         ",
        "Remove a character                           ",
        "Update role                                  ",
        "Update build state                           ",
        "Reset box                                    "
    };
    for (unsigned int i = 0; i < menu_options.size(); i++) {
        printMessage<std::string>(std::to_string(i) + ". " + menu_options.at(i));
    }
    int choice = 0;
    do {
        choice = inputUser<std::string, int>("Pick an option from the displayed one");
    } while(((choice < 0) || (choice > menu_options.size())));
    switch (choice)
    {
    case 0:
        return;
    case 1:
        box->updateCharacterData(0);
        break;
    case 2:
        box->updateCharacterData(1);
        break;
    case 3:
        box->updateCharacterData(3);
        break;
    case 4:
        box->resetBox();
        break;
    default:
        break;
    }
}

void menuSwitch(int choice, Box * box, Team_list * teams)
{
    switch (choice)
    {
    case 0: //Quit
        break;
    case 1: // Display characters from my box
        box->displayBox();
        break;
    case 2: // Add character in my box
        box->addCharacterToBox(); 
        break;
    case 3: // Modify box
        menuModify(box); 
        break;
    case 4: // Display all the team I can use
        teams->displayTeams();
        break;
    case 5: // Add a team to the list
        teams->addTeam();
        break;
    case 6: // Displays teams from one character name
        teams->displayTeamsByName();
        break;
    case 7: // Displays teams from one character
        teams->displayTeamsByName(true);
        break;
    case 8: // Displays teams from one element
        teams->displayTeamsByElement();
        break;
    default:
        printRestriction<std::string>("Not implemented yet");
        break;
    }
}


int main(int argc, char ** argv){
    // Object creation
    Box * my_box = new Box();
    Team_list * my_teams = new Team_list(my_box);
    // Menu options
    std::vector<std::string> menu_options = {
        "Quit                                        ",
        "Display characters from my box              ",
        "Add character to my box                     ",
        "Modify my box                               ",
        "Display all the teams possible              ",
        "Add a team to the database                  ",
        "Find 1 team from 1 character name           ",
        "Find 2 teams from 2 characters name         ",
        "Find 1 team from 1 character element        ",
        "Find 2 teams from 2 characters element      ",
        "Get some statistics                        "
    };

    // MENU
    int choice;
    bool result;
    do {
        std::cout << std::endl;
        printTitle<std::string>("####################### GENSHIN IMPACT TEAM SELECTOR #######################");
        for (unsigned int i = 0; i < menu_options.size(); i++) {
            printMessage<std::string>(std::to_string(i) + ". " + menu_options.at(i));
        }
        choice = inputUser<std::string, int>("Choose a listed option from the menu");
        if ((choice < 0) || (choice > menu_options.size()))
            printRestriction<std::string>("Please pick an existing choice from the list");
        else 
            menuSwitch(choice, my_box, my_teams);
    } while(choice != 0);
    printTitle<std::string>("####################### GENSHIN IMPACT TEAM SELECTOR #######################");
    // Désalocation
    free(my_box);
    free(my_teams);
    return 0;
}