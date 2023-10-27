#pragma once

#include "Drawable.h"
#include "Inspectable.h"
#include "Setupable.h"

#include "GameObject.h"
#include "Material.h"
#include "CubeMap.h"
#include "SkyBox.h"

class Batch : public Drawable, public Inspectable, public Setupable, public TransformableObject
{
	struct Vertex
	{
		ci::vec3 position{ 0,0,0 };
		ci::vec2 textureCoordinates{ 0,0 };
		ci::vec3 normal{ 0,0,0 };
		//ci::vec2 tangent{ 0,0};
		
		Vertex();

		Vertex(ci::vec3 _position, ci::vec2 _textureCoordinates, ci::vec3 _normal);
	};

	constexpr static int _maxBufferSize{ 10000 };

	std::vector<Vertex> _buffer;

	ci::gl::BatchRef _batch;
	ci::gl::GlslProgRef _shader;
	ci::gl::TextureRef _texture;
	
	ci::gl::VaoRef _vao;
	ci::gl::VboRef _vbo;
	ci::gl::VboMeshRef _vboMesh;

	static std::vector<Vertex> CubeVertices;
	
	Material _material;
	ci::vec3 _lightDirection{ 0.f, 0.f, -1.f };
	ci::vec3 _lightColor{1.f, 1.f , 1.f};

	Bindable* _environmentalMap{ nullptr };

public:

	Batch(const Material& material, Bindable* environmentalMap = nullptr);
	void Setup() override;
	void Draw() override;
	void SetLight(const ci::vec3& direction, const ci::vec3& color);
	void UpdateColor(ci::Color color);
	void UpdateBuffer(const std::vector<std::unique_ptr<GameObject>>& objects, bool includeRotations = false);

private:
	void InspectImplementation() override;
	std::vector<Vertex> CreateCube();
};
