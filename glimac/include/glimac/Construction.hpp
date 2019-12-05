#pragma once

#include "Cube.hpp"
#include <vector>

class Construction
{
private:
    std::vector <Cube> m_all_cubes;

public:
    Construction();

    inline std::vector <Cube> get_cubes() { return m_all_cubes; }

    void add_cube(glm::vec3 position);
    void delete_cube(Cube cube, glm::vec3 position);
    void extrude_cube(Cube cube, glm::vec3 position);
    void dig_cube(Cube cube, glm::vec3 position);
};