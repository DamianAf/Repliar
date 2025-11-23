#pragma once

#include <assert.h>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <vector>
#include "Repliar/ECS/components.hpp"

using Entity = std::uint32_t;
using components = std::uint16_t;

// TODO: add comments to each function

class EntityManager {
  public:
    /**
     * @brief creates an Entity
     * @return the Entity ID
     */
    static Entity CreateEntity() {

        // Recycles ID's when possible
        if (!m_freeSpaceArray.empty()) {

            m_isAlive[m_freeSpaceArray.back()] = true;
            std::uint32_t tempEntity = m_freeSpaceArray.back();

            m_freeSpaceArray.pop_back();

            return tempEntity;
        }

        m_isAlive.push_back(true);
        m_bitflags.resize(m_isAlive.size());

        return m_isAlive.size() - 1;
    }

    /**
     * @brief destroys the Entity entirely
     */
    static void DestroyEntity(Entity id) {
        m_isAlive[id] = false;
        m_freeSpaceArray.push_back(id);
        m_bitflags[id] = 0;
        if (id < m_customComponents.size()) {
            m_customComponents[id].reset();
        }
    }

    /**
     * @brief expects a Component type in the template
     * @return the component specified
     */
    template <typename T> static auto& getComponent(Entity id) {
        return m_getComponentPool<T>()[id];
    }

    /**
     * @return the custom component of the Entity
     */
    template <typename T> static auto& getCustomComponent(Entity id) {
        assert(id < m_customComponents.size());
        assert(m_customComponents[id] != nullptr);
        return static_cast<T&>(*m_customComponents[id]);
    }

    /**
     * @brief creates a new component or returns it if it already exists
     * @return the Component specified
     */
    template <typename T> static auto& addComponent(Entity id) {

        constexpr components tempComponentFlag = getComponentBitmask<T>();

        // Adds a component only if the entity doesn't already have it added
        if ((m_bitflags[id] & tempComponentFlag) == 0) {

            auto& tempComponent = m_getComponentPool<T>();

            if (tempComponent.size() <= id) {
                tempComponent.resize(id + 1);
            }

            // binds the component to the entity
            tempComponent[id] = T();
            m_bitflags[id] |= tempComponentFlag;

            return tempComponent[id];
        }
        return m_getComponentPool<T>()[id];
    }

    /**
     * @brief creates a custom component that inherits Component::Custom
     */
    template <typename T> static T& addCustomComponent(Entity id) {
        static_assert(std::is_base_of_v<Component::Custom, T>, "T must derive from Component::Custom");

        if ((m_bitflags[id] & ComponentType::CUSTOM_COMPONENT) == 0) {
            if (m_customComponents.size() <= id) {
                m_customComponents.resize(id + 1);
            }
            m_customComponents[id] = std::make_unique<T>();
            if (m_bitflags.size() <= id) {
                m_bitflags.resize(id + 1);
            }
            m_bitflags[id] |= ComponentType::CUSTOM_COMPONENT;
        }
        return static_cast<T&>(*m_customComponents[id]);
    }

    /**
     * @brief gets the bitmask value of a component
     * @return an int bit value of the component
     */
    template <typename T> static constexpr ComponentType getComponentBitmask() {
        if constexpr (std::is_same_v<T, Component::Transform>) {
            return ComponentType::TRANSFORM_COMPONENT;
        }
        if constexpr (std::is_same_v<T, Component::Sprite>) {
            return ComponentType::SPRITE_COMPONENT;
        }
        if constexpr (std::is_same_v<T, Component::Collider>) {
            return ComponentType::COLLIDER_COMPONENT;
        }
        if constexpr (std::is_base_of_v<T, Component::Custom>) {
            return ComponentType::CUSTOM_COMPONENT;
        } else {
            return ComponentType::NONE;
        }
    }

    /**
     * @brief creates the onUpdate function
     * @param id the Entity id
     * @param update a lamda or a function pointer of the onUpdate function (must expect an Entity and  a float (aka
     * deltaTime) as arguments)
     */
    static void OnUpdate(Entity id, void (*update)(Entity, float)) {
        m_updateArray.resize(id + 1);
        m_updateArray[id] = update;
    }
    /**
     * @brief creates the onStart function
     * @param id the Entity id
     * @param start a lamda or a function pointer of the onStart function (must expect an Entity type as an argument)
     */
    static void OnStart(Entity id, void (*start)(Entity)) {
        m_startArray.resize(id + 1);
        m_startArray[id] = start;
    }

  private:
    inline static std::vector<bool> m_isAlive;
    inline static std::vector<Entity> m_freeSpaceArray;
    template <typename T> inline static std::vector<T>& m_getComponentPool() {
        static std::vector<T> pool;
        return pool;
    }
    inline static std::vector<std::unique_ptr<Component::Custom>> m_customComponents;
    inline static std::vector<void (*)(Entity, float)> m_updateArray;
    inline static std::vector<void (*)(Entity)> m_startArray;
    inline static std::vector<components> m_bitflags;
};
