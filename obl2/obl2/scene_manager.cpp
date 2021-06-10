// HEADERS
// -----------------------------------------------------------------------------------
#include "scene_manager.h"

// METHODS
// -----------------------------------------------------------------------------------

// Constructor and Singleton method
// -----------------------------------------------------------------------------------

Scene::Scene() {
	this->object_counter = 0;
	this->loaded = load_scene();
}

Scene& Scene::get_instance() {
	static Scene instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}

// Getters & Setters
// -----------------------------------------------------------------------------------

bool Scene::is_loaded() {
	return this->loaded;
}

Camera* Scene::get_camera() {
	return this->camera;
}

vector<Light*> Scene::get_lights() {
	return this->lights;
}

vector<Object*> Scene::get_objects() {
	return this->objects;
}

// Main Methods
// -----------------------------------------------------------------------------------

bool Scene::load_scene() {

	// 1. Scene's objects pre-initialization
	this->camera = new Camera(new Vector(0, 0, 0), new Vector(0, 0, 0));
	this->lights = {};
	this->objects = {};

	// 2. Load config file and read root
	XMLDocument doc;
	doc.LoadFile(CONFIG_FILE.c_str());
	XMLElement* xmlScene = doc.RootElement();

	// 3. Keep reading and loading
	if (xmlScene != NULL) {
		
		// 3.1. Load camera
		XMLElement* xmlCamera = xmlScene->FirstChildElement("camera");
		if (!load_camera(xmlCamera)) {
			return false;
		}

		// 3.2. Load lights
		XMLElement* xmlLights = xmlScene->FirstChildElement("lights");
		if (xmlLights != NULL) {
			
			// 3.2.1. Read lights until there are no more
			XMLElement* xmlLight = xmlLights->FirstChildElement("light");
			while (xmlLight) {
				if (!load_light(xmlLight)) {
					return false;
				}
				xmlLight = xmlLight->NextSiblingElement("light");
			}
		}

		// 3.3. Load objects
		XMLElement* xmlObjects = xmlScene->FirstChildElement("objects");
		if (xmlObjects != NULL) {

			// 3.3.1. Read lights until there are no more
			XMLElement* xmlObject = xmlObjects->FirstChildElement("object");
			while (xmlObject) {
				if (!load_object(xmlObject)) {
					return false;
				}
				xmlObject = xmlObject->NextSiblingElement("object");
			}
		}

	}

	return true;
}

// Aux Methods
// -----------------------------------------------------------------------------------

bool Scene::load_camera(XMLElement* xmlCamera) {

	bool result = true;

	if (xmlCamera != NULL) {
		
		XMLElement* xmlCameraPosition = xmlCamera->FirstChildElement("position");
		if (xmlCameraPosition != NULL) {
			float x, y, z;
			xmlCameraPosition->FirstChildElement("x")->QueryFloatText(&x);
			xmlCameraPosition->FirstChildElement("y")->QueryFloatText(&y);
			xmlCameraPosition->FirstChildElement("z")->QueryFloatText(&z);
			this->camera->set_position(new Vector(x, y, z));
		}
		else {
			result = false;
		}

		XMLElement* xmlCameraWindowPosition = xmlCamera->FirstChildElement("window_position");
		if (xmlCameraWindowPosition != NULL) {
			float x, y, z;
			xmlCameraWindowPosition->FirstChildElement("x")->QueryFloatText(&x);
			xmlCameraWindowPosition->FirstChildElement("y")->QueryFloatText(&y);
			xmlCameraWindowPosition->FirstChildElement("z")->QueryFloatText(&z);
			this->camera->set_window_position(new Vector(x,y,z));
		}
		else {
			result = false;
		}

	}
	else {
		result = false;
	}

	return result;
}

bool Scene::load_light(XMLElement* xmlLight) {

	bool result = true;
	float x, y, z;
	double r, g, b, a;

	if (xmlLight != NULL) {

		XMLElement* xmlLightPosition = xmlLight->FirstChildElement("position");
		if (xmlLightPosition != NULL) {
			xmlLightPosition->FirstChildElement("x")->QueryFloatText(&x);
			xmlLightPosition->FirstChildElement("y")->QueryFloatText(&y);
			xmlLightPosition->FirstChildElement("z")->QueryFloatText(&z);
		}
		else {
			result = false;
		}

		XMLElement* xmlLightColor = xmlLight->FirstChildElement("color");
		if (xmlLightColor != NULL) {
			xmlLightColor->FirstChildElement("r")->QueryDoubleText(&r);
			xmlLightColor->FirstChildElement("g")->QueryDoubleText(&g);
			xmlLightColor->FirstChildElement("b")->QueryDoubleText(&b);
			xmlLightColor->FirstChildElement("a")->QueryDoubleText(&a);
		}
		else {
			result = false;
		}

		this->lights.push_back(new Light(new Vector(x, y, z), { r,g,b,a }));
	}
	else {
		result = false;
	}

	return result;
}

bool Scene::load_object(XMLElement* xmlObject) {

	// Flag
	bool result = true;
	// Type
	ObjectIs type;
	// Position
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	// Color
	double r = 0.f;
	double g = 0.f;
	double b = 0.f;
	double a = 0.f;
	// Properties
	float transparency = 0.f;
	float refraction = 0.f;
	bool reflection = false;

	if (xmlObject != NULL) {

		XMLElement* xmlObjectType = xmlObject->FirstChildElement("type");
		if (xmlObjectType != NULL) {
			std::string string_type = xmlObjectType->GetText();
			type = Object::parse_object_type(string_type);
		}
		else {
			result = false;
		}

		XMLElement* xmlObjectPosition = xmlObject->FirstChildElement("position");
		if (xmlObjectPosition != NULL) {
			xmlObjectPosition->FirstChildElement("x")->QueryFloatText(&x);
			xmlObjectPosition->FirstChildElement("y")->QueryFloatText(&y);
			xmlObjectPosition->FirstChildElement("z")->QueryFloatText(&z);
		}
		else {
			result = false;
		}

		XMLElement* xmlObjectColor = xmlObject->FirstChildElement("color");
		if (xmlObjectColor != NULL) {
			xmlObjectColor->FirstChildElement("r")->QueryDoubleText(&r);
			xmlObjectColor->FirstChildElement("g")->QueryDoubleText(&g);
			xmlObjectColor->FirstChildElement("b")->QueryDoubleText(&b);
			xmlObjectColor->FirstChildElement("a")->QueryDoubleText(&a);
		}
		else {
			result = false;
		}

		XMLElement* xmlObjectProperties = xmlObject->FirstChildElement("properties");
		if (xmlObjectProperties != NULL) {
			xmlObjectProperties->FirstChildElement("transparency")->QueryFloatText(&transparency);
			xmlObjectProperties->FirstChildElement("refraction")->QueryFloatText(&refraction);
			xmlObjectProperties->FirstChildElement("reflection")->QueryBoolText(&reflection);
		}
		else {
			result = false;
		}

		switch (type) {
		case ObjectIs::Sphere:
			this->objects.push_back(new Sphere(
				this->object_counter,
				new Vector(x, y, z),
				{ r,g,b,a },
				transparency,
				refraction,
				reflection
			));
			this->object_counter++;
			break;
		}
	}
	else {
		result = false;
	}

	return result;
}
