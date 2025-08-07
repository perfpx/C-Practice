#include "shapes.h"

#include "point3d.h"
#include "transformations.h"
#include "operations.h"

#include <cmath>
#include <memory>
#include <stdexcept>

Shape::Shape(std::shared_ptr<Shape>&& shape) noexcept
    : instance{std::move(shape)} // take ownership
{

}

Shape Shape::clone() const
{
    // if this shape just contains a pointer, we can return a simple copy
    if (instance)
        return *this;

    // otherwise, call the derived clone implementation
    return clone_impl();
}

AABB Shape::getBounds() const {
    // call the nested shape (if any)
    if (instance)
        return instance->getBounds();

    // otherwise, call the derived getBounds implementation
    return getBounds_impl();
}

bool Shape::isInside(const Point3D& p) const
{
    // call the nested shape (if any)
    if (instance)
        return instance->isInside(p);

    // otherwise, call the derived isInside implementation
    return isInside_impl(p);
}

Shape Shape::clone_impl() const
{
    // no default implementation available (but cannot set = 0, since we want to have instances of Shape)
    // if you get this error, you forgot to implement the override
    throw std::logic_error("clone called on an abstract shape");
}

AABB Shape::getBounds_impl() const
{
    // fallback default implementation
    return AABB{-1.0f, 1.0f};
}

bool Shape::isInside_impl(const Point3D&) const
{
    // no fallback implementation (but cannot set = 0, since we want to have instances of Shape)
    // if you get this error, you forgot to implement the override
    throw std::logic_error("isInside called on an abstract shape");
}

Shape Empty::clone_impl() const
{
    return {std::make_shared<Empty>()};
}

bool Empty::isInside_impl(const Point3D&) const {
    return false;
}

AABB Empty::getBounds_impl() const
{
    return AABB{};
}

Shape Cube::clone_impl() const
{
    return {std::make_shared<Cube>()};
}

bool Cube::isInside_impl(const Point3D& p) const {
    return getBounds().contains(p);
}

/** Sphere */

Sphere::Sphere(Point3D center_, double radius_) {
    center = center_;
    radius = radius_;
}
Sphere::Sphere() {
    radius = 1.0;
    center = Point3D();
}

Shape Sphere::clone_impl() const {

    return {std::make_shared<Sphere>()};
}

bool Sphere::isInside_impl(const Point3D &p) const {
    return std::sqrt( std::powf(p.x, 2) + std::powf(p.y, 2) + std::powf(p.z, 2)) <= radius;
}

/** Cylinder */

Cylinder::Cylinder(Point3D point_, double radius_, double height_) {
    point = point_;
    radius = radius_;
    height = height_;
}

Cylinder::Cylinder() {
    point = Point3D();
    radius = 1.0;
    height = 2.0;
}

Shape Cylinder::clone_impl() const {

    return {std::make_shared<Cylinder>()};
}

bool Cylinder::isInside_impl(const Point3D &p) const {

    return (std::sqrt(std::powf(p.x, 2) + std::powf(p.y, 2)) <= 1 && - 1 <= p.z && p.z <= 1);
}

/** Octahedron */

Octahedron::Octahedron(Point3D point_, double radius_) {
    radius = radius_;
    point = point_;
}

Octahedron::Octahedron() {
    radius = 1.0;
    point = Point3D();
}

Shape Octahedron::clone_impl() const {

    return {std::make_shared<Octahedron>()};
}

bool Octahedron::isInside_impl(const Point3D &p) const {
    return (std::abs(p.x) + std::abs(p.y) + std::abs(p.z) <= 1);
}

Shape Shape::operator&(const Shape &other) const {
    return And(*this, other).clone();
}

Shape Shape::operator|(const Shape &other) const {
    return Or(*this, other).clone();
}
Shape Shape::operator^(const Shape &other) const {
    return XOr(*this, other).clone();
}

Shape Shape::operator!() const {
   // return Not(*this).clone();
}

Shape Shape::operator+(const Shape &other) const {
    return *this | other;
}

Shape Shape::operator-(const Shape &other) const {
   // return And(*this, Not(other)).clone();
}

Shape Shape::scaled(Point3D factor) const {
    Scaled scale = Scaled(*this, factor);
    return scale.clone();
} 

Shape Shape::translated(Point3D offset) const {
    Translation translate = Translation(*this, offset);
    return translate.clone();
} 


Shape Shape::rotated(Axis axis, float angle) const {
    Rotation rotate = Rotation(*this, angle, axis);
    return rotate.clone();
} 
