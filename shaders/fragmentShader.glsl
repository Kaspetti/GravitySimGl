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

        float distanceFromCenter = distance(gl_FragCoord.xyz, circle.origin.xyz);
        float edgeSoftness = 2.0;

        if (distanceFromCenter > circle.radius-edgeSoftness) {
            continue;
        }

        float edgeStart = circle.radius - edgeSoftness;
        float alpha = 1.0 - smoothstep(edgeStart, circle.radius, distanceFromCenter);

        color = mix(color, circle.color.xyz, alpha);
        break;
    }
}
