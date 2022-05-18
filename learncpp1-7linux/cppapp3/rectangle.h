#ifndef RECTANGLE_H
#define RECTANGLE_H


class Rectangle{
    int width,height;
public:
    Rectangle()=default;
    Rectangle(int w,int h)
    {
        this->width=w;
        this->height=h;
    }
    int getArea(void){
        return width*height;
    }
  friend  Rectangle doubleup(Rectangle& r);

};

#endif // RECTANGLE_H
