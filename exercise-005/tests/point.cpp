#include "point.hpp"
#include <fmt/format.h>

Point::Point()
{
    m_x = 0;
    m_y = 0;
}

Point::Point(int x, int y)
{
    m_x = x;
    m_y = y;

}
    
void Point::move(int dx, int dy)
{
    m_x = m_x + dx;
    m_y = m_y + dy;
}
void Point::print() const
{
    fmt::print("Point ({},{})\n", m_x, m_y);
}
double Point::distance(const Point& other) const
{
    double dx = other.m_x - m_x;
    double dy = other.m_y - m_y;
    return std::sqrt(dx*dx + dy*dy);
}

Point::~Point()
{

}
