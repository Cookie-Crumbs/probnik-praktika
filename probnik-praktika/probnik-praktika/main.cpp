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

	Player p("kv1.png", 75, 56, 127.0, 127.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота
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
	ico_kv1.setPosition(821, 89); //т. отсчета в центр
	ico_kr1.setPosition(821, 193);
	ico_z1.setPosition(829, 309);

	//контейнер details - хранит в себе все созданные детали
	map<int, Player> details; 
	int count = 0;//количество деталей
	//Player *det = &p;
	
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = time / 800; //скорость игры

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		//std::cout << pixelPos.x << "\n";//смотрим на координату Х позиции курсора в консоли (она не будет больше ширины окна)
		//std::cout << pos.x << "\n";//смотрим на Х,которая преобразовалась в мировые координаты

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
					if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
						if (event.key.code == Mouse::Left)//а именно левая
							//a.at(1).fio

							if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
							{
								//std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
								dX = pos.x - p.sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
								dY = pos.y - p.sprite.getPosition().y;//тоже самое по игреку
								isMove = true;//можем двигать спрайт							
							}
					if (event.type == Event::MouseButtonReleased)//если отпустили клавишу
						if (event.key.code == Mouse::Left) //а именно левую
							isMove = false; //то не можем двигать спрайт
					p.sprite.setColor(Color::White);//и даем ему прежний цвет

					if (isMove) {//если можем двигать
						p.sprite.setColor(Color::Green);//красим спрайт в зеленый 
						p.x = pos.x - dX;//двигаем спрайт по Х
						p.y = pos.y - dY;//двигаем по Y
					}
				//}
			//}
			/********************************************************************************************************************************************/

		}
		///////////////////////////////////////////Управление деталькой с клавы////////////////////////////////////////////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			p.dir = 1; p.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз

		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			p.dir = 0; p.speed = 0.1;//направление вправо, см выше
	
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			p.dir = 3; p.speed = 0.1;//направление вниз, см выше

		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { //если нажата клавиша стрелка влево или англ буква А
			p.dir = 2; p.speed = 0.1;//направление вверх, см выше
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
		window.draw(p.sprite);//рисуем спрайт объекта p класса player
		if (count){
			for (int i = 1; i <= count; i++){
				
				window.draw(details.at(i).sprite);
			}
		}
		window.display();
	}

	return 0;
}

