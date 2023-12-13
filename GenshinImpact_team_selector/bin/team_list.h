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

    // FILE MANIPULATION
    void loadTeams(); // Charger les teams de la base de données
    void addTeamToFile(String_team new_team); // Ajouter une team à la base de donnée
    
    // CHECKING AND UPDATE METHODS
    void computePossibleTeams(); // Trouver les teams réalisable depuis la BDD et la box
    bool isAlreadyAdded(const String_team &team); //Vérifier si la team n'a pas déjà été ajoutée
    bool isAlreadyUsed(int team_id, std::vector<std::string> picked_character_names); // Vérifier si les personnages ne sont pas déjà utilisés
    bool checkOwnership(std::string character_name, int build); //Vérifier si le personnage est dans la box

    // DISPLAYS
    void displayTeams();
    void displayTwoTeams(int team1_id, int team2_id);

    // TEAM DISPLAY FROM NAME
    void displayTeamsByName(bool is_double_choice = false);
    
    // TEAM DISPLAY FROM ELEMENT
    void displayTeamsByElement(bool is_double_choice = false);

    // GET TEAMS
    template<class T>
    int getFirstTeam(T data);
    template<class T>
    int getSecondTeam(int team_1_id, T data);

    // USEFUL METHODS
    void addTeam();
    int buildPrompt();
    bool mainDpsPrompt();

    template<class T>
    bool isCharacterInTeamCondition(Team& team, T data, bool is_main_dps); 
};
