#include "include/FigureManager.h"
#include "include/verts.h"

PFigure::PFigure(string name, Camera& cam, vec3 pos, vec3 scale, float angle, Shader &shader, string t,
unsigned int index, vector<Texture> &tex):
PObject(name, cam, pos, scale, angle),
                    object(shader),
                    type(t),
                    textures(tex){

    mesh = new Mesh(verts::cube, textures);
}

void PFigure::Draw(Shader &s) {
    s.use();
    s.setVec3("viewPos", camera.Position);
    s.setFloat("material.shininess", 32.0f);


    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) 1280 / (float) 720, 0.1f,
                                            100.0f);
    s.setMat4("projection", projection);
    glm::mat4 view = camera.GetViewMatrix();

    s.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));
    s.setMat4("model", model);

    mesh->Draw(s, camera);
}