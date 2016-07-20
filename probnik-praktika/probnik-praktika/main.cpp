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

	//контейнер details - хранит в себе все созданные детали
	map<int, Player> details; 
	int count = 0, N=0;//количество деталей

	Player KV1("kv1.png", 75, 56, 127.0, 127.0);
	Player KR1("kr1.png", 75, 56, 102.0, 102.0);
	Player Z1("z1.png", 75, 56, 25.0, 25.0);
	
	Clock clock; //создаем переменную времени
	bool isMove = false;//переменная для щелчка мыши по спрайту
	float dX = 0;//корректировка движения по х
	float dY = 0;//по у

	Texture fon1;
	fon1.loadFromFile("images/fon.png");
	Sprite fon(fon1);
    
	//контейнер ico - 3 спрайта иконки (круг, квадрат, соединение)
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
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = time / 800; //скорость игры

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			/*-----------жмем по иконкам--------------------------------------------------------------------------------*/
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left)//а именно левая
				{
					if (ico_kv1.getGlobalBounds().contains(pos.x, pos.y)){//и при этом координата курсора попадает в спрайт
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
					if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
						if (event.key.code == Mouse::Left)//а именно левая		
							if (details.at(i).sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
								N = i;
				}
			}
			if (N){
					if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
						if (event.key.code == Mouse::Left)//а именно левая
							//a.at(1).fio

							if (details.at(N).sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
							{
								//std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
								dX = pos.x - details.at(N).sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
								dY = pos.y - details.at(N).sprite.getPosition().y;//тоже самое по игреку
								isMove = true;//можем двигать спрайт							
							}
					if (event.type == Event::MouseButtonReleased)//если отпустили клавишу
						if (event.key.code == Mouse::Left) //а именно левую
						{
							isMove = false; //то не можем двигать спрайт
							details.at(N).sprite.setColor(Color::White);//и даем ему прежний цвет
							N = 0;
						}
					if (isMove) {//если можем двигать
						details.at(N).sprite.setColor(Color::Green);//красим спрайт в зеленый 
						details.at(N).x = pos.x - dX;//двигаем спрайт по Х
						details.at(N).y = pos.y - dY;//двигаем по Y
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

