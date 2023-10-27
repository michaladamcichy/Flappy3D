#include "pch.h"

#include "SkyBox.h"
#include "Timing.h"

void SkyBox::Setup()
{
	_skyBoxCubeMap = ci::gl::TextureCubeMap::create(ci::loadImage(ci::app::loadAsset("test.png")), ci::gl::TextureCubeMap::Format().mipmap());
	const auto skyBoxGlsl = ci::gl::GlslProg::create(ci::app::loadAsset("sky_box.vert"), ci::app::loadAsset("sky_box.frag"));

	_skyBoxBatch = ci::gl::Batch::create(ci::geom::Cube() >> ci::geom::Scale(ci::vec3(skyBoxSize)), skyBoxGlsl);
	_skyBoxBatch->getGlslProg()->uniform("uCubeMapTex", 0);
}

void SkyBox::Draw()
{
	_skyBoxCubeMap->bind();
	ci::gl::pushMatrices();

	ci::gl::rotate(_rotationSpeed * ci::app::getElapsedSeconds() + 1.0f, 0, 1, 0);
	_skyBoxBatch->draw();
	ci::gl::popMatrices();
}

void SkyBox::Bind()
{
	_skyBoxCubeMap->bind(0);
}

void SkyBox::InspectImplementation()
{
	ui::InputFloat("rotationSpeeed", &_rotationSpeed);
}
