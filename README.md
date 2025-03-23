# OpenModelder 🖌️

A simple 3D modeling tool powered by OpenGL and Lua scripting for creating, lighting, and exporting 3D models.

![OpenGL](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=for-the-badge&logo=opengl)
![C++](https://img.shields.io/badge/C++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Lua](https://img.shields.io/badge/Lua-2C2D72?style=for-the-badge&logo=lua&logoColor=white)  
![Assimp](https://img.shields.io/badge/Assimp-FF6F00?style=for-the-badge&logo=assimp&logoColor=white)
![GLFW](https://img.shields.io/badge/GLFW-3C873A?style=for-the-badge)
![GLM](https://img.shields.io/badge/GLM-000000?style=for-the-badge)
![ImGui](https://img.shields.io/badge/ImGui-00BFFF?style=for-the-badge)

> **College Final Project**  
> Model, texture, and export 3D scenes through scriptable workflows.

---

## 🚀 Features
- **3D Modeling**: Create basic shapes (cubes, spheres, cones)
- **Dynamic Lighting**: Add point/directional lights with customizable properties
- **Material System**: Configure textures, specular maps, and material properties
- **Scriptable Interface**: Control everything via Lua scripts
- **Cross-format Export**: Save models in OBJ, FBX, and GLTF formats
- **Model Import**: Load existing 3D models using Assimp

---

## 🛠️ Tech Stack
| Category       | Technologies                          |
|----------------|---------------------------------------|
| **Core**       | OpenGL 4.6, C++17, Lua 5.4            |
| **Libraries**  | GLFW, GLM, Assimp, Glad               |
| **UI**         | Dear ImGui                            |
| **Build**      | CMake                                 |

---

## 📜 Script Example
```lua
-- Create a red metallic sphere
sphere = create_sphere(1.0)
set_position(sphere, {0, 0, 0})
set_material(sphere, {
    color = {1, 0, 0},
    metallic = 0.8,
    roughness = 0.2
})

-- Add directional light
light = create_light("directional")
set_light_properties(light, {
    intensity = 1.5,
    direction = {-1, -1, -1},
    color = {1, 1, 0.9}
})

-- Export to GLTF
export_scene("scene.gltf")

# Info for project OpenGL

### Tutorials
1. OpengGL Tutorial with A LOT usefull info:<br>
https://www.ogldev.org/index.html
2. OpenGl Toturial: <br>
https://learnopengl.com/
### Videos
1. Video about, how to link ImGui. Contains some info of making the easiest UI ever: <br>
https://www.youtube.com/watch?v=VRwhNKoxUtk
2. Usefull video about how to organise OpenGL objects: <br>
https://www.youtube.com/watch?v=greXpRqCTKs&list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M- 
### Links
1. Picking object using mouse: <br>
https://antongerdelan.net/opengl/raycasting.html
