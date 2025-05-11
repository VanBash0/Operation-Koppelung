#include "Menu.h"

int main() {
    std::vector<std::string> options = { "Option 1", "Option 2", "Option 3", "Exit" };
    Menu menu(options);
    menu.show();
    return 0;
}