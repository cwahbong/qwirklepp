#ifndef QWIRKLEPP_BOARD_H
#define QWIRKLEPP_BOARD_H

#include "qwirklepp_export.h"

#include <map>
#include <memory>
#include <vector>

#include <boost/optional.hpp>


namespace qwirklepp {

struct Face;
struct Location;

class QWIRKLEPP_EXPORT Board {
public:
    virtual ~Board() = 0;

    virtual auto Insert(
        const Location & location,
        const Face & face)
        -> bool = 0;
    virtual auto Peek(
        const Location & location) const
        -> boost::optional<Face> = 0;
};

namespace board {

QWIRKLEPP_EXPORT auto New()
    -> std::unique_ptr<Board>;

QWIRKLEPP_EXPORT auto IsPlacable(
    const Board & board,
    const std::vector<Location> & locations)
    -> bool;
QWIRKLEPP_EXPORT auto CalcScore(
    const Board & board,
    const std::map<Location, Face> & locationFaces)
    -> unsigned;

} // namespace board

} // namespace qwirklepp

#endif // QWIRKLEPP_BOARD_H
