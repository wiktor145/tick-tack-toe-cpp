#include "board.h"

char fieldToChar(Field field) {
    switch (field) {
    case Field(field_free):
        return ' ';
        break;

    case Field(field_x):
        return 'X';
        break;

    case Field(field_o):
        return 'O';
        break;
    }
}
