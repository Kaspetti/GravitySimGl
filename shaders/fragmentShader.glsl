#version 430 core

struct Circle {
    vec4 origin;
    vec4 color;
    float radius; 
};

layout(std140, binding = 0) buffer CirclesBuffer {
    Circle circles[];
};

out vec3 color;


void main() {
    color = vec3(circles.length()); // Default background color

    for (int i = 0; i < 1; i++) {
        Circle circle = circles[i];

        float distanceFromCenter = distance(gl_FragCoord.xyz, circle.origin.xyz);
        float edgeSoftness = 2.0;
        float edgeStart = circle.radius - edgeSoftness;
        
        float alpha = 1.0 - smoothstep(edgeStart, circle.radius, distanceFromCenter);

        color = mix(color, circle.color.xyz, alpha);
    }
}
