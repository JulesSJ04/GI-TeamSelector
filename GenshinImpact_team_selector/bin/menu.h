#ifndef MENU_H_
#define MENU_H_

#include "general.h"
#include "box.h"
#include "team_list.h"

void menuModify(Box * box);
void menuTeams(Team_list * teams);
void menuSwitch(int choice, Box * box, Team_list * teams);

#endif