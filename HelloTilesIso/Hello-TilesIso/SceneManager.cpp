#include "SceneManager.h"

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static GLuint width, height;
static int dir;

SceneManager::SceneManager()
{
	srand(time(0));
}

SceneManager::~SceneManager()
{
}

void SceneManager::initialize(GLuint w, GLuint h)
{
	width = w;
	height = h;
	
	// GLFW - GLEW - OPENGL general setup -- TODO: config file
	initializeGraphics();

}

void SceneManager::initializeGraphics()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(width, height, "Hello Transform", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	//Setando a callback de redimensionamento da janela
	glfwSetWindowSizeCallback(window, resize);
	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Build and compile our shader program
	addShader("../shaders/transformations.vs", "../shaders/transformations.frag"); //0
	addShader("../shaders/sprite.vs", "../shaders/sprite.frag"); //1

	//setup the scene -- LEMBRANDO QUE A DESCRIÇÃO DE UMA CENA PODE VIR DE ARQUIVO(S) DE 
	// CONFIGURAÇÃO
	setupScene();

	resized = true; //para entrar no setup da câmera na 1a vez
	
	setupCamera2D();

}

void SceneManager::addShader(string vFilename, string fFilename)
{
	Shader *shader = new Shader (vFilename.c_str(), fFilename.c_str());
	shaders.push_back(shader);
}


void SceneManager::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}

	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
		{
			dir = NORTE;
		}
		if (key == GLFW_KEY_S)
		{
			dir = SUL;
		}
		if (key == GLFW_KEY_A)
		{
			dir = OESTE;
		}
		if (key == GLFW_KEY_D)
		{
			dir = LESTE;
		}
	}
}

void SceneManager::resize(GLFWwindow * window, int w, int h)
{
	width = w;
	height = h;
	resized = true;

	// Define the viewport dimensions
	glViewport(0, 0, width, height);
}


void SceneManager::update()
{
	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (dir == NORTE)
	{
		//atualiza posição do mapa onde personagem irá,
		//conforme tabela de navegação do diamond
	}

	if (dir == SUL)
	{
		//atualiza posição do mapa onde personagem irá,
		//conforme tabela de navegação do diamond
	}

	if (dir == LESTE)
	{
		//atualiza posição do mapa onde personagem irá,
		//conforme tabela de navegação do diamond
		
	}

	if (dir == OESTE)
	{
		//atualiza posição do mapa onde personagem irá,
		//conforme tabela de navegação do diamond
		
	}

	//Validações pro personagem não sair do mapa
	if (poslinha < 0)
	{
		poslinha = 0;
	}
	if (poscoluna < 0)
	{
		poscoluna = 0;
	}
	if (poslinha > 9)
	{
		poslinha = 9;
	}
	if (poscoluna > 9)
	{
		poscoluna = 9;
	}
}

void SceneManager::render()
{
	// Clear the colorbuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	if (resized) //se houve redimensionamento na janela, redefine a projection matrix
	{
		setupCamera2D();
		resized = false;
	}

	shaders[0]->Use();

	float xi = 368; //metade da largura da tela - metade da largura do tile
	float yi = 100;

	for (int i = 0; i < ROWS; i++) //linhas
	{
		for (int j = 0; j < COLS; j++) //colunas
		{
			float x = xi + (j - i) * tileset[0].getWidth() / 2.0;
			float y = yi + (j + i) * tileset[0].getHeight() / 2.0;
			model = glm::mat4();
			model = glm::translate(model, glm::vec3(x, y, 0.0));
			tileset[map[i][j]].draw(model);
		}	
	}
	float x = xi + (poscoluna - poslinha) * tileset[0].getWidth() / 2.0;
	float y = yi + (poscoluna + poslinha) * tileset[0].getHeight() / 2.0;
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(x, y, 0.0));

	tileset[7].draw(model);

	//Desenha o personagem
}

void SceneManager::run()
{
	//GAME LOOP
	while (!glfwWindowShouldClose(window))
	{
		
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		//Update method(s)
		update();

		//Render scene
		render();
		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
}

void SceneManager::finish()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}


glm::vec4 normalizaRGB(glm::vec4 byteColor)
{
	glm::vec4 normColor(byteColor.r / 255.0, byteColor.g / 255.0, byteColor.b / 255.0, byteColor.a / 255.0);
	return normColor;
}


void SceneManager::setupScene()
{
	TileIso tile;
	glm::vec4 corDoTile;

	tile.setShader(shaders[0]);

	//Tile 0
	corDoTile.r = 47; corDoTile.g = 117; corDoTile.b = 181; corDoTile.a = 255;//Aqui coloca a cor RGBA 
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	//Tile 1
	corDoTile.r = 0; corDoTile.g = 176; corDoTile.b = 80; corDoTile.a = 255;//Aqui coloca a cor RGBA 
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	//Tile 2
	corDoTile.r = 191; corDoTile.g = 143; corDoTile.b = 0; corDoTile.a = 255;//Aqui coloca a cor RGBA 
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	//Tile 3
	corDoTile.r = 128; corDoTile.g = 96; corDoTile.b = 0; corDoTile.a = 255;//Aqui coloca a cor RGBA 
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	//Tile 4
	corDoTile.r = 191; corDoTile.g = 191; corDoTile.b = 191; corDoTile.a = 255;//Aqui coloca a cor RGBA 
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	//Tile 5
	corDoTile.r = 198; corDoTile.g = 89; corDoTile.b = 17; corDoTile.a = 255;//Aqui coloca a cor RGBA 
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	//Tile 6
	corDoTile.r = 31; corDoTile.g = 78; corDoTile.b = 120; corDoTile.a = 255;//Aqui coloca a cor RGBA 
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	//Tile 7
	corDoTile.r = 0; corDoTile.g = 0; corDoTile.b = 0; corDoTile.a = 255;//Aqui coloca a cor RGBA 
	tile.setCor(normalizaRGB(corDoTile));
	tile.inicializar(32, 64);
	tileset.push_back(tile);

	// Um mapa predefinido
	int mapaauxiliar[10][10] =
	{
		6,	6,	6,	6,	0,	3,	3,	3,	3,	2,
		0,	0,	0,	0,	0,	3,	3,	3,	3,	2,
		1,	1,	0,	0,	0,	0,	3,	3,	3,	2,
		1,	1,	2,	2,	0,	0,	4,	4,	4,	2,
		1,	1,	2,	2,	0,	0,	4,	4,	4,	2,
		1,	1,	2,	2,	2,	4,	4,	4,	4,	2,
		1,	1,	2,	2,	2,	4,	4,	4,	4,	2,
		1,	1,	0,	0,	0,	4,	4,	5,	5,	5,
		1,	1,	2,	2,	0,	4,	4,	5,	5,	5,
		3,	3,	6,	6,	6,	4,	4,	5,	5,	5
		
	};

	// Não está sendo usado, mas para controle de onde o personagem pode se mover
	int mapcaminhavel[10][10] =
	{
		0,	0,	0,	0,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,  1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
		1,	1,	0,	0,	0,	1,	1,	1,	1,	1

	};

	//Copiando o mapa predefinido
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			map[i][j] = mapaauxiliar[i][j]; //sorteia os índices 0 ou 1
		}
	}

	//Inicializa o personagem .....
	//...............
	
	//Inicializando pos do personagem
	poslinha = 0;
	poscoluna = 0;
	dir = PARADO;


}

void SceneManager::setupCamera2D()
{
	glViewport(0, 0, width, height);

	//Setando o tamanho da janela do mundo
	float xMin = 0.0, xMax = 800, yMin = 600, yMax = 0.0, zNear = -1.0, zFar = 1.0;
	projection = glm::ortho(xMin, xMax, yMin, yMax, zNear, zFar);

	// Passando para os shaders que a usam
	shaders[0]->Use();
	GLint projLoc = glGetUniformLocation(shaders[0]->ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	shaders[1]->Use();
	projLoc = glGetUniformLocation(shaders[1]->ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

int SceneManager::setupTexture(string filename, int &largura, int &altura, int &nroCanais)
{
	//Texture index
	unsigned int texture;

	// load and create a texture 
	// -------------------------
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	
	cout << "Nro de canais: " << nrChannels << endl;
	cout << "largura x altura: " << width << " x " << height << endl;

	if (data)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		altura = height;
		largura = width;
		nroCanais = nrChannels;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	glActiveTexture(GL_TEXTURE0);

	//Talvez eu desloque isso depois
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return texture;
}
