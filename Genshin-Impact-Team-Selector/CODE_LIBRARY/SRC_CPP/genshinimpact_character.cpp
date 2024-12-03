#include <genshinimpact_character.h>

namespace GenshinImpact
{        
    //====================================================================

    Character::Character():
        m_id(UINT16_C(0u)),
        m_name(""),
        m_role(static_cast<GenshinImpact::Common::Role>(0)),
        m_type(static_cast<GenshinImpact::Common::Element>(0)),
        m_hasSetup(false) 
    {
        // Rien à faire ici
    }

    //====================================================================

    Character::Character(
            const std::uint16_t&                    ai_id,
            const std::string&                      ai_name,
            const GenshinImpact::Common::Role&      ai_role,
            const GenshinImpact::Common::Element&   ai_type,
            const bool& ai_hasSetup
        ):
        m_id(ai_id),
        m_name(ai_name),
        m_role(ai_role),
        m_type(ai_type),
        m_hasSetup(ai_hasSetup)
    {
        // Rien à faire ici
    }

    //====================================================================

    void Character::displayCharacter(const Tools::IO::ConsoleIO::LogLevel& ai_logLevel) const
    {
        Tools::IO::ConsoleIO::messageDisplay<std::string>(ai_logLevel, m_name, "\t => Type : ");
        GenshinImpact::Common::Display::displayElement<GenshinImpact::Common::Element>(m_type);
        Tools::IO::ConsoleIO::messageDisplay<std::string>(ai_logLevel, " Role : ", "");
        GenshinImpact::Common::Display::displayRole<GenshinImpact::Common::Role>(m_role);
        Tools::IO::ConsoleIO::messageDisplay<std::string>(ai_logLevel, " Setup : " + ((m_hasSetup)? "YES", "NO"));
    }

} // End namespace genshin impact