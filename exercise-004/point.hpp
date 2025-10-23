#ifndef POINT_HPP
#define POINT_HPP

class Point {
    public:
        Point();
        Point(double x, double y);
        ~Point();
    private:
        double m_x;
        double m_y;


};

#endif // POINT_HPP