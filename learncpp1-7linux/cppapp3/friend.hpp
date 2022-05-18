#ifndef FRIEND_HPP
#define FRIEND_HPP
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
  friend  Rectangle doubleup(Rectangle& r)
  {
      Rectangle c;
      c.width=2*r.width;
      c.height=2*r.height;
      return c;
  }
}
#endif // FRIEND_HPP
