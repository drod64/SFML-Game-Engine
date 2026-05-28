#ifndef SGE_ASSETS_H
#define SGE_ASSETS_H
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sge/util/Animation.h>

namespace sge {
// TODO: test if this file correctly loads and returns the desired assets when requested.
class Assets {
private:
    std::unordered_map<std::string, sf::Texture> _textures;
    // TODO: Fix issues regarding storage of sf::Sound and sf::SoundBuffer items.
    // std::unordered_map<std::string, sf::SoundBuffer*> _soundBuffers;
    // std::unordered_map<std::string, sf::Sound*> _sounds;
    std::unordered_map<std::string, sge::Animation> _animations;
    std::unordered_map<std::string, sf::Font> _fonts;

    bool addSoundBuffer(const std::string &name, const std::string &filePath);

public:
    Assets();
    ~Assets();

    bool addTexture(const std::string &name, const std::string &filePath);
    bool addSound(const std::string &name, const std::string &filePath);
    bool addFont(const std::string &name, const std::string &filePath);
    bool addAnimation(const std::string &animationName, const std::string &textureName, size_t frameCount, size_t rows, size_t columns, float timeInterval);
    bool loadFromFile(const std::string &path);

    // TODO: Implement a way to return a default texture, sound, or font instead if a desired asset was requested and does not exist.
    const sf::Texture& getTexture(const std::string &name) const;
    const sf::Sound& getSound(const std::string &name) const;
    const sf::Font& getFont(const std::string &name) const;
    const sge::Animation& getAnimation(const std::string &animationName) const;

};

} // namespace sge

#endif // SGE_ASSETS_H