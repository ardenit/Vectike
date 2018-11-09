
#include <iostream>
#include "vector.h"

Vector::Vector(double x1, double y1, double x2, double y2, double width, Color color) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    length_ = sqrt(dx * dx + dy * dy);
    width_ = width;
    color_ = color;
    double angle = MathUtils::GetAngle(dx / length_, dy / length_);
    AddTransform(std::shared_ptr<Transform>(new RotateTransform(angle, 0, 0)));
    AddTransform(std::shared_ptr<Transform>(new MoveTransform(x1, y1)));
}

Vector::Vector(double length, double width, Color color) {
    length_ = length;
    width_ = width;
    color_ = color;
}
bool Vector::ContainsPoint(Point p) const {
    return p.x >= 0 && p.x <= length_ && p.y <= width_/2 && p.y >= -width_/2;
}

Color Vector::GetPointColor(double x, double y) const{
    //TODO изменение длины/ширины со временем
    Point current_point(x, y);
    for(auto iter = transforms_.rbegin(); iter != transforms_.rend(); ++iter) {
        current_point = iter->get()->GetOriginalPoint(current_point);
    }
    return ContainsPoint(current_point) ? color_ : Color::EmptyColor();
}
void Vector::AddTransform(std::shared_ptr<Transform> transform) {
    transforms_.push_back(transform);
}