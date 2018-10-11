#pragma once

#include "Point.h"

class Rect {
public:
    Rect() { }
    Rect(int x, int y, int width, int height)
        : m_location(x, y)
        , m_width(width)
        , m_height(height)
    {
    }

    void moveBy(int dx, int dy)
    {
        m_location.moveBy(dx, dy);
    }

    Point center() const
    {
        return { x() + width() / 2, y() + height() / 2 };
    }

    bool contains(int x, int y) const
    {
        return x >= m_location.x() && x <= right() && y >= m_location.y() && y <= bottom();
    }

    bool contains(const Point& point) const
    {
        return contains(point.x(), point.y());
    }

    int left() const { return x(); }
    int right() const { return x() + width(); }
    int top() const { return y(); }
    int bottom() const { return y() + height(); }

    int x() const { return location().x(); }
    int y() const { return location().y(); }
    int width() const { return m_width; }
    int height() const { return m_height; }

    void setX(int x) { m_location.setX(x); }
    void setY(int y) { m_location.setY(y); }
    void setWidth(int width) { m_width = width; }
    void setHeight(int height) { m_height = height; }

    Point location() const { return m_location; }

private:
    Point m_location;
    int m_width { 0 };
    int m_height { 0 };
};