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


#include "AIRegressionTester.hpp"
#include "../base/positionRepresentation/Position.hpp"
#include "../base/moveGeneration/LegalMoveGen.hpp"
#include "../base/moveGeneration/PsLegalMoveMaskGen.hpp"


void AIRegressionTester::runTests() {
    std::cout << "=== AI Regression Testing ===" << std::endl;
    std::cout << "Running self-play matches..." << std::endl << std::endl;

    const int32_t numGames = 2;
    const int32_t timePerMoveMs = 500; // 0.5 second per move
    const int32_t maxMoves = 40; // Maximum moves per game

    std::vector<GameResult> results;

    for (int32_t i = 0; i < numGames; i++) {
        std::cout << "Game " << (i + 1) << "/" << numGames << std::endl;
        GameResult result = playGame(timePerMoveMs, maxMoves);
        results.push_back(result);
        std::cout << "Result: " << result.result 
                  << ", Moves: " << result.moves 
                  << ", Time: " << result.totalTimeMs << "ms" << std::endl << std::endl;
    }

    saveResults(results, "ai_regression_results.json");

    // Print summary
    int32_t whiteWins = 0;
    int32_t blackWins = 0;
    int32_t draws = 0;
    int32_t totalMoves = 0;
    int32_t totalTime = 0;

    for (const auto &result : results) {
        if (result.result == "white") whiteWins++;
        else if (result.result == "black") blackWins++;
        else draws++;
        totalMoves += result.moves;
        totalTime += result.totalTimeMs;
    }

    std::cout << "=== Summary ===" << std::endl;
    std::cout << "Total games: " << numGames << std::endl;
    std::cout << "White wins: " << whiteWins << std::endl;
    std::cout << "Black wins: " << blackWins << std::endl;
    std::cout << "Draws: " << draws << std::endl;
    std::cout << "Average moves per game: " << (totalMoves / numGames) << std::endl;
    std::cout << "Average time per game: " << (totalTime / numGames) << "ms" << std::endl;
}


AIRegressionTester::GameResult AIRegressionTester::playGame(int32_t timePerMoveMs, int32_t maxMoves) {
    // Initialize position with standard starting position
    Position position(
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR",
        Position::NONE,  // en passant
        true,  // white long castling
        true,  // white short castling
        true,  // black long castling
        true,  // black short castling
        0.0f   // move counter
    );
    uint8_t currentSide = SIDE::WHITE;
    int32_t moveCount = 0;
    int32_t totalTimeMs = 0;

    while (moveCount < maxMoves) {
        // Check if there are legal moves
        MoveList legalMoves = LegalMoveGen::generate(position, currentSide);
        
        if (legalMoves.getSize() == 0) {
            // No legal moves - checkmate or stalemate
            // Check if in check to distinguish checkmate from stalemate
            Bitboard kingBitboard = position.getPieces().getPieceBitboard(currentSide, PIECE::KING);
            if (kingBitboard == 0) {
                // No king - should not happen in normal chess
                break;
            }
            uint8_t kingSquare = BOp::bsf(kingBitboard);
            bool inCheck = PsLegalMoveMaskGen::inDanger(position.getPieces(), kingSquare, currentSide);
            
            if (inCheck) {
                // Checkmate
                if (currentSide == SIDE::WHITE) {
                    return GameResult{"black", moveCount, totalTimeMs};
                } else {
                    return GameResult{"white", moveCount, totalTimeMs};
                }
            } else {
                // Stalemate
                return GameResult{"draw", moveCount, totalTimeMs};
            }
        }

        // Check for draw by fifty-move rule or repetition
        if (position.fiftyMovesRuleDraw() || position.threefoldRepetitionDraw()) {
            return GameResult{"draw", moveCount, totalTimeMs};
        }

        // Get AI move
        auto start = std::chrono::high_resolution_clock::now();
        Move move = AI::getBestMove(position, currentSide, timePerMoveMs);
        auto end = std::chrono::high_resolution_clock::now();
        int32_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        totalTimeMs += elapsed;

        // Make the move
        position.move(move);
        moveCount++;
        currentSide = Pieces::inverse(currentSide);
    }

    // Max moves reached - draw
    return GameResult{"draw", moveCount, totalTimeMs};
}


void AIRegressionTester::saveResults(const std::vector<GameResult> &results, const std::string &filename) {
    std::ofstream file(filename);
    
    file << "{" << std::endl;
    file << "  \"results\": [" << std::endl;
    
    for (size_t i = 0; i < results.size(); i++) {
        const auto &result = results[i];
        file << "    {" << std::endl;
        file << "      \"result\": \"" << result.result << "\"," << std::endl;
        file << "      \"moves\": " << result.moves << "," << std::endl;
        file << "      \"totalTimeMs\": " << result.totalTimeMs << std::endl;
        file << "    }";
        if (i < results.size() - 1) {
            file << ",";
        }
        file << std::endl;
    }
    
    file << "  ]" << std::endl;
    file << "}" << std::endl;
    
    file.close();
    std::cout << "Results saved to " << filename << std::endl;
}
