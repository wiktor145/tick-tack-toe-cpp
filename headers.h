#ifndef TICKTACKTOEH
#define TICKTACKTOEH

const double MIN_SCORE = -999999.0;


class Board {
public:
    char[3][3] T;
    Board * next;
};

class EvaluatedStep {
public:
    Board* board;
    double score;
    EvaluatedStep* next;
};


class AbstractStepSolver {
public:
    virtual void solve(Board *, int, int) = 0;

};

class ThreeStepSolver : AbstractStepSolver {
    private:
    Board * generatePossibleMoves(Board *);

    EvaluatedStep * evaluatePossibleMoves(Board *);

    void makeMove(EvaluatedStep *);

};


#endif // TICKTACKTOEH
