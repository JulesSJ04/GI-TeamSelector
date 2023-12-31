/**************************************************
 * 
 * Project named : Genshin Impact Team Selector
 * Author : Jules SOUFLI-JUMEL
 * 
***************************************************/

#include "general.h"
#include "menu.h"

int main(int argc, char ** argv){
    // Object creation
    Box * my_box = new Box();
    Team_list * my_teams = new Team_list(my_box);
    Statistics * my_stats = new Statistics(my_teams, my_box);
    // Menu options
    std::vector<std::string> menu_options = {
        "Quit                                        ",
        "Display characters from my box              ",
        "Add character to my box                     ",
        "Modify my box                               ",
        "Find a team                                 ",
        "Add a team to the database                  ",
        "Get some statistics                         "
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
        if ((choice < 0) || (choice > menu_options.size() - 1))
            printRestriction<std::string>("Please pick an existing choice from the list");
        else 
            menuSwitch(choice, my_box, my_teams, my_stats);
    } while(choice != 0);
    printTitle<std::string>("####################### GENSHIN IMPACT TEAM SELECTOR #######################");
    // Désalocation
    free(my_box);
    free(my_teams);
    return 0;
}
