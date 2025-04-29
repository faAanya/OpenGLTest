#include "include/PFigure.h"
#include "include/verts.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

PFigure::PFigure(string name, Camera& cam, vec3 pos, vec3 scale, float angle, Shader &shader, string t, vector<Texture> &tex):
PObject(name, cam, pos, scale, angle),
                    object(shader),
                    type(t),
                    textures(tex){

    vector<Vertex> vert(verts::cube, verts::cube + sizeof(verts::cube) / sizeof(Vertex));
    mesh = new Mesh(vert, textures);
}

void PFigure::Draw() {
    if(isDrawing){


  object.use();
  object.setVec3("viewPos", camera.Position);
  object.setFloat("material.shininess", 32.0f);
  object.setVec3("material.color", glm::vec3(0.0f, 0.0f,0.0f));


    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) 1280 / (float) 720, 0.1f,
                                            100.0f);
    object.setMat4("projection", projection);
    glm::mat4 view = camera.GetViewMatrix();

    object.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));
    object.setMat4("model", model);

    mesh->Draw(object, camera);
    }
}