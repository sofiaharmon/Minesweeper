#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "stuff.h"

using namespace std;



int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
	void buildBoard(sf::RenderWindow &window, map<string, sf::Texture> textures, Tile* arrTiles[400]);
	ofstream out("EXAMPLEFILE.TXT");
	out.close();
	map<string, sf::Texture> textures;
	sf::Texture temp1;
	temp1.loadFromFile("images/debug.png");
	textures["debug"] = temp1;
	sf::Texture temp2;
	temp2.loadFromFile("images/digits.png");
	textures["digits"] = temp2;
	sf::Texture temp3;
	temp3.loadFromFile("images/face_happy.png");
	textures["face_happy"] = temp3;
	sf::Texture temp4;
	temp4.loadFromFile("images/face_lose.png");
	textures["face_lose"] = temp4;
	sf::Texture temp5;
	temp5.loadFromFile("images/face_win.png");
	textures["face_win"] = temp5;
	sf::Texture temp6;
	temp6.loadFromFile("images/flag.png");
	textures["flag"] = temp6;
	sf::Texture temp7;
	temp7.loadFromFile("images/mine.png");
	textures["mine"] = temp7;
	sf::Texture temp8;
	temp8.loadFromFile("images/number_1.png");
	textures["number_1"] = temp8;
	sf::Texture temp9;
	temp9.loadFromFile("images/number_2.png");
	textures["number_2"] = temp9;
	sf::Texture temp10;
	temp10.loadFromFile("images/number_3.png");
	textures["number_3"] = temp10;
	sf::Texture temp11;
	temp11.loadFromFile("images/number_4.png");
	textures["number_4"] = temp11;
	sf::Texture temp12;
	temp12.loadFromFile("images/number_5.png");
	textures["number_5"] = temp12;
	sf::Texture temp13;
	temp13.loadFromFile("images/number_6.png");
	textures["number_6"] = temp13;
	sf::Texture temp14;
	temp14.loadFromFile("images/number_7.png");
	textures["number_7"] = temp14;
	sf::Texture temp15;
	temp15.loadFromFile("images/number_8.png");
	textures["number_8"] = temp15;
	sf::Texture temp16;
	temp16.loadFromFile("images/test_1.png");
	textures["test_1"] = temp16;
	sf::Texture temp17;
	temp17.loadFromFile("images/test_2.png");
	textures["test_2"] = temp17;
	sf::Texture temp18;
	temp18.loadFromFile("images/tile_hidden.png");
	textures["tile_hidden"] = temp18;
	sf::Texture temp19;
	temp19.loadFromFile("images/tile_revealed.png");
	textures["tile_revealed"] = temp19;

	void buildTestBoard(sf::RenderWindow &window, map<string, sf::Texture> textures);
	Board brd;
	brd.randoBoard(textures);

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					if (event.mouseButton.x >= 0.f && event.mouseButton.x <= 800.f && event.mouseButton.y >= 0.f && event.mouseButton.y <= 512.f) {
						brd.rightClick(event.mouseButton.x, event.mouseButton.y, textures);
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Left) {
					if (event.mouseButton.x >= 0.f && event.mouseButton.x <= 800.f && event.mouseButton.y >= 0.f && event.mouseButton.y <= 512.f) {
						brd.updateBoard(event.mouseButton.x, event.mouseButton.y, textures);
					}
					else if (event.mouseButton.x >= 384.f && event.mouseButton.x <= 448.f && event.mouseButton.y >= 512 && event.mouseButton.y <= 576.f) {
						brd.restartBoard(textures);
					}
					else if (event.mouseButton.x >= 512.f && event.mouseButton.x <= 576.f && event.mouseButton.y >= 512 && event.mouseButton.y <= 576.f) {
						brd.reveal(textures);
					}
					else if (event.mouseButton.x > 576.f && event.mouseButton.x <= 640.f && event.mouseButton.y >= 512 && event.mouseButton.y <= 576.f) {
						brd.readFile("boards/testboard.brd", textures);
					}
					else if (event.mouseButton.x > 640.f && event.mouseButton.x <= 704.f && event.mouseButton.y >= 512 && event.mouseButton.y <= 576.f) {
						brd.readFile("boards/testboard2.brd", textures);
					}
					else {}
				}
			}
		}
		window.clear();
		brd.buildBoard(window, textures, brd.arrTiles);
		window.display();
	}

	return 0;
}