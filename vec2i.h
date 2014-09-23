#ifndef __VEC2_H__
#define __VEC2_H__

struct Vec2i {
    int x, y;
    Vec2i(int X, int Y) : x(X), y(Y) {}
    inline Vec2i operator +(const Vec2i &v) const { return Vec2i(x+v.x, y+v.y); }
    inline Vec2i operator -(const Vec2i &v) const { return Vec2i(x-v.x, y-v.y); }
};

#endif //__VEC2_H__
