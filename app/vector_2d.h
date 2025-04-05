#pragma once

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <vector>

#include <library/vec2.h>

template <typename T>
requires std::default_initializable<T> &&
         std::copy_constructible<T>
class Vector2D {
public:
    Vector2D()
        : _size(0, 0)
        , _data(0)
    {}

    Vector2D(size_t width, size_t height, T filler = T{})
        : _size(width, height)
        , _data(Volume(), filler)
    {}

    template <typename UInt> requires std::unsigned_integral<UInt>
    Vector2D(Vec2<UInt> size, T filler = T{})
        : _size(size)
        , _data(Volume(), filler)
    {}

    template <typename T2>
    requires std::assignable_from<T, const T2&>
    Vector2D(const Vector2D<T2>& other)
        : _size(other._size) {
        _data.resize(other.Volume());
        for (size_t i = 0; i < other._data.size(); ++i) {
            _data[i] = other._data[i];
        }
    }

    template <typename T2>
    requires std::assignable_from<T, T2&&>
    Vector2D(Vector2D<T2>&& other) 
        : _size(other._size) {
        _data.resize(other.Volume());
        for (size_t i = 0; i < other._data.size(); ++i) {
            _data[i] = std::move(other._data[i]);
        }
        other.Clear();
    }

    Vector2D(const Vector2D& other) = default;
    Vector2D(Vector2D&& other) = default;

    Vector2D& operator=(const Vector2D& other) = default;
    Vector2D& operator=(Vector2D&& other) = default;

    template <typename T2>
    requires std::assignable_from<T, const T2&>
    Vector2D& operator=(const Vector2D<T2>& other) {
        _size = other._size;
        _data.resize(other.Volume());
        for (size_t i = 0; i < other._data.size(); ++i) {
            _data[i] = other._data[i];
        }
        return *this;
    }

    template <typename T2>
    requires std::assignable_from<T, const T2&>
    Vector2D& operator=(Vector2D<T2>&& other) {
        _size = other._size;
        _data.resize(other.Volume());
        for (size_t i = 0; i < other._data.size(); ++i) {
            _data[i] = other._data[i];
        }
        other.Clear();
        return *this;
    }

    const T& operator[](size_t x, size_t y) const {
        return Get(x, y);
    }

    T& operator[](size_t x, size_t y) {
        return Get(x, y);
    }

    const T& GetConst(size_t x, size_t y) const {
        return _data[y * _size.x + x];
    }

    T& Get(size_t x, size_t y) {
        return _data[y * _size.x + x];
    }

    const T& GetClosest(int64_t x, int64_t y) const {
        assert(!IsEmpty());
        return Get(std::clamp(x, int64_t{0}, static_cast<int64_t>(_size.x) - 1),
                   std::clamp(y, int64_t{0}, static_cast<int64_t>(_size.y) - 1));
    }

    T& GetClosest(int64_t x, int64_t y) {
        assert(!IsEmpty());
        return Get(std::clamp(x, int64_t{0}, static_cast<int64_t>(_size.x) - 1),
                   std::clamp(y, int64_t{0}, static_cast<int64_t>(_size.y) - 1));
    }

    void Clear() {
        _size.Set(0, 0);
        _data.clear();
    }

    size_t Volume() const {
        return _size.x * _size.y;
    }

    Vec2ui32 Size() const {
        return _size;
    }

    size_t Width() const {
        return _size.x;
    }

    size_t Height() const {
        return _size.y;
    }

    bool IsEmpty() const {
        return Volume() == 0;
    }

    bool IsInside(size_t x, size_t y) const {
        return x < _size.x && y < _size.y;
    }

    template <typename UInt> requires std::unsigned_integral<UInt>
    bool IsInside(Vec2<UInt> point) const {
        return point.x < _size.x && point.y < _size.y;
    }

    void Assign(size_t x, size_t y, T filler = T{}) {
        _size.Set(x, y);
        _data.assign(Volume(), filler);
    }

    template <typename UInt> requires std::unsigned_integral<UInt>
    void Assign(Vec2<UInt> size, T filler = T{}) {
        _size = size;
        _data.assign(Volume(), filler);
    }

private:
    Vec2ui32 _size;
    std::vector<T> _data;
};
