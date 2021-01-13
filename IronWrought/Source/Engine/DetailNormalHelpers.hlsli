/*
dn =  lerp(float3(0.0,0.0,1.0), dn, clamp(dnStrength*myCustomValues.y, 0.0, 4.0));
    normal = normal * 0.5 + 0.5;
    dn = dn * 0.5 + 0.5;
	normal = BlendRNM(normal, dn);
//Blending together 2 normals. They should be in 0.0-1.0 range when using this function. https://blog.selfshadow.com/publications/blending-in-detail/
float3 BlendRNM(float3 n1, float3 n2)
{
    float3 t = n1*float3( 2,  2, 2) + float3(-1, -1,  0);
    float3 u = n2.xyz*float3(-2, -2, 2) + float3( 1,  1, -1);
    float3 r = t*dot(t, u) - u*t.z;
    return normalize(r);
}

*/

float3 SetDetailNormalStrength(float3 detailNormal, float detailNormalStrength, float strengthMultiplier)
{
    float3 returnValue = lerp(float3(0.0, 0.0, 1.0), detailNormal, clamp(detailNormalStrength * strengthMultiplier, 0.0, 4.0));
    return returnValue;
}

//Blending together 2 normals. They should be in 0.0-1.0 range when using this function. https://blog.selfshadow.com/publications/blending-in-detail/
float3 BlendRNM(float3 normal1, float3 normal2)
{
    float3 t = normal1 * float3(2, 2, 2) + float3(-1, -1, 0);
    float3 u = normal2.xyz * float3(-2, -2, 2) + float3(1, 1, -1);
    float3 r = t * dot(t, u) - u * t.z;
    return normalize(r);
}
