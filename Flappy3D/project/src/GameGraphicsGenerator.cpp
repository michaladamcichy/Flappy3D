#include "pch.h"

#include "GameGraphicsGenerator.h"
#include "Gui.h"

GameGraphicsGenerator::GameGraphicsGenerator(GameLogic& gameLogic) : Inspectable{"GraphicsGenerator"s}, _gameLogic{gameLogic}
{
}

std::vector<std::unique_ptr<GameObject>> GameGraphicsGenerator::GenerateBoard(const GameLogic& gameLogic) const
{
	const auto& gameBoard{ gameLogic.GetBoard() };

	std::vector<std::unique_ptr<GameObject>> objects;

	const auto& columns{ gameBoard.GetColumns() };

	for (auto x{ 0U }; x < columns.size(); x++)
	{
		const auto& column{ columns[x] };

		for (auto y{ 0U }; y < column.size(); y++)
		{
			if (!column[y])
				continue;

			const auto position{ BoardSpaceToWorldSpace({ x,y }, gameBoard.GetSize()) };
			auto object{ std::make_unique<GameObject>(position, ci::vec3{ objectSize } ) };
			objects.push_back(std::move(object));
		}
	}

	return objects;
}

std::vector<std::unique_ptr<GameObject>> GameGraphicsGenerator::GeneratePlayer(const GameLogic& gameLogic) const
{
	const auto& player{ gameLogic.GetPlayer() };

	const auto playerShape{ Gui::GetInstance()->GetPersonalizedPlayerData() };

	std::vector<std::unique_ptr<GameObject>> objects;
	objects.reserve(playerShape.size() * playerShape[0].size());

	const auto objectOffset{ 2.0f / playerShape.size() };
	const auto objectSize{ objectOffset * 0.9f };
	const ci::vec2 shift{-0.5f, 2.0f};
	const ci::vec3 center{ shift.x / 2.0f, shift.y / 2.0f, 0.0f};

	for (auto y{ 0U }; y < playerShape.size(); y++)
		for (auto x{ 0U }; x < playerShape[0].size(); x++)
		{
			if (!playerShape[y][x])
				continue;

			const auto xValue{ shift.x + x * objectOffset + objectOffset / 2 };
			const auto yValue{ shift.y - y * objectOffset - objectOffset / 2 };
			const ci::vec3 position{ xValue, yValue, 0 };
			
			auto object{ std::make_unique<GameObject>(position) };

			object->SetScale((ci::vec3(objectSize / _playerParticlesSpread)));
			objects.push_back(std::move(object));
		}

	return objects;
}

ci::vec3 GameGraphicsGenerator::BoardSpaceToWorldSpace(ci::ivec2 coordinates, int columnsCount)
{
	const auto xShift{ static_cast<float>(columnsCount) / 2 };
	const auto yShift{ 0.5f };

	const auto xValue{ 1.0f * coordinates.x - xShift + 0.5f };
	const auto yValue{ 1.0f * coordinates.y - yShift };

	return { xValue, yValue, 0.0f };
}

void GameGraphicsGenerator::Setup()
{
	ci::app::setFrameRate(static_cast<float>(maxFpsCount));
	ci::gl::enableVerticalSync(false);
	ci::app::getWindow()->setFullScreen(true);

	_skyBox.Setup();
	_cubeMap.Setup();
	_boardBatch.Setup();
	_playerBatch.Setup();

	_satellitesBatch.Setup();

	_cubeMap.AddDrawable(&_skyBox);
	_cubeMap.AddDrawable(&_satellitesBatch);

	Gui::GetInstance()->AddInspectable(&_camera);

	ci::gl::enableDepthRead();
	ci::gl::enableDepthWrite();
}

void GameGraphicsGenerator::Update()
{
	if (_playerParticlesSpread == 1.0f && _gameLogic.GetPlayer().IsDead())
	{
		ci::app::timeline().apply(&_playerParticlesSpread, 100.0f, 2.0f, ci::EaseInAtan());
	}

	if (_playerParticlesSpread > 1.0f && !_gameLogic.GetPlayer().IsDead())
	{
		_playerParticlesSpread.stop();
		_playerParticlesSpread = 1.0f;
	}

	_camera.Update();

	if (_gameLogic.GetBoard().HasChanged())
	{
		const auto board{ GenerateBoard(_gameLogic) };
		_boardBatch.UpdateBuffer(board);
	}

	if (Gui::GetInstance()->HasPlayerDataChanged() || _gameLogic.GetPlayer().HasChanged() || _gameLogic.GetPlayer().IsDead())
	{
		const auto player{ GeneratePlayer(_gameLogic) };
		_playerBatch.UpdateBuffer(player);
		const auto color{ Gui::GetInstance()->GetPersonalizedPlayerColor() };
		_playerBatch.UpdateColor(color);
	}

	const auto playerVerticalShift{ _gameLogic.GetPlayer().GetVerticalPosition() };
	_playerBatch.SetPosition({ 0, playerVerticalShift, 0 });

	const auto boardHorizontalShift{ _gameLogic.GetBoard().GetVerticalShift() };
	_boardBatch.SetPosition({ -boardHorizontalShift, 0, 0 });

	for (const auto batch : std::vector<Batch*>{ &_boardBatch, &_playerBatch, &_satellitesBatch })
	{
		batch->SetLight(_lightDirection, _lightColor);
	}
	
	_satellitesBatch.UpdateSpeed(_gameLogic.GetGameSpeed());
	_satellitesBatch.Update();
}

void GameGraphicsGenerator::InspectImplementation()
{
	_boardBatch.Inspect();
	_playerBatch.Inspect();
	_satellitesBatch.Inspect();
	_camera.Inspect();
	
	ui::DragFloat3("lightDirection", &_lightDirection[0], 0.1f, -1.0f, 1.0f);
	ui::ColorPicker3("lightColor", &_lightColor[0]);
}

void GameGraphicsGenerator::Draw()
{
	ci::gl::clear( ci::Color::black());
	_cubeMap.Draw();

	ci::gl::setMatrices(_camera);

	_boardBatch.Draw();
	_playerBatch.Draw();
	_satellitesBatch.Draw();
	
	_skyBox.Draw();
}
