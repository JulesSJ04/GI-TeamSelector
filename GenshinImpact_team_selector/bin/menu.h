#ifndef MENU_H_
#define MENU_H_

#include "general.h"
#include "box.h"
#include "statistics.h"

void menuModify(Box * box);
void menuTeams(Team_list * teams);
void menuStatistics(Statistics * stats);
void menuSwitch(int choice, Box * box, Team_list * teams, Statistics * stats);

#endif