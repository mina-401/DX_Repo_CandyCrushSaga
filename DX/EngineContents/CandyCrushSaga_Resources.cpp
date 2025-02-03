#include "PreCompile.h"
#include "CandyCrushSaga.h"
#include <EngineCore/EngineGraphicDevice.h>
#include <EngineCore/EngineVertex.h>
#include <EngineCore/EngineIndexBuffer.h>
#include <EngineCore/Mesh.h>
#include <EngineCore/EngineBlend.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineFont.h>
#include <EnginePlatform/EngineSound.h>



void UCandyCrushSaga::CandyGSetting()
{

	{
		UEngineDirectory CurDir;
		CurDir.MoveParentToDirectory("ContentsShader");

		std::vector<UEngineFile> ShaderFiles = CurDir.GetAllFile(true, { ".fx", ".hlsl" });

		for (size_t i = 0; i < ShaderFiles.size(); i++)
		{
			UEngineShader::ReflectionCompile(ShaderFiles[i]);
		}
	}
	{
		/*UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Fonts");*/

		UEngineFont::Load("BrandonGrotesqueBold", "BrandonGrotesque-Bold");
	}
	//UEngineFont::Load("DX하늘구름 중간", "DX하늘구름 중간");
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("LMHCustomPostEffect");
		Mat->SetVertexShader("LMHCustomPostEffect.fx");
		Mat->SetPixelShader("LMHCustomPostEffect.fx");
		Mat->SetDepthStencilState("ALWAYS");

	}
}
