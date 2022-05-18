#include "State.h"

Shader* State::defaultShader;
glm::mat4 State::projectionMatrix;
glm::mat4 State::viewMatrix;
glm::mat4 State::modelMatrix;

std::vector<Light*> State::tLights;
glm::vec3 State::ambient;