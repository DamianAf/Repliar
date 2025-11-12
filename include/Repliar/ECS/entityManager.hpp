#pragma once

#include <assert.h>
#include <cstdint>
#include <type_traits>
#include <vector>
#include "Repliar/ECS/components.hpp"

using Entity = std::uint32_t;
using components = std::uint16_t;

// TODO: add comments to each function

class EntityManager {
  public:
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

    static void DestroyEntity(Entity id) {
        m_isAlive[id] = false;
        m_freeSpaceArray.push_back(id);
        m_bitflags[id] = 0;
    }

    template <typename T> static auto& getComponent(Entity id) {
        return m_getComponentPool<T>()[id];
    }

    template <typename T> static void addComponent(Entity id) {

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
        }
    }

    // NOT_IMPLEMENTED
    template <typename T> static void addCustomComponent(Entity id); // TODO: implement adding custom Component

    template <typename T> static constexpr ComponentType getComponentBitmask() {
        if constexpr (std::is_same_v<T, Transform>) {
            return ComponentType::TRANSFORM_COMPONENT;
        }
        if constexpr (std::is_same_v<T, Sprite>) {
            return ComponentType::SPRITE_COMPONENT;
        }
        if constexpr (std::is_same_v<T, Collider>) {
            return ComponentType::COLLIDER_COMPONENT;
        }
        // if constexpr (std::is_same_v<T, Transform>) {
        //     return ComponentType::TRANSFORM_COMPONENT;
        // }
        else {
            return ComponentType::NONE;
        }
    }

    static void OnUpdate(Entity id, void (*update)(float)) {
        m_updateArray.resize(id + 1);
        m_updateArray[id] = update;
    }
    static void OnStart(Entity id, void (*start)()) {
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
    inline static std::vector<void (*)(float)> m_updateArray;
    inline static std::vector<void (*)()> m_startArray;
    inline static std::vector<components> m_bitflags;
};
