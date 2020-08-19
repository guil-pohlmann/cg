#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/glew_config.h>
#include <common/glfw_config.h>
#include <common/shaders.h>
#include <common/vaoConfig.h>
#include <common/vboConfig.h>

const glm::vec2 SCREEN_SIZE(800, 600);

int main () {
    GLfloat pointsFirst[]={
            -0.2f,  0.2f, 0.0f,
            0.0f, -0.2f, 0.0f,
            -0.4f, -0.2f, 0.0f
    };

    GLfloat pointsSecond[]={
            0.2f,  0.2f, 0.0f,
            0.0f, -0.2f, 0.0f,
            0.4f, -0.2f, 0.0f
    };

    GLfloat colorsFirst[]={
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
    };

    GLfloat colorsSecond[]={
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

    GlewConfig glew;
    glew.init();

    Shader ourShader("shader.vs", "shader.fs");

    VaoConfig firstVAO;
    VboConfig pointsFirstVbo(pointsFirst, 9);
    firstVAO.bind(0, 3);
    VboConfig colorsFirstVbo(colorsFirst, 9);
    firstVAO.bind(1, 3);

    VaoConfig secondVAO;
    VboConfig pointsSecondVbo(pointsSecond, 9);
    secondVAO.bind(0, 3);
    VboConfig colorsSecondVbo(colorsSecond, 9);
    secondVAO.bind(1, 3);

    ourShader.use();


    while (!glfwWindowShouldClose (glfw.getWindow())) {
        ourShader.setMat4("matrix",matrix);

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray (firstVAO.id);
        glDrawArrays (GL_TRIANGLES, 0, 6);

        glBindVertexArray (secondVAO.id);
        glDrawArrays (GL_TRIANGLES, 0, 6);

        glfwPollEvents ();
        glfwSwapBuffers (glfw.getWindow());
    }
    glfwTerminate();
    return 0;
}