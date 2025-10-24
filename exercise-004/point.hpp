#ifndef POINT_HPP
#define POINT_HPP

class Point {

    public: 
    Point();
    Point (int x, int y);
    ~Point();
    void move(int dx, int dy);
    void print() const;

    double distance(const Point& other) const;

    private:
    int m_x;
    int m_y;

};

#endif//POINT_HPP


