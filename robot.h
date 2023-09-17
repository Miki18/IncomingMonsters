#pragma once

//that code is very similar to ghost code; just difference values for some variable and difference model

#ifndef ROBOT
#define ROBOT

extern int money;
int robot_number = 0;
extern int lives;
float test;

class Robot
{
	private:
        float wheelrotate = 0;
		float seconds;
        float speed = 0.05;
        float speedwheel = 0.001;
        void SpawnWheels()
        {
            wheelrotate = wheelrotate + speedwheel;
            glm::mat4 W = glm::mat4(1.0f); //(matrix for meshes)
            W = glm::translate(W, glm::vec3(Xposition + 0.12, 0.2f, Zposition + 0.09));

            W = glm::rotate(W, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            W = glm::rotate(W, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

            W = glm::scale(W, glm::vec3(0.05f, 0.05f, 0.05f));

            W = glm::rotate(W, wheelrotate, glm::vec3(0.0f, 0.0f, -1.0f));

            spConstant->use();//Shading program activation    //color, transform, shape, bufor
            glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

            glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(W));

            glEnableVertexAttribArray(spConstant->a("vertex"));
            glVertexAttribPointer(spConstant->a("vertex"), 4, GL_FLOAT, false, 0, vertswheel.data()); //vertex coordinates

            glEnableVertexAttribArray(spConstant->a("texCoord"));
            glVertexAttribPointer(spConstant->a("texCoord"), 2, GL_FLOAT, false, 0, texcoordswheel.data()); //texture coordinates

            glEnableVertexAttribArray(spConstant->a("normal"));
            glVertexAttribPointer(spConstant->a("normal"), 4, GL_FLOAT, false, 0, normswheel.data()); //normal coordinates

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texwheel);
            glUniform1i(spConstant->u("texwheel"), 0);   //for textures

            glDrawElements(GL_TRIANGLES, indiceswheel.size(), GL_UNSIGNED_INT, indiceswheel.data());

            glDisableVertexAttribArray(spConstant->a("vertex"));
            glDisableVertexAttribArray(spConstant->a("normal"));
            glDisableVertexAttribArray(spConstant->a("color"));

            W = glm::mat4(1.0f); //(matrix for meshes)
            W = glm::translate(W, glm::vec3(Xposition + 0.12, 0.2f, Zposition - 0.09));

            W = glm::rotate(W, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            W = glm::rotate(W, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

            W = glm::scale(W, glm::vec3(0.05f, 0.05f, 0.05f));

            W = glm::rotate(W, wheelrotate, glm::vec3(0.0f, 0.0f, -1.0f));

            spConstant->use();//Shading program activation    //color, transform, shape, bufor
            glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

            glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(W));

            glEnableVertexAttribArray(spConstant->a("vertex"));
            glVertexAttribPointer(spConstant->a("vertex"), 4, GL_FLOAT, false, 0, vertswheel.data()); //vertex coordinates

            glEnableVertexAttribArray(spConstant->a("texCoord"));
            glVertexAttribPointer(spConstant->a("texCoord"), 2, GL_FLOAT, false, 0, texcoordswheel.data()); //texture coordinates

            glEnableVertexAttribArray(spConstant->a("normal"));
            glVertexAttribPointer(spConstant->a("normal"), 4, GL_FLOAT, false, 0, normswheel.data()); //normal coordinates

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texwheel);
            glUniform1i(spConstant->u("texwheel"), 0);   //for textures

            glDrawElements(GL_TRIANGLES, indiceswheel.size(), GL_UNSIGNED_INT, indiceswheel.data());

            glDisableVertexAttribArray(spConstant->a("vertex"));
            glDisableVertexAttribArray(spConstant->a("normal"));
            glDisableVertexAttribArray(spConstant->a("color"));

            W = glm::mat4(1.0f); //(matrix for meshes)
            W = glm::translate(W, glm::vec3(Xposition - 0.12, 0.2f, Zposition + 0.09));

            W = glm::rotate(W, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            W = glm::rotate(W, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

            W = glm::scale(W, glm::vec3(0.05f, 0.05f, 0.05f));

            W = glm::rotate(W, wheelrotate, glm::vec3(0.0f, 0.0f, -1.0f));

            spConstant->use();//Shading program activation    //color, transform, shape, bufor
            glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

            glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(W));

            glEnableVertexAttribArray(spConstant->a("vertex"));
            glVertexAttribPointer(spConstant->a("vertex"), 4, GL_FLOAT, false, 0, vertswheel.data()); //vertex coordinates

            glEnableVertexAttribArray(spConstant->a("texCoord"));
            glVertexAttribPointer(spConstant->a("texCoord"), 2, GL_FLOAT, false, 0, texcoordswheel.data()); //texture coordinates

            glEnableVertexAttribArray(spConstant->a("normal"));
            glVertexAttribPointer(spConstant->a("normal"), 4, GL_FLOAT, false, 0, normswheel.data()); //normal coordinates

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texwheel);
            glUniform1i(spConstant->u("texwheel"), 0);   //for textures

            glDrawElements(GL_TRIANGLES, indiceswheel.size(), GL_UNSIGNED_INT, indiceswheel.data());

            glDisableVertexAttribArray(spConstant->a("vertex"));
            glDisableVertexAttribArray(spConstant->a("normal"));
            glDisableVertexAttribArray(spConstant->a("color"));

            W = glm::mat4(1.0f); //(matrix for meshes)
            W = glm::translate(W, glm::vec3(Xposition - 0.12, 0.2f, Zposition - 0.09));

            W = glm::rotate(W, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            W = glm::rotate(W, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

            W = glm::scale(W, glm::vec3(0.05f, 0.05f, 0.05f));

            W = glm::rotate(W, wheelrotate, glm::vec3(0.0f, 0.0f, -1.0f));

            spConstant->use();//Shading program activation    //color, transform, shape, bufor
            glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

            glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(W));

            glEnableVertexAttribArray(spConstant->a("vertex"));
            glVertexAttribPointer(spConstant->a("vertex"), 4, GL_FLOAT, false, 0, vertswheel.data()); //vertex coordinates

            glEnableVertexAttribArray(spConstant->a("texCoord"));
            glVertexAttribPointer(spConstant->a("texCoord"), 2, GL_FLOAT, false, 0, texcoordswheel.data()); //texture coordinates

            glEnableVertexAttribArray(spConstant->a("normal"));
            glVertexAttribPointer(spConstant->a("normal"), 4, GL_FLOAT, false, 0, normswheel.data()); //normal coordinates

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texwheel);
            glUniform1i(spConstant->u("texwheel"), 0);   //for textures

            glDrawElements(GL_TRIANGLES, indiceswheel.size(), GL_UNSIGNED_INT, indiceswheel.data());

            glDisableVertexAttribArray(spConstant->a("vertex"));
            glDisableVertexAttribArray(spConstant->a("normal"));
            glDisableVertexAttribArray(spConstant->a("color"));
        }
	public:
        float Xposition = 0.0;
        float Zposition = 3.0;
        bool is_alive = false;
        int health = 25;
        void CreateRobot()
        {
            is_alive = true;
            Zposition = 3.0;
            Xposition = rand() % 3 - 1;
        }
        void SpawnRobot()
        {
            glm::mat4 M = glm::mat4(1.0f); //(matrix for meshes)
            M = glm::translate(M, glm::vec3(Xposition, 0.22f, Zposition));

            M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

            M = glm::scale(M, glm::vec3(0.12f, 0.12f, 0.02f));

            spConstant->use();//Shading program activation    //color, transform, shape, bufor
            glUniform4f(spConstant->u("color"), 0, 1, 0, 1);

            glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));

            glEnableVertexAttribArray(spConstant->a("vertex"));
            glVertexAttribPointer(spConstant->a("vertex"), 4, GL_FLOAT, false, 0, vertsrobot.data()); //vertex coordinates

            glEnableVertexAttribArray(spConstant->a("texCoord"));
            glVertexAttribPointer(spConstant->a("texCoord"), 2, GL_FLOAT, false, 0, texcoordsrobot.data()); //texture coordinates

            glEnableVertexAttribArray(spConstant->a("normal"));
            glVertexAttribPointer(spConstant->a("normal"), 4, GL_FLOAT, false, 0, normsrobot.data()); //normal coordinates

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texrobot);
            glUniform1i(spConstant->u("texrobot"), 0);   //for textures

            glDrawElements(GL_TRIANGLES, indicesrobot.size(), GL_UNSIGNED_INT, indicesrobot.data());

            glDisableVertexAttribArray(spConstant->a("vertex"));
            glDisableVertexAttribArray(spConstant->a("normal"));
            glDisableVertexAttribArray(spConstant->a("color"));

            SpawnWheels();

            if (seconds == 0)   //this is to make robot movement constant; frame rate independence
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
                Zposition = Zposition - speed * dt;   //every level do +0.05
            }

            if (health <= 0)   //check if robot is dead (probably unnecessary)
            {
                DestroyRobot();
            }

            if (Zposition < -0.3)  //if ghost goes on red line than u are dead (ok, later I decided that u will have 3 lives)
            {
                lives = lives - 1;
                RemoveRobot();
            }

        }
        void DestroyRobot()  //destroy function; set all variables to default
        {
            is_alive = false;
            Zposition = 3.0;
            Xposition = rand() % 3 - 1;
            health = 25;
            money = money + 20;   //just add a little money :)
            seconds = 0;
        }
        void hurtRobot(int damage)  //damage function
        {
            health = health - damage;
            if (health <= 0)
            {
                DestroyRobot();
            }
        }
        void RemoveRobot()   //remove robot function that do the same but without give u money
        {
            is_alive = false;
            Zposition = 3.0;
            Xposition = rand() % 3 - 1;
            health = 25;
            seconds = 0;
        }
        void UpgradeRobot()
        {
            speed = speed + 0.05;
            speedwheel = speedwheel + 0.001;
        }
};

#endif // ROBOT