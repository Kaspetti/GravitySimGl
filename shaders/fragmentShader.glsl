#version 430 core


uniform vec3 centers[3];
uniform int radii[3];
uniform vec3 colors[3];


out vec3 color;


void main() {
    color = vec3(0); // Default background color

for (int i = 0; i < 3; i++) {
        float distanceFromCenter = distance(gl_FragCoord.xyz, centers[i]);
        float edgeSoftness = 1.0;
        float radius = float(radii[i]);
        float edgeStart = radius - edgeSoftness;
        
        float alpha = 1.0 - smoothstep(edgeStart, radius, distanceFromCenter);

        color = mix(color, colors[i], alpha);
    }
}
