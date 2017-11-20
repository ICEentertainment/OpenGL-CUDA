#pragma once
#include <vector>
#include "scene.h"
class LineNode: public SceneNode {
public:
	//Constructor (Initialize) our node. 
	LineNode(std::vector<Point2>& points,const int position_loc) {
		
		vertex_count = points.size();

		//Create a certain # of buffers, for us its one, and assign ID.
		glGenBuffers(2, &vbo[0]);
		
		//First Bind the buffer to the ID then transfer our data to the buffer
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Point2),
			(GLvoid*)&points.front(), GL_STATIC_DRAW);

		//Create a VAO so are settings are easily remembered. 
		/*glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(position_loc);
		glVertexAttribPointer(position_loc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);*/
	}
	void launchKernel() {
		cudaGraphicsGLRegisterBuffer(&cuda_vbo, vbo[0], cudaGraphicsMapFlagsNone);
		
	}   

	virtual ~LineNode() {
		glDeleteBuffers(2, &vbo[0]);
	}

	// Update the buffers with the ID we already gen
	virtual void Update(SceneState& scene_state) {
		vertex_count = scene_state.mouseVertices.size();
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Point2),
			(GLvoid*)&scene_state.mouseVertices.front(), GL_STATIC_DRAW);
	}

	// Draw the lines
	virtual void Draw(SceneState& scene_state) {
		//glBindVertexArray(vao);
		
		glDrawArrays(GL_LINE_STRIP, 0, vertex_count);
		glBindVertexArray(0);
	}
protected:
	uint32_t vertex_count;    // Number of vertices
	GLuint vbo[2];               // VBO for positions
	//GLuint vao;               // Vertex Array Object
	cudaGraphicsResource* cuda_vbo; // Buffer for our cuda object
};