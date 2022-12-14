#include "Ray.h"
#include <iostream>
#include <algorithm>

void lucy::RayCastPoint(int startX, int startY, int startZ, int endX, int endY, int endZ, RAYCAST_FUNCTION function) {
	int x0 = startX, y0 = startY, z0 = startZ;
	int x1 = endX, y1 = endY, z1 = endZ;

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int dz = abs(z1 - z0);

	int stepX = x0 < x1 ? 1 : -1;
	int stepY = y0 < y1 ? 1 : -1;
	int stepZ = z0 < z1 ? 1 : -1;

	double hypotenuse = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));

	double tMaxX = hypotenuse * 0.5 / dx;
	double tMaxY = hypotenuse * 0.5 / dy;
	double tMaxZ = hypotenuse * 0.5 / dz;

	double tDeltaX = hypotenuse / dx;
	double tDeltaY = hypotenuse / dy;
	double tDeltaZ = hypotenuse / dz;

	while (true) {
		if (tMaxX < tMaxY) {
			if (tMaxX < tMaxZ) {
				x0 = x0 + stepX;
				tMaxX = tMaxX + tDeltaX;
			} else if (tMaxX > tMaxZ) {
				z0 = z0 + stepZ;
				tMaxZ = tMaxZ + tDeltaZ;
			} else{
				x0 = x0 + stepX;
				tMaxX = tMaxX + tDeltaX;
				z0 = z0 + stepZ;
				tMaxZ = tMaxZ + tDeltaZ;
			}
		} else if (tMaxX > tMaxY){
			if (tMaxY < tMaxZ) {
				y0 = y0 + stepY;
				tMaxY = tMaxY + tDeltaY;
			} else if (tMaxY > tMaxZ){
				z0 = z0 + stepZ;
				tMaxZ = tMaxZ + tDeltaZ;
			} else{
				y0 = y0 + stepY;
				tMaxY = tMaxY + tDeltaY;
				z0 = z0 + stepZ;
				tMaxZ = tMaxZ + tDeltaZ;
			}
		} else {
			if (tMaxY < tMaxZ) {
				y0 = y0 + stepY;
				tMaxY = tMaxY + tDeltaY;
				x0 = x0 + stepX;
				tMaxX = tMaxX + tDeltaX;
			} else if (tMaxY > tMaxZ) {
				z0 = z0 + stepZ;
				tMaxZ = tMaxZ + tDeltaZ;
			} else {
				x0 = x0 + stepX;
				tMaxX = tMaxX + tDeltaX;
				y0 = y0 + stepY;
				tMaxY = tMaxY + tDeltaY;
				z0 = z0 + stepZ;
				tMaxZ = tMaxZ + tDeltaZ;
			}
		}

		if (function(x0, y0, z0)) {
			return;
		}

		if (x0 == x1 && y0 == y1 && z0 == z1) {
			break;
		}
	}
}

void lucy::RayCastPoint(const glm::ivec3& start, const glm::ivec3& end, RAYCAST_FUNCTION function) {
	RayCastPoint(start.x, start.y, start.z, end.x, end.y, end.z, function);
}

void lucy::RayCastDirection(const glm::ivec3& origin, const glm::vec3& direction, const float& distance, bool normalize, RAYCAST_FUNCTION function) {
	if (normalize) {
		RayCastPoint(origin, glm::normalize(direction) * distance, function);
	} else {
		RayCastPoint(origin, direction * distance, function);
	}
}
