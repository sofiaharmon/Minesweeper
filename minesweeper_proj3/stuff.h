#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <fstream>
using namespace std;


class Tile {
public:
	int pozish;
	bool mine;
	Tile* adjTiles[8];
	string textureVal;
	bool isNumber;
	int number;
	string face;
	sf::Texture texture;
	bool isFlag;
public:
	Tile();
	void updateTile(int m, Tile* arrTiles[], int index, map<string, sf::Texture> textures);
	bool isMine();
	int amtMines();
};

class Board {
public:
	Tile* arrTiles[400];
	string faceVal;
	int minecount = 0;
	bool debug;
public:
	Board();
	void buildBoard(sf::RenderWindow  &window, map<string, sf::Texture>textures, Tile* arrTiles[400]);
	void randoBoard(map<string, sf::Texture> textures);
	void updateBoard(int pos, map<string, sf::Texture> textures);
	void updateBoard(float x, float y, map<string, sf::Texture> textures);
	void rightClick(float x, float y, map<string, sf::Texture> textures);
	void rightClick(int pos, map<string, sf::Texture> textures);
	void checkSurroundings(Tile* pos, map<string, sf::Texture> textures);
	void restartBoard(map<string, sf::Texture> textures);
	void reveal(map<string, sf::Texture> textures);
	void readFile(string filename, map<string, sf::Texture> textures);
	void loser(map<string, sf::Texture> textures);
	bool didIJustWin();
	void winner(map<string, sf::Texture> textures);
};