#include "test.h"

class Lista1ex05 : public Test //você cria a sua classe derivada da classe base Test
{
public:

	float atri = 0.0f;

	Lista1ex05() {
		// Aqui no construtor você inicializa a cena
		createLine(b2Vec2(-40, 30), b2Vec2( 40 , 0.0));



	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Aperte 'B' para criar uma caixa. A primeira caixa comeca com 0.0 de atrito, ele vai aumentar ate a decima caixa ter 1.0 de atrito.");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padrão de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new Lista1ex05;
	}


	void Keyboard(int key) override { //
		switch (key)
		{
		case GLFW_KEY_B:
			createBox(b2Vec2(-38.0, 32.0), b2Vec2(1.0, 1.0), 1.0f, atri, 0.1);
			break;
		}

		if (atri < 1.0) {
			atri += 0.1f;
		}


	}

	b2Body* createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);

	b2Body* createLine(b2Vec2 position1, b2Vec2 position2, b2BodyType type = b2_staticBody);

};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("__Fisica para Jogos", "Lista1ex05", Lista1ex05::Create);

b2Body* Lista1ex05::createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type)
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

b2Body* Lista1ex05::createLine(b2Vec2 position1, b2Vec2 position2, b2BodyType type)
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
