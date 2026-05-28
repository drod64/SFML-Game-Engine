#ifndef SGE_ANIMATION_H
#define SGE_ANIMATION_H
#include <vector>
#include <SGE/util/Vec2.h>
#include <SFML/Graphics.hpp>

namespace sge {
// NOTE: Sprite sheets will be horizontal and contain ONLY animation for a current action (running, jumping, idle)
// In the future, I hope to expand this class to handle more complex spritesheets.
class Animation {
private:
    size_t _totalFrameCount;
    bool _loopedOnce;
    sf::IntRect _textureRect;
    float _timeInterval; // relative to seconds
    float _currentFrameTime;
    sf::Sprite _sprite;

public:
    Animation();
    Animation(const sf::Texture &texture, size_t frameCount, size_t rows, size_t columns, float timeInterval);
    Animation& operator = (const Animation &otherAnimation);

    /*
        Updates the current shown animation frame to the next one after the time interval has been reached.
        
        @param dt (float) the delta time that has passed since the last frame
    */
    void update(float dt);

    /*
        Sets the row which animations should be grabbed from the sprite sheet.

        @param row (size_t) the desired row to be chosen
    */
    void setRow(size_t row);

    /*
        Sets the texture of the animation object. By providing the entire number of rows and columns of the spritesheet, the sge::Animation 
        class can divide the spritesheet into individual sprite frames to be used for animation.

        @param texture  (sf::Texture&) a reference to the sf::Texture object
        @param rows     (size_t) the number of rows in the entire sprite sheet
        @param columns  (size_t) the number of columns in the entire sprite sheet
    */
    void setTexture(const sf::Texture &texture, size_t rows, size_t columns); // get
    const sf::Texture& getTexture() const;
    void setPosition(const sf::Vector2f &position); // get
    sf::Vector2f getPosition() const;
    void setTimeInterval(float timeInterval); // get
    float getTimeInterval() const;
    void setScale(const sf::Vector2f &scale);
    void scaleToSize(const sf::Vector2f &size);
    sf::Vector2f getSize() const;
    const sf::Sprite& getSprite() const;
    sf::Sprite& getSprite();
    bool hasEnded() const;


private:
    void setUp(const sf::Texture &texture, size_t rows, size_t columns);
    void setUpTextureRect(const sf::Vector2u &size, size_t rows, size_t columns);

};

}

#endif // SGE_ANIMATION_H