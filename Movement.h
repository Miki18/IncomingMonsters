#pragma once

bool mouseclicked = false;   //tell when we click on mouse or E (69) or Q (81) or W (87)
bool Eclicked = false;
bool Qclicked = false;
bool Wclicked = false;

//movement
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            if (mouseclicked != true)
            {
                //std::cout << "kill" << std::endl;
                mouseclicked = true;

            }
        }
    }
    if (action == GLFW_RELEASE)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            //std::cout << "stop kill" << std::endl;
        }
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == 69)
    {
        Eclicked = true;
    }

    if (key == 81)
    {
        Qclicked = true;
    }

    if (key == 87)
    {
        Wclicked = true;
    }
}

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
    //780x i 300y - cannon position
}

float CountAngle(double xPos, double yPos)
{
    //check if not 0 -> pitagoras for opposite side of right angle -> a/c to count angle value and multiply (-1) to switch axes
    float cannon_X = 780;   //cannon X
    float cannon_Y = 300;   //cannon Y
    float b = cannon_X - xPos;
    if (b == 0)
    {
        b = 1;
    }
    float a = cannon_Y - yPos;
    if (a == 0)
    {
        a = 1;
    }
    float c = sqrt((a * a) + (b * b));
    float angle = (a / c) * (-1);
    return angle;
}