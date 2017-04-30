#include "qwirklepp/content.h"

#include "qwirklepp/board.h"
#include "qwirklepp/cubes.h"

namespace qwirklepp {

namespace {

class ContentImpl: public Content {
public:
    ContentImpl(unsigned playerNum);

    auto GetBoard()
        -> Board & override;
    auto GetBoard() const
        -> const Board & override;

    auto GetBag()
        -> Cubes & override;
    auto GetBag() const
        -> const Cubes & override;

    auto GetHand(
        std::vector<Cubes>::size_type playerIndex)
        -> Cubes & override;
    auto GetHand(
        std::vector<Cubes>::size_type playerindex) const
        -> const Cubes & override;

    auto AddScore(
        std::vector<unsigned>::size_type playerIndex,
        unsigned add)
        -> void override;
    auto GetScores() const
        -> std::vector<unsigned> override;
    auto ClearScores()
        -> void override;

private:
    std::unique_ptr<Board> _board;
    std::unique_ptr<Cubes> _bag;
    std::vector<std::unique_ptr<Cubes>> _hands;
    std::vector<unsigned> _scores;
};

ContentImpl::ContentImpl(unsigned playerNum):
    _board(board::New()),
    _bag(cubes::New()),
    _hands(),
    _scores(playerNum)
{
    for (unsigned playerIndex = 0; playerIndex < playerNum; ++playerIndex) {
        _hands.push_back(cubes::New());
    }
}

auto ContentImpl::GetBoard()
    -> Board &
{
    return *_board;
}

auto ContentImpl::GetBoard() const
    -> const Board &
{
    return *_board;
}

auto ContentImpl::GetBag()
    -> Cubes &
{
    return *_bag;
}

auto ContentImpl::GetBag() const
    -> const Cubes &
{
    return *_bag;
}

auto ContentImpl::GetHand(
    std::vector<Cubes>::size_type playerIndex)
    -> Cubes &
{
    return *_hands[playerIndex];
}

auto ContentImpl::GetHand(
    std::vector<Cubes>::size_type playerIndex) const
    -> const Cubes &
{
    return *_hands[playerIndex];
}

auto ContentImpl::AddScore(
    std::vector<unsigned>::size_type playerIndex,
    unsigned add)
    -> void
{
    _scores[playerIndex] += add;
}

auto ContentImpl::GetScores() const
    -> std::vector<unsigned>
{
    return _scores;
}

auto ContentImpl::ClearScores()
    -> void
{
    _scores.assign(_scores.size(), 0);
}

} // namespace

Content::~Content() = default;

namespace content {

auto New(unsigned playerNum)
    -> std::unique_ptr<Content>
{
    return std::make_unique<ContentImpl>(playerNum);
}

} // namespace content

} // namespace qwirklepp
