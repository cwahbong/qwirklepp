#include "qwirklepp/cubes.h"

#include "qwirklepp/cube.h"

#include <algorithm>
#include <chrono>
#include <random>
#include <set>
#include <vector>

namespace qwirklepp {

namespace {

thread_local std::default_random_engine random_engine(std::chrono::system_clock::now().time_since_epoch().count());

class CubesImpl: public Cubes {
public:
    auto Count() const
        -> unsigned override;

    auto Clear()
        -> void override;
    auto Add(
        std::unique_ptr<Cube> cube)
        -> void override;

    auto Take()
        -> std::unique_ptr<Cube> override;
    auto Get(Index index)
        -> Cube & override;
    auto Get(Index index) const
        -> const Cube & override;
    auto ShuffleRoll()
        -> void override;

    virtual auto Take(
        const std::vector<Index> & indices)
        -> std::vector<std::unique_ptr<Cube>> override;

private:
    std::vector<std::unique_ptr<Cube>> _cubes;
};

auto CubesImpl::Count() const
    -> unsigned
{
    return _cubes.size();
}

auto CubesImpl::Clear()
    -> void
{
    _cubes.clear();
}

auto CubesImpl::Add(
    std::unique_ptr<Cube> cube)
    -> void
{
    _cubes.push_back(std::move(cube));
}

auto CubesImpl::Take()
    -> std::unique_ptr<Cube>
{
    if (_cubes.empty()) {
        return nullptr;
    }
    std::unique_ptr<Cube> cube = std::move(_cubes.back());
    _cubes.pop_back();
    return cube;
}

auto CubesImpl::Get(Index index)
    -> Cube &
{
    return *_cubes[index];
}

auto CubesImpl::Get(Index index) const
    -> const Cube &
{
    return *_cubes[index];
}

auto CubesImpl::ShuffleRoll()
    -> void
{
    for (auto && cube: _cubes) {
        cube->Roll();
    }
    std::shuffle(_cubes.begin(), _cubes.end(), random_engine);
}

auto CubesImpl::Take(
    const std::vector<Index> &indices)
    -> std::vector<std::unique_ptr<Cube>>
{
    std::set<Index> indices_set;
    for (const auto & index: indices) {
        if (indices_set.find(index) != indices_set.end() ||
            index >= _cubes.size()) {
            return std::vector<std::unique_ptr<Cube>>();
        }
        indices_set.insert(index);
    }
    std::vector<std::unique_ptr<Cube>> res;
    for (const auto & index: indices) {
        res.push_back(std::move(_cubes[index]));
    }
    const auto erase_begin = std::remove_if(_cubes.begin(), _cubes.end(), [](const std::unique_ptr<Cube> & cube) {
        return !cube;
    });
    _cubes.erase(erase_begin, _cubes.end());
    return res;
}

} // namespace

Cubes::~Cubes() = default;

namespace cubes {

auto New()
    -> std::unique_ptr<Cubes>
{
    return std::make_unique<CubesImpl>();
}

auto Roll(Cubes & cubes)
    -> void
{
    for (unsigned idx = 0; idx < cubes.Count(); ++idx) {
        cubes.Get(idx).Roll();
    }
}

auto Roll(Cubes & cubes, const std::vector<Index> & rollIndices)
    -> void
{
    for (const auto & rollIndex: rollIndices) {
        cubes.Get(rollIndex).Roll();
    }
}

} // namespace cubes

} // namespace qwirklepp
