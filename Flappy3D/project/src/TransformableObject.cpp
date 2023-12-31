#include "pch.h"

#include "TransformableObject.h"

TransformableObject::TransformableObject(ci::vec3 scale, ci::vec3 position)
{
    _scale = scale;
    _position = position;
}

ci::vec3 TransformableObject::GetPosition() const
{
    return _position;
}

ci::vec3 TransformableObject::GetScale() const
{
    return _scale;
}

ci::vec3 TransformableObject::GetRotation() const
{
    return _rotation;
}

void TransformableObject::SetPosition(ci::vec3 position)
{
    _position = position;
}

void TransformableObject::SetScale(ci::vec3 scale)
{
    _scale = scale;
}

void TransformableObject::SetRotation(ci::vec3 rotation)
{
    _rotation = rotation;
}

ci::mat4 TransformableObject::CalculateMatrix()
{
    return _additionalTransformation * 
        glm::translate(_position) * 
        glm::eulerAngleXYZ(_rotation.x, _rotation.y, _rotation.z) * 
        glm::scale(_scale);
}

ci::mat4 TransformableObject::CalculateMatrixRotations()
{
    return _additionalTransformation * 
        glm::eulerAngleXYZ(_rotation.x, _rotation.y, _rotation.z) * 
        glm::scale(_scale);
}

void TransformableObject::RotateAroundAxis(float angle, ci::vec3 axis)
{
    const auto rotation{ 
        glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) };
    _additionalTransformation = rotation * _additionalTransformation;
}
