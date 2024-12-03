#include "tools_csv_reader.h"

namespace Tools
{
    namespace CSV
    {
        //=======================================================================
        
        Reader::Reader():
            m_separator(';'),
            m_isOpen(false),
            m_csvFilePath("")
        {
            // Rien à faire ici
        }

        //=======================================================================
        
        Reader::Reader(const std::string& ai_csvFilePath, const char ai_separator):
            m_separator(ai_separator),
            m_isOpen(false),
            m_csvFilePath(ai_csvFilePath)
        {
            open(m_csvFilePath);
        }

        //=======================================================================

        Reader::~Reader()
        {
            try
            {
                close();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }  
        }

        //=======================================================================

        void Reader::open(const std::string& ai_csvFilePath)
        {
            if(!m_isOpen)
            {
                m_csvFilePath = ai_csvFilePath;
                m_inputFile.open(ai_csvFilePath);
                if(m_inputFile.is_open())
                {
                    m_isOpen = true;
                }
                else
                {
                    std::string w_errorMessage = "Unable to open file at " + ai_csvFilePath; 
                    throw std::runtime_error(w_errorMessage);
                }
            }
        }

        //=======================================================================

        void Reader::close()
        {
            if(m_isOpen)
            {
                try
                {
                    m_inputFile.close();
                    m_isOpen = false;
                }
                catch(const std::exception& e)
                {
                    std::cerr << "Couldn't close CSV : " << e.what << std::endl;
                }
            }
        }

        //=======================================================================

        size_t Reader::readFile(csv_container& ao_csvData)
        {
            size_t w_size = 0;
            if(m_isOpen)
            {
                // Chargement du header du CSV
                _loadHeader(ao_csvData);
                
                // Chargement des données du CSV
                w_size = _loadData(ao_csvData); 

                // Fermeture du CSV
                close();
            }
            else
            {
                Tools::IO::ConsoleIO::errorDisplay(
                    Tools::IO::ConsoleIO::LogLevel::DEBUG,
                    "Open file before using it"
                );
            }

            return w_size;
        }

        //=======================================================================

        void Reader::_loadHeader(csv_container& ao_csvData)
        {
            std::string w_headerLine;
            // Lecture de la ligne du CSV
            if(getline(m_inputFile, w_headerLine))
            {
                std::istringstream w_stream(w_headerLine);
                std::string w_headerTitle;
                while(getline(w_stream, w_headerTitle, m_separator))
                {
                    // Stocker les titres du header pour l'indexation futur
                    m_headerTitles.push_back(w_headerTitle);
                    ao_csvData[w_headerTitle] = std::vector<std::string>();
                }
            }
        }

        //=======================================================================

        size_t Reader::_loadData(csv_container& ao_csvData)
        {
            std::string w_dataLine;
            // Lecture de la ligne du CSV
            size_t w_lineNumber = 0;
            while(getline(m_inputFile, w_dataLine))
            {
                std::istringstream w_stream(w_dataLine);
                std::string w_singleData;
                size_t w_columnIndex = 0;
                // Lecture unitaire d'une donnée
                while(getline(w_stream, w_singleData, m_separator))
                {
                    ao_csvData[m_headerTitles[w_columnIndex]].push_back(w_singleData);
                    ++w_columnIndex;
                }
                w_lineNumber++;
            }

            return w_lineNumber;
        }

    }
} // Namespace Tools