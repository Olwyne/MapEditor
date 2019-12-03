
#include <iostream>
#include <glimac/Cube.hpp>

using namespace glimac;

const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 800; //<----------------------------CHANGE THIS

void Cube::create_vbo_vao()
{
    glGenBuffers(1, &m_vbo);
    //bind buffer vbo to a target
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    //origin + position
    Vertex3DColor vertices[] = {
                    Vertex3DColor(glm::vec3(1.0f, -1.0f, 1.0f)+ m_position, m_color), //0
                    Vertex3DColor(glm::vec3(-1.0f, -1.0f, 1.0f)+ m_position, m_color), //1
                    Vertex3DColor(glm::vec3(-1.0f, 1.0f, 1.0f)+ m_position, m_color), //2
                    Vertex3DColor(glm::vec3(1.0f, 1.0f, 1.0f)+ m_position, m_color), //3
                    Vertex3DColor(glm::vec3(1.0f, -1.0f, -1.0f)+ m_position, m_color), //4
                    Vertex3DColor(glm::vec3(-1.0f, -1.0f, -1.0f)+ m_position, m_color), //5
                    Vertex3DColor(glm::vec3(-1.0f, 1.0f, -1.0f)+ m_position, m_color), //6
                    Vertex3DColor(glm::vec3(1.0f, 1.0f, -1.0f)+ m_position, m_color) //7
                          };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //unbind target to avoid modifying it by mistake
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //=======CREATE IBO (index buffer object)===========
    GLuint ibo;
    glGenBuffers(1, &ibo);
    //different target, reserved to IBOs
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    //8 vertices, 6 faces
    uint32_t indexes[36] = {0, 1, 3, //top face 
                            1, 3, 2,
                            4, 5, 7, //bottom face
                            5, 7, 6,
                            0, 3, 4, //left face
                            3, 4, 7,
                            1, 2, 5, //right face
                            2, 5, 6,
                            3, 2, 7, //front face
                            2, 7, 6,
                            0, 1, 4, //back 
                            1, 4, 5};

    //fill IBO with indexes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36*sizeof(uint32_t), indexes, GL_STATIC_DRAW);
    //debind before doing the rest
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //data now stocked in GPU, we can do vertex specification ie create Vertex Array Object - VAO
    //vao tells us for each attribute of a vertex the way it is organised
    glGenVertexArrays(1, &m_vao);
    //bind vao (no target)
    glBindVertexArray(m_vao);
    //bind ibo on target to save ibo in vao
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    //tell OpenGL what attribute we're wanting to use (position-0)
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR = 1;

    //vbo contains data, vao describes it
    //bind vbo again
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //tell OpenGL where to find vertices and how to read data associated to each vertex
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (void*)offsetof(Vertex3DColor, m_position));
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (void*)offsetof(Vertex3DColor, m_color));
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    
    //unbind vbo and vao
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



void Cube::create_uniform_variable_location(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, Program &program)
{
    uMVP_location = glGetUniformLocation(program.getGLId(), "uMVPMatrix" );
    uMV_location = glGetUniformLocation(program.getGLId(), "uMVMatrix" );
    uNormal_location = glGetUniformLocation(program.getGLId(), "uNormalMatrix" );
}



void Cube::render(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, TrackballCamera &camera)
{
    glm::mat4 camera_VM = camera.getViewMatrix();

    //vertical angle of view, ratio width/height of window, near, far 
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_HEIGHT/WINDOW_WIDTH, 0.1f, 100.f); //<---- height/width change
    glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -5.f));
    //formula: (MV⁻1)^T
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    
    glBindVertexArray(m_vao);
        glUniformMatrix4fv(uMVP_location, 1, GL_FALSE, glm::value_ptr(ProjMatrix*camera_VM));
        glUniformMatrix4fv(uMV_location, 1, GL_FALSE, glm::value_ptr(camera_VM*MVMatrix));
        glUniformMatrix4fv(uNormal_location, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //unbind vao
    glBindVertexArray(0);
}

void Cube::liberate_resources()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}


