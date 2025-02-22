#pragma once
#include "EngineResources.h"
#include "EngineTexture.h"
#include "RenderUnit.h"
#include "EngineGraphicDevice.h"

class UPostEffect
{
	friend class UEngineRenderTarget;

public:
	URenderUnit RenderUnit;
	// 내가 준 효과가 출력될 결과물이 될 타겟
	UEngineRenderTarget* ResultTarget;

	bool IsActive = true;

protected:
	ENGINEAPI virtual void Init() = 0
	{

	}
	ENGINEAPI virtual void Effect(UEngineCamera* Camera, float _DeltaTime) = 0
	{

	}
private:
};

// 설명 :
class UEngineRenderTarget : public UEngineResources
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineRenderTarget();
	ENGINEAPI ~UEngineRenderTarget();

	// delete Function
	UEngineRenderTarget(const UEngineRenderTarget& _Other) = delete;
	UEngineRenderTarget(UEngineRenderTarget&& _Other) noexcept = delete;
	UEngineRenderTarget& operator=(const UEngineRenderTarget& _Other) = delete;
	UEngineRenderTarget& operator=(UEngineRenderTarget&& _Other) noexcept = delete;



	// DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT 색깔 범위의 최대 
	// 그래픽스 효과중에 색깔 범위를 기본으로 하는 효과들도 있다.
	// 색깔 범위를 HDR // High Dynamic Range => 색상의 표현범위가 더 넓게 만드는 효과를 HDR
	// 아니요 모니터도 hdr이고 거기에서 hdr 효과를 적용시킨 쉐이더를 만들어야 hdr를 제대로 느낄수 있습니다.
	// 어느쪽이든 제대로 조건을 달성하지 못하면 짭hdr
	ENGINEAPI void CreateTarget(float4 _Scale, float4 _ClearColor = float4::NONE, DXGI_FORMAT _Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);

	// 백버퍼는 그냥 텍스처가 스왑체인에서 준비되어 있기 때문에 그냥 ID3D11Texture2D 받아서 만드는 것이라면
	ENGINEAPI void CreateTarget(Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture2D);

	// 뎁스텍스처도 이제부터 랜더타겟이 관리합니다.
	ENGINEAPI void CreateDepth(int _Index = 0);

	ENGINEAPI void Clear();

	ENGINEAPI void Setting();

	ENGINEAPI void SetClearColor(float4 _ClearColor)
	{
		ClearColor = _ClearColor;
	}

	// 어던 랜더타겟의 요소를 다른 랜더타겟에 복사한다.
	// 지우고 복사한다.
	ENGINEAPI void CopyTo(std::shared_ptr<UEngineRenderTarget> _Target);


	ENGINEAPI void MergeTo(std::shared_ptr<UEngineRenderTarget> _Target);

	ENGINEAPI void CopyTo(UEngineRenderTarget* _Target);
	ENGINEAPI void MergeTo(UEngineRenderTarget* _Target);

	UEngineTexture* GetTexture(int _Index = 0)
	{
		return ArrTexture[_Index].get();
	}

protected:

private:
	float4 ClearColor = float4(0.0f, 0.0f, 1.0f, 1.0f);

	std::vector<std::shared_ptr<class UEngineTexture>> ArrTexture;
	std::vector<ID3D11RenderTargetView*> ArrRTVs;
	std::vector<ID3D11ShaderResourceView*> ArrSRVs;

	std::shared_ptr<class UEngineTexture> DepthTexture;

	// 타겟마다 가지게 하겠습니다.
	// 이게 낭비인거 같은데 그냥하겠습니다.
	URenderUnit TargetUnit;

	//// 포스트 이펙트 부분
public:
	template<typename EffectType>
	void AddEffect()
	{
		std::shared_ptr<EffectType> NewEffect = std::make_shared<EffectType>();

		std::shared_ptr<UPostEffect> PostEffect = std::dynamic_pointer_cast<UPostEffect>(NewEffect);

		PostEffect->ResultTarget = this;
		PostEffect->Init();
		PosEffects.push_back(NewEffect);
	}

	void Effect(UEngineCamera* _Camera, float _DeltaTime);
	std::shared_ptr<UPostEffect> GetPostEffect(int _Index)
	{
		return PosEffects[_Index];
	}

private:
	std::vector<std::shared_ptr<UPostEffect>> PosEffects;
};

