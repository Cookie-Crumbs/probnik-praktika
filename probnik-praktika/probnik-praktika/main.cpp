#include <SFML/Graphics.hpp>
#include <map> 
#include <iostream>
#include <cstdlib>
#include "spr.h"

using namespace std;
using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(980, 500), "probnik-praktica");

	Player p("kv1.png", 75, 56, 127.0, 127.0);//������� ������ p ������ player,������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������
	Clock clock; //������� ���������� �������
	bool isMove = false;//���������� ��� ������ ���� �� �������
	float dX = 0;//������������� �������� �� �
	float dY = 0;//�� �

	Texture fon1;
	fon1.loadFromFile("images/fon.png");
	Sprite fon(fon1);

	
	//��������� ico - 3 ������� ������ (����, �������, ����������)
	Texture icokv1, icokr1, icoz1;
	icokv1.loadFromFile("images/ico_kv1.png");
	icokr1.loadFromFile("images/ico_kr1.png");
	icoz1.loadFromFile("images/ico_z1.png");
	Sprite ico_kv1(icokv1), ico_kr1(icokr1), ico_z1(icoz1);
	ico_kv1.setPosition(821, 89); //�. ������� � �����
	ico_kr1.setPosition(821, 193);
	ico_z1.setPosition(829, 309);

	//��������� details - ������ � ���� ��� ��������� ������
	map<int, Player> details; 
	int count = 0;//���������� �������
	//Player *det = &p;
	
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
		clock.restart(); //������������� �����
		time = time / 800; //�������� ����

		Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
		Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)
		//std::cout << pixelPos.x << "\n";//������� �� ���������� � ������� ������� � ������� (��� �� ����� ������ ������ ����)
		//std::cout << pos.x << "\n";//������� �� �,������� ��������������� � ������� ����������

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
						details.insert(pair<int, Player>(count, Player("kv1.png", 75, 56, 127.0, 127.0)));
						//Player p("kv1.png", 75, 56, 127.0, 127.0);
						//a.insert(pair<int, A>(1, A("BBB", 5)));
					}
					else if (ico_kr1.getGlobalBounds().contains(pos.x, pos.y)){

						//count++;
					}
					else if (ico_z1.getGlobalBounds().contains(pos.x, pos.y)){

						//count++;
					}
				}
			/*-------------------------------------------------------------------------------------------------------------*/


			/*******************************************************************************************************************************/

			//if (count){
				//for (int i = 1; i <= count; i++){
					if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
						if (event.key.code == Mouse::Left)//� ������ �����
							//a.at(1).fio

							if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
							{
								//std::cout << "isClicked!\n";//������� � ������� ��������� �� ����
								dX = pos.x - p.sprite.getPosition().x;//������ �������� ����� �������� ������� � �������.��� ������������� �������
								dY = pos.y - p.sprite.getPosition().y;//���� ����� �� ������
								isMove = true;//����� ������� ������							
							}
					if (event.type == Event::MouseButtonReleased)//���� ��������� �������
						if (event.key.code == Mouse::Left) //� ������ �����
							isMove = false; //�� �� ����� ������� ������
					p.sprite.setColor(Color::White);//� ���� ��� ������� ����

					if (isMove) {//���� ����� �������
						p.sprite.setColor(Color::Green);//������ ������ � ������� 
						p.x = pos.x - dX;//������� ������ �� �
						p.y = pos.y - dY;//������� �� Y
					}
				//}
			//}
			/********************************************************************************************************************************************/

		}
		///////////////////////////////////////////���������� ��������� � �����////////////////////////////////////////////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			p.dir = 1; p.speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���

		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			p.dir = 0; p.speed = 0.1;//����������� ������, �� ����
	
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			p.dir = 3; p.speed = 0.1;//����������� ����, �� ����

		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { //���� ������ ������� ������� ����� ��� ���� ����� �
			p.dir = 2; p.speed = 0.1;//����������� �����, �� ����
		}
		
		/*for (int i = 1; i < 3; i++){
			*aaa = a.at(i);
			cout << aaa->fio + "\n";
		}*/

		p.update(time); //////////////////
		window.clear();
		window.draw(fon);
		window.draw(ico_kv1);
		window.draw(ico_kr1);
		window.draw(ico_z1);
		window.draw(p.sprite);//������ ������ ������� p ������ player
		if (count){
			for (int i = 1; i <= count; i++){
				
				window.draw(details.at(i).sprite);
			}
		}
		window.display();
	}

	return 0;
}

