//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "Triangle.hpp"

namespace ft {
    Triangle::Triangle(const Triangle &triangle) {
        _points[0] = triangle._points[0];
        _points[1] = triangle._points[1];
        _points[2] = triangle._points[2];
    }

    Triangle::Triangle(const glm::vec4 &p1, const glm::vec4 &p2, const glm::vec4 &p3) {
        _points[0] = p1;
        _points[1] = p2;
        _points[2] = p3;
    }

    const glm::vec4 &Triangle::operator[](int i) const {
        return _points[i];
    }
}