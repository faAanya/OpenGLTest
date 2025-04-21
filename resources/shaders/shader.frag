#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec2 textureCoordinates;

void main()
{
	FragColor = texture(texture1, TexCoord);
}