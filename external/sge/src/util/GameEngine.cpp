#include <SGE/util/GameEngine.h>

namespace sge {

GameEngine::GameEngine()
{}

void GameEngine::update(float dt)
{
    sUserInput();
    currentScene()->update(dt);
}

void GameEngine::sUserInput()
{
    sf::Event event;
    while (this->m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            quit();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Slash)
            {
                sf::Texture texture;
                texture.create(this->m_window.getSize().x, this->m_window.getSize().y);
                texture.update(this->m_window);
                if (texture.copyToImage().saveToFile("test.png"))
                {
                    std::cout << "screenshot saved to " << "test.png\n";
                }
            }
        }

        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            // Check if there is an associated key with the current Scene.
            if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end())
            {
                continue;
            }
            // Find out whether it is a START or END action.
            const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
            // Send this Action to the current Scene.
            currentScene()->doAction(sge::Action(currentScene()->getActionMap().at(event.key.code), actionType));
        }
    }
}
std::shared_ptr<sge::Scene> GameEngine::currentScene()
{
    return this->m_scenes.at(this->m_currentScene);
}

void GameEngine::quit()
{
    this->m_running = false;
}

void GameEngine::run()
{
    sf::Clock time;
    while (this->m_running)
    {
        update(time.restart().asSeconds());
    }
    this->m_window.close();
}

sf::RenderWindow& GameEngine::getWindow()
{
    return this->m_window;
}

const sge::Assets& GameEngine::getAssets() const
{
    return this->m_assets;
}

bool GameEngine::isRunning() const
{
    return this->m_running;
}

} // End namespace SGE
