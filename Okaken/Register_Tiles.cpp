#include"Game_Manager.hpp"

void Game_Manager::register_tiles(const String& name,const FilePathView path, const Size& regionSize, int32 xCount, int32 yCount) {

	const std::shared_ptr<Image> image = std::make_shared<Image>(path);

	for (int32 y = 0; y < yCount; ++y)
	{
		for (int32 x = 0; x < xCount; ++x)
		{
			const Rect region{ (x * regionSize.x), (y * regionSize.y), regionSize };

			std::unique_ptr<TextureAssetData> assetData = std::make_unique<TextureAssetData>();
			assetData->onLoad = [image, region](TextureAssetData& asset, const String&)
			{
				asset.texture = Texture{ image->clipped(region) };
				return static_cast<bool>(asset.texture);
			};

			const int32 index = (x + y * xCount);

			String image_name = name + U"_{}"_fmt(index);

			TextureAsset::Register(image_name, std::move(assetData));
			TextureAsset::Load(image_name);
		}
	}
}
