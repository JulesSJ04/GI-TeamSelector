#ifndef GENSHINIMPACT_COMMON_ENUMS_H
#define GENSHINIMPACT_COMMON_ENUMS_H

#include <map>

namespace GenshinImpact
{
    namespace Common
    {
        /*! @brief Description du rôle du personnage */
        enum Role
        {
            MAIN_DPS = 0,
            SUB_DPS = 1,
            DPS_SUPPORT = 2,
            HEAL_SUPPORT = 3
        };

        /*! @brief Description d'un élément */
        enum Element
        {
            ANEMO = 0,
            GEO = 1,
            ELECTRO = 2,
            DENDRO = 3,
            HYDRO = 4,
            PYRO = 5,
            CRYO = 6,
            OMNI = 7
        };


        /*! @brief Element sous forme d'une std::string
         * @param ai_element Element (INT or ELEMENT)
         * @return Element string
         */
        template<typename TElement>
        const std::string& elementToString(const TElement& ai_element);

        /*! @brief Role sous forme d'une std::string
         * @param ai_role Role (INT or ROLE)
         * @return Role string
         */
        template<typename TRole>
        const std::string& roleToString(const TRole& ai_role);

        namespace Display
        {
            
            /*! @brief Affichage d'un element
             * @param ai_element Element (INT or ELEMENT)
             */
            template<typename TElement>
            void displayElement(const TElement& ai_element);

            /*! @brief Affichage d'un role
             * @param ai_element R (INT or ELEMENT)
             */
            template<typename TRole>
            void displayRole(const TRole& ai_role);

        }

        /*! @brief Classe réalisant la conversion d'une string vers une eumération */
        class StringWrapper
        {
        public:

            /*! @brief Récupérer un Role à partir d'une string 
             * @param ai_role String décrivant le role
             * @return Role sous forme d'enum
             */
            static Role& getRole(const std::string& ai_role)
            {
                auto w_it = m_roleMap.find(ai_role);
                if(w_it != m_roleMap.end())
                {
                    return w_it->second;
                }
                else
                {
                    throw std::invalid_argument("Unknown input arg : " + ai_role);
                }
            }

            /*! @brief Récupérer un Element à partir d'une string 
             * @param ai_element String décrivant l'element
             * @return Element sous forme d'enum
             */
            static Element& getElement(const std::string& ai_element)
            {
                auto w_it = m_roleMap.find(ai_element);
                if(w_it != m_roleMap.end())
                {
                    return w_it->second;
                }
                else
                {
                    throw std::invalid_argument("Unknown input arg : " + ai_element);
                }
            }

            /*! @brief Récupérer un boolean à partir d'une string 
             * @param ai_boolean String décrivant un boolean
             * @return boolean
             */
            static bool getBoolean(const std::string& ai_boolean)
            {
                if((ai_boolean.compare("TRUE") == 0) || (ai_boolean.compare("VRAI") == 0))
                {
                    return true;
                }
                else if ((ai_boolean.compare("FALSE") == 0) || (ai_boolean.compare("FAUX") == 0))
                {
                    return false;
                }
                else
                {
                    throw std::invalid_argument("Unknown input arg : " + ai_boolean);
                }
                
            }

        private:
            static const std::map<std::string, Role> m_roleMap;
            static const std::map<std::string, Element> m_elementMap;

        };

    }
}

#endif
