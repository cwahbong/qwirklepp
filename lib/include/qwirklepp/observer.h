#ifndef QWIRKLEPP_OBSERVER_H
#define QWIRKLEPP_OBSERVER_H

#include "qwirklepp_export.h"

namespace qwirklepp {

class Content;

class QWIRKLEPP_EXPORT Observer {
public:
    virtual auto GameStarted()
        -> void = 0;
    virtual auto GameEnded(
        const Content & content)
        -> void = 0;

    virtual auto AfterSetup(
        const Content & content)
        -> void = 0;

    virtual auto BeforeRound(
        unsigned playerIndex,
        const Content & content)
        -> void = 0;
    virtual auto AfterRound(
        unsigned playerIndex,
        const Content & content)
        -> void = 0;
};

} // namespace qwirklepp

#endif // QWIRKLEPP_OBSERVER_H
