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


#ifndef MOVESORT_H
#define MOVESORT_H

#include "StaticEvaluator.hpp"
#include "../base/moveGeneration/MoveList.hpp"


class MoveSorter {
public:
    static MoveList sort(const Pieces &pieces, MoveList moves);

private:
    static int32_t evaluateMove(const Pieces &pieces, Move move);
};

#endif
