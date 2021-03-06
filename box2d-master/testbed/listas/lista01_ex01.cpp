#include "test.h"

class Lista1ex01 : public Test //voc� cria a sua classe derivada da classe base Test
{
public:
	Lista1ex01() {
		// Aqui no construtor voc� inicializa a cena
		createBox(b2Vec2(0.0f, -2.0f), b2Vec2(25.0f, 2.0f), 1.0f, 0.5f, 0.5f, b2_staticBody);


		createBox(b2Vec2(0.0f, 20.0f), b2Vec2(0.5f, 0.5f), 1.0f, 0.5f, 0.5f);
		createBox(b2Vec2(2.0f, 20.0f), b2Vec2(1.0f, 1.0f), 1.0f, 0.5f, 0.5f);
		createBox(b2Vec2(1.0f, 25.0f), b2Vec2(2.0f, 2.0f), 1.0f, 0.5f, 0.5f, b2_kinematicBody);


		createCircle(b2Vec2(3.0f, 25.0f), 1.0f, 1.0f, 0.5f, 0.5f);

		createLine(b2Vec2(15.0, 10.0), b2Vec2(10.0, 15.0));

	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simula��o e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Primeiro teste, feito durante a aula!");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padr�o de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new Lista1ex01;
	}



	b2Body* createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);

	b2Body* createCircle(b2Vec2 position, float radius, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);

	b2Body* createLine(b2Vec2 position1, b2Vec2 position2, b2BodyType type = b2_staticBody);

};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("__Fisica para Jogos", "Lista1ex01", Lista1ex01::Create);

b2Body* Lista1ex01::createBox(b2Vec2 position, b2Vec2 dimention, float density, float friction, float restitution, b2BodyType type)
{
	b2Body* newBox;

	// defini��o dos atributos gerais do corpo rigido. tipo e posi��o

	b2BodyDef boxDef;
	boxDef.position = position;
	boxDef.type = type;


	// cria��o da forma do corpo
	b2PolygonShape boxShape; //caixa
	boxShape.SetAsBox(dimention.x, dimention.y);

	// defini��o da fixture 
	b2FixtureDef boxFix;
	boxFix.shape = &boxShape;
	boxFix.density = density;
	boxFix.friction = friction;
	boxFix.restitution = restitution;


	// cria��o do corpo rigido pelo mundo e da fixture pelo corpo rigido
	newBox = m_world->CreateBody(&boxDef);
	newBox->CreateFixture(&boxFix);



	return newBox;
}

b2Body* Lista1ex01::createCircle(b2Vec2 position, float radius, float density, float friction, float restitution, b2BodyType type)
{


	b2Body* newCircle;

	// defini��o dos atributos gerais do corpo rigido. tipo e posi��o

	b2BodyDef circleDef;
	circleDef.position = position;
	circleDef.type = type;


	// cria��o da forma do corpo
	b2CircleShape circleShape; //circulo
	circleShape.m_radius = radius;

	// defini��o da fixture 
	b2FixtureDef circleFix;
	circleFix.shape = &circleShape;
	circleFix.density = density;
	circleFix.friction = friction;
	circleFix.restitution = restitution;


	// cria��o do corpo rigido pelo mundo e da fixture pelo corpo rigido
	newCircle = m_world->CreateBody(&circleDef);
	newCircle->CreateFixture(&circleFix);



	return newCircle;

}

b2Body* Lista1ex01::createLine(b2Vec2 position1, b2Vec2 position2, b2BodyType type)
{
	b2Body* newLine;

	// defini��o dos atributos gerais do corpo rigido. tipo e posi��o

	b2BodyDef lineDef;
	lineDef.position.Set(0.0f, 0.0f);
	lineDef.type = type;



	// cria��o da forma do corpo
	b2EdgeShape lineShape; //caixa
	lineShape.SetTwoSided(position1, position2);

	newLine = m_world->CreateBody(&lineDef);
	newLine->CreateFixture(&lineShape, 0.0f);



	return newLine;
}

