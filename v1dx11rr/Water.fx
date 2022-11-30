Texture2D textureColor : register(t0);
Texture2D dudvMap : register(t1);
SamplerState colorSampler : register(s0);

cbuffer cbChangerEveryFrame : register(b0)
{
    matrix worldMatrix;
};

cbuffer cbNeverChanges : register(b1)
{
    matrix viewMatrix;
};

cbuffer cbChangeOnResize : register(b2)
{
    matrix projMatrix;
};
cbuffer cbFactores : register(b3)
{
    float FAA;
    float FAD;
    float FAS;
    float paddingFactores;
};
cbuffer cbOleaje : register(b4)
{
    float factorOleaje;
    float3 padding; //
}
cbuffer cbLightBuffer : register(b5)
{
    float4 diffuseLightColor;
    float3 lightDirection;
    float paddingLight; // que tanto se mueve 
};

struct VS_Input
{
    float4 pos : POSITION;
    float4 tex0 : TEXCOORD0;
    
};

struct PS_Input
{
    float4 pos : SV_POSITION;
    float2 tex0 : TEXCOORD1;
    float4 clipspace : TEXCOORD2;
};

PS_Input VS_Main(VS_Input vertex)
{
    PS_Input vsOut = (PS_Input) 0;
    //Codigo de video
    
    vertex.pos = mul(vertex.pos, worldMatrix);
    vertex.pos = mul(vertex.pos, viewMatrix);
    vertex.pos = mul(vertex.pos, projMatrix);

    vsOut.pos = vertex.pos;
    
    vsOut.clipspace = vsOut.pos;
    
    //El ultimo valor por el que se multiplica es el tiling
    vsOut.tex0 = float2(vertex.tex0.x / 2.0 + 0.5, vertex.tex0.y / 2.0 + 0.5) * 18;
    return vsOut;
}

float4 PS_Main(PS_Input pix) : SV_TARGET
{
    const float waveStrenght = 0.5; //que tan altas estan las olas
    float2 ndc = (pix.clipspace.xy / pix.clipspace.w) / 2.0 + 0.5;
    
  
    float2 reflectTexCoords = float2(ndc.x, -ndc.y);
    //Los ultimos valores son para convertir los valores del dudv map a positivo
    
    float2 distortion1 = (dudvMap.Sample(colorSampler, float2(pix.tex0.x + paddingLight, pix.tex0.y)).rg * 2.0 - 1.0) * waveStrenght;
       
    float2 distortion2 = (dudvMap.Sample(colorSampler, float2(-pix.tex0.x + paddingLight, pix.tex0.y + paddingLight)).rg * 2.0 - 1.0) * waveStrenght;

    //un mapa de DUDV que se superpone con el mismo pero uno en negativo, para que de el efecto de movimiento
    
    float2 totalDistortion = distortion1 + distortion2;
    
    reflectTexCoords += totalDistortion;
    reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999);
    reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999, -0.001);
    
    float4 finalColor = textureColor.Sample(colorSampler, reflectTexCoords);
    
    //APORTE AMBIENTAL
    float4 LuzAmbiental = { 1.0, 1.0, 1.0, 1.0 };
    float FA = FAA;
    float4 AportAmb = LuzAmbiental * FA;
    
    finalColor.a = 0.8;
    
    return finalColor * (AportAmb);
		
}