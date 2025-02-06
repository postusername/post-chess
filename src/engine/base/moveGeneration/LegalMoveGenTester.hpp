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


#include <chrono>
#include <iomanip>
#include "LegalMoveGen.hpp"


#pragma once


#define nsecs std::chrono::high_resolution_clock::now().time_since_epoch().count()


class LegalMoveGenTester {
public:
    static void runTests();
private:
    struct Test {
        std::string shortFen;
        uint8_t enPassant;
        bool wlCastling;
        bool wsCastling;
        bool blCastling;
        bool bsCastling;
        uint8_t side;
        std::array<uint64_t, 6> nodes;
    };

    static void runTest(const Test &test);
    static uint64_t getNodesNumber(const Position& position, uint8_t side, uint32_t depth);
};