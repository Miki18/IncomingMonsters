#pragma once
#ifndef GHOST
#define GHOST

extern int money;      //some extern variables, because I need that connection to change money and lives number
int ghost_number = 0;
extern int lives;

class Ghost
{
private:
    float seconds = 0;
    float speed = 0.1;
public:
    float Xposition = 0.0;
    float Zposition = 3.0;
    bool is_alive = false;
    int health = 10;
    void CreateGhost()
    {
        is_alive = true;
        Zposition = 3.0;
        Xposition = rand()%3 -1;
    }
    void SpawnGhost()
    {
        glm::mat4 M = glm::mat4(1.0f); //(matrix for meshes)

        M = glm::translate(M, glm::vec3(Xposition, 0.8f, Zposition));

        M = glm::rotate(M, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        M = glm::scale(M, glm::vec3(0.025f, 0.05f, 0.05f));

        spConstant->use();//Shading program activation    //color, transform, shape, bufor
        glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

        glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));

        glEnableVertexAttribArray(spConstant->a("vertex"));
        glVertexAttribPointer(spConstant->a("vertex"), 4, GL_FLOAT, false, 0, vertsghost.data()); //vertex coordinates

        glEnableVertexAttribArray(spConstant->a("texCoord"));
        glVertexAttribPointer(spConstant->a("texCoord"), 2, GL_FLOAT, false, 0, texcoordsghost.data()); //texture coordinates

        glEnableVertexAttribArray(spConstant->a("normal"));
        glVertexAttribPointer(spConstant->a("normal"), 4, GL_FLOAT, false, 0, normsghost.data()); //normal coordinates

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texghost);
        glUniform1i(spConstant->u("texground"), 0);   //for textures

        glDrawElements(GL_TRIANGLES, indicesghost.size(), GL_UNSIGNED_INT, indicesghost.data());

        glDisableVertexAttribArray(spConstant->a("vertex"));
        glDisableVertexAttribArray(spConstant->a("normal"));
        glDisableVertexAttribArray(spConstant->a("color"));

        if (seconds == 0)   //this is to make ghost movement constant; frame rate independence
        {
            float LastKeyframe = seconds;
            seconds = glfwGetTime();
            float dt = seconds - LastKeyframe;
            //std::cout << dt << std::endl;
            Zposition = Zposition - 0.001;
        }
        else
        {
            float LastKeyframe = seconds;
            seconds = glfwGetTime();
            float dt = seconds - LastKeyframe;
            //std::cout << dt << std::endl;
            Zposition = Zposition - speed*dt;   //every level do +0.1
        }

        if (health <= 0)   //check if ghost is dead (probably unnecessary)
        {
            DestroyGhost();
        }

        if (Zposition < -0.3)  //if ghost goes on red line than u are dead (ok, later I decided that u will have 3 lives)
        {
            lives = lives - 1;
            RemoveGhost();
        }
    }
    void DestroyGhost()  //destroy function; set all variables to default
    {
        is_alive = false;
        Zposition = 3.0;
        Xposition = rand() % 3 - 1;
        health = 10;
        money = money + 10;   //just add a little money :)
        seconds = 0;
    }
    
    void hurtGhost(int damage)  //damage function
    {
        health = health - damage;
        if (health <= 0)
        {
            DestroyGhost();
        }
    }

    void RemoveGhost()   //remove robot function that do the same but without give u money
    {
        is_alive = false;
        Zposition = 3.0;
        Xposition = rand() % 3 - 1;
        health = 10;
        seconds = 0;
    }

    void ShowZposition()  //only for tests
    {
        std::cout << Zposition << std::endl;
    }
    void UpgradeGhost()
    {
        speed = speed + 0.1;
    }
};

#endif // GHOST