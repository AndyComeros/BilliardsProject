#include "Object.h"

void updateObject(Object* obj, float deltaTime)
{
	obj->body.position = add(
		add(
			obj->body.position, multiply(obj->body.velocity, deltaTime)
		),
		multiply(
			(multiply(obj->body.acceleration, 0.5)),
			(deltaTime * deltaTime)
		)
	); // prev pos + (prevVel*deltaTime) + (1/2* prevAccel*deltaTime^2)

	obj->body.velocity = add(
		obj->body.velocity,
		multiply(
			obj->body.acceleration,
			deltaTime
		)
	); // prevVel + prevAccel*deltatime

	obj->body.acceleration = multiply(obj->body.acceleration, deltaTime); // update acceleration
}

void updatePrevObject(Object* obj)
{
	/*
	obj->body.position = obj->body.position;
	obj->body.velocity = obj->body.velocity;
	obj->body.acceleration = obj->body.acceleration;
	obj->body.scale = obj->body.scale;
	obj->body.rotation = obj->body.rotation;
	*/
}

Vec3 centerOfMass(OffModel* cModel)
{
	Vec3 centre = { 0, 0, 0 };

	for (int i = 0; i < cModel->nVert; i++)
	{
		centre.x += cModel->vertice[i].x;
		centre.y += cModel->vertice[i].y;
		centre.z += cModel->vertice[i].z;
	}

	centre.x /= cModel->nVert;
	centre.y /= cModel->nVert;
	centre.z /= cModel->nVert;

	return centre;
}

GLfloat radiusOfBoundingSphere(OffModel* cModel)
{
	GLfloat r = 0;

	for (int i = 0; i < cModel->nVert; i++)
	{
		Vec3 v = minus(cModel->vertice[i], centerOfMass(cModel));
		float d = length(v);

		if (d > r)
			r = d;
	}

	return r;
}

void normalizeOffModel(OffModel* cModel)
{
	int i = 0;
	Vec3 c = centerOfMass(cModel);
	float r = radiusOfBoundingSphere(cModel);

	for (i = 0; i < cModel->nVert; i++)
	{
		cModel->vertice[i].x -= c.x;
		cModel->vertice[i].y -= c.y;
		cModel->vertice[i].z -= c.z;
	}

	for (i = 0; i < cModel->nVert; i++)
	{
		cModel->vertice[i].x /= r;
		cModel->vertice[i].y /= r;
		cModel->vertice[i].z /= r;
	}
}

void loadOffObject(char* filename, Object* obj)
{
    readOffFile(filename, obj);
	normalizeOffModel(&obj->off);
}

void drawComplexObject(Object* obj)
{
    for (int i = 0; i < obj->off.nFace; i++)
    {
		glColor3fv(obj->off.faces[i].colour);

		glPushMatrix();
		glTranslatef(obj->body.position.x, obj->body.position.y, obj->body.position.z);
		glScalef(obj->body.scale.x, obj->body.scale.y, obj->body.scale.z);
		glRotatef(obj->body.rotAngle, obj->body.rotation.x, obj->body.rotation.y, obj->body.rotation.z);
        glBegin(GL_POLYGON);
			glVertex3f(obj->off.faces[i].p1->x, obj->off.faces[i].p1->y, obj->off.faces[i].p1->z);
			glVertex3f(obj->off.faces[i].p2->x, obj->off.faces[i].p2->y, obj->off.faces[i].p2->z);
			glVertex3f(obj->off.faces[i].p3->x, obj->off.faces[i].p3->y, obj->off.faces[i].p3->z);
        glEnd();
		glPopMatrix();
    }
}

void drawSphereObject(Object* obj)
{
	glColor3f(0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(obj->body.position.x, obj->body.position.y, obj->body.position.z);
	glScalef(obj->body.scale.x, obj->body.scale.y, obj->body.scale.z);
	glRotatef(obj->body.rotAngle, obj->body.rotation.x, obj->body.rotation.y, obj->body.rotation.z);
	glutWireSphere(1, 10, 8);
	glPopMatrix();
}
