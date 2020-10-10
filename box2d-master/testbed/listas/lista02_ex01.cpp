#include "test.h"

class Lista2ex01 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	Lista2ex01() {
		// Aqui no construtor você inicializa a cena
		createBox(b2Vec2(-5.0f, -0.5f), b2Vec2(42.5f, 1.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);
		createBox(b2Vec2(-5.0f, 40.0f), b2Vec2(42.5f, 1.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);

		createBox(b2Vec2(-45.0f, 20.0f), b2Vec2(1.5f, 22.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);
		createBox(b2Vec2( 35.0f, 20.0f), b2Vec2(1.5f, 22.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);


		for (int y = 10; y > 0; y--) {
			selected = createBox(b2Vec2((y * 5.0f) - 26.0, 5), b2Vec2(0.6f, 5.0f), 1.0f, 1.0f, 0.0f);
		}

		m_world->SetGravity(b2Vec2(0, -10));
		applyingForce = true;
		force.SetZero();
		b2Vec2 localPoint = b2Vec2(-0.5, 1.0);
		globalPoint = b2Vec2(selected->GetWorldPoint(localPoint) + b2Vec2(0, 4.0f));

	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		processInputs();

		force.Normalize();
		force *= 5;

		g_debugDraw.DrawPoint(globalPoint, 5, b2Color(1.0, 1.0, 0.0));
		

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "No inicio uma força é aplicada na parte superior do primeiro bloco.");
		m_textLine += 15;
	}


	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padrão de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new Lista2ex01;
	}


	//Para interagir com teclado
	void Keyboard(int key) override  //esse cabe�alho n�o mudam! :)
	{
		switch (key)
		{
		case GLFW_KEY_F:
			applyingForce = true;
			break;

		case GLFW_KEY_N:
			do
			{
				if (selected->GetNext() != NULL)
				{
					selected = selected->GetNext();
				}
				else selected = m_world->GetBodyList();
			} while (selected->GetType() != b2_dynamicBody);
			break;
		}
	}



	b2Body* createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);
	void processInputs();

	//Algumas fun��es matem�ticas
	b2Vec2 getVectorComponents(float length, float angle);
	float degreesToRadians(float angle);
	float radiansToDegrees(float angle);


protected:
	b2Body* selected;
	bool applyingForce;
	b2Vec2 force;
	b2Vec2 globalPoint;

};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("__Fisica para Jogos", "Lista2ex01", Lista2ex01::Create);

b2Body* Lista2ex01::createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type)
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

void Lista2ex01::processInputs()
{
	if (applyingForce)
	{
		force = getVectorComponents(1000, 45);
		//selected->ApplyForceToCenter(force, true);

		//Para aplicar for�a a um ponto 
		selected->ApplyForce(force, globalPoint, true);

		applyingForce = false;
	}
}

b2Vec2 Lista2ex01::getVectorComponents(float length, float angle)
{
	b2Vec2 v;
	v.x = length * cos(degreesToRadians(angle));
	v.y = length * sin(degreesToRadians(angle));
	return v;
}

float Lista2ex01::degreesToRadians(float angle)
{
	return  angle * b2_pi / 180.0;
}

float Lista2ex01::radiansToDegrees(float angle)
{
	return angle * 180 / b2_pi;
}


