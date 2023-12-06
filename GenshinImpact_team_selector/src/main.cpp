#include "general.h"
#include "box.h"
#include "team_list.h"

bool menuSwitch(int choice, Box * box, Team_list * teams)
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
    case 3: // Remove character from my box
        std::cout << "Not implemented yet" << std::endl;
        break;
    case 4: // Display all the team I can use
        teams->displayTeams();
        break;
    case 5: // Displays teams from one character
        teams->displayTeamsByName();
        break;
    case 6: // Displays teams from one character
        teams->displayTwoTeam();
    default:
        break;
    }
    return true;
}

int main(int argc, char ** argv){
    Box * my_box = new Box();
    Team_list * my_teams = new Team_list(my_box);

    // MENU
    int choice;
    bool result;
    do {
        std::cout << std::endl;
        std::cout << BG_CYAN << "####################### GENSHIN IMPACT TEAM SELECTOR #######################" << RESET << std::endl;
        std::cout 
            << BG_WHITE << "0. Quit                                 " << RESET << std::endl
            << BG_WHITE << "1. Display characters from my box       " << RESET << std::endl
            << BG_WHITE << "2. Add character to my box              " << RESET << std::endl
            << BG_WHITE << "3. Remove character from my box         "  << RESET << std::endl
            << BG_WHITE << "4. Display all the teams I can use      " << RESET << std::endl
            << BG_WHITE << "5. Find 1 team from 1 character         " << RESET << std::endl
            << BG_WHITE << "6. Find 2 team from 2 character         " << RESET <<std::endl;
        std::cin >> choice;
        if ((choice < 0) && (choice > 6))
            std::cout << "Please pick an existing choice from the list" << std::endl;
        else 
            result = menuSwitch(choice, my_box, my_teams);
    } while(choice != 0);
    std::cout << BG_MAGENTA <<"####################### GENSHIN IMPACT TEAM SELECTOR #######################" << RESET << std::endl;
    free(my_box);
    free(my_teams);
    return 0;
}