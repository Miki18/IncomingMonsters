#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <windows.h>
#include "shaderprogram.h"
#include "lodepng.h"
#include "Models.h"
#include "Movement.h"
#include "Bullets.h"
#include "ghost.h"
#include <time.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "robot.h"

//information variables
int level = 1;
int money = 0;
float cooldown_time = 1.0;
int lives = 3;
int death = 0;
bool laser_beam = false;
int new_level_time = 100;

void drawAxes()
{
    //X axis
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glEnd();

    //Y axis
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glEnd();

    //Z axis
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

    //in the code there is also some colors set functions, but in viewport u will see only black lines
}

void generate_models(float angle)
{
    //GROUND
    glm::mat4 M = glm::mat4(1.0f); //(matrix for meshes)     //first translate, than rotate because if u do rotate first u will have problem with axes. Scale comes the last
    M = glm::translate(M, glm::vec3(0.0f, 0.0f, 1.0f));

    M = glm::rotate(M, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

    M = glm::scale(M, glm::vec3(2.0f, 2.0f, 3.0f));

    spConstant->use();//Shading program activation    //color, transform, shape, bufor
    glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

    glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));

    glEnableVertexAttribArray(spConstant->a("vertex"));
    glVertexAttribPointer(spConstant->a("vertex"), 4, GL_FLOAT, false, 0, vertsground.data()); //vertex coordinates

    glEnableVertexAttribArray(spConstant->a("texCoord"));
    glVertexAttribPointer(spConstant->a("texCoord"), 2, GL_FLOAT, false, 0, texcoordsground.data()); //texture coordinates

    glEnableVertexAttribArray(spConstant->a("normal"));
    glVertexAttribPointer(spConstant->a("normal"), 4, GL_FLOAT, false, 0, normsground.data()); //normal coordinates

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texground);
    glUniform1i(spConstant->u("texground"), 0);   //for textures

    glDrawElements(GL_TRIANGLES, indicesground.size(), GL_UNSIGNED_INT, indicesground.data());

    glDisableVertexAttribArray(spConstant->a("vertex"));
    glDisableVertexAttribArray(spConstant->a("normal"));
    glDisableVertexAttribArray(spConstant->a("color"));

    //drawAxes();

    //CANNON
    M = glm::mat4(1.0f); //(matrix for meshes)
    M = glm::translate(M, glm::vec3(0.0f, 0.5f, -0.5f));

    M = glm::rotate(M, glm::radians(90.0f), glm::vec3(-1.0f, 0.3f, 0.1f));

    M = glm::scale(M, glm::vec3(0.20f, 0.20f, 0.20f));

    M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));

    spConstant->use();//Shading program activation    //color, transform, shape, bufor
    glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

    glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));

    glEnableVertexAttribArray(spConstant->a("vertex"));
    glVertexAttribPointer(spConstant->a("vertex"), 4, GL_FLOAT, false, 0, vertscannon.data()); //vertex coordinates

    glEnableVertexAttribArray(spConstant->a("texCoord"));
    glVertexAttribPointer(spConstant->a("texCoord"), 2, GL_FLOAT, false, 0, texcoordscannon.data()); //texture coordinates

    glEnableVertexAttribArray(spConstant->a("normal"));
    glVertexAttribPointer(spConstant->a("normal"), 4, GL_FLOAT, false, 0, normscannon.data()); //normal coordinates

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texcannon);
    glUniform1i(spConstant->u("texground"), 0);   //for textures

    glDrawElements(GL_TRIANGLES, indicescannon.size(), GL_UNSIGNED_INT, indicescannon.data());

    glDisableVertexAttribArray(spConstant->a("vertex"));
    glDisableVertexAttribArray(spConstant->a("normal"));
    glDisableVertexAttribArray(spConstant->a("color"));


    //CANNON BASE
    M = glm::mat4(1.0f); //(matrix for meshes)
    M = glm::translate(M, glm::vec3(0.0f, 0.25f, -0.5f));

    M = glm::rotate(M, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

    M = glm::scale(M, glm::vec3(0.15f, 0.15f, 0.3f));

    spConstant->use();//Shading program activation    //color, transform, shape, bufor
    glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

    glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));

    glEnableVertexAttribArray(spConstant->a("vertex"));
    glVertexAttribPointer(spConstant->a("vertex"), 4, GL_FLOAT, false, 0, vertsbase.data()); //vertex coordinates

    glEnableVertexAttribArray(spConstant->a("texCoord"));
    glVertexAttribPointer(spConstant->a("texCoord"), 2, GL_FLOAT, false, 0, texcoordsbase.data()); //texture coordinates

    glEnableVertexAttribArray(spConstant->a("normal"));
    glVertexAttribPointer(spConstant->a("normal"), 4, GL_FLOAT, false, 0, normsbase.data()); //normal coordinates

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texbase);
    glUniform1i(spConstant->u("texground"), 0);   //for textures

    glDrawElements(GL_TRIANGLES, indicesbase.size(), GL_UNSIGNED_INT, indicesbase.data());

    glDisableVertexAttribArray(spConstant->a("vertex"));
    glDisableVertexAttribArray(spConstant->a("normal"));
    glDisableVertexAttribArray(spConstant->a("color"));


    //SHOP
    M = glm::mat4(1.0f); //(matrix for meshes)
    M = glm::translate(M, glm::vec3(-1.8f, 0.2f, -0.8f));

    M = glm::rotate(M, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

    M = glm::scale(M, glm::vec3(0.2f, 0.2f, 0.02f));

    spConstant->use();//Shading program activation    //color, transform, shape, bufor
    glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

    glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));

    glEnableVertexAttribArray(spConstant->a("vertex"));
    glVertexAttribPointer(spConstant->a("vertex"), 4, GL_FLOAT, false, 0, vertsshop.data()); //vertex coordinates

    glEnableVertexAttribArray(spConstant->a("texCoord"));
    glVertexAttribPointer(spConstant->a("texCoord"), 2, GL_FLOAT, false, 0, texcoordsshop.data()); //texture coordinates

    glEnableVertexAttribArray(spConstant->a("normal"));
    glVertexAttribPointer(spConstant->a("normal"), 4, GL_FLOAT, false, 0, normsshop.data()); //normal coordinates

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texshop);
    glUniform1i(spConstant->u("texshop"), 0);   //for textures

    glDrawElements(GL_TRIANGLES, indicesshop.size(), GL_UNSIGNED_INT, indicesshop.data());

    glDisableVertexAttribArray(spConstant->a("vertex"));
    glDisableVertexAttribArray(spConstant->a("normal"));
    glDisableVertexAttribArray(spConstant->a("color"));

    //SHOP_TOP
    M = glm::mat4(1.0f); //(matrix for meshes)
    M = glm::translate(M, glm::vec3(-1.8f, 0.2f, -0.8f));

    M = glm::rotate(M, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

    M = glm::scale(M, glm::vec3(0.2f, 0.2f, 0.02f));

    spConstant->use();//Shading program activation    //color, transform, shape, bufor
    glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

    glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));

    glEnableVertexAttribArray(spConstant->a("vertex"));
    glVertexAttribPointer(spConstant->a("vertex"), 4, GL_FLOAT, false, 0, vertsshoptop.data()); //vertex coordinates

    glEnableVertexAttribArray(spConstant->a("texCoord"));
    glVertexAttribPointer(spConstant->a("texCoord"), 2, GL_FLOAT, false, 0, texcoordsshoptop.data()); //texture coordinates

    glEnableVertexAttribArray(spConstant->a("normal"));
    glVertexAttribPointer(spConstant->a("normal"), 4, GL_FLOAT, false, 0, normsshoptop.data()); //normal coordinates

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texshop);
    glUniform1i(spConstant->u("texshop"), 0);   //for textures

    glDrawElements(GL_TRIANGLES, indicesshoptop.size(), GL_UNSIGNED_INT, indicesshoptop.data());

    glDisableVertexAttribArray(spConstant->a("vertex"));
    glDisableVertexAttribArray(spConstant->a("normal"));
    glDisableVertexAttribArray(spConstant->a("color"));
}

//Drawing scene
void drawScene(GLFWwindow* window, float angle, float time, float* bullet_cooldown, float* monster_cooldown, int* Eprice, int* Qprice, Bullet* bullets, Ghost* ghosts, Robot* robots) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 V = glm::lookAt(                //camera (Volume)
        glm::vec3(2.0f, 4.5f, 0.0f),   //observer  (where is camera) // glm::vec3(0.1f, 7.0f, 0.0f) - for whole map  glm::vec3(2.0f, 4.5f, 0.0f) - game view   glm::vec3(2.0f, 2.0f, 0.0f) - side view
        glm::vec3(0.0f, 0.0f, 0.0f),    //center    (the point we are looking at)
        glm::vec3(0.0f, 1.0f, 0.0f));   //Up vector - change that means we can look in different angle
    glm::mat4 P = glm::perspective(          //perspective (for camera)
        //matrix, volume, perspective -> MVP
        glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

    glUniformMatrix4fv(spConstant->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(spConstant->u("V"), 1, false, glm::value_ptr(V));

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (mouseclicked == true and time > *bullet_cooldown)  //if mouse is clicked - spawn new bullet
    {
        for (int i = 0; i < 100; i++)
        {
            if (bullets[i].is_used == false)
            {
                *bullet_cooldown = time + cooldown_time;
                bullets[i].create_bullet(angle); //give angle connected with cannon angle
                break;
            }
        }
        mouseclicked = false;  //un-click
    }
    mouseclicked = false;  //one more un-click (because without it game add one more unwanted bullet)

    for (int i = 0; i < 100; i++)   //render bullet
    {
        if (bullets[i].is_used == true)
        {
            bullets[i].spawnbullet(); //bullet spawn
        }
    }

    generate_models(angle);  //generate models (creating new ghost)

    if (time > *monster_cooldown)   //function that spawn monsters
    {
        int m = rand() % 3;
        if (m == 0 or m == 1)
        {
            if (ghost_number < 20)
            {
                for (int i = 0; i < 20; i++)
                {
                    if (ghosts[i].is_alive == false)
                    {
                        ghosts[i].CreateGhost();
                        *monster_cooldown = time + 2.0;
                        break;
                    }
                }
            }
        }
        else
        {
            if (robot_number < 5)
            {
                for (int i = 0; i < 5; i++)
                {
                    if (robots[i].is_alive == false)
                    {
                        robots[i].CreateRobot();
                        *monster_cooldown = time + 2.0;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 20; i++)  //show ghosts
    {
        if (ghosts[i].is_alive == true)
        {
            ghosts[i].SpawnGhost();
        }
    }

    for (int i = 0; i < 5; i++)  //show robots
    {
        if (robots[i].is_alive == true)
        {
            robots[i].SpawnRobot();
        }
    }

    for (int i = 0; i < 100; i++) //collision ghosts x bullet
    {
        if (bullets[i].is_used == true)
        {
            for (int a = 0; a < 20; a++)
            {
                if (ghosts[a].is_alive == true)
                {
                    if ((abs(bullets[i].translateX - ghosts[a].Xposition) < 0.1) && (abs(bullets[i].translateZ - ghosts[a].Zposition) < 0.1))
                    {
                        bullets[i].destroy_bullet();
                        ghosts[a].hurtGhost(bullets[i].power);
                    }
                }
            }
            for (int a = 0; a < 5; a++)
            {
                if ((abs(bullets[i].translateX - robots[a].Xposition) < 0.1) && (abs(bullets[i].translateZ - robots[a].Zposition) < 0.1))
                {
                    bullets[i].destroy_bullet();
                    robots[a].hurtRobot(bullets[i].power);
                }
            }
        }
    }

    if (Eclicked == true)    //upgrade E (cooldown)
    {
        if (money >= *Eprice)
        {
            if (cooldown_time == 1.0)
            {
                money = money - *Eprice;
                cooldown_time = 0.75;
                *Eprice = 500;
            }
            else if (cooldown_time == 0.75)
            {
                money = money - *Eprice;
                cooldown_time = 0.50;
                *Eprice = 1000;
            }
            else if (cooldown_time == 0.5)
            {
                money = money - *Eprice;
                cooldown_time = 0.25;
                *Eprice = 1500;
            }
            else if (cooldown_time == 0.25)
            {
                money = money - *Eprice;
                cooldown_time = 0.1;
            }
        }
        Eclicked = false;
    }

    if (Qclicked == true)    //upgrade Q (power)
    {
        if (money >= *Qprice)
        {
            if (bullets[0].power == 5)
            {
                money = money - *Qprice;
                *Qprice = 300;
                for (int i = 0; i < 100; i++)
                {
                    bullets[i].upgrade_bullet();
                }
            }
            else if (bullets[0].power == 10)
            {
                money = money - *Qprice;
                *Qprice = 500;
                for (int i = 0; i < 100; i++)
                {
                    bullets[i].upgrade_bullet();
                }
            }
            else if (bullets[0].power == 15)
            {
                money = money - *Qprice;
                *Qprice = 1000;
                for (int i = 0; i < 100; i++)
                {
                    bullets[i].upgrade_bullet();
                }
            }
        }
        Qclicked = false;
    }

    if (Wclicked == true)   //unlock W (laser beam)
    {
        if (money >= 1000)    //unlock laser beam and block spending money
        {
            if (laser_beam == false)
            {
                money = money - 1000;
                laser_beam = true;
            }
        }
        Wclicked = false;
    }

    if (lives >= 0)    //if u have live(s) u will see widgets with money, power level, etc. If u die, you will see dead widget
    {
        ImGui::SetNextWindowSize(ImVec2(200, 50));   //money widget
        ImGui::SetNextWindowPos(ImVec2(1080, 0));
        ImGui::Begin("Money:");
        ImGui::Text("%d", money);
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(200, 60));  //power widget
        ImGui::SetNextWindowPos(ImVec2(1080, 50));
        ImGui::Begin("Power:");
        ImGui::Text("%d", bullets[0].power);
        if (*Qprice == 1000)
        {
            ImGui::Text("MAX LEVEL");
        }
        else
        {
            ImGui::Text("Press Q to upgrade (%d)", *Qprice);
        }
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(200, 60));   //Cooldown widget
        ImGui::SetNextWindowPos(ImVec2(1080, 110));
        ImGui::Begin("Cooldown:");
        ImGui::Text("%f", cooldown_time);
        if (cooldown_time == 0.1)
        {
            ImGui::Text("MAX LEVEL");
        }
        else
        {
            ImGui::Text("Press E to upgrade (%d)", *Eprice);
        }
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(200, 45));   //laser beam widget
        ImGui::SetNextWindowPos(ImVec2(1080, 170));
        ImGui::Begin("Laser Beam:");
        if (laser_beam == false)
        {
            ImGui::Text("Press W to unlock (%d)", 1000);
        }
        else
        {
            ImGui::Text("Laser beam unlocked!");
        }
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(200, 45));   //lives widget
        ImGui::SetNextWindowPos(ImVec2(1080, 675));
        ImGui::Begin("Lives:");
        ImGui::Text("%d", lives);
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(0, 0));     //level widget
        ImGui::Begin("Current level:");
        ImGui::Text("%d                ", level);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    else
    {
        if (death == 0)
        {
            death = glfwGetTime() + 5.0;    //I want dead widget for 5 second, so when player dies I get glfwGetTime and add 5 secs.
        }
        ImGui::SetNextWindowSize(ImVec2(1280, 720));   //dead widget
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("");
        ImGui::Text("You died!");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (death <= glfwGetTime())
        {
            exit(0);
        }
    }

    glm::mat4 M = glm::mat4(1.0f);
    M = glm::mat4(1.0f); //(matrix for meshes)
    M = glm::translate(M, glm::vec3(0.0f, 0.5f, -0.5f));

    M = glm::rotate(M, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

    M = glm::scale(M, glm::vec3(0.15f, 0.15f, 0.3f));

    spConstant->use();//Shading program activation    //color, transform, shape, bufor
    glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

    glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));

    if (laser_beam == true)
    {
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        float Y = 20 * tan(angle);
        glVertex3f(Y, -20.0f, 0.0f);
        glEnd();
    }

    if (glfwGetTime() >= new_level_time)  //when we are alive longer than new_level_time than new level begins
    {
        if (lives >= 0)  //i don't want to increase level when player is dead
        {
            for (int i = 0; i < 20; i++)  //remove all ghosts and upgrade to next level
            {
                if (ghosts[i].is_alive == true)
                {
                    ghosts[i].RemoveGhost();
                }
                ghosts[i].UpgradeGhost();
            }

            for (int i = 0; i < 5; i++)  //the same for ghosts
            {
                if (robots[i].is_alive == true)
                {
                    robots[i].RemoveRobot();
                }
                robots[i].UpgradeRobot();
            }
            level = level + 1;    //next level number on widget
            new_level_time = new_level_time + 60;   //time we must survive to new level
        }
    }

    glfwSwapBuffers(window); //change buffor
}

int main(void)
{
    GLFWwindow* window; //pointer on window

    if (!glfwInit()) { //initiate GLFW
        fprintf(stderr, "Can't run GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(1280, 720, "The Lonely Soldier", NULL, NULL);  //create window (size and title)
    glfwSetWindowSizeLimits(window, 1280, 720, 1280, 720);   //moving mouse works with window size, so it can't be changed, because it would ruin a game

    if (!window) //if u can't create window, exit program
    {
        fprintf(stderr, "Nie mo¿na utworzyæ okna.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window); //show GLFW what window should it uses
    glfwSwapInterval(1); //wait

    if (glewInit() != GLEW_OK) { //initiate GLEW
        fprintf(stderr, "Nie mo¿na zainicjowaæ GLEW.\n");
        exit(EXIT_FAILURE);
    }

    initShaders();     //initiate shaders
    glEnable(GL_DEPTH_TEST);   //for 3D effect

    glfwSetKeyCallback(window, keyCallback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    texground = readTexture("groundtexture.png");  //read texture function
    texcannon = readTexture("cannon_top_texture.png");
    texbase = readTexture("black.png");
    texbullet = readTexture("yellow.png");
    texghost = readTexture("ghost.png");
    texshop = readTexture("shop.png");
    texrobot = readTexture("roo.png");
    texwheel = readTexture("thewheel.png");

    LoadModelground(std::string("ground.fbx"));   //read model funcion
    LoadModelcannon(std::string("cannon_top.fbx"));
    LoadModelbase(std::string("cannonbase.fbx"));
    LoadModelbullet(std::string("bullet.fbx"));
    LoadModelghost(std::string("ghost.fbx"));
    LoadModelshop(std::string("shop.fbx"));
    LoadModelshoptop(std::string("shop_top.fbx"));
    LoadModelrobot(std::string("robot.fbx"));
    LoadModelwheel(std::string("wheel.fbx"));
 
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);  //movement
    double xPos, yPos;
    float angle = 0;
    float seconds = 0;

    float bullet_cooldown = 0;  //cooldowns
    float monster_cooldown = 0;

    int Eprice = 250;   //cooldown    //prices
    int Qprice = 100;   //power

    Bullet bullets[100];  //arrays of objects
    Ghost ghosts[20];
    Robot robots[5];

    glfwSetTime(0); //start glfw timer
    srand(time(NULL)); //start random

    PlaySound(TEXT("brightlyfancy.wav"), NULL, SND_ASYNC | SND_LOOP);  //play song

    //Main loop
    while (!glfwWindowShouldClose(window))
    {
        seconds = glfwGetTime();
        //std::cout << seconds << std::endl;
        glfwGetCursorPos(window, &xPos, &yPos);  //get cursor
        angle = CountAngle(xPos, yPos);   //count angle
        glfwPollEvents(); //do callback procedures
        drawScene(window, angle, seconds, &bullet_cooldown, &monster_cooldown, &Eprice, &Qprice, bullets, ghosts, robots); //draw Scene procedure here - this is what we see
    }

    //exit program functions
    freeShaders();
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}