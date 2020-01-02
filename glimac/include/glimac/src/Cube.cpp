
#include <iostream>
#include <glimac/Cube.hpp>
#include <chrono>
#include <random>


using namespace glimac;


void Cube::create_vbo_vao(bool scene_modified)
{ 
    //only do this again when there's been a change: ex. new cube, change of color, etc.
    if (scene_modified)
    {

        glGenBuffers(1, &m_vbo); 
        //bind buffer vbo to a target
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        Param_Pos_Color vertices[] = {
                        //front
                        Param_Pos_Color(glm::vec3(1.0f, -1.0f, 1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, 0.0f, 1.0f)), //0
                        Param_Pos_Color(glm::vec3(-1.0f, -1.0f, 1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, 0.0f, 1.0f)), //1
                        Param_Pos_Color(glm::vec3(-1.0f, 1.0f, 1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, 0.0f, 1.0f)), //2
                        Param_Pos_Color(glm::vec3(1.0f, 1.0f, 1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, 0.0f, 1.0f)), //3
                        //back
                        Param_Pos_Color(glm::vec3(1.0f, -1.0f, -1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, 0.0f, -1.0f)), //4
                        Param_Pos_Color(glm::vec3(-1.0f, -1.0f, -1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, 0.0f, -1.0f)), //5
                        Param_Pos_Color(glm::vec3(-1.0f, 1.0f, -1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, 0.0f, -1.0f)), //6
                        Param_Pos_Color(glm::vec3(1.0f, 1.0f, -1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, 0.0f, -1.0f)), //7
                        //top
                        Param_Pos_Color(glm::vec3(1.0f, 1.0f, 1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, 1.0f, 0.0f)), //3
                        Param_Pos_Color(glm::vec3(-1.0f, 1.0f, 1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, 1.0f, 0.0f)), //2
                        Param_Pos_Color(glm::vec3(-1.0f, 1.0f, -1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, 1.0f, 0.0f)), //6
                        Param_Pos_Color(glm::vec3(1.0f, 1.0f, -1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, 1.0f, 0.0f)), //7
                        //bot
                        Param_Pos_Color(glm::vec3(1.0f, -1.0f, 1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, -1.0f, 0.0f)), //0
                        Param_Pos_Color(glm::vec3(-1.0f, -1.0f, 1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, -1.0f, 0.0f)), //1
                        Param_Pos_Color(glm::vec3(-1.0f, -1.0f, -1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, -1.0f, 0.0f)), //5
                        Param_Pos_Color(glm::vec3(1.0f, -1.0f, -1.0f)+m_position*2.f, m_color,glm::vec3(0.0f, -1.0f, 0.0f)), //4
                        //left
                        Param_Pos_Color(glm::vec3(-1.0f, -1.0f, 1.0f)+m_position*2.f, m_color,glm::vec3(-1.0f, 0.0f, 0.0f)), //1
                        Param_Pos_Color(glm::vec3(-1.0f, -1.0f, -1.0f)+m_position*2.f, m_color,glm::vec3(-1.0f, 0.0f, 0.0f)), //5
                        Param_Pos_Color(glm::vec3(-1.0f, 1.0f, -1.0f)+m_position*2.f, m_color,glm::vec3(-1.0f, 0.0f, 0.0f)), //6
                        Param_Pos_Color(glm::vec3(-1.0f, 1.0f, 1.0f)+m_position*2.f, m_color,glm::vec3(-1.0f, 0.0f, 0.0f)), //2

                        //right
                        Param_Pos_Color(glm::vec3(1.0f, -1.0f, -1.0f)+m_position*2.f, m_color,glm::vec3(1.0f, 0.0f, 0.0f)), //4
                        Param_Pos_Color(glm::vec3(1.0f, -1.0f, 1.0f)+m_position*2.f, m_color,glm::vec3(1.0f, 0.0f, 0.0f)), //0
                        Param_Pos_Color(glm::vec3(1.0f, 1.0f, 1.0f)+m_position*2.f, m_color,glm::vec3(1.0f, 0.0f, 0.0f)), //3
                        Param_Pos_Color(glm::vec3(1.0f, 1.0f, -1.0f)+m_position*2.f, m_color,glm::vec3(1.0f, 0.0f, 0.0f)) //7
        

                        
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
        const GLuint VERTEX_ATTR_NORMAL = 2;


        //vbo contains data, vao describes it
        //bind vbo again
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        //tell OpenGL where to find vertices and how to read data associated to each vertex
        glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);


        glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Param_Pos_Color), (void*)offsetof(Param_Pos_Color, m_position));
        glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Param_Pos_Color), (void*)offsetof(Param_Pos_Color, m_color));
        glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Param_Pos_Color), (void*)offsetof(Param_Pos_Color, m_normal));


        //unbind vbo and vao
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }
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
            && m_invisible == c.m_invisible );
} 


void Cube::set_invisible(const bool invisible)
{
    m_invisible = invisible;
}



glm::vec3 random_color()
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    //between 0 and 1 because we're dealing with colors
    std::uniform_real_distribution<float> uniformRealDistribution(0,1);

    float color_x = uniformRealDistribution(generator);
    float color_y = uniformRealDistribution(generator);
    float color_z = uniformRealDistribution(generator);

    return glm::vec3(color_x, color_y, color_z);
}


glm::vec3 Cube::set_type(unsigned int type)
{
    switch(type)
    {
        //initial type: 3 first layers of cubes
        case 0:
            m_color = glm::vec3(0.5,1,0);
            break;
        //red
        case 1:
            m_color = glm::vec3(0.8, 0, 0);
            break;
        //green
        case 2:
            m_color = glm::vec3(0, 0.8, 0);
            break;
        //blue
        case 3:
            m_color = glm::vec3(0, 0, 0.8);
            break;
        //random color
        case 4:
            m_color = random_color();
            break;
    }

    m_type = type;
    return m_color;

}

