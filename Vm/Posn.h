#ifndef Posn_h
#define Posn_h

struct Posn {
    int x;
    int y;
    
    Posn(): x{0}, y{0} {}
    Posn(int x, int y): x{x}, y{y} {}
    
    bool operator==(const Posn &other) const { return x == other.x && y == other.y; }
    bool operator!=(const Posn &other) const { return x != other.x || y != other.y; }
};

#endif
