#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/glew_config.h>
#include <common/glfw_config.h>
#include <common/shaders.h>
#include <common/vaoConfig.h>
#include <common/vboConfig.h>

#include <glm/gtc/matrix_transform.hpp>

const glm::vec2 SCREEN_SIZE(800, 600);
float dx = 0.0f, dy=0.0f,dz=5.0f;
glm::mat4 view;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    static bool gWireframe = 0;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        gWireframe = !gWireframe;
        if (gWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        dx -= 1.0;
    }

    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        dx += 1.0;
    }
    else if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        dy += 1.0;
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        dy -= 1.0;
    }
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        dz += 1.0;
    }
    else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
    {
        dz -= 1.0;
    }
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        dx = dy = 0.0f;
        dz = 5.0;
    }
    else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        std::cout << "dx,dy,dz = (" << dx << "," << dy << "," << dz << ")" << std::endl;
    }
}

int main () {
    GLfloat vertices[] = {
            // positions          // colors
            1.0f,  1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,   1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
            -1.0f,  1.0f, 1.0f,   1.0f, 1.0f, 0.0f,
            // positions          // colors
            1.0f,  1.0f, -1.0f,   1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f,
            -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 0.0f,
            -1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,
            // positions          // colors
            0.0f,  2.0f, 0.0f,   1.0f, 1.0f, 0.0f,
    };
    unsigned int index[] = {
            3, 1, 0,  // near / front
            1, 3, 2,
            5, 7, 4, // far / near
            7, 5, 6,
            5, 0, 1, // right
            0, 5, 4,
            7, 0, 4,  // top
            0, 7, 3,
            6, 1, 2, // bottom
            1, 6, 5,
            6, 3, 7,
            3, 6, 2,
            0, 3, 8, // top pyramid
            0, 4, 8,
            4, 7, 8,
            7, 0, 8

    };

    GlfwConfig glfw;
    glfw.init(SCREEN_SIZE);

    glfwSetKeyCallback(glfw.getWindow(), key_callback);

    GlewConfig glew;
    glew.init();

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("shader.vs", "shader.fs");

    VaoConfig vao;
    VboConfig pointsVbo(vertices, sizeof(vertices));
    vao.bind(0, 3, 6 * sizeof( GLfloat ), (GLvoid*)0);

    VboConfig colorsVbo(vertices, sizeof(vertices));
    vao.bind(1, 3, 6 * sizeof( GLfloat ), (GLvoid *)( 3 * sizeof(GLfloat)));

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    ourShader.use();

    glm::mat4 model(1.0f);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -0.5f, 0.0f));
    ourShader.setMat4("model", model);

    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f),(float)800/(float)600,0.1f,100.0f);
    ourShader.setMat4("projection", projection);

    while (!glfwWindowShouldClose (glfw.getWindow())) {
        view = glm::mat4(1.0f);
        view = glm::lookAt(glm::vec3(dx, dy, dz), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("view", view);

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray (vao.id);
        glDrawElements(GL_TRIANGLES, sizeof(index), GL_UNSIGNED_INT, 0);

        glfwPollEvents ();
        glfwSwapBuffers (glfw.getWindow());
    }
    glfwTerminate();
    return 0;
}