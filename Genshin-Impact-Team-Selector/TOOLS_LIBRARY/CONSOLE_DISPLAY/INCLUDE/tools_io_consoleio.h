#ifndef TOOLS_IO_CONSOLEIO_H
#define TOOLS_IO_CONSOLEIO_H

#include <iostream>

namespace Tools
{
    namespace IO
    { 
        /*! @brief : Classe gérant les différents affichages console et entrées. */
        class ConsoleIO
        {
            public:
                enum class LogLevel
                {
                    NONE = 0, // Aucune trace
                    INFORMATIVE = 1, // Traces minimales requises
                    DEBUG = 2  // Toutes les traces de DEBUG
                };

                /*! @brief Couleurs d'affichage du texte. */
                namespace FrontColor 
                {
                    constexpr std::string RESET       = "\033[0m";
                    constexpr std::string BLACK       = "\033[30m";
                    constexpr std::string RED         = "\033[31m";
                    constexpr std::string GREEN       = "\033[32m";
                    constexpr std::string YELLOW      = "\033[33m";
                    constexpr std::string BLUE        = "\033[34m";
                    constexpr std::string MAGENTA     = "\033[35m";
                    constexpr std::string PURPLE      = "\e[0;35m";
                    constexpr std::string CYAN        = "\033[36m";
                    constexpr std::string WHITE       = "\033[37m";
                }

                /*! @brief Couleurs d'affichage du texte en gras. */
                namespace BoldColor 
                {
                    constexpr std::string BLACK       = "\033[1m\033[30m";
                    constexpr std::string RED         = "\033[1m\033[31m";
                    constexpr std::string GREEN       = "\033[1m\033[32m";
                    constexpr std::string YELLOW      = "\033[1m\033[33m";
                    constexpr std::string BLUE        = "\033[1m\033[34m";
                    constexpr std::string MAGENTA     = "\033[1m\033[35m";
                    constexpr std::string CYAN        = "\033[1m\033[36m";
                    constexpr std::string WHITE       = "\033[1m\033[37m";
                }

                /*! @brief Couleurs d'affichage du fond de texte. */
                namespace BgColor 
                {
                    constexpr std::string BLACK       = "\033[40m";
                    constexpr std::string RED         = "\033[41m";
                    constexpr std::string GREEN       = "\033[42m";
                    constexpr std::string YELLOW      = "\033[43m";
                    constexpr std::string BLUE        = "\033[44m";
                    constexpr std::string MAGENTA     = "\033[45m";
                    constexpr std::string CYAN        = "\033[46m";
                    constexpr std::string WHITE       = "\033[47m\033[30m";
                }

                /*=========================================================================================================================
                        AFFICHAGE
                =========================================================================================================================*/

                /*! @brief Affichage console
                 * @param ai_logLevel : niveau d'affichage
                 * @param ai_message : texte à afficher
                 * @param ai_frontColor : couleur d'affichage du texte
                 * @param ai_backgroundColor : couleur d'affichage de fond du texte
                 * @param ai_goBackToLine : retourner à la ligne
                */
                template <typename TType>
                static void display(
                    const LogLevel  ai_logLevel,
                    const TType&    ai_message,
                    const std::string     ai_frontColor = ::FrontColor::WHITE,
                    const std::string     ai_backgroundColor = ::BgColor::BLACK,
                    const bool      ai_goBackToLine = true
                ) const
                {
                    if(ai_logLevel <= g_logLevel)
                    {
                        std::cout 
                            << ai_frontColor 
                            << ai_backgroundColor 
                            << ai_message
                            << ::FrontColor::RESET
                            << ::BgColor::RESET
                            << (ai_goBackToLine)? "\n" : " "; 
                    }
                }

                /*! @brief Affichage console
                 * @param ai_logLevel : niveau d'affichage
                 * @param ai_message : texte à afficher
                 * @param ai_frontColor : couleur d'affichage du texte
                 * @param ai_backgroundColor : couleur d'affichage de fond du texte
                 * @param ai_endSeparator : Separateur de fin
                */
                template <typename TType>
                static void display(
                    const LogLevel  ai_logLevel,
                    const TType&    ai_message,
                    const std::string     ai_frontColor = ::FrontColor::WHITE,
                    const std::string     ai_backgroundColor = ::BgColor::BLACK,
                    const std::string     ai_endSeparator = "\n"
                ) const
                {
                    if(ai_logLevel <= g_logLevel)
                    {
                        std::cout 
                            << ai_frontColor 
                            << ai_backgroundColor 
                            << ai_message
                            << ::FrontColor::RESET
                            << ::BgColor::RESET
                            << ai_endSeparator; 
                    }
                }

                /*! @brief Affichage d'une erreur */
                template <typename TType>
                static void errorDisplay(
                    const LogLevel ai_logLevel,
                    const TType& ai_message
                ) const
                {
                    display<TType>(ai_logLevel, ai_message, ::FrontColor::WHITE, ::BgColor::RED, true);
                }

                /*! @brief Affichage d'un titre */
                template <typename TType>
                static void titleDisplay(
                    const LogLevel ai_logLevel,
                    const TType& ai_message
                ) const
                {
                    display<TType>(ai_logLevel, ai_message, ::FrontColor::WHITE, ::BgColor::BLUE, true);
                }

                /*! @brief Affichage d'un message */
                template <typename TType>
                static void messageDisplay(
                    const LogLevel ai_logLevel,
                    const TType& ai_message,
                    const std::string& ai_endSeparator = "\n"
                ) const
                {
                    display<TType>(ai_logLevel, ai_message, ::FrontColor::BLACK, ::BgColor::WHITE, ai_endSeparator);
                }


                /*! @brief Nettoyage de l'affichage de la console */
                static void clearConsole() {
                    try {
                        int w_error = std::system("clear");
                        if (w_error == -1) {
                            throw std::runtime_error("Permission denied to clear the system");
                        }
                    } catch (const std::exception& w_e) {
                        std::cout << "An error occurred: " << w_e.what() << std::endl;
                    }
                    catch (...) {
                        std::cout << "Couldn't clear" << std::endl;
                    }
                }

                /*=========================================================================================================================
                        ENTREE
                =========================================================================================================================*/

                /*! @brief Entree user */
                template <typename TOutputType, typename TMessageType>
                static TOutputType inputUser(const TMessageType& ai_message)
                {
                    // Reinitialiser le flux d'entree
                    std::cin.clear();
                    fflush(stdin);
                    
                    // Acquisition de l'entrée user
                    TOutputType w_userInput;
                    display<TMessageType>(LogLevel::DEBUG, ai_message, ::FrontColor::BLACK, ::BgColor::CYAN, false);
                    std::cout << '\t' <<::BoldColor::BOLD_BLUE;
                    std::cin >> w_userInput;
                    std::cout << RESET;
                    
                    return  w_userInput;
                }
            
            private:
                static std::uint8_t m_logLevel; 

        }; // Class
    } // Namespace IO
} // Namespace Tools

#endif

