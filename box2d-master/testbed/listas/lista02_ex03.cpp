#include "test.h"

class Lista2ex03 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	Lista2ex03() {
		// Aqui no construtor você inicializa a cena
		createBox(b2Vec2(-5.0f, -0.5f), b2Vec2(42.5f, 1.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);
		createBox(b2Vec2(-5.0f, 40.0f), b2Vec2(42.5f, 1.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);
		createBox(b2Vec2(-45.0f, 20.0f), b2Vec2(1.5f, 22.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);
		createBox(b2Vec2(35.0f, 20.0f), b2Vec2(1.5f, 22.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);


		createBox(b2Vec2(-5.0f, 8.0f), b2Vec2(10.5f, 0.1f), 1.0f, 1.0f, 0.0f, b2_staticBody);

		createBox(b2Vec2(15.0f, 14.0f), b2Vec2(10.5f, 0.1f), 1.0f, 1.0f, 0.0f, b2_staticBody);


		selected = createBox(b2Vec2(-15.0f, 15.0f), b2Vec2(0.8f, 1.6f), 0.5f, 0.2f, 0.0f);

		m_world->SetGravity(b2Vec2(0, -10));
		applyingForce = false;
		force.SetZero();
		b2Vec2 localPoint = b2Vec2(0.5f, -1.0);

	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		processInputs(angulo);

		force.Normalize();

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Aperte A,S,D e E para controlar a direcao do bloco.");
		m_textLine += 15;
	}


	static Test* Create()  
	{
		return new Lista2ex03;
	}


	//Para interagir com teclado
	void Keyboard(int key) override  //esse cabe�alho n�o mudam! :)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			angulo = 90;
			force = b2Vec2(0.0f, 1000.0f);
			applyingForce = true;
			break;
		case GLFW_KEY_DOWN:
			angulo = 270;
			force = b2Vec2(0.0f, 1000.0f);
			applyingForce = true;
			break;
		case GLFW_KEY_RIGHT:
			angulo = 0;
			force = b2Vec2(1000.0f, 0.0f);
			applyingForce = true;
			break;
		case GLFW_KEY_LEFT:
			angulo = 180;
			force = b2Vec2(1000.0f, 0.0f);
			applyingForce = true;
			break;



		case GLFW_KEY_W:
			angulo = 90;
			force = b2Vec2(0.0f, 1000.0f);
			applyingForce = true;
			break;
		case GLFW_KEY_S:
			angulo = 270;
			force = b2Vec2(0.0f, 1000.0f);
			applyingForce = true;
			break;
		case GLFW_KEY_D:
			angulo = 0;
			force = b2Vec2(1000.0f, 0.0f);
			applyingForce = true;
			break;
		case GLFW_KEY_A:
			angulo  = 180;
			force = b2Vec2(1000.0f, 0.0f);
			applyingForce = true;
			break;
		}
	}



	b2Body* createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);
	void processInputs(int angulo);

	//Algumas fun��es matem�ticas
	b2Vec2 getVectorComponents(float length, float angle);
	float degreesToRadians(float angle);
	float radiansToDegrees(float angle);


protected:
	b2Body* selected;
	bool applyingForce;
	b2Vec2 force;
	int angulo;

};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "Lista2ex03", Lista2ex03::Create);

b2Body* Lista2ex03::createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type)
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

void Lista2ex03::processInputs(int angulo)
{
	if (applyingForce)
	{
		force = getVectorComponents(2000, angulo);
		selected->ApplyForceToCenter(force, true);

		applyingForce = false;
	}
}

b2Vec2 Lista2ex03::getVectorComponents(float length, float angle)
{
	b2Vec2 v;
	v.x = length * cos(degreesToRadians(angle));
	v.y = length * sin(degreesToRadians(angle));
	return v;
}

float Lista2ex03::degreesToRadians(float angle)
{
	return  angle * b2_pi / 180.0;
}

float Lista2ex03::radiansToDegrees(float angle)
{
	return angle * 180 / b2_pi;
}


