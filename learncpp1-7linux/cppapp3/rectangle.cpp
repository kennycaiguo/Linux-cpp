#include "rectangle.h"


Rectangle doubleup(Rectangle& r)
{
    Rectangle c;
    c.width=2*r.width;
    c.height=2*r.height;
    return c;
}
