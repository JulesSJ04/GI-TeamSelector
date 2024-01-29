#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "general.h"
#include "team_list.h"

class Statistics {
private:
    Team_list * m_team_list;
    Box * m_box;
    // Compter le nombre d'occurence de personnages par team
    std::map<std::string, int> m_character_frequency;
    // Global character frequency
    std::map<std::string, int> m_global_character_frequency;

public:
    Statistics(Team_list * tl, Box * b);
    virtual ~Statistics() {}

    // General display
    void displayStatistics();
    
    // Frequency
    void computeCharacterFrequency(Mode display_m, bool need_display = false);
    template <class T>
    void displayFrequency(Mode display_m, std::set<std::pair<std::string, int>, T> sortedSet);

    // Non added frequency
    void computeNonAddedCharacterFrequency();

};

// Custom comparator
struct GreaterValue {
    bool operator()(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) const {
        return a.second > b.second;
    }
};

struct LesserValue {
    bool operator()(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) const {
        return a.second < b.second;
    }
};

#endif