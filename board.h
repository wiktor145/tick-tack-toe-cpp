#ifndef TTT_BOARD
#define TTT_BOARD

enum Field {
    field_free = 0,
    field_x = 1,
    field_o = 2
};

struct Board {
    Field * T;
    int boardSize;
};

char fieldToChar(Field field);


#endif // TTT_BOARD
