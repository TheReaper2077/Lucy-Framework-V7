#pragma once

#include <Lucy/Lucy.h>
#include "JointAngles.h"
#include "JointLength.h"

namespace lra {
	struct Controller {
		bool enable_ik = false;
		// bool free_movt = true;

		glm::ivec3 ik_target = { 150, 150, 150 };
		float speed = 10;

		glm::ivec3 fk_result;

		JointAngles target_joint_angles = { 90, 90, 180, 180, 0, 45 };
		JointLength lra_dimension = { 105, 100, 190 };
	};
}