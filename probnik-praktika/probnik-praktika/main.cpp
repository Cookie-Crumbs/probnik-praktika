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

	//��������� details - ������ � ���� ��� ��������� ������
	map<int, Player> details; 
	int count = 0, N=0;//���������� �������

	Player KV1("kv1.png", 75, 56, 127.0, 127.0);
	Player KR1("kr1.png", 75, 56, 102.0, 102.0);
	Player Z1("z1.png", 75, 56, 25.0, 25.0);
	
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
	ico_kv1.setPosition(821, 89); 
	ico_kr1.setPosition(821, 193);
	ico_z1.setPosition(829, 309);
	
	while (window.isOpen())
	{
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
				}
			/*-------------------------------------------------------------------------------------------------------------*/

			if (count){
				for (int i = 1; i <= count; i++){
					if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
						if (event.key.code == Mouse::Left)//� ������ �����		
							if (details.at(i).sprite.getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
								N = i;
				}
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
		
		if (count){
			for (int i = 1; i <= count; i++){		
				window.draw(details.at(i).sprite);
			}
		}
		window.display();
	}

	return 0;
}

