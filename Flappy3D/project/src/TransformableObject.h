#pragma once

class TransformableObject
{
	ci::vec3 _position{ 0,0,0 };
	ci::vec3 _scale{ 1,1,1 };
	ci::vec3 _rotation{0,0,0};

	ci::mat4 _additionalTransformation{ 1.0f };

public:
	TransformableObject(ci::vec3 scale = ci::vec3{ 1.0f, 1.0f, 1.0f }, ci::vec3 position = ci::vec3{ 0.f, 0.f, 0.f });

	ci::vec3 GetPosition() const;
	ci::vec3 GetScale() const;
	ci::vec3 GetRotation() const;

	void SetPosition(ci::vec3 position);
	void SetScale(ci::vec3 scale);
	void SetRotation(ci::vec3 rotation);
	
	ci::mat4 CalculateMatrix();
	ci::mat4 CalculateMatrixRotations();

	void RotateAroundAxis(float angle, ci::vec3 axis);
};
