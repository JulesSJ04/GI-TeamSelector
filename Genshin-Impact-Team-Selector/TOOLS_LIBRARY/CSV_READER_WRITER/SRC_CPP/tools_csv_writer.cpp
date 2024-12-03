#include "tools_csv_writer.h"

namespace Tools
{
    namespace Csv
    {
        
        //====================================================================
       
        Writer::Writer():
            m_hasBeenOpened(false), 
            m_csvFilePath(""), 
            m_openMode(CsvMode::APPEND),
            m_hasWrittenHeader(false),
            m_headerLine("")
        {
            // Rien à faire ici
        }

        //====================================================================

        Writer::Writer(const std::string& ai_csvPath, const CsvMode& ai_openMode):
            m_hasBeenOpened(false),
            m_csvFilePath(ai_csvPath),
            m_openMode(ai_openMode),
            m_hasWrittenHeader(false),
            m_headerLine("")
        {
            open(ai_csvPath, ai_openMode);
        }

        //====================================================================

        Writer::~Writer()
        {
            close();
        }

        //====================================================================

        void Writer::open(const std::string& ai_csvPath, const CsvMode& ai_openMode)
        {
            if(!m_hasBeenOpened)
            {
                m_csvFilePath = ai_csvPath;
                m_openMode = ai_openMode;

                // Ouverture du fichier selon le mode
                try
                {
                    switch (ai_openMode)
                    {
                    case CsvMode::APPEND:
                        m_outputFile.open(ai_csvPath, std::ios::app);
                        break;
                    case CsvMode::WRITE:
                        // Charger la ligne d'entête pour l'écrire
                        _loadHeaderLine();
                        // Réinitialiser le fichier
                        _resetFile();
                        // Initialiser l'écrivain et écrire l'entête
                        m_openMode = CsvMode::APPEND;
                        m_outputFile.open(ai_csvPath, std::ios::app);
                        if(_isOpen())
                        {
                            writeLine(m_headerLine);
                        }
                        break;
                    case CsvMode::RESET:
                        break;
                    case CsvMode::MODIFY_FIELD:
                        break;
                    default:
                        break;
                    }
                }
                catch(const std::exception& w_e)
                {
                    std::cerr << " Error occured while opening file " << ai_csvPath << " : " << w_e.what() << '\n';
                }

                m_hasBeenOpened = _isOpen();
                 
            }
        }

        //====================================================================

        const bool Writer::_isOpen() const
        {
            return m_outputFile.is_open();
        }

        //====================================================================

        void Writer::_resetFile()
        {
            try
            {
                m_outputFile.open(m_csvFilePath, std::ios::trunc);
                if(!_isOpen())
                {
                    throw std::runtime_error("Unable to open file for reset.");
                }
                else
                {
                    m_outputFile.close();
                }
            }
            catch (const std::exception& w_e) {
                std::cout << "An error occurred: " << w_e.what() << std::endl;
            } catch (...) {
                std::cout << "An unknown error occurred" << std::endl;
            }    
        }

    } // End namespace Csv
} // End namespace Tools