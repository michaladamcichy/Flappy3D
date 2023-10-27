#pragma once

#include "Drawable.h"
#include "Bindable.h"
#include "Inspectable.h"

class SkyBox : public Drawable, public Bindable, public Inspectable
{
	static constexpr int skyBoxSize{ 500 };

	ci::gl::TextureCubeMapRef _skyBoxCubeMap;
	ci::gl::BatchRef _skyBoxBatch;
	float _rotationSpeed = 0.0f;
public:
	SkyBox() : Inspectable{ "SkyBox"s } {}

	void Setup();
	void Draw() override;
	void Bind() override;

private:
	void InspectImplementation() override;
};
