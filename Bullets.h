#pragma once
#ifndef BULLETS
#define BULLETS

//variables to organize bullets
extern int bullets_number;
int const bullets_max_number = 100;
int bullets_number = 0;

class Bullet
{
private:
    float move_angle = 0.0;
    float seconds = 0;
public:
    int power = 5;
    float translateZ = -0.3;
    float translateX = 0.0;
    bool is_used = false;
    void create_bullet(float move)
    {
        if (bullets_number < bullets_max_number)
        {
            move_angle = move;
            bullets_number++;
            is_used = true;

            float move_angle_Z = move_angle; //spawn in correct position
            if (move_angle_Z > 0)
            {
                move_angle_Z = move_angle_Z * (-1);
            }
            translateZ = translateZ + (0.02 * move_angle_Z);
            translateX = translateX + (0.25 * move_angle);
            //X - pion, Z - poziom
        }
    }

    void spawnbullet()
    {
        if (is_used == true)
        {
            glm::mat4 M = glm::mat4(1.0f); //(matrix for meshes)

            M = glm::translate(M, glm::vec3(translateX, 0.5f, translateZ));

            //M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 0.1f, 0.0f));

            M = glm::scale(M, glm::vec3(0.05f, 0.05f, 0.05f));

            spConstant->use();//Shading program activation    //color, transform, shape, bufor
            glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

            glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));

            glEnableVertexAttribArray(spConstant->a("vertex"));
            glVertexAttribPointer(spConstant->a("vertex"), 4, GL_FLOAT, false, 0, vertsbullet.data()); //vertex coordinates

            glEnableVertexAttribArray(spConstant->a("texCoord"));
            glVertexAttribPointer(spConstant->a("texCoord"), 2, GL_FLOAT, false, 0, texcoordsbullet.data()); //texture coordinates

            glEnableVertexAttribArray(spConstant->a("normal"));
            glVertexAttribPointer(spConstant->a("normal"), 4, GL_FLOAT, false, 0, normsbullet.data()); //normal coordinates

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texbullet);
            glUniform1i(spConstant->u("texground"), 0);   //for textures

            glDrawElements(GL_TRIANGLES, indicesbullet.size(), GL_UNSIGNED_INT, indicesbullet.data());

            glDisableVertexAttribArray(spConstant->a("vertex"));
            glDisableVertexAttribArray(spConstant->a("normal"));
            glDisableVertexAttribArray(spConstant->a("color"));

            if (seconds == 0)   //BULLET frame rate independence (the same story as in ghast)
            {
                float LastKeyframe = seconds;
                seconds = glfwGetTime();
                float dt = seconds - LastKeyframe;
                //std::cout << dt << std::endl;
                translateZ = translateZ + (0.02 * cos(move_angle));   //move; right traingle and mathematical formula: a = c * sin(alfa) and b = c * cos(alfa)
                translateX = translateX + (0.02 * sin(move_angle));  //where alfa is angle, a and b are sides next to right angle, c is side opposite right angle
            }
            else
            {
                float LastKeyframe = seconds;
                seconds = glfwGetTime();
                float dt = seconds - LastKeyframe;
                //std::cout << dt << std::endl;
                translateZ = translateZ + (4.0 * cos(move_angle))*dt;   //move; right traingle and mathematical formula: a = c * sin(alfa) and b = c * cos(alfa)
                translateX = translateX + (4.0 * sin(move_angle))*dt;  //where alfa is angle, a and b are sides next to right angle, c is side opposite right angle
            }

            //translateZ = translateZ + (0.02 * cos(move_angle));   //move; right traingle and mathematical formula: a = c * sin(alfa) and b = c * cos(alfa)
            //translateX = translateX + (0.02 * sin(move_angle));  //where alfa is angle, a and b are sides next to right angle, c is side opposite right angle

            if (translateZ > 3.0 or translateX > 2.0 or translateX < -2.0) //check if bullets hit in wall
            {
               destroy_bullet();
            }
            //X - pion, Z - poziom
        }
    }

    void destroy_bullet()
    {
        is_used = false;
        translateZ = -0.3;
        translateX = 0.0;
        move_angle = 0.0;
        bullets_number--;
        seconds = 0;
    }

    void upgrade_bullet()
    {
        if (power == 5)
        {
            power = 10;
        }
        else if (power == 10)
        {
            power = 15;
        }
        else if (power == 15)
        {
            power = 30;
        }
    }
};

#endif // !BULLETS