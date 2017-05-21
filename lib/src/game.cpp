#include "qwirklepp/game.h"

#include "qwirklepp/actor.h"
#include "qwirklepp/board.h"
#include "qwirklepp/content.h"
#include "qwirklepp/cube.h"
#include "qwirklepp/cubes.h"
#include "qwirklepp/observer.h"
#include "qwirklepp/types.h"

#include <set>

namespace qwirklepp {

namespace {

auto AllDifferentColorAndKind(const Cubes & cubes)
    -> bool
{
    std::set<Color> colors;
    std::set<Kind> kinds;
    for (unsigned idx = 0; idx < cubes.Count(); ++idx) {
        const auto face = cubes.Get(idx).Peek();
        if (!colors.insert(face.color).second) {
            return true;
        }
        if (!kinds.insert(face.kind).second) {
            return true;
        }
    }
    return false;
}

class GameImpl: public Game {
public:
    GameImpl(std::unique_ptr<Actor>, std::unique_ptr<Observer>, unsigned playerNum);

    virtual auto Run()
        -> std::vector<unsigned> override;

private:
    auto SetupBag()
        -> void;
    auto SetupPlayers()
        -> void;
    auto Setup()
        -> void;

    auto Round(
        unsigned playerIndex)
        -> void;
    auto RerollCubes(
        unsigned playerIndex)
        -> void;

    auto IsPlacable(
        const std::map<Index, Location> & indexLocations)
        -> bool;
    auto AddFacesAndScore(
        unsigned playerIndex,
        const std::map<Index, Location> & indexLocations)
        -> void;
    auto RemoveCubes(
        unsigned playerIndex,
        const std::map<Index, Location> & indexLocations)
        -> void;
    auto PutCubesAndScore(
        unsigned playerIndex)
        -> void;
    auto Replenish(
        unsigned playerIndex)
        -> void;

    std::unique_ptr<Actor> _actor;
    std::unique_ptr<Observer> _observer;
    unsigned _playerNum;
    std::unique_ptr<Content> _content;
    bool _isFirst;
    bool _isEnd;
};

GameImpl::GameImpl(std::unique_ptr<Actor> actor, std::unique_ptr<Observer> observer, unsigned playerNum):
    _actor(std::move(actor)),
    _observer(std::move(observer)),
    _playerNum(playerNum),
    _content(content::New(playerNum)),
    _isFirst(false),
    _isEnd(false)
{}

auto GameImpl::Run()
    -> std::vector<unsigned>
{
    _observer->GameStarted();
    Setup();
    _observer->AfterSetup(*_content);
    while(!_isEnd) {
        for (unsigned playerIndex = 0; playerIndex < _playerNum; ++playerIndex) {
            _observer->BeforeRound(playerIndex, *_content);
            Round(playerIndex);
            _observer->AfterRound(playerIndex, *_content);
        }
    }
    _observer->GameEnded(*_content);
    return _content->GetScores();
}

auto GameImpl::SetupBag()
    -> void
{
    auto & bag = _content->GetBag();
    bag.Clear();
    for (Color color = 0; color < 6; ++color) {
        for (unsigned count = 0; count < 15; ++count) {
            bag.Add(cube::New(color));
        }
    }
    bag.ShuffleRoll();
}

auto GameImpl::SetupPlayers()
    -> void
{
    for (unsigned playerIndex = 0; playerIndex < _playerNum; ++playerIndex) {
        _content->GetHand(playerIndex).Clear();
        Replenish(playerIndex);
    }
}

auto GameImpl::Setup()
    -> void
{
    _isFirst = true;
    _isEnd = false;
    _content->ClearScores();
    SetupBag();
    SetupPlayers();
}

auto GameImpl::Round(
    unsigned playerIndex)
    -> void
{
    RerollCubes(playerIndex);
    PutCubesAndScore(playerIndex);
    Replenish(playerIndex);
    _isFirst = false;
}

auto GameImpl::RerollCubes(
    unsigned playerIndex)
    -> void
{
    const auto rollIndices = _actor->AnswerRollCubes(playerIndex, *_content);
    auto & hand = _content->GetHand(playerIndex);
    cubes::Roll(hand, rollIndices);
    if (_isFirst) {
        while (AllDifferentColorAndKind(hand)) {
            cubes::Roll(hand);
        }
    }
}

auto GameImpl::IsPlacable(
    const std::map<Index, Location> & indexLocations)
    -> bool
{
    std::vector<Location> locations;
    for (const auto & indexLocation: indexLocations) {
        locations.push_back(indexLocation.second);
    }
    return board::IsPlacable(_content->GetBoard(), locations);
}

auto GameImpl::AddFacesAndScore(
    unsigned playerIndex,
    const std::map<Index, Location> & indexLocations)
    -> void
{
    std::map<Location, Face> locationFaces;
    for (const auto & indexLocation: indexLocations) {
        locationFaces[indexLocation.second] = _content->GetHand(playerIndex).Get(indexLocation.first).Peek();
    }
    _content->AddScore(playerIndex, board::CalcScore(_content->GetBoard(), locationFaces));
    for (const auto & locationFace: locationFaces) {
        _content->GetBoard().Insert(locationFace.first, locationFace.second);
    }
}

auto GameImpl::RemoveCubes(
    unsigned playerIndex,
    const std::map<Index, Location> & indexLocations)
    -> void
{
    std::vector<Index> indices;
    for (const auto & indexLocation: indexLocations) {
        indices.push_back(indexLocation.first);
    }
    _content->GetHand(playerIndex).Take(indices);
}

auto GameImpl::PutCubesAndScore(
    unsigned playerIndex)
    -> void
{
    if (_isFirst) {
        // TODO must use max number of cubes as he can
    }
    const auto indexLocations = _actor->AnswerAddCubes(playerIndex, *_content);
    if (!IsPlacable(indexLocations)) {
        // TODO ERROR handling
        return;
    }
    AddFacesAndScore(playerIndex, indexLocations);
    RemoveCubes(playerIndex, indexLocations);
}

auto GameImpl::Replenish(
    unsigned playerIndex)
    -> void
{
    auto & hand = _content->GetHand(playerIndex);
    auto & bag = _content->GetBag();
    while (hand.Count() < 6) {
        if (bag.Count() == 0) {
            _isEnd = true;
            break;
        }
        hand.Add(bag.Take());
    }
}

} // namespace

Game::~Game() = default;

namespace game {

auto New(
    std::unique_ptr<Actor> actor,
    std::unique_ptr<Observer> observer,
    unsigned playerNum)
    -> std::unique_ptr<Game>
{
    return std::make_unique<GameImpl>(std::move(actor), std::move(observer), playerNum);
}

} // namespace game

} // namespace qwirklepp
