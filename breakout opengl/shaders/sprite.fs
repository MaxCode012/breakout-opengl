#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D image;
uniform vec3 spriteColor;

uniform vec2 uvOffset;
uniform vec2 uvSize;

void main()
{
    // Calculate the adjusted UV coords for the current frame
    vec2 adjustedUV = uvOffset + TexCoords * uvSize;

    // Sample the texture using adjusted UVs
    vec4 texColor = texture(image, adjustedUV);

    // Multiply sampled color by the sprite color (for tinting)
    FragColor = texColor * vec4(spriteColor, 1.0);
}
