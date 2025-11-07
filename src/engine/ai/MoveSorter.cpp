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


#include "MoveSorter.hpp"
#include <algorithm>


MoveList MoveSorter::sort(const Pieces &pieces, MoveList moves) {
    std::sort(moves.begin(), moves.end(), [&pieces](const Move& a, const Move& b) {
        return MoveSorter::evaluateMove(pieces, a) > MoveSorter::evaluateMove(pieces, b);
    });
    return moves;
}


int32_t MoveSorter::evaluateMove(const Pieces &pieces, Move move) {
    int32_t evaluation = 0;

    if (move.getAttackerType() != PIECE::PAWN) {
        Bitboard opponentPawnsAttacks = PsLegalMoveMaskGen::generatePawnsLeftCapturesMask(
                                            pieces, Pieces::inverse(move.getAttackerSide()), true) |
                                        PsLegalMoveMaskGen::generatePawnsRightCapturesMask(
                                            pieces, Pieces::inverse(move.getAttackerSide()), true);
        if (BOp::getBit(opponentPawnsAttacks, move.getTo())) {
            switch (move.getAttackerType()) {
                case PIECE::KNIGHT:
                    evaluation = evaluation - StaticEvaluator::MATERIAL::KNIGHT;
                    break;
                case PIECE::BISHOP:
                    evaluation = evaluation - StaticEvaluator::MATERIAL::BISHOP;
                    break;
                case PIECE::ROOK:
                    evaluation = evaluation - StaticEvaluator::MATERIAL::ROOK;
                    break;
                case PIECE::QUEEN:
                    evaluation = evaluation - StaticEvaluator::MATERIAL::QUEEN;
                    break;
                default:
                    break;
            }
        }
    }

    if (move.getDefenderType() != Move::NONE) {
        switch (move.getDefenderType()) {
            case PIECE::PAWN:
                evaluation = evaluation + 1000 * StaticEvaluator::MATERIAL::PAWN;
                break;
            case PIECE::KNIGHT:
                evaluation = evaluation + 1000 * StaticEvaluator::MATERIAL::KNIGHT;
                break;
            case PIECE::BISHOP:
                evaluation = evaluation + 1000 * StaticEvaluator::MATERIAL::BISHOP;
                break;
            case PIECE::ROOK:
                evaluation = evaluation + 1000 * StaticEvaluator::MATERIAL::ROOK;
                break;
            case PIECE::QUEEN:
                evaluation = evaluation + 1000 * StaticEvaluator::MATERIAL::QUEEN;
                break;
            default:
                break;
        }

        switch (move.getAttackerType()) {
            case PIECE::PAWN:
                evaluation = evaluation - StaticEvaluator::MATERIAL::PAWN;
                break;
            case PIECE::KNIGHT:
                evaluation = evaluation - StaticEvaluator::MATERIAL::KNIGHT;
                break;
            case PIECE::BISHOP:
                evaluation = evaluation - StaticEvaluator::MATERIAL::BISHOP;
                break;
            case PIECE::ROOK:
                evaluation = evaluation - StaticEvaluator::MATERIAL::ROOK;
                break;
            case PIECE::QUEEN:
                evaluation = evaluation - StaticEvaluator::MATERIAL::QUEEN;
                break;
            default:
                break;
        }
    }

    return evaluation;
}
