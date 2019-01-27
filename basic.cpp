#include "basic.h"

Cdraw basic::draw;

basic::basic(int x, int y, const bool z, int mm[width][height]):pos({ x, y }), time(clock()), dir(up), player(z), map(mm)
{
}

basic::~basic()
{
}


