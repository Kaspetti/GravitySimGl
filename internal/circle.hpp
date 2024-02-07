#include <glm/glm.hpp>


struct GLSLCircle {
    glm::vec4 origin;
    glm::vec4 color;
    float radius;

    float padding[3];
};

struct Circle {
    Circle();

    Circle(glm::vec3 origin, glm::vec3 color, float radius, float mass);

    Circle(glm::vec3 origin, glm::vec3 color, glm::vec3 velocity, glm::vec3 delta, float radius, float mass);

    glm::vec3 origin;
    glm::vec3 color;
    float radius;

    glm::vec3 velocity;
    glm::vec3 delta;
    float mass;

    GLSLCircle getGLSLCircle();
};

