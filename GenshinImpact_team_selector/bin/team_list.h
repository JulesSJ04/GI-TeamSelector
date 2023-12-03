#include "general.h"
#include "team.h"
#include "character.h"
#include "box.h"

struct String_team {
    std::string characters[4];
    int note;
};

class Team_list {
private:
    std::vector<String_team> m_global_teams;
    std::vector<Team> m_teams;
    Box * m_box;
    
public:
    Team_list(Box * b);
    virtual ~Team_list() {}

    // Loading
    void loadTeams(); // Charger les teams de la base de données
    void computePossibleTeams(); // Trouver les teams réalisable depuis la BDD et la box

    // display all teams
    void displayTeams() const;
    void displayTeamsByName(std::string character_name);
};