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


#ifndef AI_H
#define AI_H

#include <chrono>
#include <future>
#include <iomanip>

#include "MoveSorter.hpp"
#include "SearchInterrupter.hpp"
#include "TranspositionTable.hpp"
#include "../base/moveGeneration/LegalMoveGen.hpp"


using namespace std::chrono_literals;
#define nsecs std::chrono::high_resolution_clock::now().time_since_epoch().count()


class AI {
public:
    static Move getBestMove(const Position &position, uint8_t side, int32_t ms);

private:
    static std::tuple<int32_t, bool, Move> alphaBeta(const Position &position, uint8_t side, int32_t depthLeft);

    static std::tuple<int32_t, bool, Move> alphaBetaMin(const Position &position, int32_t alpha, int32_t beta,
                                                        int32_t depthLeft, int32_t depthCurrent = 0);

    static std::tuple<int32_t, bool, Move> alphaBetaMax(const Position &position, int32_t alpha, int32_t beta,
                                                        int32_t depthLeft, int32_t depthCurrent = 0);

    static int32_t alphaBetaMinOnlyCaptures(const Position &position, int32_t alpha, int32_t beta);

    static int32_t alphaBetaMaxOnlyCaptures(const Position &position, int32_t alpha, int32_t beta);

    struct INF {
        static constexpr int32_t NEGATIVE = -1e+9;
        static constexpr int32_t POSITIVE = 1e+9;
    };
};

#endif
