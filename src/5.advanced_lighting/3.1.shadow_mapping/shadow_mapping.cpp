// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL.h>
#include <btBulletDynamicsCommon.h>

#include <string>

//#include "ParticleGenerator.h"

// Properties
const GLuint SCR_WIDTH = 1024, SCR_HEIGHT = 768;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();
GLuint loadTexture(string path, GLboolean alpha = false);
void RenderScene(Shader &shader);
void RenderCube();
void RenderQuad();

void RenderFloor1(Shader&);
void RenderModels(Shader &);
void RenderGrass(Shader &);
void RenderFlame(Shader &);
void initFloor1();
void initGrass();
void initFlame();



// Delta
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLuint flameIndex = 0;
const GLfloat FLOOR1_Y = 3.5f;
const GLfloat FLOOR_OFFSET = 1.1f;
const int NUM_INSTANCES = 10;
const int NUM_FLAME_INSTANCES = 10;
const int NUM_FLAME_FRAMES = 5;

// Options
GLboolean shadows = true;

// Global variables
GLuint woodTexture;
GLuint planeVAO;
GLuint cubeTexture;
GLuint floorTexture;
GLuint transparentTexture;
GLuint flameTexture[NUM_FLAME_FRAMES];
GLuint floor1VAO, floor1VBO;
GLuint transparentVAO, transparentVBO;
GLuint instanceVBO;
GLuint flameVAO, flameVBO;
GLuint flame_instanceVBO;

Model* monster;
Model* floor1;
Model* grass;
Model* fence;
Model* moon;
Model* tree;

vector<glm::vec3> fences;

// Camera
Camera camera(glm::vec3(10.0f, FLOOR1_Y + 1, 20.0f));
//Camera camera(glm::vec3(3,0,0));

int main()
{
    glm::mat4 m(1);
    //bulletDetectCollision(m,m);
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, SCR_WIDTH*2, SCR_HEIGHT*2);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("shaders/shadow_mapping.vs", "shaders/shadow_mapping.frag");
    Shader simpleDepthShader("shaders/shadow_mapping_depth.vs", "shaders/shadow_mapping_depth.frag");
    Shader floor1_shader("shaders/depth_testing.vs", "shaders/depth_testing.frag");
    Shader model_shader("shaders/model_shader.vs", "shaders/model_shader.frag");
    Shader grass_shader("shaders/blending_discard.vs", "shaders/blending_discard.frag");
    Shader flame_shader("shaders/flame.vs", "shaders/flame.frag");
    Shader particle_shader("shaders/fire.vs", "shaders/fire.frag");

    // Set texture samples
    shader.Use();
    glUniform1i(glGetUniformLocation(shader.Program, "diffuseTexture"), 0);
    glUniform1i(glGetUniformLocation(shader.Program, "shadowMap"), 1);

    GLfloat planeVertices[] = {
        // Positions            // Normals           // Texture Coords
        25.0f, -0.5f,  25.0f,  0.0f,  1.0f,  0.0f,  25.0f, 0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f,  1.0f,  0.0f,  0.0f,  25.0f,
        -25.0f, -0.5f,  25.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,

        25.0f, -0.5f,  25.0f,  0.0f,  1.0f,  0.0f,  25.0f, 0.0f,
        25.0f, -0.5f, -25.0f,  0.0f,  1.0f,  0.0f,  25.0f, 25.0f,
        -25.0f, -0.5f, -25.0f,  0.0f,  1.0f,  0.0f,  0.0f,  25.0f
    };
    // Setup plane VAO
    GLuint planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glBindVertexArray(0);

    // Light source
    glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
    glm::vec3 scndlightPos(-7.0f, 20.0f, -7.0f);

    // Load textures
    woodTexture = loadTexture("resources/textures/wood.png");

    // Configure depth map FBO
    const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    GLuint depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    // - Create depth texture
    GLuint depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    /*-------------------Load models--------------------*/

    monster = new Model("resources/objects/nanosuit/nanosuit.obj");
    floor1 = new Model("resources/objects/floor1/house.obj");
    grass = new Model("resources/objects/grass/Grass-small.obj");
    fence = new Model("resources/objects/fence/fence.obj");
    moon = new Model("resources/objects/floor1/moon.obj");
    tree = new Model("resources/objects/grass/tree.obj");

    /*--------------------------------------------------*/

    initFloor1();
    initGrass();
    initFlame();

    fences.push_back(glm::vec3(8.0f, FLOOR1_Y - 1.0, 18.0f));
    fences.push_back(glm::vec3(6.0f, FLOOR1_Y - 1.0, 17.0f));
    fences.push_back(glm::vec3(3.0f, FLOOR1_Y - 1.0, 16.0f));
    fences.push_back(glm::vec3(3.0f, FLOOR1_Y - 1.0, 16.0f));
    fences.push_back(glm::vec3(2.0f, FLOOR1_Y - 1.0, 15.5f));
    fences.push_back(glm::vec3(5.0f, FLOOR1_Y - 1.0, 14.0f));
    fences.push_back(glm::vec3(9.0f, FLOOR1_Y - 1.0, 13.5f));
    fences.push_back(glm::vec3(8.0f, FLOOR1_Y - 1.0, 12.0f));
    fences.push_back(glm::vec3(7.0f, FLOOR1_Y - 1.0, 16.0f));
    fences.push_back(glm::vec3(4.0f, FLOOR1_Y - 1.0, 10.5f));

    //ParticleGenerator generator(particle_shader,5,&camera);


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        Do_Movement();

        // Change light position over time
        lightPos.z = cos(glfwGetTime()) * 2.0f;

        // 2. Render scene as normal
        glViewport(0, 0, SCR_WIDTH*2, SCR_HEIGHT*2);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RenderModels(model_shader);

        // 1. Render depth of scene to texture (from light's perspective)
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        GLfloat near_plane = 1.0f, far_plane = 7.5f;
        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(1.0));
        lightSpaceMatrix = lightProjection * lightView;

        // - now render scene from light's point of view
        simpleDepthShader.Use();
        glUniformMatrix4fv(glGetUniformLocation(simpleDepthShader.Program, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        RenderScene(simpleDepthShader);
        //RenderModels(simpleDepthShader);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        glViewport(0, 0, SCR_WIDTH*2, SCR_HEIGHT*2);

        shader.Use();
        glm::mat4 projection = glm::perspective(camera.Zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        // Set light uniforms
        glUniform3fv(glGetUniformLocation(shader.Program, "lightPos"), 1, &lightPos[0]);
        glUniform3fv(glGetUniformLocation(shader.Program, "viewPos"), 1, &camera.Position[0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
        // Enable/Disable shadows by pressing 'SPACE'
        glUniform1i(glGetUniformLocation(shader.Program, "shadows"), shadows);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, woodTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);

        // ******************* 1st Room cube ************ //
        glm::mat4 model;
        model = glm::scale(model, glm::vec3(10.0,6.9,10));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(shader.Program, "reverse_normals"), 1); // A small little hack to invert normals when drawing cube from the inside so lighting still works.
        RenderCube();
        glUniform1i(glGetUniformLocation(shader.Program, "reverse_normals"), 0); // And of course disable it
        // ******************* end 1st Room cube ************ //


        // ******************* 2nd Room cube ************ //
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(10.3f, 1.5, 0.f));
        model = glm::scale(model, glm::vec3(10.0,3.9,10));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(shader.Program, "reverse_normals"), 1); // A small little hack to invert normals when drawing cube from the inside so lighting still works.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,floorTexture);
        RenderCube();
        glUniform1i(glGetUniformLocation(shader.Program, "reverse_normals"), 0); // And of course disable it
        // ******************* end 2nd Room cube ************ //

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,woodTexture);
        RenderScene(shader);
        RenderFloor1(floor1_shader);

        // Set light uniforms
        lightProjection = glm::perspective(45.0f, (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, 1.0f, 2.0f);
        lightView = glm::lookAt(scndlightPos, glm::vec3(0.0f), glm::vec3(1.0));
        lightSpaceMatrix = lightProjection * lightView;
        glUniform3fv(glGetUniformLocation(grass_shader.Program, "lightPos"), 1, &scndlightPos[0]);
        glUniformMatrix4fv(glGetUniformLocation(grass_shader.Program, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));


        //Draw the moon
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(2.0f, 20.0f, 2.0f)); // Translate it down a bit so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// It's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        moon->Draw(shader);


        RenderGrass(grass_shader);
        //RenderFlame(flame_shader);

        //generator.Update(0.1f,10,glm::vec2(1,1));
        //generator.Draw();
        // Swap the buffers
        glfwSwapBuffers(window);
    }

    delete monster;
    delete floor1;
    delete grass;
    delete moon;
    delete fence;
    delete tree;

    glfwTerminate();
    return 0;
}

void initFloor1(){

    GLfloat floor1Vertices[] = {
        // Positions            // Texture Coords (note we set these higher than 1 that together with GL_REPEAT as texture wrapping mode will cause the floor texture to repeat)
        25.0f,   FLOOR1_Y,  25.0f,  20.0f, 0.0f,
        -25.0f,  FLOOR1_Y,  25.0f,  0.0f, 0.0f,
        -25.0f,  FLOOR1_Y, -25.0f,  0.0f, 20.0f,

        25.0f,   FLOOR1_Y,  25.0f,  20.0f, 0.0f,
        -25.0f,  FLOOR1_Y, -25.0f,  0.0f, 20.0f,
        25.0f,   FLOOR1_Y, -25.0f,  20.0f, 20.0f
    };

    // Setup plane VAO
    glGenVertexArrays(1, &floor1VAO);
    glGenBuffers(1, &floor1VBO);
    glBindVertexArray(floor1VAO);
    glBindBuffer(GL_ARRAY_BUFFER, floor1VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floor1Vertices), &floor1Vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glBindVertexArray(0);

    // Load textures
    cubeTexture = loadTexture("resources/textures/marble.jpg");
    floorTexture = loadTexture("resources/textures/marble.jpg");
}

void initGrass(){

    // Generate a large list of semi-random model transformation matrices
    glm::mat4* modelMatrices;
    modelMatrices = new glm::mat4[NUM_INSTANCES];
    srand(glfwGetTime()); // initialize random seed
    for(GLuint i = 0; i < NUM_INSTANCES; i++)
    {
        glm::mat4 model;
        glm::vec3 translation(rand()%30 - 10, FLOOR1_Y + 0.5, rand()%6 + 10);
        //GLfloat size = (rand()%50);
        model = glm::translate(model, translation);
        model = glm::scale(model, glm::vec3((1, 1, 1)));
        modelMatrices[i] = model;
    }

    // Set transformation matrices as an instance vertex attribute (with divisor 1)
    // NOTE: We're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
    // Normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
    for(GLuint i = 0; i < grass->meshes.size(); i++)
    {
        GLuint VAO = grass->meshes[i].VAO;
        GLuint buffer;
        glBindVertexArray(VAO);
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, NUM_INSTANCES * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
        // Set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }

}

void RenderGrass(Shader& shader){

    // Draw meteorites
    shader.Use();

    glm::mat4 model;
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(camera.Zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindTexture(GL_TEXTURE_2D, grass->textures_loaded[0].id);
    for(GLuint i = 0; i < grass->meshes.size(); i++)
    {
        glBindVertexArray(grass->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, grass->meshes[i].vertices.size(), GL_UNSIGNED_INT, 0, NUM_INSTANCES);
        glBindVertexArray(0);
    }
}

void initFlame(){

    glm::vec3 translations[NUM_FLAME_INSTANCES];
    int index = 0;

    for(GLint y = 0; y < NUM_FLAME_INSTANCES; y++)
    {
        glm::vec3 translation;
        translation.x =  rand()%30 - 15;
        translation.y = FLOOR1_Y + 0.5;
        translation.z =  rand()%6 + 3;
        translations[index++] = translation;
    }

    glGenBuffers(1, &flame_instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, flame_instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_INSTANCES, &translations[0], GL_STATIC_DRAW);

    GLfloat transparentVertices[] = {
        // Positions         // Texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
    };

    // Setup transparent plane VAO
    glGenVertexArrays(1, &flameVAO);
    glGenBuffers(1, &flameVBO);
    glBindVertexArray(flameVAO);
    glBindBuffer(GL_ARRAY_BUFFER, flameVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glBindVertexArray(0);

    for (int i = 1; i <= NUM_FLAME_FRAMES; ++i) {
        flameTexture[i-1] = loadTexture("resources/textures/flames/tmp-" + std::to_string(i) + ".png", true);
    }

}

void RenderFlame(Shader& shader){

    shader.Use();
    glm::mat4 model;
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(camera.Zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    // Vegetation
    glBindVertexArray(flameVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, flameTexture[++flameIndex%=NUM_FLAME_FRAMES]);

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, flame_instanceVBO);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glVertexAttribDivisor(3, 1);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 30, NUM_FLAME_INSTANCES);
    glBindVertexArray(0);
}


void RenderFloor1(Shader &shader){

    shader.Use();
    glm::mat4 model;
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(camera.Zoom, (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Floor
    glBindVertexArray(floor1VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    model = glm::mat4();
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void RenderModels(Shader &shader){

    // Draw objects
    shader.Use();

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(camera.Zoom, (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Draw the loaded model
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(2.0f, FLOOR1_Y+FLOOR_OFFSET, 2.0f)); // Translate it down a bit so it's at the center of the scene
    //model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// It's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    floor1->Draw(shader);

    /*--------------------------DRAWING OBJ------------------*/

    // Draw the loaded model
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(2.0f, -0.50f, 2.0f)); // Translate it down a bit so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// It's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    monster->Draw(shader);

    /*--------------------------DRAWING OBJ------------------*/

    // Draw the loaded fences
    for (int i = 0; i < fences.size(); ++i) {
        model = glm::mat4();
        model = glm::translate(model, fences[i]);
        //model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        fence->Draw(shader);
    }

    /*********************DRAW TREES************/
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(10.0f, FLOOR1_Y, 2.0f)); // Translate it down a bit so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));	// It's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    tree->Draw(shader);

    model = glm::mat4();
    model = glm::translate(model, glm::vec3(-10.0f, FLOOR1_Y, -5.0f)); // Translate it down a bit so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));	// It's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    tree->Draw(shader);
    /********************* END DRAW TREES************/

}

void RenderScene(Shader &shader)
{
    // Floor
    glm::mat4 model;
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    // Cubes
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    RenderCube();
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    RenderCube();
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
    model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(0.5));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    RenderCube();

}


// RenderQuad() Renders a 1x1 quad in NDC, best used for framebuffer color targets
// and post-processing effects.
GLuint quadVAO = 0;
GLuint quadVBO;
void RenderQuad()
{
    if (quadVAO == 0)
    {
        GLfloat quadVertices[] = {
            // Positions        // Texture Coords
            -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
            1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
            1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        };
        // Setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

// RenderCube() Renders a 1x1 3D cube in NDC.
GLuint cubeVAO = 0;
GLuint cubeVBO = 0;
void RenderCube()
{
    // Initialize (if necessary)
    if (cubeVAO == 0)
    {
        GLfloat vertices[] = {
            // Back face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  // top-right
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,// top-left
            // Front face
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // top-right
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom-left
            // Left face
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
            // Right face
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-right
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-left
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
            // Bottom face
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,// bottom-left
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            // Top face
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f // bottom-left
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // Fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // Link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // Render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

// This function loads a texture from file. Note: texture loading functions like these are usually
// managed by a 'Resource Manager' that manages all resources (like textures, models, audio).
// For learning purposes we'll just define it as a utility function.
GLuint loadTexture(string path, GLboolean alpha)
{
    //Generate texture ID and load texture data
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width,height;
    const char* p = path.c_str();
    unsigned char* image = SOIL_load_image(p, &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, alpha ? GL_RGBA : GL_RGB, width, height, 0, alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT );	// Use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes value from next repeat
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    return textureID;
}

bool keys[1024];
bool keysPressed[1024];
// Moves/alters the camera positions based on user input
void Do_Movement()
{
    // Camera controls
    if (keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (keys[GLFW_KEY_SPACE] && !keysPressed[GLFW_KEY_SPACE])
    {
        shadows = !shadows;
        keysPressed[GLFW_KEY_SPACE] = true;
    }
}

GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key <= 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
            keysPressed[key] = false;
        }
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

/*void initGrass(){

    glm::vec3 translations[NUM_INSTANCES];
    int start = sqrt(NUM_INSTANCES);
    int index = 0;

    for(GLint y = 0; y < start; y += 2)
    {
        for(GLint x = 0; x < start; x += 2)
        {
            glm::vec3 translation;
            translation.x =  rand()%30 - 15;
            translation.y = FLOOR1_Y + 0.5;
            translation.z =  rand()%6 + 3;
            translations[index++] = translation;
        }
    }

    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NUM_INSTANCES, &translations[0], GL_STATIC_DRAW);


    GLfloat transparentVertices[] = {
        // Positions         // Texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
    };

    // Setup transparent plane VAO
    glGenVertexArrays(1, &transparentVAO);
    glGenBuffers(1, &transparentVBO);
    glBindVertexArray(transparentVAO);
    glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glBindVertexArray(0);

    transparentTexture = loadTexture("resources/textures/thorn.png", true);
}

void RenderGrass(Shader& shader){

    shader.Use();
    glm::mat4 model;
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(camera.Zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    // Vegetation
    glBindVertexArray(transparentVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, transparentTexture);

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glVertexAttribDivisor(3, 1);

    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 30, NUM_INSTANCES);
    glBindVertexArray(0);

}*/
