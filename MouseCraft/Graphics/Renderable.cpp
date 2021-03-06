#include "Renderable.h"
#include "../Core/Entity.h"
#include "../Loading/ModelLoader.h"
#include "../Loading/ImageLoader.h"
#include <string>

Renderable::Renderable()
{
}

Model* Renderable::getModel() {
	return _model;
}

void Renderable::setModel(Model& model) {
	_model = &model;
}

Transform Renderable::getTransform() {
	Entity* e = GetEntity();
	if (e != nullptr) {
		return e->transform;
	}
}

Color Renderable::getColor() {
	return _color;
}

void Renderable::setColor(Color color) {
	_color = color;
}



#pragma region prefab support 

Component* Renderable::CreateFromJson(json json)
{
	auto c = ComponentManager<Renderable>::Instance().Create<Renderable>();

	// parse color 
	if (json.find("color") != json.end())
	{
		c->_color = Color(
			json["color"]["r"].get<double>(),
			json["color"]["g"].get<double>(),
			json["color"]["b"].get<double>());
	}

	// parse geometry and texture
	c->_model = ModelLoader::loadModel(json["model_path"].get<std::string>());
	c->_model->setTexture(new std::string(json["texture_path"].get<std::string>()));

	return c;
}

PrefabRegistrar Renderable::reg("Renderable", &Renderable::CreateFromJson);

#pragma endregion