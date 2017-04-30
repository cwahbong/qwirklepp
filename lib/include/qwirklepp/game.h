#ifndef QWIRKLEPP_GAME_H
#define QWIRKLEPP_GAME_H

#include "qwirklepp_export.h"

#include <memory>
#include <vector>

namespace qwirklepp {

class Actor;
class Observer;

class QWIRKLEPP_EXPORT Game {
public:
    virtual ~Game() = 0;

    virtual auto Run() -> std::vector<unsigned> = 0;
};

namespace game {

QWIRKLEPP_EXPORT auto New(
    std::unique_ptr<Actor> actor,
    std::unique_ptr<Observer> observer,
    unsigned player_num)
    -> std::unique_ptr<Game>;

} // namespace game

} // namespace qwirklepp

#endif // QWIRKLEPP_GAME_H
