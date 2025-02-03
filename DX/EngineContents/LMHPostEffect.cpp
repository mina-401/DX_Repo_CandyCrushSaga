#include "PreCompile.h"
#include "LMHPostEffect.h"
#include <EngineCore/EngineCore.h>

ULMHPostEffect::ULMHPostEffect()
{
}

ULMHPostEffect::~ULMHPostEffect()
{
}
void ULMHPostEffect::Init()
{
	UPostEffect::Init();
	// ����Ʈ ����Ʈ�� ������ ���� Ÿ���� �����ϴ� ������ �����Ѵ�.
	CopyTarget = std::make_shared<UEngineRenderTarget>();
	CopyTarget->CreateTarget(UEngineCore::GetScreenScale());

	// Renderer���� ������� ���������� 

	RenderUnit.SetMesh("FullRect");
	RenderUnit.SetMaterial("LMHCustomPostEffect");


}

void ULMHPostEffect::Effect(UEngineCamera* _Camera, float _DeltaTime)
{
	UPostEffect::Effect(_Camera, _DeltaTime);
	// ���� Ÿ���� Copy�մϴ�.
	ResultTarget->CopyTo(CopyTarget);
	// ����Ʈ Ÿ���� ������ ����� �Ǿ���.
	ResultTarget->Setting();
	// ����Ʈ Ÿ���� ������ ����� �Ǿ���.
	RenderUnit.Render(_Camera, _DeltaTime);

}
