attribute vec3 position;
attribute vec4 color;
attribute vec2 texcoord;

uniform mat4 mvpMatrix;

varying vec4 v_color;
varying vec2 v_texcoord;

void main()
{
    v_color = color;
    v_texcoord = texcoord;

    gl_Position = mvpMatrix * vec4(position, 1.0);
}
