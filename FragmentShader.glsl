#version 330

// Input from Vertex Shader
in vec3 frag_color;
in vec2 frag_coord;
in vec3 frag_normal;
in vec3 frag_position;
in float noise_value; // Noise input

// Uniforms
uniform vec3 culoare1;
uniform vec3 culoare2;

// Output
layout(location = 0) out vec4 out_color;

void main() {
    // Interpolate colors based on noise value
    vec3 final_color = mix(culoare1, culoare2, noise_value);

    out_color = vec4(final_color, 1.0);
}
