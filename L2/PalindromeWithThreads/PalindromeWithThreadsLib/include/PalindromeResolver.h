#pragma once

#include <string>
#include <vector>
#include <tuple>

namespace ITEA {
namespace Coach {
namespace L2 {

class PalindromeResolver
{
public:
    using Word = std::u32string;
    using Words = std::vector<Word>;
    using PalindormeStrings = Words;
    using NonPalindormeStrings = PalindormeStrings;
    using PalindromeResults = std::tuple<NonPalindormeStrings, PalindormeStrings>;

    PalindromeResolver() = default;
    explicit PalindromeResolver(const Words& words);
    virtual ~PalindromeResolver() = default;

    virtual PalindromeResults resolve();

    static PalindromeResults resolve(const Words& words);

private:
    Words m_words;
};

} // ITEA
} // Coach
} // ITEA
