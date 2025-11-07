/*
 *  chess-cpp
 *  Copyright (C) 2025 postusername
 *
 *  chess-cpp is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  chess-cpp is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with chess-cpp.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef AI_REGRESSION_TESTER_H
#define AI_REGRESSION_TESTER_H

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "AI.hpp"


class AIRegressionTester {
public:
    static void runTests();

private:
    struct GameResult {
        std::string result; // "white", "black", "draw"
        int32_t moves;
        int32_t totalTimeMs;
    };

    static GameResult playGame(int32_t timePerMoveMs, int32_t maxMoves);
    static void saveResults(const std::vector<GameResult> &results, const std::string &filename);
};

#endif
