#include <TestingEngine/TestingEngine.h>

TestingEngine::TestingEngine() :
TestingEngine("nothing")
{}

TestingEngine::TestingEngine(const std::string &filePath) :
sge::GameEngine()
{
    // TODO load level file stuff
    this->m_currentScene = "PLAY";
    this->m_assets.addFont("sansfont", "comicSans.ttf");
    this->m_assets.addTexture("sansSprites", "sans.png");
    this->m_assets.addAnimation("sansWalk", "sansSprites", 1, 4, 9, 0.1);

    this->changeScene<Scene_Play>(this->m_currentScene, filePath, false);

    this->m_window.create({800, 600}, "Testing Engine");
    this->m_window.setFramerateLimit(60);
}