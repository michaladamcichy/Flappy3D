#include "pch.h"

#include "Batch.h"

Batch::Batch(const Material& material, Bindable* environmentalMap) :
	Inspectable{ "Batch"s },
	_material{ material },
	_environmentalMap{ environmentalMap }
{
}

Batch::Vertex::Vertex() {}

Batch::Vertex::Vertex(ci::vec3 _position, ci::vec2 _textureCoordinates, ci::vec3 _normal) :
	position(_position),
	textureCoordinates(_textureCoordinates),
	normal(_normal)
{
}

void Batch::Setup()
{
	CubeVertices = CreateCube();

	_shader = ci::gl::GlslProg::create(ci::app::loadAsset("env_map.vert"), ci::app::loadAsset("env_map.frag"));
	_texture = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset(_material.textureName)));

	ci::gl::VboMesh::Layout layout;
	layout.attrib(ci::geom::POSITION, 3);
	layout.attrib(ci::geom::TEX_COORD_0, 2);
	layout.attrib(ci::geom::NORMAL, 3);
	
	_vboMesh = ci::gl::VboMesh::create(_maxBufferSize, GL_TRIANGLES, { layout });

	ci::geom::BufferLayout vboLayout;
	vboLayout.append(ci::geom::POSITION, 3, sizeof(Vertex), offsetof(Vertex, position));
	vboLayout.append(ci::geom::TEX_COORD_0, 2, sizeof(Vertex), offsetof(Vertex, textureCoordinates));
	vboLayout.append(ci::geom::NORMAL, 3, sizeof(Vertex), offsetof(Vertex, normal));

	_vbo = ci::gl::Vbo::create(GL_ARRAY_BUFFER, sizeof(Vertex) * _maxBufferSize, nullptr, GL_DYNAMIC_DRAW);
	_vboMesh->appendVbo(vboLayout, _vbo);

	_buffer = std::vector<Vertex>(_maxBufferSize, Vertex());
	_vbo->bufferData(_buffer.size() * sizeof(Vertex), _buffer.data(), GL_DYNAMIC_DRAW);

	_batch = ci::gl::Batch::create(_vboMesh, _shader);
}

void Batch::Draw()
{
	_shader->bind();

	if (_environmentalMap)
		_environmentalMap->Bind();

	_texture->bind(1);
	
	_shader->uniform("uCubeMapTex", 0);
	_shader->uniform("objectTexture", 1);
	_shader->uniform("reflectiveness"s, _material.reflectiveness);
	_shader->uniform("lightDirection"s, _lightDirection);
	_shader->uniform("lightColor"s, _lightColor);
	_shader->uniform("objectColor", _material.color);

	ci::gl::pushMatrices();
	ci::gl::setModelMatrix(CalculateMatrix());
	
	_batch->draw(0, _buffer.size());
	
	ci::gl::popMatrices();
}

void Batch::SetLight(const ci::vec3& direction, const ci::vec3& color)
{
	_lightDirection = direction;
	_lightColor = color;
}

void Batch::InspectImplementation()
{
	ui::InputFloat("reflectiveness", &_material.reflectiveness);
}

void Batch::UpdateColor(ci::Color color)
{
	_material.color = color;
}

void Batch::UpdateBuffer(const std::vector<std::unique_ptr<GameObject>>& objects, bool includeRotations)
{
	_buffer.clear();

	for (const auto& object : objects)
	{
		auto cube = CubeVertices;
		const ci::mat4 matrix{ 
			includeRotations ? object->CalculateMatrix() : ci::mat4(1.0f)
		};
		const ci::mat4 matrixRotations{
			includeRotations ? object->CalculateMatrixRotations() : ci::mat4(1.0f) 
		};

		for (auto& vertex : cube)
		{
			if (includeRotations)
			{
				vertex.position =  matrix * ci::vec4(vertex.position, 1.0f);
				vertex.normal = matrixRotations * ci::vec4(vertex.normal, 1.0f);
			}
			else
			{
				vertex.position *= object->GetScale();
				vertex.position += object->GetPosition();
			}
			
			_buffer.push_back(vertex);
		}
	}

	_vbo->bufferSubData(0, _buffer.size() * sizeof(Vertex), _buffer.data());
}

std::vector<Batch::Vertex> Batch::CreateCube()
{
	constexpr int verticesCount{ 36 };

	std::vector<Vertex> vertices;
	vertices.reserve(verticesCount);

	const ci::vec3 positions[] = {
		ci::vec3(-0.5f, -0.5f, 0.5f),
		ci::vec3(0.5f, -0.5f, 0.5f),
		ci::vec3(0.5f, 0.5f, 0.5f),
		ci::vec3(-0.5f, 0.5f, 0.5f),

		ci::vec3(-0.5f, -0.5f, -0.5f),
		ci::vec3(0.5f, -0.5f, -0.5f),
		ci::vec3(0.5f, 0.5f, -0.5f),
		ci::vec3(-0.5f, 0.5f, -0.5f)
	};

	const ci::vec2 textureCoords[] = {
		ci::vec2(1, 0),
		ci::vec2(1, 1),
		ci::vec2(0, 1),
		ci::vec2(0, 0),
	};

	const auto getTextureCoord([](int vertexNumber)
		{
			switch (vertexNumber)
			{
			case 0: return 0;
			case 1: return 1;
			case 2: return 2;
			case 3: return 2;
			case 4: return 3;
			case 5: return 0;
			}
		});

	const ci::vec3 normals[] = {
		ci::vec3(0, 0, 1), 
		ci::vec3(1, 0, 0), 
		ci::vec3(0, 0, -1),
		ci::vec3(-1, 0, 0),
		ci::vec3(0, -1, 0),
		ci::vec3(0, 1, 0), 
	};

	const int indices[] = {
		0, 1, 2, 2, 3, 0,
		1, 5, 6, 6, 2, 1,
		4, 7, 6, 6, 5, 4,
		4, 0, 3, 3, 7, 4,
		4, 5, 1, 1, 0, 4,
		3, 2, 6, 6, 7, 3 
	};

	for (int i = 0; i < verticesCount; ++i)
	{
		vertices.push_back(Vertex(
			positions[indices[i]],
			textureCoords[getTextureCoord(i % 6)],
			normals[i / 6]
		));
	}

	return vertices;
}

std::vector<Batch::Vertex> Batch::CubeVertices;
