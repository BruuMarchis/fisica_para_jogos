#include "test.h"

class Lista1ex02 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	Lista1ex02() {
		// Aqui no construtor você inicializa a cena

		m_world->SetGravity(b2Vec2(rand() %21 - 10, rand() %21 - 10));

		createLine(b2Vec2(-40.0, -2.0), b2Vec2(-40.0, 42.0));
		createLine(b2Vec2( 30.0, 42.0), b2Vec2( 30.0, -2.0));
		createLine(b2Vec2( 30.0, 42.0), b2Vec2(-40.0, 42.0));
		createLine(b2Vec2( 30.0, -2.0), b2Vec2(-40.0, -2.0));




		
		//createBox(b2Vec2(0.0f, 20.0f), b2Vec2(4.0f, 4.0f), 1.0f, 0.5f, 0.8f);
		createBox(b2Vec2(10.0f, 20.0f), b2Vec2(2.0f, 2.0f), 1.0f, 0.5f, 0.5f);
		createCircle(b2Vec2(0.0f, 20.0f), 4.0f, 1.0f, 0.5f, 0.5f);




	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Aperte 'R' para reiniciar o teste. A gravidade, tanto em X quanto em Y vai sempre ser aleatoria.");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padrão de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new Lista1ex02;
	}


	b2Body* createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);

	b2Body* createCircle(b2Vec2 position, float radius, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);

	b2Body* createLine(b2Vec2 position1, b2Vec2 position2, b2BodyType type = b2_staticBody);

};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("__Fisica para Jogos", "Lista1ex02", Lista1ex02::Create);

b2Body* Lista1ex02::createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type)
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

b2Body* Lista1ex02::createCircle(b2Vec2 position, float radius, float density, float friction, float restitution, b2BodyType type)
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

b2Body* Lista1ex02::createLine(b2Vec2 position1, b2Vec2 position2, b2BodyType type)
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

