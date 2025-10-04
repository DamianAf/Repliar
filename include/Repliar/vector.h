#pragma once
#include <numbers>
#include <cmath>
#include <string>
#include <format>

// TODO: Comment the remaining functions

template <typename T> class Vector2 {
  public:
    T x, y;

  public:
    /**
     * @brief Creates a 2D vector with the specified values
     * @param x The x-coordinate (horizontal component).
     * @param y The y-coordinate (vertical component).
     * */
    Vector2(T x, T y) : x(x), y(y) {
    }
    /**
     * @brief Creates an empty 2D
     * @details Sets x and y member variables to 0
     * */
    Vector2() : x{}, y{} {
    }

    /**
     * @brief calculates the magnitute/length of a vector
     * @return The length/magnitude of the vector as a double
     */
    double length() const {
        return std::sqrt(x * x + y * y);
    }

    /**
     * @brief Formats the vector to be used as a string
     * @return std::string with the format (x, y)
     */
    std::string ToString() const {
        return std::format("({}, {})", x, y);
    }

    /**
     * @brief Returns a normalized vector without modifying the current vector
     * @returns New Normalized 2D vector
     */
    Vector2<T> normalized() const {
        static_assert(std::is_floating_point_v<T>,
                      "Normalized() is only supported for floating-point vectors (float, double).");
        T tempLength = length();
        if (tempLength != 0) {
            T tempx = x / tempLength;
            T tempy = y / tempLength;
            return Vector2<T>(tempx, tempy);
        }
        return Vector2<T>();
    }

    /**
     * @brief Normalizes the current vector
     */
    Vector2<T>& Normalize() {
        static_assert(std::is_floating_point_v<T>,
                      "Normalized() is only supported for floating-point vectors (float, double).");
        T tempLength = length();
        if (tempLength != 0) {
            x /= tempLength;
            y /= tempLength;
            return *this;
        }
        return *this;
    }

  public:
    static T Dot(const Vector2& vector1, const Vector2& vector2) {
        return vector1.x * vector2.x + vector1.y * vector2.y;
    }

    static double Angle(const Vector2& from, const Vector2& to, bool inDegrees = true) {
        T dot = from.x * to.x + from.y * to.y;

        T cross = from.x * to.y - from.y * to.x;

        double angleRad = std::atan2(static_cast<double>(cross), static_cast<double>(dot));
        if (inDegrees) {
            return angleRad * 180.0 / std::numbers::pi;
        }

        return angleRad;
    }

    // TODO: implement the Distance function that takes in 2 vectors and return the distance between them
    static double Distance() {
    }

  public:
    // operator overloading functions

    Vector2<T> operator+(const Vector2<T>& other) const {
        return Vector2(x + other.x, y + other.y);
    }
    Vector2<T> operator-(const Vector2<T>& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    Vector2<T> operator*(const Vector2<T>& other) const {
        return Vector2(x * other.x, y * other.y);
    }
    Vector2<T> operator/(const Vector2<T>& other) const {
        return Vector2(x / other.x, y / other.y);
    }
    Vector2<T> operator*(T scalar) const {
        return Vector2<T>(x * scalar, y * scalar);
    }
    Vector2<T> operator/(T scalar) const {
        return Vector2<T>(x / scalar, y / scalar);
    }
    Vector2<T>& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2<T>& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
    bool operator==(const Vector2<T>& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Vector2<T>& other) const {
        return !(*this == other);
    }
    friend Vector2<T> operator*(T scalar, const Vector2<T>& v) {
        return v * scalar;
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector2<T>& vector) {
        return os << vector.ToString();
    }
};