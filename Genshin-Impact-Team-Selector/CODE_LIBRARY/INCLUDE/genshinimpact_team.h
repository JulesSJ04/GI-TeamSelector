#ifndef GENSHINIMPACT_TEAM_H
#define GENSHINIMPACT_TEAM_H

#include <string>
#include <array>

#include "genshinimpact_common_enums.h"
#include "tools_io_consoleio.h"

#include "genshinimpact_character.h"

namespace GenshinImpact
{
    /*! @brief Classe décrivant une équipe */
    class Team
    {
        public:
            static constexpr std::uint8_t TEAM_SIZE = UINT8_C(4);

            /*! @brief Constructeur par défaut d'une équipe 
             * @warning : Ne pas utiliser => aucun team crée
             */
            Team();

            /*! @brief Constructeur d'une équipe
             * @param ai_teamName           : Nom de l'équipe 
             * @param ai_firstCharacter     : Premier personnage 
             * @param ai_secondCharacter    : Second personnage
             * @param ai_thirdCharacter     : Troisième personnage
             * @param ai_fourthCharacter    : Quatrième personnage
             * @param ai_grade              : Note attribuée
             */
            Team(
                const std::string&              ai_teamName,
                const GenshinImpact::Character& ai_firstCharacter,
                const GenshinImpact::Character& ai_secondCharacter,
                const GenshinImpact::Character& ai_thirdCharacter,
                const GenshinImpact::Character& ai_fourthCharacter,
                const std::uint8_t&             ai_grade
            );

            /*! @brief Destructeur */
            virtual ~Team() {}

            /*! @brief Méthode d'affichage d'une équipe */
            void displayTeam
                (const Tools::IO::ConsoleIO::LogLevel& ai_logLevel = Tools::IO::ConsoleIO::LogLevel::DEBUG) 
                const;

            /*! @brief Vérifier la présence d'un personnage par son nom
             *  @param ai_name      : Nom du personnage cherché
             *  @param ai_needBuild : Nécéssité d'avoir un setup
             */
            const bool isCharacterInTeam(const std::string& ai_name, const bool& ai_needSetup = false) const;

            /*! @brief Vérifier si le personnage a le bon élément
             * @param ai_element    : Element du personnage
             * @param ai_needMainDpsRole : Nécéssite que le personnage soit un main dps
             */
            template <typename TElement>
            const bool hasCharacterSelectedElement(const TElement& ai_element, const bool& ai_needMainDpsRole = false) const;

            /*! @brief Récupérer la note de l'équipe */
            const std::uint8_t& getGrade() const {return m_teamGrade;}

        
        private:
            //============ Attributs ===========//
            const std::string                               m_teamName;
            const std::uint8_t                              m_teamGrade;
            std::array<GenshinImpact::Character, TEAM_SIZE> m_team;
    };
}

#endif
