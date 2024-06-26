#version 120

// Interpolated values from the vertex shader
varying vec2 UV;

// Values that stay constant for the whole mesh.
uniform sampler2D textureSampler;
uniform vec4 textColor;

void main()
{
	// Output color = color of the texture at the specified UV
    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture2D(textureSampler, UV).r);
	gl_FragColor = textColor * sampled;
}