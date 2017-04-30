#ifndef QWIRKLEPP_TYPES_H
#define QWIRKLEPP_TYPES_H

#include <cstdint>
#include <functional>
#include <utility>

namespace qwirklepp {

using Index = size_t;
using Axis = int_fast16_t;

struct QWIRKLEPP_EXPORT Location {
    Axis row;
    Axis col;

    friend bool operator< (const Location & lhs, const Location & rhs) {
        return std::make_pair(lhs.row, lhs.col) < std::make_pair(rhs.row, rhs.col);
    }

    friend bool operator== (const Location & lhs, const Location & rhs) {
        return lhs.row == rhs.row && lhs.col == rhs.col;
    }
};

using Color = int_fast8_t;
using Kind = int_fast8_t;

struct QWIRKLEPP_EXPORT Face {
    Color color;
    Kind kind;

    friend bool operator== (const Face & lhs, const Face & rhs) {
        return lhs.color == rhs.color && lhs.kind == rhs.kind;
    }
};

} // namespace qwirklepp

namespace std {

template <>
struct hash<qwirklepp::Location> {
    size_t operator() (const qwirklepp::Location & location) const noexcept {
        return location.row << 16 | location.col;
    }
};

} // namespace std

#endif // QWIRKLEPP_TYPES_H
