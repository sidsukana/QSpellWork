attribute vec3 position;
attribute vec3 normal;
attribute vec2 texcoord;
attribute vec4 boneindices;
attribute vec4 boneweights;

uniform mat4 mvpMatrix;
uniform mat3 normalMatrix;
uniform mat4 bones[100];
uniform mat4 textureMatrix;

varying vec2 v_texcoord;
varying vec3 v_normal;

void main()
{
    gl_Position  = (bones[int(boneindices.x * 255.0)] * vec4(position, 1.0)) * (boneweights.x);
    gl_Position += (bones[int(boneindices.y * 255.0)] * vec4(position, 1.0)) * (boneweights.y);
    gl_Position += (bones[int(boneindices.z * 255.0)] * vec4(position, 1.0)) * (boneweights.z);
    gl_Position += (bones[int(boneindices.w * 255.0)] * vec4(position, 1.0)) * (boneweights.w);

    gl_Position = mvpMatrix * vec4(gl_Position.xyz, 1.0);

    v_texcoord = (textureMatrix * vec4(texcoord, 1.0, 1.0)).xy;

    v_normal  = ((bones[int(boneindices.x * 255.0)] * vec4(normal, 0.0)) * (boneweights.x)).xyz;
    v_normal += ((bones[int(boneindices.y * 255.0)] * vec4(normal, 0.0)) * (boneweights.y)).xyz;
    v_normal += ((bones[int(boneindices.z * 255.0)] * vec4(normal, 0.0)) * (boneweights.z)).xyz;
    v_normal += ((bones[int(boneindices.w * 255.0)] * vec4(normal, 0.0)) * (boneweights.w)).xyz;
    
    v_normal = normalMatrix * v_normal;
}
