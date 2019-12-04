#include <iostream>
#include <glimac/Cursor.hpp>

void Cursor::create_vbo_vao()
{
    glGenBuffers(1, &m_vbo);
    //bind buffer vbo to a target
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    //origin + position
    Vertex3DColor vertices[] = {
                    Vertex3DColor(glm::vec3(1.0f, -1.0f, -1.0f)+ m_position, m_color), //0
                    Vertex3DColor(glm::vec3(1.0f, 1.0f, -1.0f)+ m_position, m_color), //1
                    Vertex3DColor(glm::vec3(-1.0f, 1.0f, -1.0f)+ m_position, m_color), //2
                    Vertex3DColor(glm::vec3(-1.0f, -1.0f, -1.0f)+ m_position, m_color), //3
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
    uint32_t indexes[get_index()] = {0, 1, 2,
                            2, 3, 0};

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
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (void*)offsetof(Vertex3DColor, m_position));
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (void*)offsetof(Vertex3DColor, m_color));
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    
    //unbind vbo and vao
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}