#ifndef QWIRKLEPP_CUBES_H
#define QWIRKLEPP_CUBES_H

#include "qwirklepp_export.h"

#include "types.h"

#include <memory>
#include <vector>

namespace qwirklepp {

class Cube;

class QWIRKLEPP_EXPORT Cubes {
public:
    virtual ~Cubes() = 0;

    virtual auto Count() const
        -> unsigned = 0;

    virtual auto Clear()
        -> void = 0;
    virtual auto Add(
        std::unique_ptr<Cube> cube)
        -> void = 0;

    virtual auto Take()
        -> std::unique_ptr<Cube> = 0;
    virtual auto Get(Index index)
        -> Cube & = 0;
    virtual auto Get(Index index) const
        -> const Cube & = 0;
    virtual auto ShuffleRoll()
        -> void = 0;

    virtual auto Take(
        const std::vector<Index> & indices)
        -> std::vector<std::unique_ptr<Cube>> = 0;
};

namespace cubes {

QWIRKLEPP_EXPORT auto New()
    -> std::unique_ptr<Cubes>;

QWIRKLEPP_EXPORT auto Roll(Cubes & cubes)
    -> void;
QWIRKLEPP_EXPORT auto Roll(Cubes & cubes, const std::vector<Index> & rollIndices)
    -> void;

} // namespace cubes

} // namespace qwirklepp

#endif // QWIRKLEPP_CUBES_H
