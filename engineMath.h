#ifndef ENGINEMATH_H

#define ENGINEMATH_H

#include <math.h>
#include <stdlib.h>

typedef struct {
	float x;
	float y;
} Vector2;

typedef struct {
	float x;
	float y;
	float z;
} Vector3;

typedef struct {
	int width;
	int height;
	float** contents;
} Matrix;

float vector2Magnitude(Vector2 vector);
float vector3Magnitude(Vector3 vector);

Vector2 subtractVector2(Vector2 a, Vector2 b);
Vector3 subtractVector3(Vector3 a, Vector3 b);

Vector2 addVector2(Vector2 a, Vector2 b);
Vector3 addVector3(Vector3 a, Vector3 b);

Vector2 multiplyVector2byNumber(Vector2 a, float k);
Vector3 multiplyVector3byNumber(Vector3 a, float k);

void normalizeVector2(Vector2* vector);
void normalizeVector3(Vector3* vector);

float vector2Dot(Vector2 a, Vector2 b);
float vector3Dot(Vector3 a, Vector3 b);

Vector3 vector3Cross(Vector3 a, Vector3 b);

Matrix* createMatrix(int width, int height);
void freeMatrix(Matrix** matrixPtr);

Matrix* addMatrix(Matrix* a, Matrix* b);

Matrix* multiplyMatrixbyNumber(Matrix* matrix, float k);

Matrix* multiplyMatrix(Matrix* a, Matrix* b);

Matrix* multiplyMatrixVector3(Matrix* matrix, Vector3 vector);

#endif
