#include <SGE/util/Assets.h>

sge::Assets::Assets()
{
    
}

sge::Assets::~Assets()
{
    // for (std::pair<std::string, sf::SoundBuffer*> pair : this->_soundBuffers)
    // {
    //     delete pair.second;
    // }

    // for (std::pair<std::string, sf::Sound*> pair : this->_sounds)
    // {
    //     delete pair.second;
    // }
}

bool sge::Assets::addTexture(const std::string &name, const std::string &filePath)
{
    return this->_textures[name].loadFromFile(filePath);
}

// TODO
// bool sge::Assets::addSoundBuffer(const std::string &name, const std::string &filePath)
// {
//     this->_soundBuffers[name] = new sf::SoundBuffer();
//     return this->_soundBuffers[name]->loadFromFile(filePath);
// }

// TODO
// bool sge::Assets::addSound(const std::string &name, const std::string &filePath)
// {
//     if (!this->addSoundBuffer(name, filePath)) return false;
//     this->_sounds[name] = new sf::Sound();
//     this->_sounds[name]->setBuffer(*this->_soundBuffers.at(name));
//     return true;
// }

bool sge::Assets::addFont(const std::string &name, const std::string &filePath)
{
    return this->_fonts[name].loadFromFile(filePath);
}

bool sge::Assets::addAnimation(const std::string &animationName, const std::string &textureName, size_t row, size_t rows, size_t columns, float timeInterval)
{
    this->_animations[animationName].setTexture(getTexture(textureName), rows, columns);
    this->_animations[animationName].setTimeInterval(timeInterval);
    this->_animations[animationName].setRow(row);
    // NOTE: I don't really use frameCount so like bruh
    return false;
}

bool sge::Assets::loadFromFile(const std::string &path)
{
    // TODO: Implement a way for this class to read in a file and load in the correct assets(textures, sounds, fonts, etc.)
    return false;
}

const sf::Texture& sge::Assets::getTexture(const std::string &name) const
{
    return this->_textures.at(name);
}

// const sf::Sound& sge::Assets::getSound(const std::string &name) const
// {
//     return *this->_sounds.at(name);
// }

const sf::Font& sge::Assets::getFont(const std::string& name) const
{
    return this->_fonts.at(name);
}

const sge::Animation& sge::Assets::getAnimation(const std::string &animationName) const
{
    return this->_animations.at(animationName);
} 