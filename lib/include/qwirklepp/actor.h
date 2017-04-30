#ifndef QWIRKLEPP_ACTOR_H
#define QWIRKLEPP_ACTOR_H

#include "qwirklepp_export.h"

#include "types.h"

#include <map>
#include <vector>

namespace qwirklepp {

class Content;

class QWIRKLEPP_EXPORT Actor {
public:
    virtual auto AnswerRollCubes(
        unsigned playerIndex,
        const Content & content)
        -> std::vector<Index> = 0;
    virtual auto AnswerAddCubes(
        unsigned playerIndex,
        const Content & content)
        -> std::map<Index, Location> = 0;
};

} // namespace qwirklepp

#endif // QWIRKLEPP_ACTOR_H
