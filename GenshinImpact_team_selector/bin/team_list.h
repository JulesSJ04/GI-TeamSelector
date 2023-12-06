#include "general.h"
#include "team.h"
#include "character.h"
#include "box.h"

struct String_team {
    std::string name;
    std::string characters[4];
    int note;
};

class Team_list {
private:
    static int s_team_id;
    std::vector<String_team> m_global_teams;
    std::unordered_map<int, Team> m_teams;
    Box * m_box;
    
public:
    Team_list(Box * b);
    virtual ~Team_list() {}

    // Loading
    void loadTeams(); // Charger les teams de la base de données
    void computePossibleTeams(); // Trouver les teams réalisable depuis la BDD et la box
    bool isAlreadyAdded(const String_team &team); //Vérifier si la team n'a pas déjà été ajoutée
    bool isAlreadyUsed(int team_id, std::vector<std::string> picked_character_names);
    int buildPrompt();
    bool checkOwnership(std::string character_name, int build);
    // display all teams
    void displayTeams();
    void displayTeamsByName();
    void displayTwoTeams(int team1_id, int team2_id);


    // Select two teams
    int getFirstTeam(std::string character_name);
    void displayTwoTeam();
};