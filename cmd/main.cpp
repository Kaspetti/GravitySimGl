#include "main.hpp"
#include "../shaders/shaders.hpp"

#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <glm/glm.hpp>


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

    GLint centersLocation = glGetUniformLocation(programId, "centers");
    GLint radiiLocation = glGetUniformLocation(programId, "radii");
    GLint colorsLocation = glGetUniformLocation(programId, "colors");

    vec3 centers[3] = {vec3(100,100,0), vec3(170, 100, 0), vec3(200, 100, 0)};
    int radii[3] = {50, 25, 12};
    vec3 colors[3] = {vec3(1,0,0), vec3(0,1,0), vec3(0,0,1)};

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programId);

        for (int i = 0; i < 3; i++) {
            if (centers[i].x > 500) {
                centers[i] -= vec3(0.4,0,0);
            } else {
                centers[i] += vec3(0.4,0,0);
            }

        }

        glUniform1iv(radiiLocation, 3, radii);
        glUniform3fv(centersLocation, 3, &centers[0][0]);
        glUniform3fv(colorsLocation, 3, &colors[0][0]);

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
    window = glfwCreateWindow(1024, 768, "Gravity Simulator", NULL, NULL);
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
