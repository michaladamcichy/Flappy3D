#pragma once

#include "pch.h"
#include "Camera.h"
#include "CubeMap.h"

void CubeMap::Setup()
{
	_cubeMapFbo = ci::gl::FboCubeMap::create(defaultCubeMapSize, defaultCubeMapSize);
	_camera = ci::CameraPersp(_cubeMapFbo->getWidth(), _cubeMapFbo->getHeight(), cubeMapCameraFov, Camera::defaultNear, Camera::defaultFar);
}

void CubeMap::Draw()
{
	ci::gl::pushViewport(ci::ivec2(0, 0), _cubeMapFbo->getSize());
	ci::gl::context()->pushFramebuffer();
	
	for (int dir = 0; dir < 6; ++dir)
	{
		ci::gl::setProjectionMatrix(_camera.getProjectionMatrix());
		ci::gl::setViewMatrix(_cubeMapFbo->calcViewMatrix(GL_TEXTURE_CUBE_MAP_POSITIVE_X + dir, ci::vec3(0)));
		_cubeMapFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X + dir);

		ci::gl::clear({0, 0, 0, 0});
		for (auto drawable : _drawables)
		{
			drawable->Draw();
		}
	}
	
	ci::gl::context()->popFramebuffer();
	ci::gl::popViewport();
}

void CubeMap::Bind()
{
	_cubeMapFbo->bindTexture(0);
}

void CubeMap::AddDrawable(Drawable* drawable)
{
	_drawables.push_back(drawable);
}
