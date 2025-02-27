#version 330

// Input
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 coord;
layout(location = 3) in vec3 normal;

// Uniforms
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform float Time;

// Outputs to Fragment Shader
out vec3 frag_color;
out vec2 frag_coord;
out vec3 frag_normal;
out vec3 frag_position;
out float noise_value; // Noise output

// Noise Functions
float random(vec2 p) {
    return fract(sin(dot(p, vec2(12.9898,78.233))) * 43758.5453123);
}

float perlinNoise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);

    vec2 u = f * f * (3.0 - 2.0 * f);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    return mix(mix(a, b, u.x), mix(c, d, u.x), u.y);
}

// Function to modify terrain height
float terrainHeight(vec2 p, float time) {
    float noise = perlinNoise(p * 0.1);
    noise += 0.1 * sin(time * 0.2);
    return noise;
}

void main() {
    frag_color = color;
    frag_coord = coord;
    frag_normal = mat3(Model) * normal; // Transform normal
    frag_position = vec3(Model * vec4(position, 1.0));

    float height = 0.0;
    height = terrainHeight(frag_position.xz, 1.0);
    frag_position.y += height;

    noise_value = perlinNoise(frag_position.xz);

    gl_Position = Projection * View * Model * vec4(frag_position, 1.0);  // Update gl_Position with new terrain height
}