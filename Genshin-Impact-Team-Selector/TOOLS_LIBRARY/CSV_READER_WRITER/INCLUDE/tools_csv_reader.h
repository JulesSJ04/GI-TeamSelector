#ifndef TOOLS_CSV_READER_H
#define TOOLS_CSV_READER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

namespace Tools
{
    namespace Csv
    { 
        /*! @brief : Classe gérant la lecture d'un fichier CSV. */
        class Reader
        {
            public:
                /*! CSV Type map 
                 * => Key : Header
                 * => Value : Vecteur des données
                */
                typedef std::map<std::string, std::vector<std::string>> csv_container;

                /*! @brief Default CTOR */
                Reader();

                /*! @brief Constructeur surchargé avec le chemin du fichier
                 * @param ai_csvFilePath : Chemin du CSV a ouvrir
                 * @param ai_separator : Separateur
                 */
                Reader(const std::string& ai_csvFilePath, const char ai_separator = ';');

                /*! @brief Destructeur */
                virtual ~Reader();

                /*! @brief Fermeture du CSV */
                void close();

                /*! @brief Ouverture du CSV 
                 * @param ai_csvFilePath : Chemin du CSV a ouvrir
                 */
                void open(const std::string& ai_csvFilePath);

                /*! @brief Remplir le containeur de données.
                 * @param ao_csvData : Conteneur de données à remplir
                 * @return Taille du conteneur de données
                 */
                size_t readFile(csv_container& ao_csvData);

            private:

                /*! @brief : Méthode du chargement du header dans le conteneur de données.
                 * @param ao_csvData : Conteneur de données à remplir 
                 */
                void _loadHeader(csv_container& ao_csvData);

                /*! @brief : Méthode du chargement des données dans le conteneur de données.
                 * @param ao_csvData : Conteneur de données à remplir 
                 * @return Taille du vecteur
                 */
                size_t _loadData(csv_container& ao_csvData);
                
                //============ Attributs ============//
                const char                  m_separator;
                bool                        m_isOpen;
                std::string                 m_csvFilePath; 
                std::ifstream               m_inputFile;
                std::vector<std::string>    m_headerTitles; // Stocker les entêtes

        }; // Class
    } // Namespace Csv
} // Namespace Tools

#endif

