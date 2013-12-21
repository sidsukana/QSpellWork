uniform struct {
    vec3 position;
    vec4 ambient;
    vec4 diffuse;
} light;

uniform struct {
    float opacity;
    vec4 emission;
} material;

uniform bool lighting;

uniform sampler2D texture;

varying vec2 v_texcoord;
varying vec3 v_normal;

void main()
{
    vec3 normal = normalize(v_normal);

    if (gl_FrontFacing == false)
        normal = -normal;

    gl_FragColor = material.emission;

    if (lighting) {
        float NdotL = max(dot(normal, normalize(light.position)), 0.0); 

        gl_FragColor += material.opacity * (light.ambient + light.diffuse * NdotL);
    } else {
        gl_FragColor += material.opacity * vec4(1.0, 1.0, 1.0, 1.0);
    }

    gl_FragColor *= texture2D(texture, v_texcoord);
}
