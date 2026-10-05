#include "core/GameRunner.h"
#include "core/GameExceptions.h"
#include "ui/ColorTheme.h"
#include <iostream>
#include <exception>

int main() {
    try {
        GameRunner runner;
        runner.run();
        return 0;

    } catch (const GameException& e) {
        std::cerr << ColorTheme::RED << "\n❌ Game Error: " << e.what()
                  << ColorTheme::RESET << std::endl;
        return 1;

    } catch (const std::exception& e) {
        std::cerr << ColorTheme::RED << "\n❌ Unexpected Error: " << e.what()
                  << ColorTheme::RESET << std::endl;
        return 2;

    } catch (...) {
        std::cerr << ColorTheme::RED << "\n❌ Unknown error occurred!"
                  << ColorTheme::RESET << std::endl;
        return 3;
    }
}
