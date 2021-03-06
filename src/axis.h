#pragma once

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "api/shader.h"

class Axis
{
public:

    Axis();
    ~Axis();

    void Draw(Shader& shader);

private:
    GLuint quadVAO_;
    Shader shader_;
};
