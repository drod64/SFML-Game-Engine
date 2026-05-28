#include <SGE/util/Animation.h>

sge::Animation::Animation() = default;

sge::Animation::Animation(const sf::Texture &texture, size_t frameCount, size_t rows, size_t columns, float timeInterval)
{
    this->_totalFrameCount = frameCount;
    this->_loopedOnce = false;
    this->_timeInterval = timeInterval;
    this->_currentFrameTime = 0;
    setUp(texture, rows, columns);
}

sge::Animation& sge::Animation::operator=(const Animation &otherAnimation)
{
    if (this != &otherAnimation)
    {
        this->_totalFrameCount = otherAnimation._totalFrameCount;
        this->_textureRect = otherAnimation._textureRect;
        this->_timeInterval = otherAnimation._timeInterval;
        this->_currentFrameTime = otherAnimation._currentFrameTime;

        this->_sprite = otherAnimation._sprite;
    }
    return *this;
}
void sge::Animation::update(float dt)
{
    this->_currentFrameTime += dt;
    if (this->_currentFrameTime > this->_timeInterval)
    {
        if (this->_textureRect.left + this->_textureRect.width >= this->_sprite.getTexture()->getSize().x)
        {
            this->_textureRect.left = 0;
            this->_loopedOnce = true;
        }
        else
        {
            this->_textureRect.left += this->_textureRect.width;
        }
        this->_currentFrameTime = 0;
    }
    this->_sprite.setTextureRect(this->_textureRect);
}

void sge::Animation::setRow(size_t row)
{
    this->_textureRect.top = this->_textureRect.height * row;
}

void sge::Animation::setTexture(const sf::Texture &texture, size_t rows, size_t columns)
{
    setUp(texture, rows, columns);
}

const sf::Texture& sge::Animation::getTexture() const
{
    return *this->_sprite.getTexture();
}

void sge::Animation::setPosition(const sf::Vector2f &position)
{
    this->_sprite.setPosition(position);
}

sf::Vector2f sge::Animation::getPosition() const
{
    return this->_sprite.getPosition();
}

void sge::Animation::setTimeInterval(float timeInterval)
{
    this->_timeInterval = timeInterval;
}

float sge::Animation::getTimeInterval() const
{
    return this->_timeInterval;
}

void sge::Animation::setScale(const sf::Vector2f &scale)
{
    this->_sprite.scale(scale);
}

void sge::Animation::scaleToSize(const sf::Vector2f &size)
{
    float scaleX = size.x / static_cast<float>(this->_textureRect.width);
    float scaleY = size.y / static_cast<float>(this->_textureRect.height);
    this->_sprite.scale(scaleX, scaleY);
}

sf::Vector2f sge::Animation::getSize() const
{
    sf::FloatRect bounds = this->_sprite.getGlobalBounds();
    return {bounds.width, bounds.height};
}

const sf::Sprite& sge::Animation::getSprite() const
{
    return this->_sprite;
}

sf::Sprite& sge::Animation::getSprite()
{
    return this->_sprite;
}

bool sge::Animation::hasEnded() const
{
    return this->_loopedOnce;
}

void sge::Animation::setUp(const sf::Texture &texture, size_t rows, size_t columns)
{
    this->_sprite.setTexture(texture);
    setUpTextureRect(texture.getSize(), rows, columns);
    this->_sprite.setTextureRect(this->_textureRect);
    this->_sprite.setOrigin(static_cast<float>(this->_textureRect.width / 2.f),
                            static_cast<float>(this->_textureRect.height / 2.f));
}

void sge::Animation::setUpTextureRect(const sf::Vector2u &size, size_t rows, size_t columns)
{
    this->_textureRect.width = static_cast<int>( floor(static_cast<float>(size.x) / static_cast<float>(columns) + 0.5) ); // ceils result
    this->_textureRect.height = static_cast<int>(size.y) / rows;
    this->_textureRect.top = 0;
    this->_textureRect.left = 0;
}