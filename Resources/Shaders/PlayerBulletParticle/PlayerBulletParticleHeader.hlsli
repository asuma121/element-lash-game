cbuffer cbuff0 : register(b0)
{
	matrix mat;	//3D変換行列
	matrix matBillboard;	//ワールド行列
}

//頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 pos : POSITION;	//システム用頂点座標
	float scale : SCALE;	//スケール
    float frame : FRAME;	//タイマー
};

//ジオメトリシェーダからピクセルシェーダへの出力
struct GSOutput
{
	float4 svpos:SV_POSITION;	//システム用頂点座標
	float2 uv:TEXCOORD;	//uv値
    float frame : FRAME;	//タイマー
};