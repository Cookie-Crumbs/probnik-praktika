#include <SFML/Graphics.hpp>
using namespace sf;
void icon();
int main()
{
	sf::RenderWindow window(sf::VideoMode(980, 500), "probnik-praktica");
	
	Texture fon1;
	fon1.loadFromFile("images/fon.png");
	Sprite fon(fon1);

	//3 спрайта колесо соединение квадрат
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
	//
	
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(fon);
		window.draw(ico_kv1);
		window.draw(ico_kr1);
		window.draw(ico_z1);
		window.display();
	}

	return 0;
}

