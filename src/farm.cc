#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "farm.h"
#include "controller.h"

const GLfloat vertices[] =
{
    // position         // normal         // color                // texture
     25.0f, 0.0f,  25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
     25.0f, 0.0f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -25.0f, 0.0f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -25.0f, 0.0f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -25.0f, 0.0f,  25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
     25.0f, 0.0f,  25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
};

Farm::Farm()
{
    GLuint VBO;

    glGenVertexArrays(1, &this->quadVAO_);
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->quadVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(10 * sizeof(float)));

    glBindVertexArray(0);
}

Farm::~Farm()
{
}

void Farm::Draw(Shader& shader)
{
    this->shader_ = shader;
    this->shader_.Use();
    //this->shader_.SetMatrix4("projection", Controller::projection);
    //this->shader_.SetMatrix4("view", Controller::view);
    // for no texture only
    this->shader_.SetVector4f("shader_color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    // for texture only
    this->shader_.SetInteger("material.diffuse", 0.3);
    this->shader_.SetVector3f("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    this->shader_.SetFloat("material.shininess", 64.0f);

    this->shader_.SetMatrix4("model", glm::mat4(1.0f));

    glBindVertexArray(this->quadVAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}
