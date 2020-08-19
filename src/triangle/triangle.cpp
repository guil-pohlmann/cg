#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/glew_config.h>
#include <common/glfw_config.h>
#include <common/shaders.h>
#include <common/vaoConfig.h>
#include <common/vboConfig.h>

const glm::vec2 SCREEN_SIZE(800, 600);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_UP) {
            std::cout << "Tecla para cima pressionada\n";
        } else if(key == GLFW_KEY_DOWN) {
            std::cout << "Tecla para baixo pressionada\n";
        } else if (key == GLFW_KEY_LEFT) {
            std::cout << "Tecla para esquerda pressionada\n";
        } else if (key == GLFW_KEY_RIGHT) {
            std::cout << "Tecla para direita pressionada\n";
        }
    }
}

int main () {
    GLfloat points[]={
            0.0f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
    };

    GLfloat colors[]={
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
    };

    glm::mat4 matrix (
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    );

    GlfwConfig glfw;
    glfw.init(SCREEN_SIZE);

    glfwSetKeyCallback(glfw.getWindow(), key_callback);

    GlewConfig glew;
    glew.init();

    Shader ourShader("shader.vs", "shader.fs");

    VaoConfig vao;
    VboConfig pointsVbo(points, 9);
    vao.bind(0, 3);
    VboConfig colorsVbo(colors, 9);
    vao.bind(1, 3);

    ourShader.use();


    while (!glfwWindowShouldClose (glfw.getWindow())) {
//        matrix = reflection.calculateReflectedMatrix(matrix);
        ourShader.setMat4("matrix",matrix);

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray (vao.id);
        glDrawArrays (GL_TRIANGLES, 0, 3);

        glfwPollEvents ();
        glfwSwapBuffers (glfw.getWindow());
    }
    glfwTerminate();
    return 0;
}