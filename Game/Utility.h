#pragma once

#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>

namespace projectz {
    namespace game {
        class Utility
        {
        public:
            static std::set<int> WriteHighScore(int score);
        };
    }
}