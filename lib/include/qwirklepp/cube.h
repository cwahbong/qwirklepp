#ifndef QWIRKLEPP_CUBE_H
#define QWIRKLEPP_CUBE_H

#include "qwirklepp_export.h"

#include "types.h"

#include <memory>

namespace qwirklepp {

class QWIRKLEPP_EXPORT Cube {
public:
    virtual ~Cube() = 0;

    virtual auto Peek() const
        -> Face = 0;
    virtual auto Roll()
        -> void = 0;
};

namespace cube {

QWIRKLEPP_EXPORT auto New(const Color &)
    -> std::unique_ptr<Cube>;

} // namespace cube

} // namespace qwirklepp

#endif // QWIRKLEPP_CUBE_H
