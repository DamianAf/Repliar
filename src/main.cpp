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
    Entity ent2 = EntityManager::CreateEntity();

    struct Comp : Component::Custom {
        int i = 10;
    };

    EntityManager::addCustomComponent<Comp>(ent1);
    EntityManager::addCustomComponent<Comp>(ent2);

    EntityManager::addComponent<Component::Transform>(ent1);
    EntityManager::addComponent<Component::Sprite>(ent1);
    // clang-format off
    EntityManager::OnStart(ent1, [](Entity e) {
        auto& spriteComp = EntityManager::getComponent<Component::Sprite>(e);
        spriteComp.loadTexture("./assets/test.png");
    });
    EntityManager::addComponent<Component::Transform>(ent2);
    EntityManager::addComponent<Component::Sprite>(ent2);
    // clang-format off
    EntityManager::OnStart(ent2, [](Entity e) {
        auto& spriteComp = EntityManager::getComponent<Component::Sprite>(e);
        auto& transComp = EntityManager::getComponent<Component::Transform>(e);
        transComp.position.x = 100;
        spriteComp.loadTexture("./assets/test.png");
    });
    // clang-format on

    // Game loop
    game.Start();
    while (game.running) {
        game.Update();
    }
}
