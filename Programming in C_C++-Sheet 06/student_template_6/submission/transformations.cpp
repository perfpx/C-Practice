#include "transformations.h"
#include "aabb.h"
#include "point3d.h"
#include "shapes.h"
#include <cmath>
#include <memory>
#include <stdexcept>

// helper function for 2D rotations
std::pair<float, float> rotate2D(float x, float y, float angle)
{
    float sin, cos;
    __sincosf(angle, &sin, &cos); // in Mac OSX sincosf may not be found, try __sincosf. But you need to use sincosf for submission.

    return {cos*x-sin*y, sin*x+cos*y};
}


Transformation::Transformation(const Shape& shape)
    : sub_shape{shape.clone()}
{

}

/** Scaled */

Scaled::Scaled(const Shape& shape_, const Point3D& scalingPoint_): Transformation(shape_.clone()) {

    scalingPoint = Point3D(scalingPoint_);
}

Shape Scaled::clone_impl() const {
    return {std::make_shared<Scaled>(Scaled::sub_shape, scalingPoint)};
}

AABB Scaled::getBounds_impl() const {

    Point3D minPoint, maxPoint;

    minPoint = sub_shape.getBounds().min * scalingPoint;
    maxPoint = sub_shape.getBounds().max * scalingPoint;

    return AABB{minPoint, maxPoint};
}

bool Scaled::isInside_impl(const Point3D &point) const {
    return sub_shape.isInside(point / scalingPoint);
}

/** Translation*/

Translation::Translation(const Shape& shape_, const Point3D& scalingPoint_) : Transformation(shape_.clone()) {
    scalingPoint = scalingPoint_;
}

Shape Translation::clone_impl() const {
    return {std::make_shared<Translation>(Transformation::sub_shape, scalingPoint)};
}

AABB Translation::getBounds_impl() const {
    Point3D maxPoint, minPoint;
    minPoint = sub_shape.getBounds().min + scalingPoint;
    maxPoint = sub_shape.getBounds().max + scalingPoint;

    return AABB{minPoint, maxPoint};
}

bool Translation::isInside_impl(const Point3D &point) const {
    return Translation::sub_shape.isInside(point - scalingPoint);
}

/** Rotation*/

Rotation::Rotation(const Shape& shape_, const float angle_, const Axis axis_):Transformation(shape_.clone()) {
    angle = angle_;
    axis = axis_;
}

Shape Rotation::clone_impl() const {
    return {std::make_shared<Rotation>(sub_shape, angle, axis)};
}

AABB Rotation::getBounds_impl() const {

    const float root = std::sqrt(2);

    Point3D scalingPoint;

    switch (axis) {
    case Axis::X:
        scalingPoint = Point3D{1, root, root};
        return AABB{sub_shape.getBounds().min*scalingPoint, sub_shape.getBounds().max*scalingPoint};
    case Axis::Y:
        scalingPoint = Point3D{root, 1, root};
        return AABB{sub_shape.getBounds().min*scalingPoint, sub_shape.getBounds().max*scalingPoint};
    case Axis::Z:
        scalingPoint = Point3D{root, root, 1};
        return AABB{sub_shape.getBounds().min*scalingPoint, sub_shape.getBounds().max*scalingPoint};
    default:
        throw std::runtime_error("Invalid Axis");
        break;
    }
}

bool Rotation::isInside_impl(const Point3D &point) const {
  Point3D rotatingPoint;
  
  switch (axis) {
    case Axis::X: {
        auto [y, z] = rotate2D(point.y, point.z, -angle);
        rotatingPoint = Point3D{point.x, y, z};
        break;  
    }
  case Axis::Y: {
    auto [z, x] = rotate2D(point.z, point.x, -angle);
    rotatingPoint = Point3D{x, point.y, z};
    break;
  }

  case Axis::Z: {
    auto [x, y] = rotate2D(point.x, point.y, -angle);
    rotatingPoint = Point3D{x, y, point.z};
    break;
  }
  default: {
    throw std::runtime_error("You provided an invalid axis!");
    break;
  }
  }

  return sub_shape.isInside(rotatingPoint);
}