// Reference: http://www.lighthouse3d.com/tutorials/view-frustum-culling/

// HEADERS
// -----------------------------------------------------------------------------------
#include "frustum_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor and Singleton method
// -----------------------------------------------------------------------------------

FrustumGeometric::FrustumGeometric() {}

FrustumGeometric& FrustumGeometric::get_instance() {
	static FrustumGeometric instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}

// Main methods
// -----------------------------------------------------------------------------------


int FrustumGeometric::point_in_frustum(Vector3& point) {
	int result = INSIDE;
	for (int i = 0; i < 6; i++) {
		if (planes[i].distance(point) < 0)
			return OUTSIDE;
	}
	return(result);

}

int FrustumGeometric::sphere_in_frustum(Vector3& point, float radio) {
	int result = INSIDE;
	float distance;

	for (int i = 0; i < 6; i++) {
		distance = planes[i].distance(point);
		if (distance < -radio)
			return OUTSIDE;
		else if (distance < radio)
			result = INTERSECT;
	}
	return(result);

}

/*int FrustumGeometric::box_in_frustum(AABox& b) {
	int result = INSIDE;
	for (int i = 0; i < 6; i++) {

		if (planes[i].distance(b.getVertexP(planes[i].normal)) < 0)
			return OUTSIDE;
		else if (planes[i].distance(b.getVertexN(planes[i].normal)) < 0)
			result = INTERSECT;
	}
	return(result);

}*/

void FrustumGeometric::draw_points() {
	glBegin(GL_POINTS);

	glVertex3f(near_top_left.x, near_top_left.y, near_top_left.z);
	glVertex3f(near_top_right.x, near_top_right.y, near_top_right.z);
	glVertex3f(near_bottom_left.x, near_bottom_left.y, near_bottom_left.z);
	glVertex3f(near_bottom_right.x, near_bottom_right.y, near_bottom_right.z);

	glVertex3f(far_top_left.x, far_top_left.y, far_top_left.z);
	glVertex3f(far_top_right.x, far_top_right.y, far_top_right.z);
	glVertex3f(far_bottom_left.x, far_bottom_left.y, far_bottom_left.z);
	glVertex3f(far_bottom_right.x, far_bottom_right.y, far_bottom_right.z);

	glEnd();
}


void FrustumGeometric::draw_lines() {
	glBegin(GL_LINE_LOOP);
	//near plane
	glVertex3f(near_top_left.x, near_top_left.y, near_top_left.z);
	glVertex3f(near_top_right.x, near_top_right.y, near_top_right.z);
	glVertex3f(near_bottom_right.x, near_bottom_right.y, near_bottom_right.z);
	glVertex3f(near_bottom_left.x, near_bottom_left.y, near_bottom_left.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//far plane
	glVertex3f(far_top_right.x, far_top_right.y, far_top_right.z);
	glVertex3f(far_top_left.x, far_top_left.y, far_top_left.z);
	glVertex3f(far_bottom_left.x, far_bottom_left.y, far_bottom_left.z);
	glVertex3f(far_bottom_right.x, far_bottom_right.y, far_bottom_right.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//bottom plane
	glVertex3f(near_bottom_left.x, near_bottom_left.y, near_bottom_left.z);
	glVertex3f(near_bottom_right.x, near_bottom_right.y, near_bottom_right.z);
	glVertex3f(far_bottom_right.x, far_bottom_right.y, far_bottom_right.z);
	glVertex3f(far_bottom_left.x, far_bottom_left.y, far_bottom_left.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//top plane
	glVertex3f(near_top_right.x, near_top_right.y, near_top_right.z);
	glVertex3f(near_top_left.x, near_top_left.y, near_top_left.z);
	glVertex3f(far_top_left.x, far_top_left.y, far_top_left.z);
	glVertex3f(far_top_right.x, far_top_right.y, far_top_right.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//left plane
	glVertex3f(near_top_left.x, near_top_left.y, near_top_left.z);
	glVertex3f(near_bottom_left.x, near_bottom_left.y, near_bottom_left.z);
	glVertex3f(far_bottom_left.x, far_bottom_left.y, far_bottom_left.z);
	glVertex3f(far_top_left.x, far_top_left.y, far_top_left.z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// right plane
	glVertex3f(near_bottom_right.x, near_bottom_right.y, near_bottom_right.z);
	glVertex3f(near_top_right.x, near_top_right.y, near_top_right.z);
	glVertex3f(far_top_right.x, far_top_right.y, far_top_right.z);
	glVertex3f(far_bottom_right.x, far_bottom_right.y, far_bottom_right.z);

	glEnd();
}


void FrustumGeometric::draw_planes() {
	glBegin(GL_QUADS);

	//near plane
	glVertex3f(near_top_left.x, near_top_left.y, near_top_left.z);
	glVertex3f(near_top_right.x, near_top_right.y, near_top_right.z);
	glVertex3f(near_bottom_right.x, near_bottom_right.y, near_bottom_right.z);
	glVertex3f(near_bottom_left.x, near_bottom_left.y, near_bottom_left.z);

	//far plane
	glVertex3f(far_top_right.x, far_top_right.y, far_top_right.z);
	glVertex3f(far_top_left.x, far_top_left.y, far_top_left.z);
	glVertex3f(far_bottom_left.x, far_bottom_left.y, far_bottom_left.z);
	glVertex3f(far_bottom_right.x, far_bottom_right.y, far_bottom_right.z);

	//bottom plane
	glVertex3f(near_bottom_left.x, near_bottom_left.y, near_bottom_left.z);
	glVertex3f(near_bottom_right.x, near_bottom_right.y, near_bottom_right.z);
	glVertex3f(far_bottom_right.x, far_bottom_right.y, far_bottom_right.z);
	glVertex3f(far_bottom_left.x, far_bottom_left.y, far_bottom_left.z);

	//top plane
	glVertex3f(near_top_right.x, near_top_right.y, near_top_right.z);
	glVertex3f(near_top_left.x, near_top_left.y, near_top_left.z);
	glVertex3f(far_top_left.x, far_top_left.y, far_top_left.z);
	glVertex3f(far_top_right.x, far_top_right.y, far_top_right.z);

	//left plane

	glVertex3f(near_top_left.x, near_top_left.y, near_top_left.z);
	glVertex3f(near_bottom_left.x, near_bottom_left.y, near_bottom_left.z);
	glVertex3f(far_bottom_left.x, far_bottom_left.y, far_bottom_left.z);
	glVertex3f(far_top_left.x, far_top_left.y, far_top_left.z);

	// right plane
	glVertex3f(near_bottom_right.x, near_bottom_right.y, near_bottom_right.z);
	glVertex3f(near_top_right.x, near_top_right.y, near_top_right.z);
	glVertex3f(far_top_right.x, far_top_right.y, far_top_right.z);
	glVertex3f(far_bottom_right.x, far_bottom_right.y, far_bottom_right.z);

	glEnd();

}

void FrustumGeometric::draw_normals() {
	Vector3 a, b;

	glBegin(GL_LINES);

	// near
	a = (near_top_right + near_top_left + near_bottom_right + near_bottom_left) * 0.25;
	b = a + planes[NEARP].normal;
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	// far
	a = (far_top_right + far_top_left + far_bottom_right + far_bottom_left) * 0.25;
	b = a + planes[FARP].normal;
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	// left
	a = (far_top_left + far_bottom_left + near_bottom_left + near_top_left) * 0.25;
	b = a + planes[LEFT].normal;
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	// right
	a = (far_top_right + near_bottom_right + far_bottom_right + near_top_right) * 0.25;
	b = a + planes[RIGHT].normal;
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	// top
	a = (far_top_right + far_top_left + near_top_right + near_top_left) * 0.25;
	b = a + planes[TOP].normal;
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	// bottom
	a = (far_bottom_right + far_bottom_left + near_bottom_right + near_bottom_left) * 0.25;
	b = a + planes[BOTTOM].normal;
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	glEnd();
}

// Getters & Setters
// -----------------------------------------------------------------------------------

void FrustumGeometric::set_cam_internals(float angle, float ratio, float near_distance, float far_distance) {
	this->ratio = ratio;
	this->angle = angle;
	this->near_distance = near_distance;
	this->far_distance = far_distance;

	tang = (float)tan(angle * ANG2RAD * 0.5);
	near_height = near_distance * tang;
	near_width = near_height * ratio;
	far_height = far_distance * tang;
	far_width = far_height * ratio;
}

void FrustumGeometric::set_cam_def(Vector3& p, Vector3& l, Vector3& u) {
	Vector3 dir, nc, fc, X, Y, Z;

	Z = p - l;
	Z.normalize();

	X = u * Z;
	X.normalize();

	Y = Z * X;

	nc = p - Z * near_distance;
	fc = p - Z * far_distance;

	near_top_left = nc + Y * near_height - X * near_width;
	near_top_right = nc + Y * near_height + X * near_width;
	near_bottom_left = nc - Y * near_height - X * near_width;
	near_bottom_right = nc - Y * near_height + X * near_width;

	far_top_left = fc + Y * far_height - X * far_width;
	far_top_right = fc + Y * far_height + X * far_width;
	far_bottom_left = fc - Y * far_height - X * far_width;
	far_bottom_right = fc - Y * far_height + X * far_width;

	planes[TOP].set3Points(near_top_right, near_top_left, far_top_left);
	planes[BOTTOM].set3Points(near_bottom_left, near_bottom_right, far_bottom_right);
	planes[LEFT].set3Points(near_top_left, near_bottom_left, far_bottom_left);
	planes[RIGHT].set3Points(near_bottom_right, near_top_right, far_bottom_right);
	planes[NEARP].set3Points(near_top_left, near_top_right, near_bottom_right);
	planes[FARP].set3Points(far_top_right, far_top_left, far_bottom_left);
}
