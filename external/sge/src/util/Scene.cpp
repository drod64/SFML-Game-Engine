#include <SGE/util/Scene.h>
#include <SGE/util/GameEngine.h>

sge::Scene::Scene() :
Scene(nullptr)
{}

sge::Scene::Scene(sge::GameEngine *gameEngine)
{
    this->m_game = gameEngine;
    this->m_paused = false;
    this->m_hasEnded = false;
    this->m_currentFrame = 0;
}

void sge::Scene::setPaused(bool paused)
{
    this->m_paused = paused;
}

void sge::Scene::doAction(const Action &action)
{
    this->sDoAction(action);
}

void sge::Scene::simulate(size_t frames)
{
    // TODO
}

void sge::Scene::registerAction(int inputKey, const std::string &actionName)
{
    this->m_actionMap[inputKey] = actionName;
}

size_t sge::Scene::getWidth() const
{
    return this->m_game->getWindow().getSize().x;
}

size_t sge::Scene::getHeight() const
{
    return this->m_game->getWindow().getSize().y;
}

size_t sge::Scene::getCurrentFrame() const
{
    return this->m_currentFrame;
}

bool sge::Scene::hasEnded() const
{
    return this->m_hasEnded;
}

const std::map<int, std::string>& sge::Scene::getActionMap() const
{
    return this->m_actionMap;
}

sf::VertexArray sge::Scene::createLine(const sm::Vec2 &p1, const sm::Vec2 &p2)
{
    sf::VertexArray line (sf::Lines, 2);
    line[0].position = {p1.x, p1.y};
    line[0].color = sf::Color(0,0,0);

    line[1].position = {p2.x, p2.y};
    line[1].color = sf::Color(0,0,0);

    return line;
}