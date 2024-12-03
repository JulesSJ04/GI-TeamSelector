#include "genshinimpact_team.h"

namespace GenshinImpact
{
    //====================================================================

    Team::Team():
        m_teamName(""),
        m_teamGrade(UINT8_C(0))
    {
        // Rien à faire ici
    }

    //====================================================================

    Team::Team(
        const std::string&              ai_teamName,
        const GenshinImpact::Character& ai_firstCharacter,
        const GenshinImpact::Character& ai_secondCharacter,
        const GenshinImpact::Character& ai_thirdCharacter,
        const GenshinImpact::Character& ai_fourthCharacter,
        const std::uint8_t&             ai_grade):
        m_teamName(ai_teamName),
        m_teamGrade(ai_grade)
    {
        m_team = {ai_firstCharacter,
            ai_secondCharacter,
            ai_thirdCharacter,
            ai_fourthCharacter};

        Tools::IO::ConsoleIO::messageDisplay<std::string>(Tools::IO::ConsoleIO::LogLevel::DEBUG, "New team added : ");
        displayTeam();
    }

    //====================================================================

    const bool Team::isCharacterInTeam(const std::string& ai_name, const bool& ai_needSetup) const
    {
        for(size_t w_it = 0; w_it < TEAM_SIZE; w_it++)
        {
            if(m_team[w_it].getName().compare(ai_name) == 0)
            {
                if(ai_needSetup)
                {
                    return m_team[w_it].getHasSetup();
                }
                else
                {
                    return true;
                }
            }
        }
        return false;
    }

    //====================================================================

    template <typename TElement>
    const bool Team::hasCharacterSelectedElement(const TElement& ai_element, const bool& ai_needMainDpsRole) const
    {
        GenshinImpact::Common::Element w_choosenElement = static_cast<GenshinImpact::Common::Element>(ai_element);

        for(size_t w_it = 0; w_it < TEAM_SIZE ; w_it++)
        {
            if(m_team[w_it].getElement() == w_choosenElement)
            {
                if(ai_needMainDpsRole)
                {
                    return (m_team[w_it].getRole() == GenshinImpact::Common::Role::MAIN_DPS);
                }
                else
                {
                    return true;
                }
            }
        }
        return false;
    }

    //====================================================================

    void Team::displayTeam(const Tools::IO::ConsoleIO::LogLevel& ai_logLevel) const
    {
        std::string w_message = " ########### " + m_teamName + "(" + std::to_string(m_teamGrade) + ")" + " ########### ";
        Tools::IO::ConsoleIO::titleDisplay<std::string>(ai_logLevel, w_message);

        for(size_t w_it = 0; w_it < TEAM_SIZE; w_it++)
        {
            m_team[w_it].displayCharacter(ai_logLevel);
        }
        
        std::cout << std::endl;
    }


}