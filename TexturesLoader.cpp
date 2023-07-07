#include "TexturesLoader.h"

typedef std::pair<int, std::shared_ptr<Texture>> TextureIndexPair;

TexturesLoader& TexturesLoader::GetInstance() {
	static TexturesLoader& instance = TexturesLoader();
	return instance;
}

void TexturesLoader::Load(std::list<TextureInfo> const textures) {
	for (auto textureInfo : textures) {
		
		auto surface = std::make_shared<Tmpl8::Surface>
			((char*)textureInfo.path.c_str());

		auto texture = std::make_shared<Texture>(
			surface, 
			TextureInfo(textureInfo));


		m_Textures.insert(TextureIndexPair(
			textureInfo.index,
			texture
		));
	}
}
void TexturesLoader::GetTexture(
	int index, 
	Texture& const out) {
	
	auto texture = *m_Textures[index].get();
	
	out = texture;
}