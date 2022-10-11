#include "Cell.h"
Cell::Cell()
{
}
Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;
    this->piece = NULL;
}

Cell::~Cell()
{
}
