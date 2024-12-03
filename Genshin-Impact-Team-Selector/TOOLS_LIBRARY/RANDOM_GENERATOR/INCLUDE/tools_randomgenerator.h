#ifndef TOOLS_RANDOMGENERATOR_H
#define TOOLS_RANDOMGENERATOR_H

#include <iostream>
#include <random>

namespace Tools
{
    class RandomGenerator
    {
        public:

            /*! @brief Générer un random aléatoire entre min et max. */
            template<typename TType>
            static TType generate_random(const TType& ai_minNum, const TType& ai_maxNum)
            {
                // Mersenne Twister 19937 generator
                std::random_device w_rd;
                std::mt19937 w_gen(w_rd()); 
                std::uniform_int_distribution<TType> distribution(ai_minNum, ai_maxNum);
                TType w_randomIndex = distribution(w_gen);
                return w_randomIndex;
            }

    }; // Class 
} // Namespace Tools

#endif

