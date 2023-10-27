#pragma once

#include "Bindable.h"
#include "Drawable.h"

class CubeMap : public Bindable, public Drawable
{
	constexpr static int defaultCubeMapSize{ 1024 };
	constexpr static float cubeMapCameraFov{ 90.0f };

	ci::gl::FboCubeMapRef _cubeMapFbo;
	ci::CameraPersp _camera;
	std::vector<Drawable*> _drawables;

public:
	void Setup();
	void Draw() override;
	void Bind() override;

	void AddDrawable(Drawable* drawable);
};
