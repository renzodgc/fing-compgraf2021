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
	double diffuse_r = 0.f;
	double diffuse_g = 0.f;
	double diffuse_b = 0.f;
	double diffuse_a = 0.f;
	double specular_r = 0.f;
	double specular_g = 0.f;
	double specular_b = 0.f;
	double specular_a = 0.f;
	// Properties
	float refraction_coef = 0.f;
	float transmission_coef = 0.f;
	float specular_coef = 0.f;
	float diffuse_coef = 0.f;
	float ambience_coef = 0.f;
	bool reflective = false;

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

		XMLElement* xmlObjectDiffuseColor = xmlObject->FirstChildElement("diffuse_color");
		if (xmlObjectDiffuseColor != NULL) {
			xmlObjectDiffuseColor->FirstChildElement("r")->QueryDoubleText(&diffuse_r);
			xmlObjectDiffuseColor->FirstChildElement("g")->QueryDoubleText(&diffuse_g);
			xmlObjectDiffuseColor->FirstChildElement("b")->QueryDoubleText(&diffuse_b);
			xmlObjectDiffuseColor->FirstChildElement("a")->QueryDoubleText(&diffuse_a);
		}
		else {
			result = false;
		}

		XMLElement* xmlObjectSpecularColor = xmlObject->FirstChildElement("specular_color");
		if (xmlObjectSpecularColor != NULL) {
			xmlObjectSpecularColor->FirstChildElement("r")->QueryDoubleText(&specular_r);
			xmlObjectSpecularColor->FirstChildElement("g")->QueryDoubleText(&specular_g);
			xmlObjectSpecularColor->FirstChildElement("b")->QueryDoubleText(&specular_b);
			xmlObjectSpecularColor->FirstChildElement("a")->QueryDoubleText(&specular_a);
		}
		else {
			result = false;
		}

		XMLElement* xmlObjectProperties = xmlObject->FirstChildElement("properties");
		if (xmlObjectProperties != NULL) {
			xmlObjectProperties->FirstChildElement("refraction_coef")->QueryFloatText(&refraction_coef);
			xmlObjectProperties->FirstChildElement("transmission_coef")->QueryFloatText(&transmission_coef);
			xmlObjectProperties->FirstChildElement("specular_coef")->QueryFloatText(&specular_coef);
			xmlObjectProperties->FirstChildElement("diffuse_coef")->QueryFloatText(&diffuse_coef);
			xmlObjectProperties->FirstChildElement("ambience_coef")->QueryFloatText(&ambience_coef);
			xmlObjectProperties->FirstChildElement("reflective")->QueryBoolText(&reflective);
		}
		else {
			result = false;
		}

		switch (type) {
		case ObjectIs::Sphere:
			this->objects.push_back(new Sphere(
				this->object_counter,
				new Vector(x, y, z),
				{ diffuse_r, diffuse_g, diffuse_b, diffuse_a },
				{ specular_r, specular_g, specular_b, specular_a },
				refraction_coef,
				transmission_coef,
				specular_coef,
				diffuse_coef,
				ambience_coef,
				reflective,
				3.f // TODO: Parse radius
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
