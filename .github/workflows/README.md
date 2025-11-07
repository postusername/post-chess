# AI Regression Testing

This directory contains the GitHub Actions workflow for testing the chess engine AI for regressions.

## Overview

The AI regression testing system runs automated self-play matches between the chess engine playing against itself. This helps detect:

- **Performance regressions**: Significant increases in computation time
- **Strength regressions**: Changes that make the AI weaker or behave differently
- **Consistency issues**: Variations in game outcomes that may indicate bugs

## How It Works

1. **Self-Play Matches**: The workflow runs multiple games where the AI plays both sides
2. **Metrics Collection**: For each game, it records:
   - Game outcome (white win, black win, or draw)
   - Number of moves played
   - Total computation time
3. **Baseline Comparison**: Results are compared against a stored baseline from previous runs
4. **Regression Detection**: Alerts if performance degrades beyond acceptable thresholds

## Workflow Triggers

The workflow runs:
- On pull requests to `main` or `master` branches
- Manually via workflow_dispatch

## Setting Up a Baseline

When first introduced, the workflow has no baseline to compare against. To establish one:

1. Run the workflow (it will execute on the next PR or manual trigger)
2. Go to the workflow run in GitHub Actions
3. Download the artifact named `ai-regression-results-<sha>`
4. Go to any workflow run and manually upload this artifact as `ai-regression-baseline`
   - You can use the GitHub CLI: `gh run upload <run-id> ai_regression_results.json --name ai-regression-baseline`
   - Or use the Actions API to upload artifacts

Alternatively, you can create a one-time workflow run to establish the baseline:

```yaml
# .github/workflows/create-baseline.yml
name: Create AI Regression Baseline
on: workflow_dispatch
jobs:
  create-baseline:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Install dependencies
        run: sudo apt-get update && sudo apt-get install -y cmake make g++ libsfml-dev
      - name: Build and test
        run: |
          mkdir -p build && cd build
          cmake .. -DCMAKE_BUILD_TYPE=Release && make
          ./chess-cpp --test-ai-regression
      - name: Upload as baseline
        uses: actions/upload-artifact@v4
        with:
          name: ai-regression-baseline
          path: build/ai_regression_results.json
          retention-days: 400
```

## Regression Thresholds

The workflow considers it a regression if:

- **Time increases by >50%**: The AI takes significantly longer to make moves
- **Average moves decrease by >30%**: Games end much faster, potentially indicating weaker play

These thresholds can be adjusted in the workflow file.

## Interpreting Results

### Example PR Comment

```
## AI Regression Test Results

**Games played:** 3
**Results:**
- White wins: 1
- Black wins: 0
- Draws: 2

**Performance:**
- Average moves per game: 45.3
- Average time per game: 23450ms

### Comparison with Baseline
- Time change: +2.5%
- Moves change: -3.1%
```

### What to Look For

- **Consistent results**: White/black win rates should be roughly equal (the AI plays both sides)
- **Stable performance**: Time and move counts should be similar to baseline
- **Draw rate**: Higher draw rates often indicate stronger play in chess engines

## Running Tests Locally

You can run the regression tests locally:

```bash
cd build
./chess-cpp --test-ai-regression
```

This will:
1. Run 3 self-play games
2. Save results to `ai_regression_results.json`
3. Print a summary to the console

## Configuration

Test parameters can be modified in `src/engine/ai/AIRegressionTester.cpp`:

- `numGames`: Number of games to play (default: 2)
- `timePerMoveMs`: Time allocated per move in milliseconds (default: 500)
- `maxMoves`: Maximum moves before declaring a draw (default: 40)

## Limitations

- **Determinism**: The AI may use randomness or timing-dependent behavior, causing variation
- **Small sample size**: With few games, statistical noise can affect results
- **Time sensitivity**: Running on different hardware will affect absolute time measurements

## Future Improvements

Potential enhancements:
- Increase number of test games for better statistical significance
- Add position-specific tests (e.g., endgame positions, tactical puzzles)
- Track Elo rating changes over time
- Compare against external chess engines (Stockfish, etc.)
- Add memory usage profiling
