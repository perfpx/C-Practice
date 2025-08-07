#include "voxel_grid.h"

#include "point3d.h"
#include "transformations.h"
#include "operations.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

VoxelGrid::VoxelGrid(const Shape& shape)
{
    //throw std::logic_error("task 6.4 b)");
    //(void) shape; // silence unused parameter warning

    Point3D resVec = shape.getBounds().extents() * level_of_detail;

    if(resVec < 0){
        res_x = 1;
        res_y = 1;
        res_z = 1;
        voxels.push_back(false);
        return;
    }

    auto [X, Y, Z] = resVec;

    bounds = shape.getBounds();
    res_x = std::abs(X);
    res_y = std::abs(Y);
    res_z = std::abs(Z);

    voxels.reserve(res_x * res_y * res_z);

    for(unsigned int a = 0; a < res_x; a++){
        for(unsigned int b = 0; b < res_y; b++){
            for(unsigned int c = 0; c < res_z; c++){
                Point3D point = voxelCenter(a, b, c);
                voxels.push_back(shape.isInside(point));
            }
        }
    }

}

std::tuple<uint32_t, uint32_t, uint32_t> VoxelGrid::getResolution() const
{
    return {res_x, res_y, res_z};
}

VoxelSlice VoxelGrid::extractSlice(Axis axis, uint32_t slice) const
{
    //throw std::logic_error("task 6.4 d)");
    //(void) axis, (void) slice; // silence unused parameter warning

    switch(axis){
        case(Axis::X):{
            VoxelSlice voxSlice = VoxelSlice(res_y, res_z);
            for(int y = 0; y < res_y; y++){
                for(int z = 0; z < res_z; z++){
                    voxSlice.data[y][z] = isSet(slice, y, z);
                }
            }
            return voxSlice;
        }
        case(Axis::Y):{
            VoxelSlice voxSlice = VoxelSlice(res_x, res_z);
            for(int x = 0; x < res_x; x++){
                for(int z = 0; z < res_z; z++){
                    voxSlice.data[x][z] = isSet(x, slice, z);
                }
            }
            return voxSlice;
        }
        case(Axis::Z):{
            VoxelSlice voxSlice = VoxelSlice(res_x, res_y);
            for(int y = 0; y < res_y; y++){
                for(int x = 0; x < res_x; x++){
                    voxSlice.data[y][x] = isSet(x, y, slice);
                }
            }
            return voxSlice;
        }
        default:
            throw (std::runtime_error("You provided an invalid axis!"));

    }
}

Shape VoxelGrid::clone_impl() const
{
    return {std::make_shared<VoxelGrid>(*this)};
}

AABB VoxelGrid::getBounds_impl() const
{
    return bounds;
}

bool VoxelGrid::isInside_impl(const Point3D& p) const
{
    //throw std::logic_error("task 6.4 f)");
    //(void) p; // silence unused parameter warning

    if(p.x <= bounds.min.x || p.y <= bounds.min.y || p.z <= bounds.min.z) {
        return false;
    }
    else if (p.x >= bounds.max.x || p.y >= bounds.max.y || p.z >= bounds.max.z) {
        return false;
    }
    else if (p < bounds.min || p > bounds.max) {
        return false;
    }

    Point3D voxCoordinates = (p - bounds.min) * Point3D(level_of_detail);

    unsigned int x = std::trunc(voxCoordinates.x);
    unsigned int y = std::trunc(voxCoordinates.y);
    unsigned int z = std::trunc(voxCoordinates.z);

    return isSet(x, y, z);
}

bool VoxelGrid::isSet(uint32_t x, uint32_t y, uint32_t z) const
{
    // When running in debug mode, these will check whether the supplied indices are valid or "trap" to the debugger.
    // When no debugger is running, failing the assertion will terminate the program immediately.
    // When compiled in release mode, assert() does nothing.
    assert(x < res_x);
    assert(y < res_y);
    assert(z < res_z);

    //throw std::logic_error("task 6.4 c)");

    unsigned int val = (z + res_z * (y + res_y * x));
    return voxels.at(val);
}

Point3D VoxelGrid::voxelCenter(uint32_t x, uint32_t y, uint32_t z) const
{
    //throw std::logic_error("task 6.4 a)");
    //(void) x, (void) y, (void) z; // silence unused parameter warning

    float xPoint = 1 / static_cast<float>(res_x) * (static_cast<float>(x) + 0.5);
    float yPoint = 1 / static_cast<float>(res_y) * (static_cast<float>(y) + 0.5);
    float zPoint = 1 / static_cast<float>(res_z) * (static_cast<float>(z) + 0.5);

    return Point3D{xPoint, yPoint, zPoint} * bounds.extents() + bounds.min;
}

std::ostream& operator<<(std::ostream& ostream, const VoxelSlice& slice)
{
    //throw std::logic_error("task 6.4 e)");
    //(void) slice; // silence unused parameter warning

    for(auto vector : slice.data){
        for(bool entry : vector){
            ostream << (entry ? "X" : ".");
            ostream << " ";
        }
        ostream << "\n";
    }

    return ostream;
}

std::ostream& operator<<(std::ostream& ostream, const VoxelGrid& vg)
{
    uint32_t res_z;
    std::tie(std::ignore, std::ignore, res_z) = vg.getResolution();

    for (uint32_t z=0; z<res_z; ++z) {
        auto slice = vg.extractSlice(Axis::Z, z);
        ostream << slice << std::endl;
    }
    return ostream;
}