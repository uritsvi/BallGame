#pragma once

#include <list>
#include <string>
#include <unordered_map>
#include <memory>

#include "template.h"
#include "surface.h"

struct TextureInfo{
	TextureInfo() = default;

	TextureInfo(
		std::string path, 
		int index,
		bool useAnimation,
		int numOfFrames = 1,
		int animationInterval = 0) {
		
		this->path = path;
		this->index = index;
		this->numOfFrames = numOfFrames;
		this->animationInterval = animationInterval;
		this->useAnimation = useAnimation;
	}

	std::string path;
	int index;

	int numOfFrames;
	int animationInterval;
	bool useAnimation;
};

struct Texture{
	Texture() = default;

	Texture(
		std::shared_ptr<Tmpl8::Surface> surface, 
		TextureInfo& const info) {
		
		this->surface = surface;
		this->info = std::make_shared<TextureInfo>(TextureInfo(
			info.path, 
			info.index, 
			info.useAnimation, 
			info.numOfFrames, 
			info.animationInterval));
	}

	std::shared_ptr<Tmpl8::Surface> surface;
	std::shared_ptr<TextureInfo> info;
};

class TexturesLoader
{

public:
	static TexturesLoader& GetInstance();

	void Load(std::list<TextureInfo> const textures);

	void GetTexture(
		int index, 
		Texture& const out);

private:
	std::unordered_map<int, std::shared_ptr<Texture>> m_Textures;
};

