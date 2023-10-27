#include "pch.h"

#include "Gui.h"
#include "Camera.h"
#include "Timing.h"
#include "GameLogic.h"
#include "GameGraphicsGenerator.h"

class Flappy3DApp : public ci::app::App {
public:
	void setup() override;
	void mouseDown(ci::app::MouseEvent event) override;
	void keyDown(ci::app::KeyEvent event) override;
	void update() override;
	void draw() override;
	void resize() override;

	GameLogic _gameLogic;
	GameGraphicsGenerator _graphicsGenerator{ _gameLogic };
	Gui _gui;
};

void Flappy3DApp::setup()
{
	_gameLogic.Setup();
	_gui.Setup();
	_graphicsGenerator.Setup();
	_gui.SetOnQuitClicked([&]() { quit(); });
}

void Flappy3DApp::mouseDown(ci::app::MouseEvent event) {}

void Flappy3DApp::keyDown(ci::app::KeyEvent event)
{
	_gameLogic.OnInput(event);
}

void Flappy3DApp::update()
{
	_gameLogic.Update();
	_graphicsGenerator.Update();
	
	const auto fps{ round(getAverageFps()) };
	_gui.UpdateFps(fps);

	Timing::Update();
}

void Flappy3DApp::resize()
{
}

void Flappy3DApp::draw()
{
	_graphicsGenerator.Draw();

	_gui.Draw();
}

CINDER_APP(Flappy3DApp, ci::app::RendererGl(ci::app::RendererGl::Options().msaa(8)));

