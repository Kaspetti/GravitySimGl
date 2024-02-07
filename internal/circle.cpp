#include "circle.hpp"


GLSLCircle Circle::getGLSLCircle() {
    GLSLCircle glslCircle;

    glslCircle.origin = glm::vec4(origin, 1.0f);
    glslCircle.color = glm::vec4(color, 1.0f);
    glslCircle.radius = radius;

    return glslCircle;
}


Circle::Circle() {
    origin = glm::vec3(0);
    color = glm::vec3(1,0,0);
    velocity = glm::vec3(0);
    delta = glm::vec3(0);
    radius = 50;
    mass = 1;
}


Circle::Circle(glm::vec3 origin, glm::vec3 color, float radius, float mass) {
    this->origin = origin;
    this->color = color;
    this->velocity = glm::vec3(0);
    this->delta = glm::vec3(0);
    this->radius = radius;
    this->mass = mass;
}


Circle::Circle(glm::vec3 origin, glm::vec3 color, glm::vec3 velocity, glm::vec3 delta, float radius, float mass) {
    this->origin = origin;
    this->color = color;
    this->velocity = velocity;
    this->delta = delta;
    this->radius = radius;
    this->mass = mass;
}
