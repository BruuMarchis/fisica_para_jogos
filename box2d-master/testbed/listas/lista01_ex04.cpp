#include "test.h"

class Lista1ex04 : public Test //você cria a sua classe derivada da classe base Test
{
public:

	float rest = 0.0f;

	Lista1ex04() {
		// Aqui no construtor você inicializa a cena
		createBox(b2Vec2(0.0f, -2.0f), b2Vec2(35.0f, 2.0f), 1.0f, 0.5f, 0.0f, b2_staticBody);



	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Aperte 'B' para criar uma caixa. A primeira caixa comeca com 0.0 de restituicao, ela vai aumentar ate a decima caixa ter 1.0 de restituicao.");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padrão de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new Lista1ex04;
	}

	void Keyboard(int key) override { //
		switch (key)
		{
		case GLFW_KEY_B:
			createBox(b2Vec2(0, 30.0), b2Vec2(1.0, 1.0), 1.0f, 0.5f, rest);
			break;
		}

		if (rest < 1.0) {
			rest += 0.1f;
		}


	}


	b2Body* createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);


};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "Lista1ex04", Lista1ex04::Create);

b2Body* Lista1ex04::createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type)
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

