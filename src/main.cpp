#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "check_gl.hpp" // includes glad/glad.h
#include <GLFW/glfw3.h> // must be placed behind glad/glad.h
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <cstdlib>


void drawRingCircle(float centerx, float centery, float z)
{
    constexpr int n = 100;
    constexpr float pi = 3.1415926535897f;
    float radius = 0.2f;
    float inner_radius = 0.1f;
    //static int x = 0;
    //x++;
    //if (x > n)
    //    x -= n;
    for (int i = 0; i < n; i++) {

        float angle = i / (float)n * pi * 2;
        float angle_next = (i + 1) / (float)n * pi * 2;
        //glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(centerx + radius * sinf(angle), centery + radius * cosf(angle), z);
        glVertex3f(centerx + radius * sinf(angle_next), centery + radius * cosf(angle_next), z);
        glVertex3f(centerx + inner_radius * sinf(angle), centery + inner_radius * cosf(angle), z);

        glVertex3f(centerx +inner_radius * sinf(angle_next), centery + inner_radius * cosf(angle_next), z);
        glVertex3f(centerx +inner_radius * sinf(angle), centery + inner_radius * cosf(angle), z);
        glVertex3f(centerx +radius * sinf(angle_next), centery + radius * cosf(angle_next), z);
    }
}

static void render() {
    //glBegin(GL_TRIANGLES);
    //glColor3f(1.0f, 0.0f, 0.0f);
    //glVertex3f(0.0f, 0.5f, 0.0f);
    //glColor3f(0.0f, 1.0f, 0.0f);
    //glVertex3f(-0.5f, -0.5f, 0.0f);
    //glColor3f(0.0f, 0.0f, 1.0f);
    //glVertex3f(0.5f, -0.5f, 0.0f);
    //CHECK_GL(glEnd());
    /* glBegin(GL_TRIANGLES); */
    /* constexpr int n = 100; */
    /* constexpr float pi = 3.1415926535897f; */
    /* float radius = 0.5f; */
    /* float inner_radius = 0.25f; */
    /* static int x = 0; */
    /* x++; */
    /* if (x > n) */
    /*     x -= n; */
    /* for (int i = 0; i < x; i++) { */
    /*     float angle = i / (float)n * pi * 2; */
    /*     float angle_next = (i + 1) / (float)n * pi * 2; */
    /*     glVertex3f(0.0f, 0.0f, 0.0f); */
    /*     glVertex3f(radius * sinf(angle), radius * cosf(angle), 0.0f); */
    /*     glVertex3f(radius * sinf(angle_next), radius * cosf(angle_next), 0.0f); */
        /* glVertex3f(inner_radius * sinf(angle), inner_radius * cosf(angle), 0.0f); */
        /* glVertex3f(inner_radius * sinf(angle_next), inner_radius * cosf(angle_next), 0.0f); */
        /* glVertex3f(inner_radius * sinf(angle), inner_radius * cosf(angle), 0.0f); */
        /* glVertex3f(radius * sinf(angle_next), radius * cosf(angle_next), 0.0f); */
    /* } */
    /* CHECK_GL(glEnd()); */

    float lengthSide = 0.46f;
    float z = 0.0f;

    //1 等边三角形
    float x11 = 0.0f;
    float y11 = lengthSide / 2 * 1.73f;
    float x12 = -lengthSide / 2;
    float y12 = 0.0f;
    float x13 = lengthSide / 2;
    float y13 = 0.0f;
    float z1 = 0.0f; 

    //2 等边三角形 缩小一半
    float x21 = lengthSide / 4;
    float y21 = y11 / 2;
    float x22 = lengthSide - lengthSide / 4;
    float y22 = lengthSide / 2 * 1.73f / 2;
    float x23 = x13;
    float y23 = y13;
    float z2 =  0.0f;

    glBegin(GL_TRIANGLES);


    glColor3f(1.0f, 0.0f, 0.0f);
    drawRingCircle(x11, y11, z);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawRingCircle(x12, y12, z);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(x11, y11, z1);
    glVertex3f(x12, y12, z1);
    glVertex3f(x13, y13, z1);
    glColor3f(0.0f, 0.0f, 1.0f);
    drawRingCircle(x13, y13, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(x21, y21, z2);
    glVertex3f(x22, y22, z2);
    glVertex3f(x23, y23, z2);

    CHECK_GL(glEnd());
}

int main() {
    if (!glfwInit()) {
        const char *errmsg;
        glfwGetError(&errmsg);
        if (!errmsg) errmsg = "(no error)";
        std::cerr << "failed to initialize GLFW: " << errmsg << '\n';
        return -1;
    }

    // hint the version required: OpenGL 2.0
    constexpr int version = 20;
    glfwWindowHint(GLFW_OPENGL_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version / 10);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version % 10);
    if (version >= 33) {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    // Create window
    GLFWwindow *window = glfwCreateWindow(640, 640, "Example", NULL, NULL);
    if (!window) {
        const char *errmsg;
        glfwGetError(&errmsg);
        if (!errmsg) errmsg = "(no error)";
        std::cerr << "GLFW failed to create window: " << errmsg << '\n';
        std::cerr << "==============================================\n";
        if (!strcmp(errmsg, "X11: The DISPLAY environment variable is missing")) {
            std::cerr << "You seems not running with graphic display\n";
        } else if (!strcmp(errmsg, "WGL: The driver does not appear to support OpenGL")) {
            std::cerr << "Please consider install an OpenGL driver, or use the mesa driver\n";
        } else if (!strcmp(errmsg, "WGL: Failed to create OpenGL context")) {
            std::cerr << "Your driver seems not supporting the required OpenGL version\n";
        }
        std::cerr << "- If you have a physical graphic card (e.g. NVIDIA), install it from your graphic card vendor official website: http://www.nvidia.com/Download/index.aspx\n";
        std::cerr << "- If you are using Windows, download opengl32.dll from https://pan.baidu.com/s/1TZ6nVJC7DZIuUarZrGJYow?pwd=opgl and place it into the same directory as this executable file (alternatively you may download opengl32sw.dll from Internet and rename it to opengl32.dll to place into the same directory as this executable file)\n";
        std::cerr << "- If you are using Linux or WSL1, install the mesa driver: https://ubuntuhandbook.org/index.php/2021/07/install-latest-mesa-ubuntu-20-04-21-04/";
        std::cerr << "- If you use WSL2, install WSLg: https://learn.microsoft.com/zh-cn/windows/wsl/tutorials/gui-apps\n";
        std::cerr << "- If you are using SSH remote server, try connect it using ssh -X <ip address>\n";
        std::cerr << "- If you are using MacOS, you probably want to use Windows or Linux instead for better OpenGL support\n";
        std::cerr << "- If you are using a Laptop with dual-cards, make sure you have switch to dedicated card (NVIDIA) instead of the integrated card (Intel)\n";
        std::cerr << "==============================================\n";
#ifdef _WIN32
        std::system("pause");
#endif
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load glXXX function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        std::cerr << "GLAD failed to load GL functions\n";
        return -1;
    }
    std::cerr << "OpenGL version: " << glGetString(GL_VERSION) << '\n';

    CHECK_GL(glEnable(GL_LINE_SMOOTH));
    CHECK_GL(glEnable(GL_BLEND)); 
    CHECK_GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    //CHECK_GL(glPointSize(64.0f));

    // start main game loop
    while (!glfwWindowShouldClose(window)) {
        // render graphics
        CHECK_GL(glClear(GL_COLOR_BUFFER_BIT));
        render();
        // refresh screen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
