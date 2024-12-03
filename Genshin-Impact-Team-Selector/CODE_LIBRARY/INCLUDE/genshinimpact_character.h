#ifndef GENSHINIMPACT_CHARACTER_H
#define GENSHINIMPACT_CHARACTER_H

#include <string>

#include "genshinimpact_common_enums.h"
#include "tools_io_consoleio.h"

namespace GenshinImpact
{
    /*! @brief Classe décrivant un personnage */
    class Character
    {
        public:
            /*! @brief Constructeur par défaut d'un personnage 
             * @warning : Ne pas utiliser => aucun personnage de crée
             */
            Character();

            /*! @brief Constructeur d'un personnage 
             * @param ai_id   : Id  
             * @param ai_name : Nom du personnage
             * @param ai_role : Role du personnage
             * @param ai_type : Type élémentaire
             * @param ai_hasSetup : Status de build
             */
            Character(
                const std::uint16_t&                    ai_id,
                const std::string&                      ai_name,
                const GenshinImpact::Common::Role&      ai_role,
                const GenshinImpact::Common::Element&   ai_type,
                const bool& ai_hasSetup = false
            );

            /*! @brief Destructeur */
            virtual ~Character() {}

            /*! @brief Méthode d'affichage d'un personnage */
            void displayCharacter
                (const Tools::IO::ConsoleIO::LogLevel& ai_logLevel = Tools::IO::ConsoleIO::LogLevel::DEBUG) 
                const;

            /*! @brief ID du personnage */
            const std::uint16_t& getId() const {return m_id;}
            /*! @brief Nom du personnage */
            const std::string& getName() const {return m_name;}
            /*! @brief Role du personnage */
            const GenshinImpact::Common::Role& getRole() const {return m_role;}
            /*! @brief Element du personnage */
            const GenshinImpact::Common::Element& getElement() const {return m_type;}
            /*! @brief Etat de setup du personnage */
            const bool& getHasSetup() const {return m_hasSetup;}
            
            /*! @brief Mettre à jour le statut de build
             * @param ai_hasSetup : Nouveau setup
             */
            void setHasSetup(const bool& ai_hasSetup) {m_hasSetup = ai_hasSetup;}       

        private:
            //============ Attributs ===========//
            std::uint16_t                           m_id;
            const std::string                       m_name;
            const GenshinImpact::Common::Role       m_role;
            const GenshinImpact::Common::Element    m_type;
            bool                                    m_hasSetup;

    };
}

#endif
