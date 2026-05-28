#include <TestingEngine/Scene_Play.h>

Scene_Play::Scene_Play() :
sge::Scene(nullptr)
{}

Scene_Play::Scene_Play(sge::GameEngine *gameEngine, const std::string &levelPath) :
sge::Scene(gameEngine)
{
    this->m_levelPath = levelPath;
    this->m_drawCollision = false;
    this->m_drawGrid = false;
    this->m_drawTextures = true;
    init(this->m_levelPath);
}

void Scene_Play::update(float dt)
{
    this->m_entities.update();

    if (!this->m_paused)
    {
        this->sMovement();
        this->sLifeSpan();
        // this->sCollision();
        this->sAnimation(dt);
    }
    this->sRender();

    if (this->hasEnded()) this->m_game->quit();
}

void Scene_Play::sDoAction(const sge::Action &action)
{
    // TODO keep adding actions that may need to be accounted for
    // TODO Find a way to implement toggle actions
    if (action.getType() == "START")
    {
        // Toggle / Single press actions
            if (action.getName() == "TOGGLE_TEXTURE")       { this->m_drawTextures = !this->m_drawTextures; }
        else if (action.getName() == "TOGGLE_COLLISION")    { this->m_drawCollision = !this->m_drawCollision; }
        else if (action.getName() == "TOGGLE_GRID")         { this->m_drawGrid = !this->m_drawGrid; }
        else if (action.getName() == "PAUSE")               { this->m_paused = !this->m_paused; }
        else if (action.getName() == "QUIT")                { this->onEnd(); }
        
        // Held actions
        else if (action.getName() == "RIGHT")               { this->m_player->getComponent<sge::CInput>().right = true; }
        else if (action.getName() == "LEFT")                { this->m_player->getComponent<sge::CInput>().left = true; }
        else if (action.getName() == "JUMP")                { this->m_player->getComponent<sge::CInput>().up = true; }
        else if (action.getName() == "SHOOT")               { this->m_player->getComponent<sge::CInput>().shoot = true; }
        else if (action.getName() == "DOWN")                { this->m_player->getComponent<sge::CInput>().down = true; }
    }
    else if (action.getType() == "END")
    {
            if (action.getName() == "RIGHT")               { this->m_player->getComponent<sge::CInput>().right = false; }
        else if (action.getName() == "LEFT")                { this->m_player->getComponent<sge::CInput>().left = false; }
        else if (action.getName() == "JUMP")                { this->m_player->getComponent<sge::CInput>().up = false; }
        else if (action.getName() == "SHOOT")               { this->m_player->getComponent<sge::CInput>().shoot = false; }
        else if (action.getName() == "DOWN")               { this->m_player->getComponent<sge::CInput>().down = false; }
    }
}

void Scene_Play::sRender()
{
    // Color the background darker to indicate game is paused.
    if (!this->m_paused) { this->m_game->getWindow().clear(sf::Color(100, 100, 255)); }
    else { this->m_game->getWindow().clear(sf::Color(50, 50, 150)); }

    // set the viewport of the window to be centered on the player if it's far enough right
    auto &playerPos = this->m_player->getComponent<sge::CTransform>().position;
    float windowCenterX = std::max(this->m_game->getWindow().getSize().x / 2.0f, playerPos.x);
    sf::View view = this->m_game->getWindow().getView();
    view.setCenter(windowCenterX, this->m_game->getWindow().getSize().y - view.getCenter().y);
    this->m_game->getWindow().setView(view);

    // draw all Entity textures / animations
    if (this->m_drawTextures)
    {
        for (auto e : this->m_entities.getEntities())
        {
            auto &transform = e->getComponent<sge::CTransform>();

            if (e->hasComponent<sge::CAnimation>())
            {
                auto &animation = e->getComponent<sge::CAnimation>().animation;

                animation.getSprite().setRotation(transform.angle);
                animation.setPosition({transform.position.x, transform.position.y});
                // NOTE: the sge::Animation class has it's own setScale() function which is relative to the current size of the sprite
                // ...(not its original size in file), while the SFML sf::Sprite setScale() is relative to the original size of the sprite 
                animation.setScale({transform.scale.x, transform.scale.y});

                this->m_game->getWindow().draw(animation.getSprite());
            }
        }
    }

    // draw all Entity collision bounding boxes with a rectangle shape
    if (this->m_drawCollision)
    {
        for (auto e : this->m_entities.getEntities())
        {
            if (e->hasComponent<sge::CBoundingBox>())
            {
                auto &box = e->getComponent<sge::CBoundingBox>();
                auto &transform = e->getComponent<sge::CTransform>();
                sf::RectangleShape rect;

                rect.setSize({box.size().x - 1, box.size().y - 1});
                rect.setOrigin({box.halfSize().x, box.halfSize().y});
                rect.setPosition(transform.position.x, transform.position.y);
                rect.setFillColor(sf::Color(0, 0, 0, 0));
                rect.setOutlineColor(sf::Color(255, 255, 255, 255));
                rect.setOutlineThickness(1);
                this->m_game->getWindow().draw(rect);
            }
        }
    }

    // FIXED. Make sure you have an actual grid size set prior to attempting to draw it
    if (this->m_drawGrid)
    {
        float leftX = this->m_game->getWindow().getView().getCenter().x - getWidth() / 2;
        float rightX = leftX + getWidth() + this->m_gridSize.x;
        float nextGridX = leftX - ((int)leftX % (int)this->m_gridSize.x);

        for (float x = nextGridX; x < rightX; x += this->m_gridSize.x)
        {
            this->m_game->getWindow().draw(createLine({x, 0}, {x, (float)getHeight()}));
        }

        for (float y = 0; y < getHeight(); y += this->m_gridSize.y)
        {
            this->m_game->getWindow().draw(createLine({leftX, getHeight() - y}, {rightX, getHeight() - y}));

            for (float x = nextGridX; x < rightX; x += this->m_gridSize.x)
            {
                std::string xCell = std::to_string((int)x / (int)this->m_gridSize.x);
                std::string yCell = std::to_string((int)y / (int)this->m_gridSize.y);
                this->m_gridText.setString("(" + xCell + ", " + yCell + ")");
                this->m_gridText.setPosition(x + 3, getHeight() - y - this->m_gridSize.y + 2);
                this->m_game->getWindow().draw(this->m_gridText);
            }
        }
    }

    this->m_game->getWindow().display();
}

void Scene_Play::onEnd()
{
    this->m_hasEnded = true;
}

void Scene_Play::init(const std::string &levelPath)
{
    // Basic game actions
    this->registerAction(sf::Keyboard::P,       "PAUSE");
    this->registerAction(sf::Keyboard::Escape,  "QUIT");
    this->registerAction(sf::Keyboard::B,       "TOGGLE_COLLISION");
    this->registerAction(sf::Keyboard::N,       "TOGGLE_TEXTURE");
    this->registerAction(sf::Keyboard::M,       "TOGGLE_GRID");

    // Player actions
    this->registerAction(sf::Keyboard::Left,    "LEFT");
    this->registerAction(sf::Keyboard::X,       "JUMP");
    this->registerAction(sf::Keyboard::Right,   "RIGHT");
    this->registerAction(sf::Keyboard::Down,    "DOWN");
    this->registerAction(sf::Keyboard::Z,       "SHOOT");

    this->m_gridText.setFont(this->m_game->getAssets().getFont("sansfont"));
    this->m_gridText.setCharacterSize(10);

    spawnPlayer();

    this->m_gridSize = {50, 50};


    // TODO load level information
}

void Scene_Play::spawnPlayer()
{
    this->m_player = this->m_entities.addEntity("Player");

    this->m_player->addComponent<sge::CAnimation>(this->m_game->getAssets().getAnimation("sansWalk"), true);
    this->m_player->addComponent<sge::CBoundingBox>(sge::Vec2(50,50));
    this->m_player->getComponent<sge::CAnimation>().animation.scaleToSize({50, 50});

    this->m_player->addComponent<sge::CInput>();
    this->m_player->addComponent<sge::CScore>(0);
    this->m_player->addComponent<sge::CTransform>(sge::Vec2(0, 300), sge::Vec2(0, 0), 0);
    this->m_player->getComponent<sge::CTransform>().scale = {1, 1};
}

void Scene_Play::sMovement()
{
    // Update player velocity based on keyboard input
    sge::Vec2 playerVelocity = {0, 0};
    sge::CInput &input = this->m_player->getComponent<sge::CInput>();
    
    if (input.left)         { playerVelocity.x = -3; }
    else if (input.right)   { playerVelocity.x = 3; }
    
    if (input.up)           { playerVelocity.y = -3; }
    else if (input.down)    { playerVelocity.y = 3; }
    // else if (input.shoot)   {} TODO implement shooting functionality
    this->m_player->getComponent<sge::CTransform>().velocity = playerVelocity;

    // Update all entity positions with their velocities
    for (auto &e : this->m_entities.getEntities())
    {
        e->getComponent<sge::CTransform>().position += e->getComponent<sge::CTransform>().velocity;
    }
}

void Scene_Play::sLifeSpan()
{
    for (auto &e : this->m_entities.getEntities())
    {
        if (e->hasComponent<sge::CLifespan>())
        {
            // If the lifespan has been reached, destroy the entity
            if (e->getComponent<sge::CLifespan>().remaining <= 0)
            {
                e->destroy();
            }
            // Otherwise decrement the remaining frame count
            else
            {
                --e->getComponent<sge::CLifespan>().remaining;
            }
        }
    }
}

void Scene_Play::sAnimation(float dt)
{
    for (auto &e : this->m_entities.getEntities())
    {
        if (e->hasComponent<sge::CAnimation>())
        {
            // If animation is not looped, destroy the entity
            if (!e->getComponent<sge::CAnimation>().repeat && e->getComponent<sge::CAnimation>().animation.hasEnded())
            {
                e->destroy();
            }
            // Otherwise update the animation frame
            else
            {
                e->getComponent<sge::CAnimation>().animation.update(dt);
            }
        }
    }
}