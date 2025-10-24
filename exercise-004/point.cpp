#include "point.hpp"
#include <fmt/format.h>

Point::Point()
{

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
    int dx = other.m_x - m_x;
    int dy = other.m_y - m_y;
    return std::sqrt(dx*dx + dy*dy);
}

Point::~Point()
{

}
