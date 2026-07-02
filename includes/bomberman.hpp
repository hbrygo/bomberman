#ifndef BOMBERMAN_HPP
# define BOMBERMAN_HPP

# include <ctime>
# include <string>
# include <vector>
# include <map>

constexpr int ESCAPE = 27;

class Game;

enum class Resolution {
    LOW = 480,
    MEDIUM = 720,
    HIGH = 1080
};

enum class TileType {
    WALL = '1',
    PATH = '0',
    UNBREAKABLE_WALL = '2',
    BONUS = 'B'
};

enum class BonusType {
    SPEED = 0,
};

enum class Inputs {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    PLACE_BOMB,
    ACTIVE_BONUS
};

enum class GameMode {
    CAMPAIGN,
    MULTI,
    ARCADE
};

enum class Grade {
    S,
    A,
    B,
    C,
    D,
    E,
    F
};

class AEntity {
    protected:
        int _x;
        int _y;
    
    public:
        AEntity();
        virtual ~AEntity();
        int get_x();
        int get_y();
        int set_x(int x);
        int set_y(int y);
        bool move(int dx, int dy);
        bool is_alive();
        void take_damage(int damage);
};

class Sound {
    private:
        std::string _level_music_path;
        std::string _menu_music_path;
        std::string _death_music_path;
        std::string _bonus_music_path;
        std::string _bomb_music_path;
        std::string _victory_music_path;
        int _volume;
        bool _active;

    public:
        Sound();
        ~Sound();
        void play_music(std::string path);
        void stop_music();
        void set_volume(int volume);
};

class Level {
    private:
        std::string _map_path;
        int _stars;
        bool _unlocked;
        Grade _grade;
        std::time_t _time;

    public:
        Level();
        ~Level();
        void start_level();
        void end_level();
};

class Save {
    private:
        int _id;
        Resolution _resolution;
        int _stars;
        std::map<Inputs, int> _inputs;
        std::vector<Level> _campaign_stats;
        std::vector<BonusType> _bonuses;
    
    public:
        Save();
        ~Save();
        void save_game(Game &game);
        void load_game(Game &game);
};

class Player : public AEntity {
    private:
        int _id;
        int _bombs;
        std::map<Inputs, int> _inputs;
        std::map<BonusType, bool> _bonuses;

    public:
        Player();
        ~Player();
};

class Map {
    private:
        std::vector<std::string> _map;
        std::vector<BonusType> _bonuses;
        int _width;
        int _height;
    
    public:
        Map();
        ~Map();
};

class Game {
    private:
        Save _save;
        // Sound _music;
        Player _player;
        Map _map_in_play;
        Level _level_in_play;
        GameMode _game_mode;

    public:
        Game();
        ~Game();
        void start_game();
        void end_game();
};

class MusicData {
    private:
        std::string _path;
        float _duration;
        bool _status;
    
    public:
        MusicData();
        ~MusicData();
        void play();
        void stop();
};

class Bonus {
    private:
        std::string _definition;
        std::string _img;
        std::string _name;
        BonusType _id;
        std::time_t _duration;
        bool _unlocked;
        int _speed;
    
    public:
        Bonus();
        ~Bonus();
};

#endif