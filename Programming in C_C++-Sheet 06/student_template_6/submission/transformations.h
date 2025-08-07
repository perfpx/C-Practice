#pragma once

#include "aabb.h"
#include "point3d.h"
#include "shapes.h"

#include <memory>

/// shared abstract transformation base class containing a nested shape to be transformed
class Transformation : public Shape {
protected:
    Transformation(const Shape& shape);
public:
    Shape sub_shape;
};

// of course, one could implement all these transformations jointly as a single transformation matrix.
// for simplicity, we don't do that here.

class Scaled final : public Transformation {
    public:
        Scaled(const Shape &shape, const Point3D &scalingPoint);
        Shape clone_impl() const override;
        AABB getBounds_impl() const override;
        bool isInside_impl(const Point3D &point) const override;
    protected:
        Point3D scalingPoint;
};

class Translation final : public Transformation {
    public:
        Translation(const Shape &shape, const Point3D &scalingPoint);
        Shape clone_impl() const override;
        AABB getBounds_impl() const override;
        bool isInside_impl(const Point3D &point) const override;
    protected:
        Point3D scalingPoint;
};

class Rotation final : public Transformation {
    public:
        Rotation(const Shape &shape, const float angle, const Axis axis);
        Shape clone_impl() const override;
        AABB getBounds_impl() const override;
        bool isInside_impl(const Point3D &point) const override;
    protected:
        float angle;
        Axis axis;
};