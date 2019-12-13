
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
    Param_Pos_Color vertices[] = {
                    Param_Pos_Color(glm::vec3(1.0f, -1.0f, 1.0f)*m_size  + 2.f*m_size*m_position, m_color), //0
                    Param_Pos_Color(glm::vec3(-1.0f, -1.0f, 1.0f)*m_size  + 2.f*m_size*m_position, m_color), //1
                    Param_Pos_Color(glm::vec3(-1.0f, 1.0f, 1.0f)*m_size  + 2.f*m_size*m_position, m_color), //2
                    Param_Pos_Color(glm::vec3(1.0f, 1.0f, 1.0f)*m_size  + 2.f*m_size*m_position, m_color), //3
                    Param_Pos_Color(glm::vec3(1.0f, -1.0f, -1.0f)*m_size  + 2.f*m_size*m_position, m_color), //4
                    Param_Pos_Color(glm::vec3(-1.0f, -1.0f, -1.0f)*m_size  + 2.f*m_size*m_position, m_color), //5
                    Param_Pos_Color(glm::vec3(-1.0f, 1.0f, -1.0f)*m_size  + 2.f*m_size*m_position, m_color), //6
                    Param_Pos_Color(glm::vec3(1.0f, 1.0f, -1.0f)*m_size  + 2.f*m_size*m_position, m_color) //7
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
    uint32_t indexes[get_index()] = {0, 1, 3, //top face 
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, get_index()*sizeof(uint32_t), indexes, GL_STATIC_DRAW);
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
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Param_Pos_Color), (void*)offsetof(Param_Pos_Color, m_position));
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Param_Pos_Color), (void*)offsetof(Param_Pos_Color, m_color));
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    
    //unbind vbo and vao
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Cube::set_color(const glm::vec3 color) 
{
    m_color = color;
}

Cube& Cube::operator=(const Cube& c)
{
    if(this != &c)
    {
        m_color = c.m_color;
        m_nb_index = c.m_nb_index;
        m_vao = c.m_vao;
        m_vbo = c.m_vbo;
        m_size = c.m_size;
        m_invisible = c.m_invisible;
    }
    return *this;
} 


bool Cube::operator==(const Cube& c)
{
    return ( m_color == c.m_color
            && m_nb_index == c.m_nb_index
            && m_vao == c.m_vao
            && m_vbo == c.m_vbo
            && m_size == c.m_size
            && m_invisible == c.m_invisible );
} 


void Cube::set_invisible(const bool invisible)
{
    m_invisible = invisible;
}

void Cube::set_type(unsigned int type)
{
    m_type = type;

    switch(type)
    {
        case 0:
            m_size = 1;
            m_texture = 0;
            m_color = glm::vec3(0.2,1,0);
            break;
        case 1:
            m_size = 1;
            m_texture = 0;
            glm::vec3(0,0.7,0.2);
            break;
        case 2:
            m_size = 1;
            m_texture = 0;
            glm::vec3(0.8,0,0.2);
            break;
    }
}