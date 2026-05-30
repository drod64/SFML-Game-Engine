#ifndef SGE_SCENE_H
#define SGE_SCENE_H
#include <memory>
#include <SGE/entities/EntityManager.h>
#include <SGE/util/Action.h>


namespace sge {

class GameEngine;

class Scene {
protected:
    GameEngine* m_game;
    sge::EntityManager m_entities;
    std::map<int, std::string> m_actionMap;
    bool m_paused;
    bool m_hasEnded;
    size_t m_currentFrame;

    virtual void onEnd() = 0;
    void setPaused(bool paused);

public:
    Scene();
    Scene(GameEngine *gameEngine);

    virtual void update(float dt) = 0;
    virtual void sDoAction(const sge::Action &action) = 0;
    virtual void sRender() = 0;

    virtual void doAction(const Action &action);
    void simulate(const size_t frames);
    void registerAction(int inputKey, const std::string &actionName);

    size_t getWidth() const;
    size_t getHeight() const;
    size_t getCurrentFrame() const;

    bool hasEnded() const;
    const std::map<int, std::string>& getActionMap() const;
    sf::VertexArray createLine(const sm::Vec2 &p1, const sm::Vec2 &p2);

};

}

#endif // SGE_SCENE_H