#pragma once

#include <vector>
#include "scene.h"

class PointNode: public SceneNode {
public:
	//Constructor (Initialize) our node. 
	PointNode(std::vector<Point2>& points, const int position_loc) {

		vertex_count = points.size();

		//Create a certain # of buffers, for us its one, and assign ID.
		glGenBuffers(1, &vbo);

		//First Bind the buffer to the ID then transfer our data to the buffer
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Point2),
			(GLvoid*)&points.front(), GL_STATIC_DRAW);
		
		//Create a VAO so are settings are easily remembered. 
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(position_loc);
		glVertexAttribPointer(position_loc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}


	virtual ~PointNode() {
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	/*
	* ReSize the Buffer with our new vertices
	*/
	virtual void Update(SceneState& scene_state) {
		vertex_count = scene_state.mouseVertices.size();
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Point2),
			(GLvoid*)&scene_state.mouseVertices.front(), GL_STATIC_DRAW);
	}

	virtual void Draw(SceneState& scene_state) {
		//Set Variables for Frag Shader
		glUniform1f(scene_state.SceneWidth_loc, scene_state.SceneWidth);
		glUniform1f(scene_state.SceneHeight_loc, scene_state.SceneHeight);

		glPointSize(scene_state.pointSize);
		//Load points vao and start drawing
		glBindVertexArray(vao);
		glDrawArrays(GL_POINTS, 0, vertex_count);
		glBindVertexArray(0);
	}
protected:
	uint32_t vertex_count;    // Number of vertices
	GLuint vbo;               // VBO for positions
	GLuint vao;               // Vertex Array Object
};
