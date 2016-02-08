#version 330 core
//in vec2 TexCoords;
//out vec4 FragColor;

//in VS_OUT {
//    vec3 FragPos;
//    vec3 Normal;
//    vec2 TexCoords;
//    vec4 FragPosLightSpace;
//} fs_in;

//uniform sampler2D texture1;
//uniform sampler2D shadowMap;

//uniform vec3 lightPos;
//uniform vec3 viewPos;

//uniform bool shadows;

//const vec3 fogColor = vec3(0.5, 0.5,0.5);
//const float FogDensity = 0.10;

//float ShadowCalculation(vec4 fragPosLightSpace)
//{
//    // perform perspective divide
//    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
//    // Transform to [0,1] range
//    projCoords = projCoords * 0.5 + 0.5;
//    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
//    float closestDepth = texture(shadowMap, projCoords.xy).r;
//    // Get depth of current fragment from light's perspective
//    float currentDepth = projCoords.z;
//    // Calculate bias (based on depth map resolution and slope)
//    vec3 normal = normalize(fs_in.Normal);
//    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
//    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
//    // Check whether current frag pos is in shadow
//    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
//    // PCF
//    float shadow = 0.0;
//    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
//    for(int x = -1; x <= 1; ++x)
//    {
//        for(int y = -1; y <= 1; ++y)
//        {
//            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
//            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
//        }
//    }
//    shadow /= 9.0;

//    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
//    if(projCoords.z > 1.0)
//        shadow = 0.0;

//    return shadow;
//}

in vec2 TexCoords;
out vec4 color;

uniform sampler2D texture1;

void main()
{
    color = texture(texture1, TexCoords);
}
