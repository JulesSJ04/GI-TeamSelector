#ifndef TOOLS_CSV_WRITER_H
#define TOOLS_CSV_WRITER_H

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

        /*! @brief : Mode d'écriture d'un CSV 
         * @enum APPEND : Ajouter une ligne à la fin
         * @enum WRITE : Réecrire le fichier sauf les entêtes
         * @enum RESET : Modifier entièrement le fichier, ne garde pas l'entête
         * @enum MODIFY_FIELD : Modifier un champ 
         */
        enum class CsvMode
        {
            APPEND = 0,
            WRITE = 1,
            RESET = 2,
            MODIFY_FIELD
        };
        
        /*! @brief : Classe gérant l'écriture dans un fichier CSV. */
        class Writer
        {
        public:
            /*! @brief Default CTOR */
            Writer();

            /*! @brief CTOR surchargé avec l'ouverture du fichier 
             * @param ai_csvPath : Chemin d'ouverture du csv
             * @param ai_openMode : Méthode d'ouverture du csv
             */
            Writer(const std::string& ai_csvPath, const CsvMode& ai_openMode = CsvMode::APPEND);

            /*! @brief Destructeur */
            virtual ~Writer();

            /*! @brief Méthode d'ouverture du fichier
             * @param ai_csvPath : Chemin d'ouverture du csv
             * @param ai_openMode : Méthode d'ouverture du csv
             */
            void open(const std::string& ai_csvPath, const CsvMode& ai_openMode = CsvMode::APPEND);

            /*! @brief Fermeture du csv */
            void close();

            /*! @brief Méthode d'écriture 
             * @param ai_line : Ligne à écrire dans le fichier
             */
            void writeLine(const std::string& ai_line);

        private:
            /*! @brief Retourne l'état d'ouverture du fichier 
             * @return Etat d'ouverture
             */
            const bool _isOpen() const;

            /*! @brief Charger la ligne d'entête du CSV */
            void _loadHeaderLine();

            /*! @brief Reset le fichier */
            void _resetFile();

            //============ Attributs ============//
            bool            m_hasBeenOpened;
            std::string     m_csvFilePath;
            std::ofstream   m_outputFile;
            CsvMode         m_openMode;

            // Attributs propres au mode WRITE
            bool            m_hasWrittenHeader;
            std::ifstream   m_inputHeaderFile;
            std::string     m_headerLine;
        };


    } // End namespace Csv
} // End namespace Tools

#endif