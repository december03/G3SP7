#include "ShaderStructs.hlsli"
#include "MathHelpers.hlsli"

PixelOutPut PixelShader_Color(VertexToPixel input)
{
    PixelOutPut output;
    float4 color = colorTexture.Sample(defaultSampler, input.myUV.xy).rgba;
	color.rgb = GammaToLinear(color.rgb);
	output.myColor.rgb = color;
	output.myColor.a = color.a;
    return output;
}

PixelOutPut PixelShader_Normal(VertexToPixel input)
{
    float3 normal = normalTexture.Sample(defaultSampler, input.myUV.xy).agr;
    
    normal = (normal * 2) - 1;
    normal.z = sqrt(1 - saturate((normal.x * normal.x) + (normal.y * normal.y)));
    normal = normalize(normal);

    float3x3 tangentSpaceMatrix = float3x3(normalize(input.myTangent.xyz), normalize(input.myBiNormal.xyz), normalize(input.myNormal.xyz));
    normal = mul(normal.xyz, tangentSpaceMatrix);
    normal = normalize(normal);

    PixelOutPut output;
    
    output.myColor.xyz = normal.xyz;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutPut PixelShader_TextureNormal(VertexToPixel input)
{
    float3 normal = normalTexture.Sample(defaultSampler, input.myUV.xy).agr;
    
    PixelOutPut output;
    output.myColor.xyz = normal.xyz;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutPut PixelShader_AmbientOcclusion(VertexToPixel input)
{
    PixelOutPut output;
    float ao = normalTexture.Sample(defaultSampler, input.myUV.xy).b;
    output.myColor.rgb = ao.xxx;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutPut PixelShader_Material(VertexToPixel input)
{
    PixelOutPut output;
    float3 material = materialTexture.Sample(defaultSampler, input.myUV.xy).rgb;
    output.myColor.rgb = material.rgb;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutPut PixelShader_Metalness(VertexToPixel input)
{
    PixelOutPut output;
    PixelOutPut material = PixelShader_Material(input);
    output.myColor.rgb = material.myColor.rrr;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutPut PixelShader_PerceptualRoughness(VertexToPixel input)
{
    PixelOutPut output;
    PixelOutPut material = PixelShader_Material(input);
    output.myColor.rgb = material.myColor.ggg;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutPut PixelShader_Emissive(VertexToPixel input)
{
    PixelOutPut output;
    PixelOutPut material = PixelShader_Material(input);
    output.myColor.rgb = material.myColor.bbb;
    output.myColor.a = 1.0f;
    return output;
}

