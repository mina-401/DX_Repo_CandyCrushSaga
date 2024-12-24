#include "PreCompile.h"
#include "EngineSprite.h"
#include "EngineBase/EngineDebug.h"

UEngineSprite::UEngineSprite()
{
}

UEngineSprite::~UEngineSprite()
{
}

std::shared_ptr<UEngineSprite> UEngineSprite::CreateSpriteToMeta(std::string_view _Name)
{
	std::shared_ptr<UEngineTexture> Tex = UEngineTexture::Find<UEngineTexture>(_Name);

	if (nullptr == Tex)
	{
		MSGASSERT("존재하지 않는 텍스처로 스프라이트를 만들수는 없습니다.");
		return nullptr;
	}

	std::shared_ptr<UEngineSprite> NewRes = std::make_shared<UEngineSprite>();
	PushRes<UEngineSprite>(NewRes, _Name, "");
	NewRes->Texture = Tex.get();


	// 파싱 문자열을 자르고 쪼개서 의미를 부여하는 것을 파싱이라고 합니다.
	// 문자가 일정 규칙으로 구성되어있다는 것을 파악하고 
	// 이걸 기반으로 한 언어들을 스트럭처드 언어라고 부른다.
	// 대표적으로 xml json 등등이 있다.

	UEnginePath Path = Tex->GetPath();
	std::string FileName = Path.GetFileName();
	FileName += ".meta";
	Path.MoveParent();
	Path.Append(FileName);

	UEngineFile File = Path;

	File.FileOpen("rt");

	std::string Text = File.GetAllFileText();

	std::vector<std::string> SpriteDataTexts;

	size_t StartPosition = 0;
	while (true)
	{
		size_t RectIndex = Text.find("rect:", StartPosition);
		size_t AligIndex = Text.find("alignment:", RectIndex);

		if (RectIndex == std::string::npos || AligIndex == std::string::npos)
		{
			break;
		}

		SpriteDataTexts.push_back(Text.substr(RectIndex, AligIndex - RectIndex));
		StartPosition = AligIndex;
	}

	FVector TexSize = Tex->GetTextureSize();

	std::vector<FSpriteData> TestData;

	for (size_t i = 0; i < SpriteDataTexts.size(); i++)
	{
		std::string Text = SpriteDataTexts[i];

		size_t Start = 0;

		FSpriteData SpriteData;

		{
			std::string Number = UEngineString::InterString(Text, "x:", "\n", Start);
			SpriteData.CuttingPos.X = static_cast<float>(atof(Number.c_str()));
		}

		{
			std::string Number = UEngineString::InterString(Text, "y:", "\n", Start);
			SpriteData.CuttingPos.Y = static_cast<float>(atof(Number.c_str()));
		}
		{
			std::string Number = UEngineString::InterString(Text, "width:", "\n", Start);
			SpriteData.CuttingSize.X = static_cast<float>(atof(Number.c_str()));
		}

		{
			std::string Number = UEngineString::InterString(Text, "height:", "\n", Start);
			SpriteData.CuttingSize.Y = static_cast<float>(atof(Number.c_str()));
		}

		SpriteData.CuttingPos.X /= TexSize.X;
		SpriteData.CuttingPos.Y /= TexSize.Y;
		SpriteData.CuttingSize.X /= TexSize.X;
		SpriteData.CuttingSize.Y /= TexSize.Y;


		TestData.push_back(SpriteData);
	}


	NewRes->SpriteDatas = TestData;

	return NewRes;

}


ID3D11ShaderResourceView* UEngineSprite::GetSRV()
{
	return Texture->GetSRV();
}