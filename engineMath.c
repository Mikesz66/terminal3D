#include "engineMath.h"

float vector2Magnitude(Vector2 vector) {
	return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

float vector3Magnitude(Vector3 vector) {
	return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

Vector2 subtractVector2(Vector2 a, Vector2 b) {
	Vector2 result =  {a.x - b.x, a.y - b.y};
	return result;
}

Vector3 subtractVector3(Vector3 a, Vector3 b) {
	Vector3 result = {a.x - b.x, a.y - b.y, a.z - b.z};
	return result;
}

Vector2 addVector2(Vector2 a, Vector2 b) {
	Vector2 result = {a.x + b.x, a.y + b.y};
	return result;
}

Vector3 addVector3(Vector3 a, Vector3 b) {
	Vector3 result = {a.x + b.x, a.y + b.y, a.z + b.z};
	return result;
}

Vector2 multiplyVector2byNumber(Vector2 a, float k) {
	Vector2 result = {a.x * k, a.y * k};
	return result;
}

Vector3 multiplyVector3byNumber(Vector3 a, float k) {
	Vector3 result = {a.x * k, a.y * k, a.z * k};
	return result;
}

void normalizeVector2(Vector2* vector) {
	float magnitude = vector2Magnitude(*vector);
	if (magnitude != 0.0f) {
		*vector = multiplyVector2byNumber(*vector, 1.0f / magnitude);
	}
}

void normalizeVector3(Vector3* vector) {
	float magnitude = vector3Magnitude(*vector);
	if (magnitude != 0.0f) {
		*vector = multiplyVector3byNumber(*vector, 1.0f / magnitude);
	}
}

float vector2Dot(Vector2 a, Vector2 b) {
	return a.x * b.x + a.y * b.y;
}

float vector3Dot(Vector3 a, Vector3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 vector3Cross(Vector3 a, Vector3 b) {
	Vector3 result = {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
	return result;
}

Matrix* createMatrix(int width, int height) {
	Matrix* matrix = malloc(sizeof(Matrix));
	if (!matrix) return NULL;

	matrix->width = width;
	matrix->height = height;

	matrix->contents = malloc(height * sizeof(float*));
	if (!matrix->contents) {
		free(matrix);
		return NULL;
	}

	for (int i = 0; i < height; i++) {
		matrix->contents[i] = malloc(width * sizeof(float));
		if (!matrix->contents[i]) {
			for (int j = 0; j < i; j++) {
				free(matrix->contents[j]);
			}
			free(matrix->contents);
			free(matrix);
			return NULL;
		}
	}
	return matrix;
}

void freeMatrix(Matrix** matrixPtr) {
	Matrix* matrix = *matrixPtr;
	for (int i = 0; i < matrix->height; i++) {
		free(matrix->contents[i]);
	}
	free(matrix->contents);
	free(matrix);
	*matrixPtr = NULL;
}

Matrix* addMatrix(Matrix* a, Matrix* b) {
	if (a->width != b->width || a->height != b->height) {
		return NULL;
	}

	Matrix* result = createMatrix(a->width, a->height);
	if (!result) return NULL;

	for (int y = 0; y < result->height; y++) {
		for (int x = 0; x < result->width; x++) {
			result->contents[y][x] = a->contents[y][x] + b->contents[y][x];
		}
	}
	return result;
}

Matrix* multiplyMatrixbyNumber(Matrix* matrix, float k) {
	Matrix* result = createMatrix(matrix->width, matrix->height);
	if (!result) return NULL;

	for (int y = 0; y < result->height; y++) {
		for (int x = 0; x < result->width; x++) {
			result->contents[y][x] = matrix->contents[y][x] * k;
		}
	}
	return result;
}

Matrix* multiplyMatrix(Matrix* a, Matrix* b) {
	if (a->width != b->height) {
		return NULL;
	}

	Matrix* result = createMatrix(b->width, a->height);
	if(!result) return NULL;

	for (int y = 0; y < a->height; y++) {
		for (int x = 0; x < b->width; x++) {
			float sum = 0.0f;
			for (int k = 0; k < a->width; k++) {
				sum += a->contents[y][k] * b->contents[k][x];
			}
			result->contents[y][x] = sum;
		}
	}
	return result;
}

Matrix* multiplyMatrixVector3(Matrix* matrix, Vector3 vector) {
	if (matrix->width != 3) return NULL;
	Matrix* result = createMatrix(1, matrix->height);
	if (!result) return NULL;

	for (int y = 0; y < result->height; y++) {
		result->contents[y][0] = matrix->contents[y][0] * vector.x
			+ matrix->contents[y][1] * vector.y
			+ matrix->contents[y][2] * vector.z;
	}
	return result;
}
