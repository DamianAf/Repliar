#include "Repliar/ECS/components.hpp"
#include "Repliar/ECS/entityManager.hpp"
#include <Repliar/repliar.hpp>
#include <iostream>

int main() {
    Repliar game(800, 800, "hello");

    // Testing Vector class

    Vector2 vec4(1, 2);
    Vector2 vec5(3, 4);
    std::cout << Vector2<int>::Angle(vec4, vec5) << std::endl;

    // Testing Entity Manager class

    Entity ent1 = EntityManager::CreateEntity();

    struct Comp : Component::Custom {
        int i = 10;
    };

    EntityManager::addCustomComponent<Comp>(ent1);

    EntityManager::OnStart(ent1, [](Entity e) {
        std::cout << EntityManager::getCustomComponent<Comp>(e).i << std::endl;
        ;
    });

    // Game loop

    while (game.running) {
        game.Update();
    }
}
