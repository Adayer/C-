#pragma once
#include <vector>
#include "maths_funcs.h"

struct Node {

	Node* parent;
	std::vector<Node*> children;

	vec3 position;
	versor rotation;
	vec3 scale;

	mat4 localMatrix;
	mat4 localInverseMatrix;

	mat4 worldMatrix;
	mat4 worldInverseMatrix;

	//Matriz de traslacion
	mat4 T;
	//Matriz de rotación
	mat4 R;
	//Matriz de escala
	mat4 S;

	//Matriz inversa traslacion
	mat4 Tinv;
	//Matriz inversa rotacion
	mat4 Rinv;
	//Matriz inversa escala
	mat4 Sinv;
	


	Node();

	void init();
	void addChild(Node& node) ;
	void removeChild(Node& node) ;
	void updateLocal();
	void updateHierarchy();
};

