#ifndef SGE_GAME_ENGINE_H
#define SGE_GAME_ENGINE_H
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SGE/entities/EntityManager.h>
#include <SGE/util/Assets.h>
#include <SGE/util/Scene.h>

namespace sge {

class GameEngine {
protected:
    sf::RenderWindow m_window;
    sge::Assets m_assets;
    std::string m_currentScene;
    std::unordered_map<std::string, std::shared_ptr<sge::Scene>> m_scenes; 
    size_t m_simulationSpeed;
    bool m_running;

    GameEngine();
    void update(float dt);
    void sUserInput();
    std::shared_ptr<sge::Scene> currentScene();

public:
    template <typename T>
    void changeScene(const std::string &sceneName, const std::string &levelPath, bool endCurrentScene = false)
    {
        this->m_window.setView(this->m_window.getDefaultView());
        // Remove Scene from map.
        if (endCurrentScene)
        {
            auto it = this->m_scenes.find(sceneName);
            if (it != this->m_scenes.end())
            this->m_scenes.erase(it);
        }
        // If Scene does not exist, create it.
        if (this->m_scenes.find(sceneName) == this->m_scenes.end())
        {
            std::cout << "Creating scene: " << sceneName << '\n';
            std::shared_ptr<sge::Scene> scene = std::make_shared<T>(this, levelPath);
            this->m_scenes[sceneName] = scene;
        }
        std::cout << "Changed scene\n";
        this->m_currentScene = sceneName;
    }

    void quit();
    void run();

    sf::RenderWindow& getWindow();
    const sge::Assets& getAssets() const;
    bool isRunning() const;
};

}

#endif // SGE_GAME_ENGINE_H