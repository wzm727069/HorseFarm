#include "input.h"
#include "../controller.h"

bool Input::Keys[1024];
bool Input::KeysProcessed[1024];

std::map<int, bool> Input::keyDown;
std::map<int, bool> Input::keyUp;
std::map<int, bool> Input::keyHeld;

void Input::ProcessInput(GLfloat dt)
{
    if (Input::Keys[GLFW_KEY_LEFT])
    {
        Controller::c_horizontal += 1.0f;
    }
    else if (Input::Keys[GLFW_KEY_RIGHT])
    {
        Controller::c_horizontal -= 1.0f;
    }
    else if (Input::Keys[GLFW_KEY_UP])
    {
        Controller::c_vertical += 1.0f;
        if(Controller::c_vertical >= 90.0)
        {
            Controller::c_vertical = 89.0f;
        }
    }
    else if (Input::Keys[GLFW_KEY_DOWN])
    {
        Controller::c_vertical -= 1.0f;
        if(Controller::c_vertical < 0)
        {
            Controller::c_vertical = 0.0f;
        }
    }
}
