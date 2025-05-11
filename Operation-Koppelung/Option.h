#include <string>
#include <vector>

class Option {
public:
    std::string getDescription() { return description; }
    virtual void execute() = 0;
    virtual ~Option() = default;

protected:
    Option(std::string description, std::vector<std::string> story) : description(description), story(story) {};
    std::string description;
    std::vector<std::string> story;
};

class ExplorationOption : public Option {
private:
    int loot_id;
public:
    void execute() override;
    ExplorationOption(std::string description, std::vector<std::string> story, int loot_id) : Option{ description, story }, loot_id(loot_id) {};
};

class GrammophoneOption : public Option {
private:
    int sanity_restore;
public:
    void execute() override;
    GrammophoneOption(std::string description, std::vector<std::string> story, int sanity_restore) : Option{ description, story }, sanity_restore(sanity_restore) {};
};

class BattleOption : public Option {
private:
    std::vector<int> enemies_id;
public:
	void execute() override;
	BattleOption(std::string description, std::vector<std::string> story, std::vector<int> enemies_id) : Option{ description, story }, enemies_id(enemies_id) {};
};

class RoomchangeOption : public Option {
private:
	int room_id;
public:
	void execute() override;
	RoomchangeOption(std::string description, std::vector<std::string> story, int room_id) : Option{ description, story }, room_id(room_id) {};
};