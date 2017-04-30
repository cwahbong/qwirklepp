#include "qwirklepp/board.h"
#include "qwirklepp/types.h"

#include <unordered_map>


namespace qwirklepp {

namespace {

class BoardImpl: public Board {
public:
    auto Insert(
        const Location & location,
        const Face & face)
        -> bool override;
    auto Peek(
        const Location & location) const
        -> boost::optional<Face> override;

private:
    std::unordered_map<Location, Face> _locator;
};

auto BoardImpl::Insert(
    const Location & location,
    const Face & face)
    -> bool
{
    const auto it = _locator.find(location);
    if (it != _locator.end()) {
        return false;
    }
    _locator[location] = face;
    return true;
}

auto BoardImpl::Peek(
    const Location & location) const
    -> boost::optional<Face>
{
    const auto it = _locator.find(location);
    if (it == _locator.end()) {
        return boost::none;
    }
    return it->second;
}

} // namespace

Board::~Board() = default;

namespace board {

auto New()
    -> std::unique_ptr<Board>
{
    return std::make_unique<BoardImpl>();
}

auto IsPlacable(
    const Board & board,
    const std::vector<Location> & locations)
    -> bool
{
    for (const auto & location: locations) {
        if (board.Peek(location)) {
            return false;
        }
    }
    return true;
}

auto CalcScore(
    const Board & board,
    const std::map<Location, Face> & locationFaces)
    -> unsigned
{
    // TODO
    return 0;
}

} // namespace board

} // namespace qwirklepp
