#pragma once

#include "Drawable.h"
#include "Inspectable.h"
#include "Setupable.h"
#include "Updatable.h"

#include "GameObject.h"
#include "GameBoard.h"
#include "Player.h"
#include "GameLogic.h"
#include "Batch.h"
#include "SatellitesBatch.h"
#include "Camera.h"

class GameGraphicsGenerator : public Drawable, public Inspectable, public Setupable, public Updatable
{
	constexpr static int maxFpsCount{ 1000 };
	constexpr static float objectSize{ 0.9f };
	
public:
	GameGraphicsGenerator(GameLogic& gameLogic);

	GameLogic& _gameLogic;
	SkyBox _skyBox;
	CubeMap _cubeMap;
	Camera _camera;

	Batch _boardBatch{ Material{"board.jpg", 0.6f}, &_cubeMap };
	Batch _playerBatch{ Material{"player.jpg", 0.2f}, &_cubeMap };
	SatellitesBatch _satellitesBatch{ Material{"orange.jpg", 0.2f}, &_skyBox };

	ci::vec3 _lightDirection{ -0.2f, -0.2f, -0.5f };
	ci::vec3 _lightColor{ 1.0f, 0.96f, 0.95f };

	ci::Anim<float> _playerParticlesSpread{ 1.0f };

	std::vector<std::unique_ptr<GameObject>> GenerateBoard(const GameLogic& gameLogic) const;
	std::vector<std::unique_ptr<GameObject>> GeneratePlayer(const GameLogic &gameLogic) const;

	static ci::vec3 BoardSpaceToWorldSpace(ci::ivec2 coordinates, int columnsCount);

	void Setup() override;
	void Update() override;
	void Draw() override;

private:
	void InspectImplementation() override;
};
