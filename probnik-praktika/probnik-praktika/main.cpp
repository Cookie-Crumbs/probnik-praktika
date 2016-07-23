#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <map> 
#include <vector>
#include <iostream>
#include <cstdlib>
#include<cmath>
#include "spr.h"

using namespace std;
using namespace sf;

const  float SCALE = 30.f; //���������
const float DEG = 57.29599f; //�������
b2Vec2 Gravity(0.f, 9.8f);
b2World World(Gravity);

//�����
//�������������+�2_��� 
//���������� ���������
//���������� ����������
//�������� ������� �������

void setWall(int x, int y, int w, int h);

int main()
{
	sf::RenderWindow window(sf::VideoMode(980, 500), "probnik-praktica");
	bool sozdanie = true;

	//��������� details - ������ � ���� ��� ��������� ������
	map<int, Player> details;
	int count = 0, N = 0, D = 0, X, ud = 0, v = 0;//���������� �������
	int V[5] = {};

	b2BodyDef bdef;//��������� ������� ����
	bdef.type = b2_dynamicBody;
	b2Body *bodyV = World.CreateBody(&bdef);
	b2CircleShape circle;
	circle.m_radius = (102.0 / 2) / SCALE;// ����� ��� �� 102/2 ? 
	bodyV = World.CreateBody(&bdef);//CreateBody(&bdef) ������� ����, ���������� � m_world, ������ ������ �� ����
	bodyV->CreateFixture(&circle, 1); //����������� ������ � ����

	b2Vec2 Q(10.0f, 0.0f);
	Player KV1("kv1.png", 75, 56, 127.0, 127.0, "kv1");
	Player KR1("kr1.png", 75, 56, 102.0, 102.0, "kr1");
	Player Z1("z1.png", 75, 56, 25.0, 25.0, "z1");

	Clock clock; //������� ���������� �������
	bool isMove = false;//���������� ��� ������ ���� �� �������
	float dX = 0;//������������� �������� �� �
	float dY = 0;//�� �

	Texture fon1;
	fon1.loadFromFile("images/fon.png");
	Sprite fon(fon1);

	Texture fon_2;
	fon_2.loadFromFile("images/fon2.png");
	Sprite fon2(fon_2);
	bool f2 = true;

	//��������� ico - 3 ������� ������ (����, �������, ����������)
	Texture icokv1, icokr1, icoz1, icoc;
	icokv1.loadFromFile("images/ico_kv1.png");
	icokr1.loadFromFile("images/ico_kr1.png");
	icoz1.loadFromFile("images/ico_z1.png");
	icoc.loadFromFile("images/ico_con.png");
	Sprite ico_kv1(icokv1), ico_kr1(icokr1), ico_z1(icoz1), ico_c(icoc);
	ico_kv1.setPosition(821, 89);
	ico_kr1.setPosition(821, 193);
	ico_z1.setPosition(829, 309);
	ico_c.setPosition(795, 390);

	while (window.isOpen())
	{
		if (sozdanie == true){
			float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
			clock.restart(); //������������� �����
			time = time / 800; //�������� ����

			Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
			Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				/*-----------���� �� �������--------------------------------------------------------------------------------*/
				if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
					if (event.key.code == Mouse::Left)//� ������ �����
					{
						if (ico_kv1.getGlobalBounds().contains(pos.x, pos.y)){//� ��� ���� ���������� ������� �������� � ������
							count++;
							details.insert(pair<int, Player>(count, KV1));
						}
						else if (ico_kr1.getGlobalBounds().contains(pos.x, pos.y)){
							count++;
							details.insert(pair<int, Player>(count, KR1));
						}
						else if (ico_z1.getGlobalBounds().contains(pos.x, pos.y)){

							count++;
							details.insert(pair<int, Player>(count, Z1));
						}
						else if (ico_c.getGlobalBounds().contains(pos.x, pos.y)){
							sozdanie = false;
						}
					}
				/*-------------------------------------------------------------------------------------------------------------*/

				if (count){
					for (int i = 1; i <= count; i++){
						if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
						{
							if (event.key.code == Mouse::Left)//� ������ �����		
								if (details.at(i).sprite.getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
									N = i;
							if (event.key.code == Mouse::Right)//�������� �������� �� ������� ����� ���� 
								if (details.at(i).sprite.getGlobalBounds().contains(pos.x, pos.y)){
									D = i;
									ud++;
								}
						}
					}
				}
				if (D != 0){
					details.at(D).del = true;
					D = 0;
				}
				if (N){
					if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
						if (event.key.code == Mouse::Left)//� ������ �����
							//a.at(1).fio

							if (details.at(N).sprite.getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
							{
								//std::cout << "isClicked!\n";//������� � ������� ��������� �� ����
								dX = pos.x - details.at(N).sprite.getPosition().x;//������ �������� ����� �������� ������� � �������.��� ������������� �������
								dY = pos.y - details.at(N).sprite.getPosition().y;//���� ����� �� ������
								isMove = true;//����� ������� ������							
							}
					if (event.type == Event::MouseButtonReleased)//���� ��������� �������
						if (event.key.code == Mouse::Left) //� ������ �����
						{
							isMove = false; //�� �� ����� ������� ������
							details.at(N).sprite.setColor(Color::White);//� ���� ��� ������� ����
							N = 0;
						}
					if (isMove) {//���� ����� �������
						details.at(N).sprite.setColor(Color::Green);//������ ������ � ������� 
						details.at(N).x = pos.x - dX;//������� ������ �� �
						details.at(N).y = pos.y - dY;//������� �� Y
					}
				}
			}

			if (count){
				for (int i = 1; i <= count; i++) details.at(i).update(time); //////////////////
			}
			window.clear();
			window.draw(fon);
			window.draw(ico_kv1);
			window.draw(ico_kr1);
			window.draw(ico_z1);
			window.draw(ico_c);
			if (count){
				for (int i = 1; i <= count; i++){
					if (details.at(i).del == false)
						window.draw(details.at(i).sprite);
				}
			}
			window.display();

		}//if (sozdanie == true)

		if (sozdanie == false){

			if (f2){

				setWall(490, 463, 490, 37);// 74||37 426||463


				//��� �������� ��� ��������
				if (count){

					b2BodyDef bdef;//��������� ������� ����
					bdef.type = b2_dynamicBody;
					std::vector<b2Body *>body(count - ud);
					b2Body *body3 = World.CreateBody(&bdef);

					int bb = 0;//������ �������� ������ ����
					double Cx, Cy;
					//bdef.position.Set(4, 20);
					//
					b2RevoluteJointDef jointDef;

					for (int i = 1; i <= count; i++){

						if (details.at(i).del == false)
						{
							details.at(i).BB = bb;


							//����
							if (details.at(i).t == "kr1"){


								b2CircleShape circle;
								details.at(i).sprite.setOrigin(51, 51);
								circle.m_radius = (102.0 / 2) / SCALE;// ����� ��� �� 102/2 ? 
								bdef.position.Set((details.at(i).x + 51) / SCALE, (details.at(i).y + 51) / SCALE);

								body[bb] = World.CreateBody(&bdef);//CreateBody(&bdef) ������� ����, ���������� � m_world, ������ ������ �� ����
								body[bb]->CreateFixture(&circle, 1); //����������� ������ � ����

								body[bb]->SetUserData("Box");
								v = bb;
								bodyV = body[bb];
								//bodyV->SetAngularVelocity(0.5f);


								bb++;

							}

							//�������
							if (details.at(i).t == "kv1"){

								b2PolygonShape shape;//������� ������
								details.at(i).sprite.setOrigin(63.5, 63.5);
								shape.SetAsBox(63.5 / SCALE, 63.5 / SCALE); //���������
								bdef.position.Set((details.at(i).x + 63.5) / SCALE, (details.at(i).y + 63.5) / SCALE);

								body[bb] = World.CreateBody(&bdef);//CreateBody(&bdef) ������� ����, ���������� � m_world, ������ ������ �� ����
								body[bb]->CreateFixture(&shape, 10); //����������� ������ � ����
								body[bb]->SetUserData("Box");


								bb++;

								//body[0] = m_world->CreateBody(&bdef);//CreateBody(&bdef) ������� ����, ���������� � m_world, ������ ������ �� ����
								//body[0]->CreateFixture(&shape, 1); //����������� ������ � ����

							}

							//���������� ��������, ���������
							if (details.at(i).t == "z1"){

								b2CircleShape soed;
								details.at(i).sprite.setOrigin(12.5, 12.5);
								soed.m_radius = (25.0 / 2) / SCALE;

								body[bb] = World.CreateBody(&bdef);//CreateBody(&bdef) ������� ����, ���������� � m_world, ������ ������ �� ����
								body[bb]->CreateFixture(&soed, 1); //����������� ������ � ����
								body[bb]->SetUserData("Box");
								//body[bb]->SetLinearVelocity(Q);
								//v = bb;
								for (int j = 1; j <= count; j++){
									if (details.at(j).t != "z1"){

										if (details.at(j).t == "kr1")
										{
											if ((pow((details.at(i).x - (details.at(j).x + 51)), 2) + pow((details.at(i).y - (details.at(j).y + 51)), 2)) <= (pow(51.0, 2))){
												//������ � ����� �����
												Cx = (details.at(i).x - ((details.at(j).x) + 51));
												Cy = (details.at(i).y - ((details.at(j).y) + 51));
												//�� �������� ������ �� �����


												//������������ � ���� ������� (������,����) �� ����������
												jointDef.Initialize(body[details.at(j).BB], body[bb], body[details.at(j).BB]->GetWorldCenter());
												//jointDef.localAnchorA.Set(0,0);
												//jointDef.localAnchorB.Set(0, 0);//51  / SCALE
												World.CreateJoint(&jointDef);
												//body[bb]->SetAngularVelocity(0.5f);
											}
										}
										else if (details.at(j).t == "kv1"){
											if ((details.at(i).x >= details.at(j).x) && (details.at(i).y >= details.at(j).y) && (details.at(i).x <= (details.at(j).x + 127)) && (details.at(i).y <= (details.at(j).y + 127))){//������ �������������� ��������



												if (details.at(i).x >= (details.at(j).x + 63)){

													jointDef.Initialize(body[bb], body[details.at(j).BB], body[bb]->GetWorldCenter());
													jointDef.localAnchorA.Set(0, 0);

													jointDef.localAnchorB.Set(-63.5 / SCALE, 0);//0,0 �������� | (0, 63.5/SCALE) - verh/niz | (63.5 / SCALE,0) -levo/pr |
													World.CreateJoint(&jointDef);
												}
												else if (details.at(i).x <= (details.at(j).x + 30)){

													jointDef.Initialize(body[bb], body[details.at(j).BB], body[bb]->GetWorldCenter());
													jointDef.localAnchorA.Set(0, 0);

													jointDef.localAnchorB.Set(63.5 / SCALE, 0);//0,0 �������� | (0, 63.5/SCALE) - verh/niz | (63.5 / SCALE,0) -levo/pr |
													World.CreateJoint(&jointDef);
												}
												else if (details.at(i).y >= (details.at(j).y + 63)){

													jointDef.Initialize(body[bb], body[details.at(j).BB], body[bb]->GetWorldCenter());
													jointDef.localAnchorA.Set(0, 0);

													jointDef.localAnchorB.Set(0, -63.5 / SCALE);//0,0 �������� | (0, 63.5/SCALE) - verh/niz | (63.5 / SCALE,0) -levo/pr |
													World.CreateJoint(&jointDef);

													/*//��+��
													jointDef.Initialize(body[v], body[details.at(j).BB], body[v]->GetWorldCenter());
													jointDef.localAnchorA.Set(0, 0);

													jointDef.localAnchorB.Set(0, (-63.5 + 51.0) / SCALE);//0,0 �������� | (0, 63.5/SCALE) - verh/niz | (63.5 / SCALE,0) -levo/pr |
													World.CreateJoint(&jointDef);*/

												}
												else if (details.at(i).y <= (details.at(j).y + 30)){

													jointDef.Initialize(body[bb], body[details.at(j).BB], body[bb]->GetWorldCenter());
													jointDef.localAnchorA.Set(0, 0);

													jointDef.localAnchorB.Set(0, 63.5 / SCALE);//0,0 �������� | (0, 63.5/SCALE) - verh/niz | (63.5 / SCALE,0) -levo/pr |
													World.CreateJoint(&jointDef);
												}

												//������������ � ���� ������� (������,����) �� ����������
												//details.at(j).sprite.setOrigin(63.5, 63.5);

												//body[bb]->SetAngularVelocity(0.5f);

												//������ � ����� ������ ��� �������
												//���������
											}
										}
									}

								}

								bb++;
								//body[2] = m_world->CreateBody(&bdef);//CreateBody(&bdef) ������� ����, ���������� � m_world, ������ ������ �� ����
								//body[2]->CreateFixture(&soed, 1); //����������� ������ � ����


								//����� �������� �������

								//��������� ���������� �� �� ������ ������� (�������� �� ���� ��������)

								//���� ��
								//������ � ����� �����
								//������������ � ���� ������� (������,����) �� ����������
								/////////////////////////////////////

								/*for (int ii = 0,cr=0,cv=0; ii < v; ii++){
								if (details.at(V[ii]).t == "kv1")
								cv = V[ii];
								if (details.at(V[ii]).t == "kr1")
								cr = V[ii];

								if (ii == v - 1)
								{
								jointDef.Initialize(body[details.at(cr).BB], body[details.at(cv).BB], body[details.at(cr).BB]->GetWorldCenter());
								jointDef.localAnchorA.Set(0, 0);

								jointDef.localAnchorB.Set(0, -63.5 / SCALE);//0,0 �������� | (0, 63.5/SCALE) - verh/niz | (63.5 / SCALE,0) -levo/pr |
								World.CreateJoint(&jointDef);
								}
								}*/

							}
							//b_ground->SetUserData("Box")

						}
						//body[v]->SetAngularVelocity(1.5f);
					}
				}

				f2 = false;
			}

			sf::Event e;
			while (window.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
					window.close();
			}
			World.Step(1 / 60.f, 8, 3);

			window.clear();
			window.draw(fon2);
			bodyV->SetAngularVelocity(0.5f);
			X = 0;
			if (count){
				for (b2Body* it = World.GetBodyList(); it != 0; it = it->GetNext()){//�������� ��������� �� ���� �����

					X++;

					if (it->GetUserData() == "Box")//���� ��� ��������
					{
						while (details.at(X).del == true)
						{
							X++;
						}
						b2Vec2 pos = it->GetPosition();
						float angle = it->GetAngle();//ugol
						details.at(X).sprite.setPosition(pos.x*SCALE, pos.y*SCALE);
						details.at(X).sprite.setRotation(angle*DEG);
						window.draw(details.at(X).sprite);
					}
				}
			}
			window.display();
		}
	}




	return 0;
}

/**********************************************************************/
void setWall(int x, int y, int w, int h){//�������� ������ � ������ 90 px = 3 m => 1.5
	b2PolygonShape gr;
	gr.SetAsBox(w / SCALE, h / SCALE); //����� �� ���� ��� ������� � ������

	b2BodyDef bdef; //����������� ����
	bdef.position.Set(x / SCALE, y / SCALE); //����� � �����

	b2Body *b_ground = World.CreateBody(&bdef); //������� ����
	b_ground->CreateFixture(&gr, 1);//���������� ����

	//b_ground->SetUserData("Box");

}

