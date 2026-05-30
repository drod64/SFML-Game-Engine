#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H
#include <string>
#include <SGE/util/Scene.h>
#include <SGE/entities/Entity.h>
#include <SGE/util/GameEngine.h>

class Scene_Play : public sge::Scene {
    
    struct PlayerConfig {
        float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
        std::string WEAPON;
    };

private:
    std::shared_ptr<sge::Entity> m_player;
    std::string m_levelPath;
    PlayerConfig m_playerConfig;
    bool m_drawTextures;
    bool m_drawCollision;
    bool m_drawGrid;
    sm::Vec2 m_gridSize;

    sf::Text m_gridText;

    /////////////////////////////
    //   Overriden functions   //
    /////////////////////////////
    /**
     * Handles the updating logic for the Scene_Play class.
     * @param dt the time lapsed since the last frame
     */
    void update(float dt) override;

    /**
     * Keeps track of which actions should be done (depending on whether key was released or pressed).
     * @param action data that contains whether the key was pressed or released [action.getType()]
     * and the action name (which tells the scene which specific logic to carry out next)
     */
    void sDoAction(const sge::Action &action) override;

    /**
     * Handles the rendering logic of the Scene_Play class.
     */
    void sRender() override;

    /**
     * Ends the current scene.
     */
    void onEnd() override;

    ////////////////////
    //     Other      //
    ////////////////////
    /**
     * 
     */
    void init(const std::string &levelPath);

    /**
     * Handles the logic for spawning the player for the Scene_Play class.
     */
    void spawnPlayer();

    /////////////////////
    //     Systems     //
    /////////////////////
    /**
     * Handles movement logic for the Scene_Play class.
     */
    void sMovement();

    /**
     * Handles life span logic for the Scene_Play class.
     */
    void sLifeSpan();

    /**
     * Handles collision logic for the Scene_Play class.
     */
    // void sCollision();

    /**
     * Handles animation logic for the Scene_Play class.
     */
    void sAnimation(float dt);

    /**
     * Private default constructor
     */
    Scene_Play();

public:
    /** 
     * Scene_Play Constructor
     * @param gameEngine an exisiting gameEngine pointer (associated with this scene)
     * @param levelPath a file path to the file containing data on level generation
     */
    Scene_Play(sge::GameEngine *gameEngine, const std::string &levelPath);

};

#endif // SCENE_PLAY_H