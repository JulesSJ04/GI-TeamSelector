#ifndef GENSHINIMPACT_TEAMMANAGER_H
#define GENSHINIMPACT_TEAMMANAGER_H

#include "genshinimpact_team.h"
#include <unordered_map>

namespace GenshinImpact
{
    /*! @brief Class permettant de manipuler les équipes d'une box
     *  - Charger les équipes connues de la base de donnée
     *  - Ajouter une équipe à la base de donnée
     *  - Affichage des équipes
     *  - Recherche d'une équipe
     */
    class TeamManager
    {
        public:

        private:



        static std::uint32_t m_teamId;
        std::unordered_map<std::uint32_t, GenshinImpact::Team> m_teams;
        
    };
}


#endif
