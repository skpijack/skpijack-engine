#include "Mesh.hpp"

using namespace e;

mesh::mesh(const std::vector<float>& vertices, const std::vector<et::u32>& indices) {
	// Get array size
	indexCount = indices.size();
	// Argument count defines the count of number of points on the vertices array for single time argument buffer
	// for ex. // Vertex 1, 2, 3, // Normals 4, 5, 6 so total is 6 for each line
	et::u32 argumentCount = 6; 

	// Generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// Upload vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	// Upload index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(et::u32), indices.data(), GL_STATIC_DRAW);

	// Position Attributes
	// (0 -> 2) vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, argumentCount * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal Attributes
	// (3->5) normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, argumentCount * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind
}

void mesh::draw() const {
	// Bind, draw, unbindd
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

mesh::~mesh() {
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}