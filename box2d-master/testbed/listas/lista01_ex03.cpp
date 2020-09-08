#include "test.h"

class Lista1ex03 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	Lista1ex03() {
		// Aqui no construtor você inicializa a cena
		createBox(b2Vec2(0.0f, -2.0f), b2Vec2(25.0f, 2.0f), 1.0f, 0.5f, 0.5f, b2_staticBody);

			}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Aperte 'B' para criar uma caixa, 'C' para criar um circulo e 'L' para criar uma linha. Todos os atributos serao aleatorios.");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padrão de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new Lista1ex03;
	}

	void Keyboard(int key) override { 

		switch (key)
		{
		case GLFW_KEY_B:
			createBox(b2Vec2(rand() % 61 - 30, rand() % 51), b2Vec2(rand() % (59 + 1) / 10.0, rand() % (59 + 1) / 10.0), rand() % 11 / 10.0, rand() % 11 / 1.0, rand() % 11 / 10.0);
			break;
		case GLFW_KEY_C:
			createCircle(b2Vec2(rand() % 61 - 30, rand() % 51), rand() % (59 + 1) / 10.0, rand() % 11 / 10.0, rand() % 11 / 10.0, rand() % 11 / 10.0);
			break;
		case GLFW_KEY_L:
			createLine(b2Vec2(rand() % 97 - 48, rand() % 51-5), b2Vec2(rand() % 97 - 48, rand() % 51-5));
			break;
		}
	}



	b2Body* createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);

	b2Body* createCircle(b2Vec2 position, float radius, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);

	b2Body* createLine(b2Vec2 position1, b2Vec2 position2, b2BodyType type = b2_staticBody);

};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "Lista1ex03", Lista1ex03::Create);

b2Body* Lista1ex03::createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type)
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

b2Body* Lista1ex03::createCircle(b2Vec2 position, float radius, float density, float friction, float restitution, b2BodyType type)
{


	b2Body* newCircle;

	// definição dos atributos gerais do corpo rigido. tipo e posição

	b2BodyDef circleDef;
	circleDef.position = position;
	circleDef.type = type;


	// criação da forma do corpo
	b2CircleShape circleShape; //circulo
	circleShape.m_radius = radius;

	// definição da fixture 
	b2FixtureDef circleFix;
	circleFix.shape = &circleShape;
	circleFix.density = density;
	circleFix.friction = friction;
	circleFix.restitution = restitution;


	// criação do corpo rigido pelo mundo e da fixture pelo corpo rigido
	newCircle = m_world->CreateBody(&circleDef);
	newCircle->CreateFixture(&circleFix);



	return newCircle;

}

b2Body* Lista1ex03::createLine(b2Vec2 position1, b2Vec2 position2, b2BodyType type)
{
	b2Body* newLine;

	// definição dos atributos gerais do corpo rigido. tipo e posição

	b2BodyDef lineDef;
	lineDef.position.Set(0.0f, 0.0f);
	lineDef.type = type;



	// criação da forma do corpo
	b2EdgeShape lineShape; //caixa
	lineShape.SetTwoSided(position1, position2);

	newLine = m_world->CreateBody(&lineDef);
	newLine->CreateFixture(&lineShape, 0.0f);



	return newLine;
}

