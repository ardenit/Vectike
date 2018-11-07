#include "move-transform.h"
#include "../drawables/drawable.h"

MoveTransform::MoveTransform(double dx, double dy) {
    dx_ = dx;
    dy_ = dy;
}

void MoveTransform::ApplyTo(std::shared_ptr<Drawable> drawable) const {
    drawable->Move(dx_, dy_);
}