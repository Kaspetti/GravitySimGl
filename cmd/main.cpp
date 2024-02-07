#include "main.hpp"
#include "../internal/circle.hpp"
#include "../shaders/shaders.hpp"

#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <vector>


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


static const GLfloat g_plane_verex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    -1.0, 1.0, 0.0f,
};


using namespace glm;
int main() {
    GLFWwindow *window = StartGL();
    if (window == NULL) {
        fprintf(stderr, "Failed to start GL.\n");
        return -1;
    }

    GLuint programId = LoadShaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    // Create the VAO (vertex array object) and bind it
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_plane_verex_buffer_data), g_plane_verex_buffer_data, GL_STATIC_DRAW);

    std::vector<Circle> circles = std::vector<Circle>{};
    circles.push_back(Circle(vec3(600, 600, 0), vec3(0.749f, 0.431f, 0.749f), 50.0f, 1.0f));
    circles.push_back(Circle(vec3(200, 200, 0), vec3(0.8f, 0.31f, 0.196f), 30.0f, 1.0f));
    circles.push_back(Circle(vec3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), vec3(0.263f, 0.69f, 0.475f), 25.0f, 1.0f));

    GLSLCircle glslCircles[circles.size()];
    for (int i = 0; i < circles.size(); i++) {
        glslCircles[i] = circles[i].getGLSLCircle();
    }

    GLuint ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glslCircles), glslCircles, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programId);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(1);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    return 0;
}


GLFWwindow* StartGL() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        return NULL;
    }

    glfwWindowHint(GL_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Gravity Simulator", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to create GLFW window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW.¨\n");
        return NULL;
    }

    return window;
}
