#pragma once

# include <Siv3D.hpp>

class LightBloom {
public:
	const RenderTexture gaussianA1, gaussianB1;
	const RenderTexture gaussianA4, gaussianB4;
	const RenderTexture gaussianA8, gaussianB8;
	const Size sceneSize;

	LightBloom(const Size& size = {1920,1080}) :sceneSize{ size },
		gaussianA1{ size }, gaussianB1{ size },
		gaussianA4{ size / 4 }, gaussianB4{ size / 4 },
		gaussianA8{ size / 8 }, gaussianB8{ size / 8 } {}

	void draw(float v)const {

		//Vec2 pos = { 0 + scroll.x,0 + scroll.y };

		//Vec2 pos = { 0 - scroll.x,0 - scroll.y };

		Vec2 pos = { 0,0 };

		//Print << U"scroll::" << scroll;

		Shader::GaussianBlur(gaussianA1, gaussianB1, gaussianA1);
		Shader::Downsample(gaussianA1, gaussianA4);
		Shader::GaussianBlur(gaussianA4, gaussianB4, gaussianA4);
		Shader::Downsample(gaussianA4, gaussianA8);
		Shader::GaussianBlur(gaussianA8, gaussianB8, gaussianA8);
		const ScopedRenderStates2D blend{ BlendState::Additive };
		gaussianA1.resized(sceneSize).draw(pos, ColorF{ 0.1 * v });
		gaussianA4.resized(sceneSize).draw(pos, ColorF{ 0.4 * v });
		gaussianA8.resized(sceneSize).draw(pos, ColorF{ 0.8 * v });
	}
};

class ScopedLightBloom {
public:
	ScopedLightBloom(const LightBloom& lightBloom) :target{ lightBloom.gaussianA1.clear(ColorF{ 0.0 }) } {}
	const ScopedRenderTarget2D target;
	const ScopedRenderStates2D blend{ BlendState::Additive };
};
