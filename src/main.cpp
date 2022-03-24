#include <game/app.h>

int main() {
    punkyoi::Punkyoi& theGame = punkyoi::Punkyoi::createPunkyoi();
    theGame.run();
    return 0;
}
