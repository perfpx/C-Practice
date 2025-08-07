#include "operations.h"
#include "shapes.h"
#include <memory>
#include <sys/signal.h>

Operation::Operation(const Shape& shape_a, const Shape& shape_b)
    : sub_shape_a{shape_a.clone()}, sub_shape_b{shape_b.clone()}
{

}

AABB Operation::getBounds_impl() const
{
    return sub_shape_a.getBounds()+sub_shape_b.getBounds();
}

And::And(const Shape& shape_a, const Shape& shape_b) : Operation(shape_a, shape_b)
{

}
bool And::isInside_impl(const Point3D &p) const {

    if(sub_shape_a.isInside(p) && sub_shape_a.isInside(p)) {
        return true;
    }
    return false;
}

Shape And::clone_impl() const {
    return {std::make_shared<And>(sub_shape_a, sub_shape_b)};
}

Or::Or(const Shape& shape_a, const Shape& shape_b) : Operation(shape_a, shape_b) {}

bool Or::isInside_impl(const Point3D &p) const {
    if(sub_shape_a.isInside(p) || sub_shape_b.isInside(p)) {
        return true;
    }
    return false;
}

Shape Or::clone_impl() const {
    return {std::make_shared<And>(sub_shape_a, sub_shape_b)};
}

XOr::XOr(const Shape& shape_a, const Shape& shape_b) : Operation(shape_a, shape_b) {}

bool XOr::isInside_impl(const Point3D &p) const {

    if((sub_shape_a.isInside(p) && !sub_shape_b.isInside(p)) || (!sub_shape_a.isInside(p) && sub_shape_b.isInside(p))) {
        return true;
    }
    return false;
}

Shape XOr::clone_impl() const {
    return {std::make_shared<And>(sub_shape_a, sub_shape_b)};
}

Not::Not(const Shape& shape_a, const Shape&shape_b) : Operation(shape_a, shape_b) {}

bool Not::isInside_impl(const Point3D &p) const {
    if(!sub_shape_a.isInside(p) || !sub_shape_b.isInside(p)) {
        return true;
    }
    return false;
}

Shape Not::clone_impl() const {
    return {std::make_shared<Not>(sub_shape_a)};
}