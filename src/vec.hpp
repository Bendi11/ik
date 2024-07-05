#pragma once

#include <cmath>
#include <cstdint>


struct bfp_t {
    static constexpr uint8_t FRACTION_SHIFT = 8;

    inline constexpr bfp_t() : _v{0} {}
    inline constexpr bfp_t(int32_t v) : _v{v << FRACTION_SHIFT} {}


    static inline constexpr bfp_t raw(int32_t v) {
        return bfp_t{v, true};
    }
    
    inline bfp_t& operator=(const bfp_t& other) {
        _v = other._v;
        return *this;
    }

    inline constexpr bfp_t operator+(bfp_t const& other) const { return bfp_t::raw(_v + other._v); }
    inline constexpr bfp_t operator-(bfp_t const& other) const { return bfp_t::raw(_v - other._v); }


    inline constexpr bfp_t operator*(bfp_t const& other) const { return bfp_t::raw((_v * other._v) >> FRACTION_SHIFT); }
    inline constexpr bfp_t operator/(bfp_t const& other) const { return bfp_t::raw((_v << FRACTION_SHIFT) / other._v); }
    inline constexpr bfp_t operator>>(unsigned const& shift) const { return bfp_t::raw(_v >> shift); }
    inline constexpr bfp_t operator<<(unsigned const& shift) const { return bfp_t::raw(_v << shift); }

    inline constexpr bfp_t operator-() const {
        return bfp_t::raw(-_v);
    }

    inline constexpr bool operator<(bfp_t const& other) const { return _v < other._v; }
    inline constexpr bool operator>(bfp_t const& other) const { return _v > other._v; }
    inline constexpr bool operator==(bfp_t const& other) const { return _v == other._v; }
    inline constexpr bool operator!=(bfp_t const& other) const { return _v != other._v; }

    inline constexpr bool is_negative() const { return (_v & ((int32_t)1 << 31)) != 0; }
private:
    int32_t _v;

    inline explicit constexpr bfp_t(int32_t v, bool _raw) : _v{v} {}
};

struct Vec2 {
    bfp_t x;
    bfp_t y;

    inline constexpr Vec2(bfp_t _x, bfp_t _y) : x{_x}, y{_y} {}

    inline Vec2& operator=(Vec2 const& other) = default;
    inline constexpr Vec2 operator+(Vec2 const& other) const {
        return Vec2(x + other.x, y + other.y);
    }
    inline constexpr Vec2 operator-(Vec2 const& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    inline constexpr Vec2 operator*(bfp_t v) const {
        return Vec2(x * v, y * v);
    }

    inline constexpr Vec2 operator/(bfp_t v) const {
        return Vec2(x / v, y / v);
    }

    inline constexpr bfp_t dot(Vec2 const& other) const {
        return other.x * x + other.y * y;
    }
};
