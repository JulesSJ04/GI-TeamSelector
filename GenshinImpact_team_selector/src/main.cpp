#include "general.h"
#include "box.h"

bool menuSwitch(int choice, Box * box)
{
    switch (choice)
    {
    case 0: //Quit
        break;
    case 1:
        box->displayBox();
        break;
    case 2:
        box->addCharacterToBox();
        break;
    case 3:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case 4:
        std::cout << "Not implemented yet" << std::endl;
        break;
    default:
        break;
    }
    return true;
}

int main(int argc, char ** argv){
    Box * my_box = new Box();

    // MENU
    int choice;
    bool result;
    do {
        std::cout << std::endl;
        std::cout << "####################### GENSHIN IMPACT TEAM SELECTOR #######################" << std::endl;
        std::cout << "0. Quit" << std::endl
            << "1. Display characters from my box" << std::endl
            << "2. Add character in my box" << std::endl
            << "3. Remove character from my box" << std::endl
            << "4. Update a character role from my box" << std::endl
            << "5. Append a team to the list" << std::endl
            << "6. Find 1 team from 1 main DPS" << std::endl
            << "7. Find 2 team from 2 main DPS" << std::endl;
        std::cin >> choice;
        if ((choice < 0) && (choice > 5))
            std::cout << "Please pick an existing choice from the list" << std::endl;
        else 
            result = menuSwitch(choice, my_box);
    } while(choice != 0);
    std::cout << "####################### GENSHIN IMPACT TEAM SELECTOR #######################" << std::endl;
    free(my_box);
    return 0;
}