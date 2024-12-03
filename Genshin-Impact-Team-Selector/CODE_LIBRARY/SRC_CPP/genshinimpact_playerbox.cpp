#include "genshinimpact_playerbox.h"
#include "tools_csv_reader.h"

namespace GenshinImpact
{
    //====================================================================

    PlayerBox::PlayerBox()
    {
        _loadCharacters();
    }

    //====================================================================

    void PlayerBox::_loadCharacters()
    {
        // Etape 1 : Ouvrir le fichier csv
        std::map<std::string, std::vector<std::string>> w_dataContainer;
        Tools::Csv::Reader w_characterReader;
        w_characterReader.open("./../DATA/player_characters.csv");

        // Etape 2 : Lecture des données
        size_t w_size = w_characterReader.readFile(w_dataContainer);

        // Etape 3 : Parcourir les données pour créer les personnages
        for(size_t w_it = 0; w_it < w_size; w_it++)
        {
            // name, element, role, build, appartenance
            std::vector<std::string> w_datas;
            for(const auto& elem: w_dataContainer)
            {
                w_datas.push_back(elem.second[w_it]);
            }

            // Creation du personnage
            Character w_newCharacter{
                static_cast<std::uint16_t>(w_it),
                w_datas[0],
                ::Common::StringWrapper::getRole(w_datas[2]),
                ::Common::StringWrapper::getElement(w_datas[1]),
                ::Common::StringWrapper::getBoolean(w_datas[3])
            };

            // Insertion dans la map
            m_characters[w_datas[0]] = std::make_pair(
                w_newCharacter, ::Common::StringWrapper::getBoolean(w_datas[4]));

        }

        Tools::IO::ConsoleIO::messageDisplay<std::string>(Tools::IO::ConsoleIO::LogLevel::DEBUG,
            "Loaded all characters");
    }

    //====================================================================

    void PlayerBox::displayPlayerCharacters() const
    {
        Tools::IO::ConsoleIO::clearConsole();
        Tools::IO::ConsoleIO::titleDisplay(Tools::IO::ConsoleIO::LogLevel::DEBUG, 
            "##################### === PLAYER BOX === #####################"); 

        for (const auto& w_names: m_characters)
        {
            // Si personnage acquis par le joueur
            if(w_names.second.second)
            {
                w_names.second.first.displayCharacter();
            }
        }
    }

    //====================================================================

    void PlayerBox::displayCharactersList() const
    {
        Tools::IO::ConsoleIO::clearConsole();
        Tools::IO::ConsoleIO::errorDisplay(Tools::IO::ConsoleIO::LogLevel::DEBUG, 
            "##################### === CHARACTERS LIST === #####################"); 

        for (const auto& w_names: m_characters)
        {
            w_names.second.first.displayCharacter();
        }
    }

    //====================================================================

    void PlayerBox::displayNonAddedCharacters() const
    {
        Tools::IO::ConsoleIO::clearConsole();
        Tools::IO::ConsoleIO::errorDisplay(Tools::IO::ConsoleIO::LogLevel::DEBUG, 
            "##################### === CHARACTERS LIST === #####################"); 

        for (const auto& w_names: m_characters)
        {
            if(!w_names.second.second)
            {
                w_names.second.first.displayCharacter();
            }
        }
    }

    //====================================================================

    bool PlayerBox::hasCharacter(const std::string& ai_name, const bool ai_needStuff) const
    {
        auto w_it = m_characters.find(ai_name);
        if(w_it != m_characters.end())
        {
            if(!ai_needStuff)
            {
                return true
            }
            return w_it->second.first.getHasSetup();
        }
        return false;
    }

    //====================================================================

    bool PlayerBox::isCharacterLoaded(const std::string& ai_name) const
    {
        if(m_characters.find(ai_name) != m_characters.end())
        {
            return true;
        }
        return false;
    }



}