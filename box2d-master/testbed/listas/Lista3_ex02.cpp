#include "test.h"

class Lista3ex02 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	Lista3ex02() {

		int e_count = 30;
		b2Body* m_middle;
		// Aqui no construtor você inicializa a cena

		b2Body* ground = createBox(b2Vec2(0.0, -1.0), b2Vec2(50.0, 1.0), 1.0, 0.5, 0.5, b2_staticBody);
		createBox(b2Vec2(-45.0, 25.0), b2Vec2(2.0, 30.0), 1.0, 0.5, 0.5, b2_staticBody);
		createBox(b2Vec2(45.0, 25.0), b2Vec2(2.0, 30.0), 1.0, 0.5, 0.5, b2_staticBody);
		createBox(b2Vec2(0.0, 42.0), b2Vec2(50.0, 2.0), 1.0, 0.5, 0.5, b2_staticBody);

		selected = createBox(b2Vec2(0.0, 20.0), b2Vec2(0.5, 1), 1.0, 0.5, 0.2);



		{

			b2Body* body = createBox(b2Vec2(-14.5f - 2.0f, 2.8f), b2Vec2(1.0f, 2.7f), 20.0f, 0.2f, 0.5, b2_staticBody);


			b2RevoluteJointDef jd;

			b2Body* prevBody = ground;


			b2Vec2 anchor1(-15.0f - 1.0f, 5.0f);
			jd.Initialize(prevBody, body, anchor1);
			m_world->CreateJoint(&jd);

			prevBody = body;

			for (int32 i = 0; i < e_count; ++i)
			{

				body = createBox(b2Vec2(-14.5f + 1.0f * i, 5.0f), b2Vec2(1.0, 0.3), 1.0, 0.5, 0.2, b2_dynamicBody);


				b2Vec2 anchor(-15.0f + 1.0f * i, 5.0f);
				jd.Initialize(prevBody, body, anchor);
				m_world->CreateJoint(&jd);

				if (i == (e_count >> 1))
				{
					m_middle = body;
				}
				prevBody = body;
			}


			body = createBox(b2Vec2(-14.5f + e_count + 1, 2.8f), b2Vec2(1.0f, 2.7f), 20.0f, 0.2f, 0.5, b2_staticBody);

			b2Vec2 anchor2(-15.0f + 1.0f * e_count, 5.0f);
			jd.Initialize(prevBody, body, anchor2);
			m_world->CreateJoint(&jd);

			prevBody = body;

			b2Vec2 anchor(-15.0f + 1.0f * (e_count + 1), 5.0f);
			jd.Initialize(prevBody, ground, anchor);
			m_world->CreateJoint(&jd);
		}




		//m_world->SetGravity(b2Vec2(0, 10));
		applyingForce = false;
		force.SetZero();
		globalPoint.SetZero();

	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		processInputs();

		force.Normalize();
		force *= 5;

		g_debugDraw.DrawPoint(selected->GetWorldCenter(), 5, b2Color(1.0, 0.0, 0.0));
		g_debugDraw.DrawSegment(selected->GetWorldCenter(), selected->GetWorldCenter() + force, b2Color(1.0, 0.0, 0.0));

		//Para poder desenhar o ponto referente ao local onde está se aplicando uma força
		b2Vec2 localPoint = b2Vec2(-0.5, 1.0);
		globalPoint = b2Vec2(selected->GetWorldPoint(localPoint));
		g_debugDraw.DrawPoint(globalPoint, 5, b2Color(1.0, 1.0, 0.0));
		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Ponte simples. Aperte B para criar uma caixa e C para criar um circulo.");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padrão de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new Lista3ex02;
	}

	//Para interagir com teclado
	void Keyboard(int key) override  //esse cabeçalho não mudam! :)
	{
		switch (key)
		{
		case GLFW_KEY_B:
			createBox(b2Vec2(rand() % 61 - 30, rand() % 51), b2Vec2(rand() % 5 + 1, rand() % 5 + 1), 1.0, 0.5, 0.5);
			break;

		case GLFW_KEY_C:
			createCircle(b2Vec2(rand() % 61 - 30, rand() % 51), rand() % 5 + 1, 1.0, 0.5, 0.5);
			break;

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

	b2Body* createBox(b2Vec2 pos, b2Vec2 dim, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);
	b2Body* createCircle(b2Vec2 pos, float radius, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);
	void processInputs();

	//Algumas funções matemáticas
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
static int testIndex = RegisterTest("__Fisica para Jogos", "Lista3ex02", Lista3ex02::Create);

b2Body* Lista3ex02::createBox(b2Vec2 pos, b2Vec2 dim, float density, float friction, float restitution, b2BodyType type)
{
	b2Body* newBox;

	//Definição dos atributos gerais do corpo rígido
	b2BodyDef boxDef;
	boxDef.position = pos;
	boxDef.type = type;

	//Definição da forma do corpo*
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dim.x, dim.y);

	//Definição da fixture
	b2FixtureDef boxFix;
	boxFix.shape = &boxShape;
	boxFix.density = density;
	boxFix.friction = friction;
	boxFix.restitution = restitution;

	//Criação do corpo rígido pelo mundo e da fixture pelo corpo rígido
	newBox = m_world->CreateBody(&boxDef);
	newBox->CreateFixture(&boxFix);

	return newBox;
}

b2Body* Lista3ex02::createCircle(b2Vec2 pos, float radius, float density, float friction, float restitution, b2BodyType type)
{
	b2Body* newCircle;

	//Definição dos atributos gerais do corpo rígido
	b2BodyDef circleDef;
	circleDef.position = pos;
	circleDef.type = type;

	//Definição da forma do corpo*
	b2CircleShape circleShape;
	circleShape.m_radius = radius;

	//Definição da fixture
	b2FixtureDef circleFix;
	circleFix.shape = &circleShape;
	circleFix.density = density;
	circleFix.friction = friction;
	circleFix.restitution = restitution;

	//Criação do corpo rígido pelo mundo e da fixture pelo corpo rígido
	newCircle = m_world->CreateBody(&circleDef);
	newCircle->CreateFixture(&circleFix);

	return newCircle;
}

void Lista3ex02::processInputs()
{
	if (applyingForce)
	{
		force = getVectorComponents(1000, 45);
		selected->ApplyForceToCenter(force, true);

		//Para aplicar força a um ponto 
		//selected->ApplyForce(force, globalPoint, true);

		applyingForce = false;
	}
}

b2Vec2 Lista3ex02::getVectorComponents(float length, float angle)
{
	b2Vec2 v;
	v.x = length * cos(degreesToRadians(angle));
	v.y = length * sin(degreesToRadians(angle));
	return v;
}

float Lista3ex02::degreesToRadians(float angle)
{
	return  angle * b2_pi / 180.0;
}

float Lista3ex02::radiansToDegrees(float angle)
{
	return angle * 180 / b2_pi;
}
