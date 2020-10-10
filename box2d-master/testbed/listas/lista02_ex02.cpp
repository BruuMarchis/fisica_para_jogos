#include "test.h"

class Lista2ex02 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	Lista2ex02() {
		// Aqui no construtor você inicializa a cena
		createBox(b2Vec2(-5.0f, -0.5f), b2Vec2(42.5f, 1.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);
		createBox(b2Vec2(-5.0f, 40.0f), b2Vec2(42.5f, 1.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);

		createBox(b2Vec2(-45.0f, 20.0f), b2Vec2(1.5f, 22.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);
		selected = createBox(b2Vec2(35.0f, 20.0f), b2Vec2(1.5f, 22.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);



		m_world->SetGravity(b2Vec2(0, -10));
		applyingForce = false;
		force.SetZero();
		globalPoint = b2Vec2(0, 10);
		angulo = 45;
		intencidade = 5000;

	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		processInputs(angulo, intencidade);

		force.Normalize();
		force *= 5;


		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Aperte M para criar um projetil. Seu angulo inicial e de 45 graus, aperte W(+) e S(-) para mudar o valor do grau em 5. Aperte A(-) e D(+) para mudar a intencidade.");
		m_textLine += 15;
	}


	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padrão de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new Lista2ex02;
	}


	//Para interagir com teclado
	void Keyboard(int key) override  //esse cabe�alho n�o mudam! :)
	{
		switch (key)
		{
		case GLFW_KEY_SPACE:
			selected = createCircle(b2Vec2(-35.0f, 2.0f), 1.0f, 1.0, 0.5, 0.5);
			applyingForce = true;
			break;
		case GLFW_KEY_UP:
			angulo += 5;
			if (angulo >= 360) {
				angulo = 0;
			}
			break;
		case GLFW_KEY_DOWN:
			angulo -= 5;
			if (angulo < 0) {
				angulo = 360 + angulo;
			}
			break;
		case GLFW_KEY_RIGHT:
			intencidade += 1000;
			if (intencidade >= 15000) {
				intencidade = 25000;
			}
			break;
		case GLFW_KEY_LEFT:
			intencidade -= 1000;
			if (intencidade < 1000) {
				intencidade = 1000;
			}
			break;


		case GLFW_KEY_M:
			selected = createCircle(b2Vec2(-35.0f, 2.0f), 1.0f, 1.0, 0.5, 0.5);
			applyingForce = true;
			break;
		case GLFW_KEY_W:
			angulo += 5;
			if (angulo >= 360) {
				angulo = 0;
			}
			break;
		case GLFW_KEY_S:
			angulo -= 5;
			if (angulo < 0) {
				angulo = 360 + angulo;
			}
			break;
		case GLFW_KEY_D:
			intencidade += 1000;
			if (intencidade >= 15000) {
				intencidade = 25000;
			}
			break;
		case GLFW_KEY_A:
			intencidade -= 1000;
			if (intencidade < 1000) {
				intencidade = 1000;
			}
			break;

		}
	}



	b2Body* createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);
	b2Body* createCircle(b2Vec2 position, float radius, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);
	void processInputs(int angulo, int intencidade);

	//Algumas fun��es matem�ticas
	b2Vec2 getVectorComponents(float length, float angle);
	float degreesToRadians(float angle);
	float radiansToDegrees(float angle);


protected:
	b2Body* selected;
	bool applyingForce;
	b2Vec2 force;
	b2Vec2 globalPoint;
	int angulo, intencidade;

};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("__Fisica para Jogos", "Lista2ex02", Lista2ex02::Create);

b2Body* Lista2ex02::createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type)
{
	b2Body* newBox;

	// definição dos atributos gerais do corpo rigido. tipo e posição

	b2BodyDef boxDef;
	boxDef.position = position;
	boxDef.type = type;


	// criação da forma do corpo
	b2PolygonShape boxShape; //caixa
	boxShape.SetAsBox(dimention.x, dimention.y);

	// definição da fixture 
	b2FixtureDef boxFix;
	boxFix.shape = &boxShape;
	boxFix.density = density;
	boxFix.friction = friction;
	boxFix.restitution = restitution;


	// criação do corpo rigido pelo mundo e da fixture pelo corpo rigido
	newBox = m_world->CreateBody(&boxDef);
	newBox->CreateFixture(&boxFix);



	return newBox;
}

b2Body* Lista2ex02::createCircle(b2Vec2 pos, float radius, float density, float friction, float restitution, b2BodyType type)
{
	b2Body* newCircle;

	//Defini��o dos atributos gerais do corpo r�gido
	b2BodyDef circleDef;
	circleDef.position = pos;
	circleDef.type = type;

	//Defini��o da forma do corpo*
	b2CircleShape circleShape;
	circleShape.m_radius = radius;

	//Defini��o da fixture
	b2FixtureDef circleFix;
	circleFix.shape = &circleShape;
	circleFix.density = density;
	circleFix.friction = friction;
	circleFix.restitution = restitution;

	//Cria��o do corpo r�gido pelo mundo e da fixture pelo corpo r�gido
	newCircle = m_world->CreateBody(&circleDef);
	newCircle->CreateFixture(&circleFix);

	return newCircle;
}

void Lista2ex02::processInputs(int angulo, int intencidade)
{
	if (applyingForce)
	{
		force = getVectorComponents(intencidade, angulo);
		selected->ApplyForceToCenter(force, true);

		//Para aplicar for�a a um ponto 
		//selected->ApplyForce(force, globalPoint, true);

		applyingForce = false;
	}
}

b2Vec2 Lista2ex02::getVectorComponents(float length, float angle)
{
	b2Vec2 v;
	v.x = length * cos(degreesToRadians(angle));
	v.y = length * sin(degreesToRadians(angle));
	return v;
}

float Lista2ex02::degreesToRadians(float angle)
{
	return  angle * b2_pi / 180.0;
}

float Lista2ex02::radiansToDegrees(float angle)
{
	return angle * 180 / b2_pi;
}


