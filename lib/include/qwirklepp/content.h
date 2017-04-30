#ifndef QWIRKLEPP_CONTENT_H
#define QWIRKLEPP_CONTENT_H

#include "qwirklepp_export.h"

#include <memory>
#include <vector>

namespace qwirklepp {

class Board;
class Cube;
class Cubes;

class QWIRKLEPP_EXPORT Content {
public:
    virtual ~Content() = 0;

    virtual auto GetBoard()
        -> Board & = 0;
    virtual auto GetBoard() const
        -> const Board & = 0;

    virtual auto GetBag()
        -> Cubes & = 0;
    virtual auto GetBag() const
        -> const Cubes & = 0;

    virtual auto GetHand(
        std::vector<Cubes>::size_type playerIndex)
        -> Cubes & = 0;
    virtual auto GetHand(
        std::vector<Cubes>::size_type playerIndex) const
        -> const Cubes & = 0;

    virtual auto AddScore(
        std::vector<unsigned>::size_type playerIndex,
        unsigned add)
        -> void = 0;
    virtual auto GetScores() const
        -> std::vector<unsigned> = 0;
    virtual auto ClearScores()
        -> void = 0;
};

namespace content {

QWIRKLEPP_EXPORT auto New(unsigned playerNum)
    -> std::unique_ptr<Content>;

}

} // namespace qwirklepp

#endif // QWIRKLEPP_CONTENT_H
