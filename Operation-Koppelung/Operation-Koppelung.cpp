#include "Menu.h"
#include <string>

int main() {
    std::vector<std::string> data = { "Option", "I love Paris", "Smth else" };
    Menu menu = Menu(data);
    menu.run();
}