#include <headers.h>


void ThreeStepSolver::solve(Board* board, int currentDepth, int maxDepth) {
    if (currentDepth == maxDepth) {
        return;
    }

    Board * possibleSteps = generatePossibleMoves(board);

    EvaluatedStep * evaluatedSteps = evaluatePossibleMoves(possibleSteps);

    makeMove(evaluatedSteps);
}

void ThreeStepSolver::makeMove(EvaluatedStep * evaluatedSteps) {
    if (evaluatedSteps == nullptr) {
        return;
    }

    Board * bestMove = nullptr;
    double bestScore = MIN_SCORE;







}




