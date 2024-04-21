#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        HASH_INDEX_T w[5] {0};
        int i = 4;
        std::string temp = k;
        size_t n = temp.size();
        while (n > 6) 
        {
            w[i] = baseConversionPower(temp.substr(n - 6, 6));
            temp = temp.substr(0, n - 6);
            n = temp.size();
            i--;
        }
        if (n > 0 && i >= 0) w[i] = baseConversionPower(temp);

        HASH_INDEX_T h = 0;
        for(int index = 0; index < 5; index++)
        {
            h += rValues[index] * w[index];
        }   
        return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        if (std::isdigit(letter))
        {
            return 26 + (letter - '0');
        }
        else
        {
            char lowercase = std::tolower(letter);
            return lowercase - 'a';
        }

    }
    
    HASH_INDEX_T baseConversionPower(const std::string& substring) const
    {
        if (substring.size() == 1)
            return letterDigitToNumber(substring[0]);
        int n = substring.size();
        return letterDigitToNumber(substring[n-1]) + 36 * baseConversionPower(substring.substr(0, n-1));
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
