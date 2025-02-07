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


#ifndef LEGALMOVGEN_H
#define LEGALMOVGEN_H

#include "MoveList.hpp"
#include "PsLegalMoveMaskGen.hpp"


class LegalMoveGen {
public:
    static MoveList generate(const Position &position, uint8_t side, bool onlyCaptures = false);
private:
    static void pieceMaskToMoves(const Pieces &pieces, Bitboard mask, uint8_t attackerP, uint8_t attackerType, uint8_t attackerSide, MoveList &moves);
    static void pawnsMaskToMoves(const Pieces &pieces, Bitboard mask, uint8_t attackerSide, int8_t attackerIndex, bool checkDefender, uint8_t flag, MoveList &moves);

    static bool isLegal(Pieces pieces, Move move);

    static void addEnPassantCaptures(const Pieces &pieces, uint8_t side, uint8_t enPassant, MoveList &moves);
    static void addCastlingMoves(const Pieces &pieces, uint8_t side, bool lCastling, bool sCastling, MoveList &moves);
};

#endif
