#include "genshinimpact_common_enums.h"
#include "tools_io_consoleio.h"

namespace GenshinImpact
{
    namespace Common
    {

        //====================================================================
        
        const std::map<std::string, Role> StringWrapper::m_roleMap{
            {"MAIN_DPS", Role::MAIN_DPS},
            {"SUB_DPS", Role::SUB_DPS},
            {"HEAL_SUPPORT", Role::HEAL_SUPPORT},
            {"DPS_SUPPORT", Role::DPS_SUPPORT}
        };

        const std::map<std::string, Element> StringWrapper::m_elementMap{
            {"ANEMO", Element::ANEMO},
            {"GEO", Element::GEO},
            {"ELECTRO", Element::ELECTRO},
            {"DENDRO", Element::DENDRO},
            {"HYDRO", Element::HYDRO},
            {"PYRO", Element::PYRO},
            {"CRYO", Element::CRYO},
            {"OMNI", Element::OMNI}
        };
        
        //====================================================================

        template<typename TElement>
        const std::string& elementToString(const TElement& ai_element)
        {
            switch (static_cast<Element>(ai_element))
            {
            case ANEMO: return "Anemo";
            case GEO: return "Geo";
            case ELECTRO: return "Electro";
            case DENDRO: return "Dendro";
            case HYDRO: return "Hydro";
            case PYRO: return "Pyro";
            case CRYO: return "Cryo";
            case OMNI: return "Omni";
            default:
                throw ("Unknown element specified");
                return "";
            }
        }

        //====================================================================

        template<typename TRole>
        const std::string& roleToString(const TRole& ai_role)
        {
            switch (static_cast<TRole>(ai_role))
            {
            case MAIN_DPS: return "DPS";
            case SUB_DPS: return "Sub DPS";
            case DPS_SUPPORT: return "Support";
            case HEAL_SUPPORT: return "Healer";
            default:
                throw ("Unknown role specified");
                return "";
            }
        }

        //====================================================================
        
        namespace Display
        {
            template<typename TElement>
            void displayElement(const TElement& ai_element)
            {             
                std::string w_textColor;
                
                switch (static_cast<Element>(ai_element))
                {
                case ANEMO:
                    w_textColor = Tools::IO::ConsoleIO::BoldColor::GREEN;
                    break;
                case GEO:
                    w_textColor = Tools::IO::ConsoleIO::FrontColor::YELLOW;
                    break;
                case ELECTRO:
                    w_textColor = Tools::IO::ConsoleIO::FrontColor::PURPLE;
                    break;
                case DENDRO:
                    w_textColor = Tools::IO::ConsoleIO::FrontColor::GREEN;
                    break;
                case HYDRO:
                    w_textColor = Tools::IO::ConsoleIO::FrontColor::BLUE;
                    break;
                case PYRO:
                    w_textColor = Tools::IO::ConsoleIO::FrontColor::RED;
                    break;
                case CRYO:
                    w_textColor = Tools::IO::ConsoleIO::FrontColor::CYAN;
                    break;
                case OMNI:
                    w_textColor = Tools::IO::ConsoleIO::BoldColor::CYAN;
                    break;
                default:
                    throw("Unable to find the given element");
                    break;
                }

                Tools::IO::ConsoleIO::display<std::string>(
                    Tools::IO::ConsoleIO::LogLevel::DEBUG,
                    elementToString<Element>(ai_element),
                    w_textColor,
                    Tools::IO::ConsoleIO::BgColor::BLACK,
                    false);

            }

            //====================================================================

            template<typename TRole>
            void displayRole(const TRole& ai_role)
            {             
                std::string w_textColor;
                
                switch (static_cast<Element>(ai_role))
                {
                case MAIN_DPS:
                    w_textColor = Tools::IO::ConsoleIO::FrontColor::RED;
                    break;
                case SUB_DPS:
                    w_textColor = Tools::IO::ConsoleIO::FrontColor::BLUE;
                    break;
                case DPS_SUPPORT:
                    w_textColor = Tools::IO::ConsoleIO::FrontColor::YELLOW;
                    break;
                case HEAL_SUPPORT:
                    w_textColor = Tools::IO::ConsoleIO::FrontColor::GREEN;
                    break;
                default:
                    throw("Unable to find the given role");
                    break;
                }

                Tools::IO::ConsoleIO::display<std::string>(
                    Tools::IO::ConsoleIO::LogLevel::DEBUG,
                    roleToString<Role>(ai_role),
                    w_textColor,
                    Tools::IO::ConsoleIO::BgColor::BLACK,
                    false);

            }

        }
    }
}