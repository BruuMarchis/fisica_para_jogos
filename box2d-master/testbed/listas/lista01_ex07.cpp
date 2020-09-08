#include "test.h"

class Lista1ex07 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	Lista1ex07() {
		// Aqui no construtor você inicializa a cena
		createBox(b2Vec2(0.0f, -3.5f), b2Vec2(35.0f, 1.8f), 1.0f, 1.0f, 0.0f, b2_staticBody);



		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				float xf = 0.0;
				if (y % 2 > 0) {
					xf = x + 0.5;
				}
				else {
					xf = x;
				}
				createBox(b2Vec2((xf * 4.0f) - 25.0, y * 3.0f), b2Vec2(2.0f, 1.5f), 1.0f, 1.0f, 0.0f);
			}
		}




	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Muro 10x10. (fiz eles terem um acrecimo de 0.5 em X nas linhas de numero par!) ");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padrão de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new Lista1ex07;
	}



	b2Body* createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);


};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "Lista1ex07", Lista1ex07::Create);

b2Body* Lista1ex07::createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type)
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