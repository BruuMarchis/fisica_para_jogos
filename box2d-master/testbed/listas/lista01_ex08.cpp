#include "test.h"

class Lista1ex08 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	Lista1ex08() {
		// Aqui no construtor você inicializa a cena

		b2Body* body = nullptr;

		b2Body * newBox;
		b2BodyDef boxDef;
		boxDef.position = b2Vec2(0.0f, -2.0f);
		boxDef.type = b2_staticBody;
		b2PolygonShape boxShape;
		boxShape.SetAsBox(25.0f, 2.0f);
		b2FixtureDef boxFix;
		boxFix.shape = &boxShape;
		boxFix.density = 1.0f;
		boxFix.friction = 0.5f;
		boxFix.restitution = 0.5f;
		newBox = m_world->CreateBody(&boxDef);
		newBox->CreateFixture(&boxFix);

		b2FixtureDef *fixs[9];

		b2BodyDef poliDef;

		b2Vec2 *pontos[9];

		int cont[]{4, 4, 4, 4, 4, 4, 8, 3, 3};

		pontos[0] = new b2Vec2[4]{ b2Vec2(0.0, 25.0), b2Vec2( 12.0, 24.0), b2Vec2(0.0, 25.1), b2Vec2( 12.0, 24.1) };
		pontos[1] = new b2Vec2[4]{ b2Vec2(0.0, 25.0), b2Vec2( 12.0, 28.0), b2Vec2(0.0, 25.1), b2Vec2( 12.0, 28.1) };
		pontos[2] = new b2Vec2[4]{ b2Vec2(0.0, 25.0), b2Vec2( 12.0, 20.0), b2Vec2(0.0, 25.1), b2Vec2( 12.0, 20.1) };
		pontos[3] = new b2Vec2[4]{ b2Vec2(0.0, 25.0), b2Vec2(-12.0, 24.0), b2Vec2(0.0, 25.1), b2Vec2(-12.0, 24.1) };
		pontos[4] = new b2Vec2[4]{ b2Vec2(0.0, 25.0), b2Vec2(-12.0, 28.0), b2Vec2(0.0, 25.1), b2Vec2(-12.0, 28.1) };
		pontos[5] = new b2Vec2[4]{ b2Vec2(0.0, 25.0), b2Vec2(-12.0, 20.0), b2Vec2(0.0, 25.1), b2Vec2(-12.0, 20.1) };
		pontos[6] = new b2Vec2[8]{ b2Vec2(-6.0, 36.0), b2Vec2(6.0, 36.0), b2Vec2(-4.0, 20.0), b2Vec2(4.0, 20.0), b2Vec2(-10.0, 30.0), b2Vec2(10.0, 30.0), b2Vec2(-10.0, 24.0), b2Vec2(10.0, 24.0) };
		pontos[7] = new b2Vec2[3]{ b2Vec2(-6.0, 36.0), b2Vec2(-0.5, 36.0), b2Vec2(-3.0, 42.0)};
		pontos[8] = new b2Vec2[3]{ b2Vec2( 0.5, 36.0), b2Vec2( 6.0, 36.0), b2Vec2( 3.0, 42.0)};


		b2PolygonShape poliShape[9];

		for (int x = 0; x < 9; x++)
		{
			poliShape[x].Set(pontos[x], cont[x]);
			// definição da fixture 
			fixs[x] = new b2FixtureDef;
			fixs[x]->shape = &poliShape[x];
			fixs[x]->density = 1.0;
			fixs[x]->friction = 0.5;
			fixs[x]->restitution = 0.5;

		}



		poliDef.type = b2_dynamicBody;
		body = m_world->CreateBody(&poliDef);



		for (int x = 0; x < 9; x++)
		{
			body->CreateFixture(fixs[x]);

		}

		




	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Gatinho!! ");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padrão de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new Lista1ex08;
	}


};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("__Fisica para Jogos", "Lista1ex08", Lista1ex08::Create);


