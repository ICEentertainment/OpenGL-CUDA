
#include <iostream>
#include <vector>

#include "scene.h"

// Root of the scene graph
SceneNode* SceneRoot;

// Scene state
SceneState MySceneState;

// Simple logging function
void logmsg(const char *message, ...) {
  // Open file if not already opened
  static FILE *lfile = NULL;
  if (lfile == NULL) {
    lfile = fopen("Module2.log", "w");
  }

  va_list arg;
  va_start(arg, message);
  vfprintf(lfile, message, arg);
  putc('\n', lfile);
  fflush(lfile);
  va_end(arg);
}

void reshape(int width, int height) {
  MySceneState.ortho[0]  = 2.0f / static_cast<float>(width);
  MySceneState.ortho[1]  = 0.0f;
  MySceneState.ortho[2]  = 0.0f;
  MySceneState.ortho[3]  = 0.0f;
  MySceneState.ortho[4]  = 0.0f;
  MySceneState.ortho[5] = -2.0f / static_cast<float>(height);
  MySceneState.ortho[6]  = 0.0f;
  MySceneState.ortho[7]  = 0.0f;
  MySceneState.ortho[8]  = 0.0f;
  MySceneState.ortho[9]  = 0.0f;
  MySceneState.ortho[10] = 1.0f;
  MySceneState.ortho[11] = 0.0f;
  MySceneState.ortho[12] = -1.0f;
  MySceneState.ortho[13] = 1.0f;
  MySceneState.ortho[14] = 0.0f;
  MySceneState.ortho[15] = 1.0f;

  // Update the viewport
  glViewport(0, 0, width, height);
}

/**
 * Create the scene.
 */
void CreateScene() {
	SceneRoot = new SceneNode();

	//Create buffers and properties
	PointNode* points = new PointNode(MySceneState.mouseVertices, MySceneState.position_loc);
	LineNode* lines = new LineNode(MySceneState.mouseVertices, MySceneState.position_loc);
	
	//Create the tree
	SceneRoot->AddChild(lines);
	SceneRoot->AddChild(points);
	
}
/*
 * Update the scene
 */
void Update() {
	SceneRoot->Update(MySceneState);
}
/**
* Keyboard CallBack
*/
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		// Escape key
	case 27:
		exit(0);
		break;
	case 49:
		MySceneState.lineWidth = 1;
		MySceneState.pointSize = MySceneState.lineWidth*2;
		Update();
		break;
	case 50:
		MySceneState.lineWidth = 2;
		MySceneState.pointSize = MySceneState.lineWidth * 2;
		Update();
		break;
	case 51:
		MySceneState.lineWidth = 3;
		MySceneState.pointSize = MySceneState.lineWidth * 2;
		Update();
		break;
	case 52:
		MySceneState.lineWidth = 4;
		MySceneState.pointSize = MySceneState.lineWidth * 2;
		Update();
		break;
	case 53:
		MySceneState.lineWidth = 5;
		MySceneState.pointSize = MySceneState.lineWidth * 2;
		Update();
		break;
	case 54:
		MySceneState.lineWidth = 6;
		MySceneState.pointSize = MySceneState.lineWidth * 2;
		Update();
		break;
	case 55:
		MySceneState.lineWidth = 7;
		MySceneState.pointSize = MySceneState.lineWidth * 2;
		Update();
		break;
	case 56:
		MySceneState.lineWidth = 8;
		MySceneState.pointSize = MySceneState.lineWidth * 2;
		Update();
		break;
	case 57:
		MySceneState.lineWidth = 9;
		MySceneState.pointSize = MySceneState.lineWidth * 2;
		Update();
		break;
	default:
		break;
	}
}
/**
* Mouse Callback
*/
void mouse(int button, int state, int x, int y) {
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		MySceneState.mouseVertices.push_back(Point2(x, y));
		Update();
	default:
		break;
	}
}
/*
* Redraw last state of the scene every call
*/
void display(void) {
	//Clearing the screen
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Drawing the last state of the screen
	SceneRoot->Draw(MySceneState);
	CheckError("RedrawScreen");

	//Swap buffers
	glutSwapBuffers();
}

/**
 * Main - entry point for GetStarted GLUT application.
 */
int main(int argc, char** argv) {
  std::cout << "Keyboard Controls:" << std::endl;
  std::cout << "1-9 : Alter line width and point size" << std::endl;
  std::cout << "ESC - Exit program" << std::endl;

  // Initialize free GLUT
  glutInit(&argc,argv);
  
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  // Initialize display mode and window
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(800, 600);
 
  // Create the window and register callback methods
  glutCreateWindow("\"Hello\" from Joshua Brooks");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);

  // Initialize Open 3.2 core profile
  if (gl3wInit()) {
    fprintf(stderr, "gl3wInit: failed to initialize OpenGL\n");
    return -1;
  }
  if (!gl3wIsSupported(3, 2)) {
    fprintf(stderr, "OpenGL 3.2 not supported\n");
    return -1;
  }
  printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

  glClearColor(1.0, 1.0, 1.0, 1.0);

  // Create the scene
  CreateScene();
  CheckError("CreateScene");

  // Main GLUT loop
  glutMainLoop();
  return 0;
}