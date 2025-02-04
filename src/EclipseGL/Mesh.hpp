#pragma once
#include <glad/glad.h>
#include <EclipseUtils/Defines.hpp>
#include <vector>

namespace e {
	class mesh {
	private:
		et::u32 VAO;
		et::u32 VBO;
		et::u32 EBO;
		et::u32 indexCount;
	public:
		mesh(const std::vector<float>& vertices, const std::vector<et::u32>& indices);
		void draw() const;
		~mesh();
	};
}