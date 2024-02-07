#version 430 core

struct circle {
    vec4 origin;
    vec4 color;
    float radius; 
    float padding[3];
};

layout(std430, binding = 0) buffer circlesbuffer {
    circle circles[];
};

out vec3 color;


void main() {
    color = vec3(0);

    for (int i = 0; i < circles.length(); i++) {
        circle circle = circles[i];

        float distancefromcenter = distance(gl_FragCoord.xyz, circle.origin.xyz);
        float edgesoftness = 2.0;
        float edgestart = circle.radius - edgesoftness;
        
        float alpha = 1.0 - smoothstep(edgestart, circle.radius, distancefromcenter);

        color = mix(color, circle.color.xyz, alpha);
    }
}
