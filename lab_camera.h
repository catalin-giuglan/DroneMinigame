#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace implemented
{
	class Tema2Camera
	{
	public:
		Tema2Camera()
		{
			position = glm::vec3(0, 2, 5);
			forward = glm::vec3(0, 0, -1);
			up = glm::vec3(0, 1, 0);
			right = glm::vec3(1, 0, 0);
			distanceToTarget = 2;
		}

		Tema2Camera(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
		{
			Set(position, center, up);
		}

		~Tema2Camera()
		{ }

		// Update Tema2Camera
		void Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
		{
			this->position = position;
			forward = glm::normalize(center - position);
			right = glm::cross(forward, up);
			this->up = glm::cross(right, forward);
		}

		void MoveForward(float distance)
		{
			// Translates the Tema2Camera using the dir vector computed from
			// forward. Movement will always keep the Tema2Camera at the same
			// height. For example, if you rotate your head up/down, and then
			// walk forward, then you will still keep the same relative
			// distance (height) to the ground!
			glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
			position += dir * distance;
		}

		void TranslateForward(float distance)
		{
			// TODO(student): Translate the Tema2Camera using the forward vector.
			// What's the difference between TranslateForward() and
			// MoveForward()?
			position += forward * distance;

		}

		void TranslateUpward(float distance)
		{
			// TODO(student): Translate the Tema2Camera using the up vector.
			position += up * distance;

		}

		void TranslateRight(float distance)
		{
			// TODO(student): See instructions below. Read the entire thing!
			// You need to translate the Tema2Camera using the right vector.
			// Usually, however, translation using Tema2Camera's right vector
			// is not very useful, because if the Tema2Camera is rotated around the
			// forward vector, then the translation on the right direction
			// will have an undesired effect, more precisely, the Tema2Camera will
			// get closer or farther from the ground. The solution is to
			// actually use the projected right vector (projected onto the
			// ground plane), which makes more sense because we will keep the
			// same distance from the ground plane.

			glm::vec3 projectedRight = glm::normalize(glm::vec3(right.x, 0, right.z));
			position += projectedRight * distance;

		}

		void RotateFirstPerson_OX(float angle)
		{
			// TODO(student): Compute the new forward and up vectors.
			// Don't forget to normalize the vectors! Use glm::rotate().

			glm::mat3 rotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, right));
			forward = glm::normalize(rotationMatrix * forward);
			up = glm::cross(right, forward);
			up = glm::normalize(rotationMatrix * up);

		}

		void RotateFirstPerson_OY(float angle)
		{
			// TODO(student): Compute the new forward, up and right
			// vectors. Use glm::rotate(). Don't forget to normalize the
			// vectors!

			glm::mat3 rotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)));
			forward = glm::normalize(rotationMatrix * forward);
			right = glm::normalize(rotationMatrix * right);

			up = glm::cross(right, forward);
			up = glm::normalize(rotationMatrix * up);

		}

		void RotateFirstPerson_OZ(float angle)
		{
			// TODO(student): Compute the new right and up. This time,
			// forward stays the same. Use glm::rotate(). Don't forget
			// to normalize the vectors!
			glm::mat3 rotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, forward));
			right = glm::normalize(rotationMatrix * right);

			up = glm::cross(right, forward);
			up = glm::normalize(rotationMatrix * up);

		}

		void RotateThirdPerson_OX(float angle)
		{
			// TODO(student): Rotate the Tema2Camera in third-person mode around
			// the OX axis. Use distanceToTarget as translation distance.
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OX(angle);
			TranslateForward(-distanceToTarget);

		}

		void RotateThirdPerson_OY(float angle)
		{
			// TODO(student): Rotate the Tema2Camera in third-person mode around
			// the OY axis.
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OY(angle);
			TranslateForward(-distanceToTarget);

		}

		void RotateThirdPerson_OZ(float angle)
		{
			// TODO(student): Rotate the Tema2Camera in third-person mode around
			// the OZ axis.
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OZ(angle);
			TranslateForward(-distanceToTarget);

		}

		glm::mat4 GetViewMatrix()
		{
			// Returns the view matrix
			return glm::lookAt(position, position + forward, up);
		}

		glm::vec3 GetTargetPosition()
		{
			return position + forward * distanceToTarget;
		}

	public:
		float distanceToTarget;
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;
	};
}   // namespace implemented