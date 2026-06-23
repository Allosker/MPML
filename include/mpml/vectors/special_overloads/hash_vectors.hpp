#pragma once 
// MIT
// Allosker - 2026
// ===================================================
// Defines some overloads and utility functions for the "unordered_map" stl container
// ===================================================

#include <unordered_map>
#include "mpml/vectors/vectors.hpp"


template <typename T>
inline void hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    // 0x9e3779b97f4a7c15 is a golden ratio constant to ensure bit distribution
    seed ^= hasher(v) + 0x9e3779b97f4a7c15 + (seed << 6) + (seed >> 2);
}

template <typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) {
    hash_combine(seed, v);
    hash_combine(seed, rest...);
}

namespace std
{
    template <typename U>
    struct hash<mpml::Vector2<U>>
    {
        size_t operator ()(const mpml::Vector2<U>& vec) const 
        {
            std::size_t seed{};
            hash_combine(seed, vec.x, vec.y);

            return seed;
        }
    };

    template <typename U>
    struct hash<mpml::Vector3<U>>
    {
        size_t operator ()(const mpml::Vector3<U>& vec) const
        {
            std::size_t seed{};
            hash_combine(seed, vec.x, vec.y, vec.z);

            return seed;
        }
    };

    template <typename U>
    struct hash<mpml::Vector4<U>>
    {
        size_t operator ()(const mpml::Vector4<U>& vec) const
        {
            std::size_t seed{};
            hash_combine(seed, vec.x, vec.y, vec.z, vec.w);

            return seed;
        }
    };
}
