#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "utils/timer.h"

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    //FOR MACOS
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    int Width = 640, Height = 400;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(Width, Height, "Newton", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "F";
    }

    // Postions of the vertex
    float size = 100.0f;
    float positions[] = {
        -size, size, 0.0, 0.0,
        -size, -size, 1.0, 0.0,
        size, -size, 1.0, 1.0,
        size, size, 0.0, 1.0
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    IndexBuffer ib(indices, 6);

    VertexBufferLayout layout;
    layout.AddFloat(2);
    layout.AddFloat(2);

    va.AddBuffer(vb, layout);

    Shader shader("../assets/shaders/Basic.vertexShader.hlsl", "../assets/shaders/basic.pixelShader.hlsl");
    shader.Bind();

    Texture texture("../assets/textures/mandelbrot.png");
    texture.Bind();

    Timer timer;
    float time = timer.getTimeMs();

    //Shader
    shader.SetUniform1i("u_Texture", 0);
    shader.SetUniform1f("u_Time", time);

    float aspect = (float)Width/Height;
    shader.SetUniform1f("u_Aspect", aspect);

    Renderer renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    //MVP matrix 
    glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)Width,
                                            0.0f, (float)Height,
                                             -1.0f, 1.0f);
    
    float field_of_view = 45.0f;
    float closestDistance = 0.1f;
    float farthestDistance = 500.0f;
    
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));

    glm::vec3 translationModel(0,0,-300.0f);
    glm::vec3 translationView(0,0,0);

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        modelMatrix = glm::translate(glm::mat4(1.0f), translationModel);

        shader.Bind();
        shader.SetUniform4f("u_Color", 0.1, 0.3, 0.8, 1.0);
        time = timer.getTimeMs();

        projectionMatrix = glm::perspective(glm::radians(field_of_view), aspect, closestDistance, farthestDistance);
            
        shader.SetUniform1f("u_Time", time);
        shader.SetUniformMat4f("u_Model", modelMatrix);
        shader.SetUniformMat4f("u_View", viewMatrix);
        shader.SetUniformMat4f("u_Proj", projectionMatrix);

        renderer.Draw(va, ib, shader);

        // IMGUI
        ImGui_ImplGlfwGL3_NewFrame();

        ImGui::SliderFloat3("Translation1", &translationModel.x, -960.0f, 960.0f);
        ImGui::SliderFloat("Field of View", &field_of_view, 15.0f, 90.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
