#include <Repliar/repliar.h>
#include <iostream>

int main() {
    Repliar game(800, 800, "hello");

    Vector2 vec4(1, 2);
    Vector2 vec5(3, 4);
    std::cout << vec4.length() << std::endl;
    double angle = Vector2<int>::Angle(vec5, vec4);
    std::cout << "angle: " << angle << "; dot: " << Vector2<int>::Dot(vec4, vec5) << std::endl;
    while (game.running) {
        game.Update();
    }
}