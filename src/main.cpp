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


#define TEST_LEGAL_MOVE_GENERATOR false
#define SHOW_UI true


#include <iostream>
#include <string>

#if TEST_LEGAL_MOVE_GENERATOR
    #include "engine/base/moveGeneration/LegalMoveGenTester.hpp"
#elif SHOW_UI
    #include "ui/UI.hpp"
#endif

#include "engine/base/moveGeneration/LegalMoveGenTester.hpp"
#include "engine/ai/AIRegressionTester.hpp"


int main(int argc, char* argv[]) {
    // Check for command-line arguments
    if (argc > 1) {
        std::string arg = argv[1];
        
        if (arg == "--test-movegen") {
            LegalMoveGenTester::runTests();
            return 0;
        } else if (arg == "--test-ai-regression") {
            AIRegressionTester::runTests();
            return 0;
        } else if (arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [option]" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "  --test-movegen        Run move generation tests" << std::endl;
            std::cout << "  --test-ai-regression  Run AI regression tests" << std::endl;
            std::cout << "  --help                Show this help message" << std::endl;
            std::cout << "  (no option)           Start the UI" << std::endl;
            return 0;
        } else {
            std::cerr << "Unknown option: " << arg << std::endl;
            std::cerr << "Use --help for available options" << std::endl;
            return 1;
        }
    }

    #if TEST_LEGAL_MOVE_GENERATOR
        LegalMoveGenTester::runTests();
    #elif SHOW_UI
        UI ui;
        ui.start();
    #endif

    return 0;
}