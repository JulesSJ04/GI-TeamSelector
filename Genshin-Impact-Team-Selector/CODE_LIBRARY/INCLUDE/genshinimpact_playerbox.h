#ifndef GENSHINIMPACT_PLAYERBOX_H
#define GENSHINIMPACT_PLAYERBOX_H

#include <unordered_map>
#include <pair>
#include "genshinimpact_character.h"

namespace GenshinImpact
{
    class PlayerBox
    {
    public:

        /*! @brief Constructeur. */
        PlayerBox();

        /*! @brief Destructeur. */
        virtual ~PlayerBox() {};

        //===== DISPLAYS =====//
        /*! @brief Affichage des personnages d'une box */
        void displayPlayerCharacters() const;

        /*! @brief Affichage de l'ensemble des personnages */
        void displayCharactersList() const;

        /*! @brief Affichage de l'ensemble des personnages */
        void displayNonAddedCharacters() const;

        //===== CHECKERS =====//
        /*! @brief Verifier si le personnage est contenu dans la box du joueur 
         * @param ai_name       : Nom du personnage
         * @param ai_needStuff  : Nécéssité d'être build
         * @return true ou false
         */
        bool hasCharacter(const std::string& ai_name, const bool ai_needStuff = false) const;

        /*! @brief Verifier si le personnage existe dans la liste
         * @param ai_name       : Nom du personnage
         * @return true ou false
         */
        bool isCharacterLoaded(const std::string& ai_name) const;

    private:
        /*! @brief Chargement du fichier de personnages. */
        void _loadCharacters();

        std::unordered_map<std::string, std::pair<Character, bool>> m_characters;

        

    };
}

#endif