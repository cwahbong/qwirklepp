#include "qwirklepp/cube.h"

#include "qwirklepp/types.h"

#include <chrono>
#include <random>

namespace qwirklepp {

namespace {

thread_local std::default_random_engine random_engine(std::chrono::system_clock::now().time_since_epoch().count());
thread_local std::uniform_int_distribution<Kind> unidist(0, 6);

Kind randKind()
{
    return unidist(random_engine);
}

class CubeImpl: public Cube {
public:
    CubeImpl(const Color &color);

    auto Peek() const
        -> Face override;
    auto Roll()
        -> void override;

private:
    Color _color;
    Kind _kind;
};

CubeImpl::CubeImpl(const Color &color):
    _color(color),
    _kind(0)
{}

auto CubeImpl::Peek() const
    -> Face
{
    return Face {
        .color = _color,
        .kind = _kind,
    };
}

auto CubeImpl::Roll()
    -> void
{
    _kind = randKind();
}

} // namespace

Cube::~Cube() = default;

namespace cube {

auto New(const Color & color)
    -> std::unique_ptr<Cube>
{
    return std::make_unique<CubeImpl>(color);
}

} // namespace cube

} // namespace qwirklepp
