#include <GL/glut.h>

// Pontos de desenho
#define POINTS_SPACESHIP 7
#define POINTS_ASTEROID 10

// Cenas
#define SCENE_MENU 0
#define SCENE_START 1
#define SCENE_GAME 2
#define SCENE_GAMEOVER 3
#define SCENE_WIN 4

// Valores de controle
#define ASTEROID_VELOCITY 0.010f
#define ASTEROID_RANGE_ANGLES 360

#define SPACESHIP_ACCELERATION 0.0001f
#define SPACESHIP_OFFSET_ANGLE 90
#define SPACESHIP_ANGLE_STEP 0.5
#define SPACESHIP_DESACCELERATION_FACTOR 1.003f

#define BULLET_SPEED 0.030f
#define BULLETS_MAXIMUM_QUANTITY 20
#define DELAY_FOR_SHOOT 0.3

typedef struct {
	float x;
	float y;
} Point;

typedef struct {
	bool enable;
	GLfloat angle;
	GLfloat Tx, Ty;
	GLfloat xStep, yStep;
	GLfloat minX, minY, maxX, maxY;
	int size = 1;

} Object_transformation;

typedef struct node {
	Object_transformation asteroid;
	struct node *left;
	struct node *right;
} ASTEROIDS_TREE;

// Variáveis de controle de tela

// Variáveis relacionadas a janela de visualização
GLfloat tx = 0;
GLfloat win = 25;
int range = 25;

// Variáveis que guardam a largura e altura da janela
GLfloat windowXmin, windowXmax;
GLfloat windowYmin, windowYmax;

// Controle de objetos na tela
Object_transformation *bullets = NULL;
int bulletsLength = 0;
float spaceshipShootTime = 0;

Object_transformation spaceship;
bool spaceshipWithAcceleration = false;

Point pointsNave[POINTS_SPACESHIP];
Point pointsAsteroid[POINTS_ASTEROID];

// Variáveis de controle
bool spaceshipCollision = false;
bool bulletColision = false;
int scene = SCENE_START;
int lives = 3;
bool winCondition = false;

int currentColor = 0;
float redValue = 1.0f;
float greenValue = 1.0f;
float blueValue = 1.0f;

bool isObjectInScreen(Object_transformation object) {
	return (
		object.Tx > -range && object.Tx < +range && 
		object.Ty > -range && object.Ty < +range
	);
}
