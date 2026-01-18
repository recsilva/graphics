#version 330 core

in Vertex{
    smooth vec4 color;
} IN;

out vec4 fragColor;
void main() { 
    fragColor = IN.color; 
}