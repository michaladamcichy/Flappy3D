#version 150

uniform samplerCube uCubeMapTex;
uniform sampler2D objectTexture;
uniform float reflectiveness;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 objectColor;

in vec3	NormalWorldSpace;
in vec3 EyeDirWorldSpace;
in vec2 TextureCoordinations;

out vec4 oColor;

void main( void )
{
	vec3 normalizedNormalWorldSpace = normalize(NormalWorldSpace);
	vec3 reflectedEyeWorldSpace = reflect( EyeDirWorldSpace, normalizedNormalWorldSpace );
	vec4 textureColor =  texture( objectTexture, TextureCoordinations);
	vec4 cubeMapColor = texture( uCubeMapTex, reflectedEyeWorldSpace);
	
	float diffuseLighting = max(0, dot(normalizedNormalWorldSpace, normalize(-lightDirection)));
	float ambientLighting = 0.5f;
	float diffuseMultiplier = 1.5f;
	float lighting = diffuseLighting * diffuseMultiplier + ambientLighting;
	oColor = vec4(mix(textureColor * vec4(objectColor, 1), cubeMapColor, reflectiveness).rgb * lightColor * lighting, 1);
}
