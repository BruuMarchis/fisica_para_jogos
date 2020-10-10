#include "test.h"

class Lista3ex01 : public Test 
{
public:
	Lista3ex01() {

		

		b2Body* ground = createBox(b2Vec2(  0.0, -1.0), b2Vec2(50.0,  1.0), 0.5, 0.5, 0.5, b2_staticBody);
		b2Body* roof = createBox(b2Vec2( 0.0f, 40.0f), b2Vec2(52.5f,  1.0f), 1.0f, 1.0f, 0.0f, b2_staticBody);
		createBox(b2Vec2(-45.0f, 20.0f), b2Vec2( 1.0f, 22.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);
		createBox(b2Vec2( 35.0f, 20.0f), b2Vec2( 1.0f, 22.5f), 1.0f, 1.0f, 0.0f, b2_staticBody);



		b2Vec2 pontos[8]{
		b2Vec2(-2.0, 12.5), b2Vec2(2.0, 12.5),
		b2Vec2(-4.0, 10.0), b2Vec2(4.0, 10.0),
		b2Vec2(-5.0,  5.0), b2Vec2(5.0,  5.0),
		b2Vec2(-4.0,  2.5), b2Vec2(4.0,  2.5)
		};
		b2Body* roboBase = createPoli(pontos, 8, 1.0, 0.5, 0.2, b2_dynamicBody);
		b2PrismaticJointDef pjd;
		// Horizontal
		pjd.Initialize(ground, roboBase, roboBase->GetPosition(), b2Vec2(1.0f, 0.0f));
		pjd.enableMotor = false;
		pjd.enableLimit = false;
		m_joint = (b2PrismaticJoint*)m_world->CreateJoint(&pjd);

		


		{
			b2RevoluteJointDef jd;
			b2Body* prevBody = roboBase;
			b2Body* cabeba = createCircle(b2Vec2(0.0f, 15.0f), 2.5f, 1.0, 0.5, 0.2);
			b2Vec2 anchorO(0.0f, 15.0f);
			jd.lowerAngle = -0.25f * b2_pi;
			jd.upperAngle = 0.25f * b2_pi;
			jd.enableLimit = true;
			jd.Initialize(prevBody, cabeba, anchorO);
			m_world->CreateJoint(&jd);


			b2DistanceJointDef jc;
			
			b2Vec2 p1, p2, d;
			
			float frequencyHz = 2.0f;
			float dampingRatio = 1.0f;
			
			jc.bodyA = roof;
			jc.bodyB = cabeba;
			jc.localAnchorA.Set(0.0f, 0.0f);
			jc.localAnchorB.Set(0.0f, 0.f);
			p1 = jc.bodyA->GetWorldPoint(jc.localAnchorA);
			p2 = jc.bodyB->GetWorldPoint(jc.localAnchorB);
			d = p2 - p1;
			jc.length = d.Length() + 1.0f;
			b2LinearStiffness(jc.stiffness, jc.damping, frequencyHz, dampingRatio, jc.bodyA, jc.bodyB);
			m_joints_c = m_world->CreateJoint(&jc);




		}
	

		//rodas
		{			
			b2Body* roda1 = createCircle(b2Vec2(-2.5, 2.0), 2.0f, 1.0f, 0.9f, 1.0f);;
			b2Body* roda2 = createCircle(b2Vec2( 2.5, 2.0), 2.0f, 1.0f, 0.9f, 1.0f);


			b2WheelJointDef jd;
			b2Vec2 axis(0.0f, 1.0f);

			float mass1 = roda1->GetMass();
			float mass2 = roda2->GetMass();

			float hertz = 4.0f;
			float dampingRatio = 0.7f;
			float omega = 2.0f * b2_pi * hertz;

			jd.Initialize(roboBase, roda1, roda1->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 100.0f;
			jd.enableMotor = false;
			jd.stiffness = mass1 * omega * omega;
			jd.damping = 2.0f * mass1 * dampingRatio * omega;
			jd.lowerTranslation = -1.25f;
			jd.upperTranslation =  1.25f;
			jd.enableLimit = true;
			m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);

			jd.Initialize(roboBase, roda2, roda2->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 100.0f;
			jd.enableMotor = false;
			jd.stiffness = mass2 * omega * omega;
			jd.damping = 2.0f * mass2 * dampingRatio * omega;
			jd.lowerTranslation = -1.25f;
			jd.upperTranslation =  1.25f;
			jd.enableLimit = true;
			m_spring2 = (b2WheelJoint*)m_world->CreateJoint(&jd);

			m_spring1->SetMotorSpeed(0.0f);
		}
		//braços1
		{
			int e_count = 4;

			b2RevoluteJointDef jd;
			b2Body* prevBody = roboBase;
			ombro1 = createCircle(b2Vec2(-4.0, 11.0f), 1.5f, 1.0, 0.5, 0.2);
			b2Vec2 anchorO(-4.0, 11.0f);
			jd.lowerAngle = -0.25f * b2_pi;
			jd.upperAngle = 0.15f * b2_pi;
			jd.enableLimit = true;
			jd.Initialize(prevBody, ombro1, anchorO);
			m_world->CreateJoint(&jd);
			prevBody = ombro1;

			for (int32 i = 0; i < e_count; ++i)
			{
				b2Body* body = createBox(b2Vec2(-6.0f + 1.5f * -i, 11.0f), b2Vec2(1.0, 0.5), 2.0, 0.8, 0.2, b2_dynamicBody);
				b2Vec2 anchor(-6.0f + 1.5f * -(i - 1), 11.0f);
				jd.Initialize(prevBody, body, anchor);
				m_world->CreateJoint(&jd);
				if (i == (e_count >> 1))
				{
					m_middle = body;
				}
				prevBody = body;
			}

			m_world->CreateJoint(&jd);

		}
		//braços2
		{
			int e_count = 4;

			b2RevoluteJointDef jd;
			b2Body* prevBody = roboBase;
			ombro2 = createCircle(b2Vec2( 4.0, 11.0f), 1.5f, 1.0, 0.5, 0.2);
			b2Vec2 anchorO( 4.0, 11.0f);
			jd.lowerAngle = -0.15f * b2_pi;
			jd.upperAngle = 0.25f * b2_pi;
			jd.enableLimit = true;
			jd.Initialize(prevBody, ombro2, anchorO);
			m_world->CreateJoint(&jd);
			prevBody = ombro2;

			for (int32 i = 0; i < e_count; ++i)
			{
				b2Body* body = createBox(b2Vec2( 6.0f + 1.5f * i, 11.0f), b2Vec2(1.0, 0.5), 2.0, 0.8, 0.2, b2_dynamicBody);
				b2Vec2 anchor( 6.0f + 1.5f * (i - 1), 11.0f);
				jd.Initialize(prevBody, body, anchor);
				m_world->CreateJoint(&jd);
				if (i == (e_count >> 1))
				{
					m_middle = body;
				}
				prevBody = body;
			}

			m_world->CreateJoint(&jd);

		}


	} 

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);


		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Mova o robo com o mouse  [[PrismaticJoint trava o Robo na horizontal. DistanceJoint faz o robo voltar sempre para o centro. RevoluteJoint faz o movimento dos bracos. ]] ");
		m_textLine += 15;
	}

	static Test* Create()  
	{
		return new Lista3ex01;
	}

	//Para interagir com teclado
	void Keyboard(int key) override  //esse cabeçalho não mudam! :)
	{
		switch (key)
		{

			//a Distance Joint Está impedindo esses botões de terem efeito
		case GLFW_KEY_A:
			m_spring1->SetMotorSpeed(m_speed);
			break;

		case GLFW_KEY_S:
			m_spring1->SetMotorSpeed(0.0f);
			break;

		case GLFW_KEY_D:
			m_spring1->SetMotorSpeed(-m_speed);
			break;

		}
		
		
	}

	b2Body* createPoli(b2Vec2* pos, int vertexes, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);
	b2Body* createBox(b2Vec2 pos, b2Vec2 dim, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);
	b2Body* createCircle(b2Vec2 pos, float radius, float density, float friction, float restitution, b2BodyType type = b2_dynamicBody);
	b2Body* createLine(b2Vec2 position1, b2Vec2 position2, b2BodyType type = b2_staticBody);

	//Algumas funções matemáticas
	b2Vec2 getVectorComponents(float length, float angle);
	float degreesToRadians(float angle);
	float radiansToDegrees(float angle);


protected:
	b2Body* ombro1;
	b2Body* ombro2;
	bool applyingForce;
	b2Vec2 force;
	b2Vec2 globalPoint;

	b2Body* m_middle;
	float m_speed = 50.0f;
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;
	b2PulleyJoint* m_joint1;
	b2PrismaticJoint* m_joint;
	b2Joint* m_joints_c;
};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("__Fisica para Jogos", "Lista3ex01", Lista3ex01::Create);

b2Body* Lista3ex01::createPoli(b2Vec2* pos, int vertexes, float density, float friction, float restitution, b2BodyType type)
{
	b2Body* newPoli;

	b2BodyDef poliDef;
	poliDef.type = type;


	b2PolygonShape poliShape;
	poliShape.Set(pos, vertexes);

	b2FixtureDef poliFix;
	poliFix.shape = &poliShape;
	poliFix.density = density;
	poliFix.friction = friction;
	poliFix.restitution = restitution;

	newPoli = m_world->CreateBody(&poliDef);
	newPoli->CreateFixture(&poliFix);

	return newPoli;
}

b2Body* Lista3ex01::createBox(b2Vec2 pos, b2Vec2 dim, float density, float friction, float restitution, b2BodyType type)
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

b2Body* Lista3ex01::createCircle(b2Vec2 pos, float radius, float density, float friction, float restitution, b2BodyType type)
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

b2Body* Lista3ex01::createLine(b2Vec2 position1, b2Vec2 position2, b2BodyType type)
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



b2Vec2 Lista3ex01::getVectorComponents(float length, float angle)
{
	b2Vec2 v;
	v.x = length * cos(degreesToRadians(angle));
	v.y = length * sin(degreesToRadians(angle));
	return v;
}

float Lista3ex01::degreesToRadians(float angle)
{
	return  angle * b2_pi / 180.0;
}

float Lista3ex01::radiansToDegrees(float angle)
{
	return angle * 180 / b2_pi;
}
