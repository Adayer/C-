#include "Node.h"
#include "maths_funcs.h"

Node::Node()
	:parent(0)
{ ; }

void Node::init() { 
	position = vec3(0, 0, 0);
	rotation = versor(0,0,0,1);
	scale = vec3(1,1,1);

	localMatrix = identity_mat4();
	worldMatrix = identity_mat4();
	localInverseMatrix = identity_mat4();
	worldInverseMatrix = identity_mat4();	
	
}

void Node::addChild(Node& node) { 
	node.parent = this;
	children.push_back(&node);
}

void Node::removeChild(Node& node) { 
	auto it = std::find(children.begin(), children.end(), &node);
	if (it != children.end()) {
		node.parent = nullptr;
		children.erase(it);
	}
}

void  Node::updateLocal() 
{ 
	// todo: given position, rotation and scale, create T,R and S such that
	//Matriz de posicion
	T = translate(identity_mat4(), position);
	//Matriz de rotaci�n
	R = quat_to_mat4(rotation);
	//Matriz de escala
	S = scaler(identity_mat4(), scale);

	localMatrix = T*R*S;

	// todo: given all above, create Sinv, Rinv and Tinv such that

	//Inversa de la posici�n
	Tinv = translate(identity_mat4(), position * -1.f);

	//Inversa de la rotaci�n
	Rinv = transpose(R);

	//Inversa de la escala
	Sinv = S;
	for (unsigned int i = 0; i < 10; i += 5)
	{
		Sinv.m[i] = 1.f / S.m[i];
	}
	
	localInverseMatrix = Sinv*Rinv*Tinv;
}

void  Node::updateHierarchy()
{
	updateLocal();
	mat4 parentMatrix = identity_mat4();
	mat4 parentInverseMatrix = identity_mat4();
	if (parent!= nullptr) {
		parentMatrix = (*parent).worldMatrix;
		parentInverseMatrix = (*parent).worldInverseMatrix;
	}
	worldMatrix = parentMatrix*localMatrix;
	worldInverseMatrix = parentInverseMatrix*localInverseMatrix;

	for (size_t i = 0; i < children.size(); ++i) {
		Node* child = children[i];
		if (child != nullptr) {
			(*child).updateHierarchy();
		}
	}
}
