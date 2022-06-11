#pragma once

#include "Shader.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "TileIso.h"

// #include "Sprite.h" -- INCLUAM O DE VCS!

#include <vector>

#include<ctime>

#define ROWS 10
#define COLS 10

enum direcoes{PARADO, NORTE, SUL, LESTE, OESTE};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void initialize(GLuint width, GLuint height);
	void initializeGraphics();

	void addShader(string vFilename, string fFilename);

	//GLFW callbacks
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void resize(GLFWwindow* window, int width, int height);

	void update();
	void render();
	void run();
	void finish();


	// scene
	void setupScene();
	void setupCamera2D();
	int setupTexture(string filename, int& largura, int& altura, int& nroCanais); //apenas mostra como criar uma textura
private:
	
	//GFLW window
	GLFWwindow *window;

	//Array de programas de shader
	vector <Shader*> shaders;

	//scene attributes
	GLuint VAO;

	//Transformations - Model Matrix
	glm::mat4 model;

	//2D Camera - Projection matrix
	glm::mat4 projection;

	//Conjunto de tiles
	vector <TileIso> tileset;

	int map[ROWS][COLS];

	//Sprite personagem; -- INCLUAM O DE VCS
	glm::vec2 characterPos; //Posição no mundo
	int poslinha; //POS Y DO PERSONAGEM NO MAPA
	int poscoluna; //POS X DO PERSONAGEM NO MAPA

};

