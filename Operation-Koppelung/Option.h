#pragma once
#include <string>
#include <vector>
#include "ViewManager.h"
#include "Player.h"
#include "ItemManager.h"
#include "Battle.h"

class Option {
public:
    std::string getDescription() { return description; }
    virtual void execute(std::shared_ptr<ViewManager> viewManager, std::shared_ptr<Player> player, std::shared_ptr<ItemManager> itemManager, std::shared_ptr<EnemyManager> enemyManager) = 0;
    virtual ~Option() = default;

protected:
    Option(std::string description, std::string story, std::string after_story, bool isPicked) : description(description), story(story), after_story(after_story), isPicked(isPicked) {};
    std::string description;
    std::string story;
    std::string after_story;
    bool isPicked;
};

class ExplorationOption : public Option {
private:
    int loot_id;
public:
    void execute(std::shared_ptr<ViewManager> viewManager, std::shared_ptr<Player> player, std::shared_ptr<ItemManager> itemManager, std::shared_ptr<EnemyManager> enemyManager) override;
    ExplorationOption(std::string description, std::string story, std::string after_story, bool isPicked, int loot_id) : Option{ description, story, after_story, isPicked }, loot_id(loot_id) {};
};

class GramophoneOption : public Option {
private:
    int sanity_restore;
public:
    void execute(std::shared_ptr<ViewManager> viewManager, std::shared_ptr<Player> player, std::shared_ptr<ItemManager> itemManager, std::shared_ptr<EnemyManager> enemyManager) override;
    GramophoneOption(std::string description, std::string story, std::string after_story, bool isPicked, int sanity_restore) : Option{ description, story, after_story, isPicked }, sanity_restore(sanity_restore) {};
};

class BattleOption : public Option {
private:
    std::vector<int> enemies_id;
public:
    void execute(std::shared_ptr<ViewManager> viewManager, std::shared_ptr<Player> player, std::shared_ptr<ItemManager> itemManager, std::shared_ptr<EnemyManager> enemyManager) override;
    BattleOption(std::string description, std::string story, std::string after_story, bool isPicked, std::vector<int> enemies_id) : Option{ description, story, after_story, isPicked }, enemies_id(enemies_id) {};
};

class RoomChangeOption : public Option {
private:
	int room_id;
public:
    void execute(std::shared_ptr<ViewManager> viewManager, std::shared_ptr<Player> player, std::shared_ptr<ItemManager> itemManager, std::shared_ptr<EnemyManager> enemyManager) override;
    RoomChangeOption(std::string description, std::string story, std::string after_story, bool isPicked, int room_id) : Option{ description, story, after_story, isPicked }, room_id(room_id) {};
};