#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "stuff.h"
using namespace std;


Tile::Tile() {
	mine = false;
	textureVal = "tile_hidden";
	isNumber = false;
	isFlag = false;
}

bool Tile::isMine() {
	return mine;
}

int Tile::amtMines() {
	int i = 0;
	for (int k = 0; k < 8; k++) {
		if (adjTiles[k] != nullptr) {
			if (adjTiles[k]->isMine() == true) {
				i++;
			}
		}
	}
	return i;
}

Board::Board() {
	for (int i = 0; i < 400; i++) {
		arrTiles[i] = new Tile();
	}
	faceVal = "face_happy";
}

void Board::loser(map<string, sf::Texture> textures) {
	faceVal = "face_lose";
	reveal(textures);
}

bool Board::didIJustWin() {
	for (int i = 0; i < 400; i++) {
		if (this->arrTiles[i]->mine == false && this->arrTiles[i]->textureVal == "tile_hidden") {
			return false;
		}
	}
	return true;
}

void Board::winner(map<string, sf::Texture> textures) {
	faceVal = "face_win";
	for (int i = 0; i < 400; i++) {
		if (arrTiles[i]->mine == true) {
			if (debug == true) {
				arrTiles[i]->textureVal = "mine";
				arrTiles[i]->texture = textures["flag"];
			}

			arrTiles[i]->textureVal = "tile_hidden";
			arrTiles[i]->isFlag = true;
			arrTiles[i]->texture = textures["mine"];

			//rightClick(i, textures);
		}
	}
	minecount = 0;
}

void Board::readFile(string filename, map<string, sf::Texture> textures) {
	if (faceVal == "face_lose") {
		return;
	}
	int numArr[400];
	ifstream file(filename);
	int m = 0;
	if (file.is_open()) {
		string strang;
		int i = 0;
		while (getline(file, strang)) {
			for (unsigned int k = 0; k < strang.length(); k++) {
				if (strang[k] == '0') {
					numArr[i] = 0;
				}
				else { numArr[i] = 1; m++; }
				i++;
			}
		}
	}
	Board tempBih;
	for (int k = 0; k < 400; k++) {
		tempBih.arrTiles[k]->updateTile(numArr[k], tempBih.arrTiles, k, textures);
	}
	for (int i = 0; i < 400; i++) {
		this->arrTiles[i] = tempBih.arrTiles[i];
	}
	minecount = m;
}

void Board::randoBoard(map<string, sf::Texture> textures) {
	for (int k = 0; k < 400; k++) {
		arrTiles[k]->updateTile(0, arrTiles, k, textures);
	}
	srand(time(NULL));
	for (int i = 0; i < 50; i++) {
		int k = rand() % 400;
		if (arrTiles[k]->mine != true) {
			arrTiles[k]->mine = true;
		}
		else {
			int t = rand() % 400;
			while (arrTiles[t]->mine == true) {
				t = rand() % 400;
			}
			arrTiles[t]->mine = true;
		}
	}
	for (int y = 0; y < 400; y++) {
		if (arrTiles[y]->mine == true) {
			minecount++;
		}
	}
}

void Board::reveal(map<string, sf::Texture> textures) {
	if (debug == true && faceVal == "face_happy") {
		for (int i = 0; i < 400; i++) {
			if (arrTiles[i]->mine == true) {
				arrTiles[i]->textureVal = "tile_hidden";
				arrTiles[i]->isNumber = false;
			}
			if (arrTiles[i]->isFlag == true) {
				arrTiles[i]->texture = textures["flag"];
			}
		}
		debug = false;
		return;
	}
	for (int i = 0; i < 400; i++) {
		if (arrTiles[i]->mine == true) {
			updateBoard(i, textures);
		}
	}
	debug = true;
}

void Board::restartBoard(map<string, sf::Texture> textures) {
	Board tempBih;
	tempBih.randoBoard(textures);
	for (int i = 0; i < 400; i++) {
		this->arrTiles[i] = tempBih.arrTiles[i];
	}
	faceVal = "face_happy";
	minecount = 50;
}

void Board::checkSurroundings(Tile* pos, map<string, sf::Texture> textures) {
	if (pos->textureVal == "tile_revealed") {
		return;
	}
	pos->textureVal = "tile_revealed";
	if (pos->amtMines() != 0) {
		pos->isNumber = true;
		if (pos->amtMines() == 1) {
			pos->texture = textures["number_1"];
		}
		else if (pos->amtMines() == 2) {
			pos->texture = textures["number_2"];
		}
		else if (pos->amtMines() == 3) {
			pos->texture = textures["number_3"];
		}
		else if (pos->amtMines() == 4) {
			pos->texture = textures["number_4"];
		}
		else if (pos->amtMines() == 5) {
			pos->texture = textures["number_5"];
		}
		else if (pos->amtMines() == 6) {
			pos->texture = textures["number_6"];
		}
		else if (pos->amtMines() == 7) {
			pos->texture = textures["number_7"];
		}
		else if (pos->amtMines() == 8) {
			pos->texture = textures["number_8"];
		}
		return;
	}
	for (int i = 0; i < 8; i++) {
		if (pos->adjTiles[i] != nullptr) {
			checkSurroundings(pos->adjTiles[i], textures);
		}
	}
}

void Board::rightClick(int pos, map<string, sf::Texture> textures) {
	if (faceVal == "face_lose") {
		return;
	}
	if (arrTiles[pos]->textureVal == "tile_revealed" || debug == true) {
		return;
	}
	if (arrTiles[pos]->isFlag == true && faceVal == "face_happy") {
		arrTiles[pos]->isFlag = false;
		arrTiles[pos]->texture = textures["tile_hidden"];
	}
	else {
		arrTiles[pos]->textureVal = "tile_hidden";
		arrTiles[pos]->isFlag = true;
		arrTiles[pos]->texture = textures["flag"];
	}
}

void Board::rightClick(float x, float y, map<string, sf::Texture> textures) {
	if (faceVal == "face_lose") {
		return;
	}

	int pos;
	pos = ((int)y / 32) * 25 + (int)x / 32;
	if (arrTiles[pos]->textureVal == "tile_revealed") {
		return;
	}
	if (arrTiles[pos]->isFlag == true) {
		arrTiles[pos]->isFlag = false;
		arrTiles[pos]->texture = textures["tile_hidden"];
		minecount++;
	}
	else {
		arrTiles[pos]->textureVal = "tile_hidden";
		arrTiles[pos]->isFlag = true;
		arrTiles[pos]->texture = textures["flag"];
		minecount--;
	}
}

void Tile::updateTile(int m, Tile* arrTiles[], int index, map<string, sf::Texture> textures) {
	//textureVal = "tile_hidden";
	if (m == 1) {
		mine = true;
	}
	//left edge cases 
	if (index > 0 && ((index % 25 != 0)|| index < 25)) {
		adjTiles[0] = arrTiles[index - 1];
	}
	else { adjTiles[0] = nullptr; }
	//right edge cases
	if (index != 399 && (((index + 1) % 25 != 0 )|| index < 24)) {
		adjTiles[1] = arrTiles[index + 1];
	}
	else { adjTiles[1] = nullptr; }
	//top edge cases
	if (index - 25 > -1) {
		adjTiles[2] = arrTiles[index - 25];
	}
	else { adjTiles[2] = nullptr; }
	//bottom edge cases
	if (index + 25 < 399) {
		adjTiles[3] = arrTiles[index + 25];
	}
	else { adjTiles[3] = nullptr; }
	//NW edge case
	if (index > 25 && index % 25 != 0) {
		adjTiles[4] = arrTiles[index - 26];
	}
	else { adjTiles[4] = nullptr; }
	//NE edge cases
	if (index > 23 && ((index - 24) % 25 != 0)) {
		adjTiles[5] = arrTiles[index - 24];
	}
	else { adjTiles[5] = nullptr; }
	//SE edge 
	if (index < 374 && ((index + 26) % 25 != 0)) {
		adjTiles[6] = arrTiles[index + 26];
	}
	else { adjTiles[6] = nullptr; }
	//SW edge cases
	if (index < 375 && (index % 25 != 0)) {
		adjTiles[7] = arrTiles[index + 24];
	}
	else { adjTiles[7] = nullptr; }
	pozish = index;
}


void Board::buildBoard(sf::RenderWindow &window, map<string, sf::Texture> textures, Tile* arrTiles[400]) {
	int count = 0;
	for (int k = 0; k < 16; k++) {
		for (int g = 0; g < 25; g++) {
			sf::Sprite spr;
			spr.setPosition(sf::Vector2f(g*32.f, k*32.f));
			spr.setTexture(textures[arrTiles[count]->textureVal]);
			window.draw(spr);
			if (arrTiles[count]->isNumber == true || arrTiles[count]->isFlag == true) {
				sf::Sprite otherSpr;
				otherSpr.setPosition(sf::Vector2f(g*32.f, k*32.f));
				otherSpr.setTexture(arrTiles[count]->texture);
				window.draw(otherSpr);
			}
			if (faceVal == "face_win" && arrTiles[count]->mine == true) {
				sf::Sprite hello;
				hello.setPosition(sf::Vector2f(g*32.f, k*32.f));
				hello.setTexture(textures["flag"]);
				window.draw(hello);
			}
			//spr.setTexture(textures[arrTiles[count]->textureVal]);
			count++;
		}
	}


	sf::Sprite face;
	face.setTexture(textures[this->faceVal]);
	face.setOrigin(sf::Vector2f(16.f, 0.f));
	face.setPosition(sf::Vector2f(400.f, 16 * 32.f));
	window.draw(face);
	sf::Sprite debug;
	debug.setTexture(textures["debug"]);
	debug.setPosition(sf::Vector2f(512.f, 16 * 32.f));
	window.draw(debug);
	sf::Sprite test1;
	test1.setTexture(textures["test_1"]);
	test1.setPosition(sf::Vector2f(576.f, 16 * 32.f));
	window.draw(test1);
	sf::Sprite test2;
	test2.setTexture(textures["test_2"]);
	test2.setPosition(sf::Vector2f(640.f, 16 * 32.f));
	window.draw(test2);
	sf::Sprite dig10;
	dig10.setTexture(textures["digits"]);
	dig10.setTextureRect(sf::IntRect(minecount / 10 * 21, 0, 21, 32));
	dig10.setPosition(sf::Vector2f(0, 16 * 32.f));
	window.draw(dig10);
	sf::Sprite dig1;
	dig1.setTexture(textures["digits"]);
	dig1.setTextureRect(sf::IntRect(minecount % 10 * 21, 0, 21, 32));
	dig1.setPosition(sf::Vector2f(21, 16 * 32.f));
	window.draw(dig1);
}

void buildTestBoard(sf::RenderWindow &window, map<string, sf::Texture> textures) {
	for (int i = 0; i < 400; i++) {
		for (int k = 0; k < 16; k++) {
			for (int g = 0; g < 25; g++) {
				sf::Sprite spr;
				spr.setPosition(sf::Vector2f(g*32.f, k*32.f));
				spr.setTexture(textures["tile_hidden"]);
				window.draw(spr);
			}
		}
	}
	sf::Sprite face;
	face.setTexture(textures["face_happy"]);
	face.setOrigin(sf::Vector2f(16.f, 0.f));
	face.setPosition(sf::Vector2f(400.f, 16 * 32.f));
	window.draw(face);
	sf::Sprite debug;
	debug.setTexture(textures["debug"]);
	debug.setPosition(sf::Vector2f(496.f, 16 * 32.f));
	window.draw(debug);
	sf::Sprite test1;
	test1.setTexture(textures["test_1"]);
	test1.setPosition(sf::Vector2f(560.f, 16 * 32.f));
	window.draw(test1);
	sf::Sprite test2;
	test2.setTexture(textures["test_2"]);
	test2.setPosition(sf::Vector2f(624.f, 16 * 32.f));
	window.draw(test2);
}

void Board::updateBoard(float x, float y, map<string , sf::Texture> textures) {
	if (faceVal == "face_lose") {
		return;
	}
	int pos;
	pos = ((int)y / 32) * 25 + (int)x / 32;
	if (arrTiles[pos]->isFlag == true) {
		return;
	}
	if (arrTiles[pos]->isMine() == false) {
		if (arrTiles[pos]->amtMines() == 0) {
			checkSurroundings(arrTiles[pos], textures);
		}
		else if (arrTiles[pos]->amtMines() == 1) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 1;
			arrTiles[pos]->texture = textures["number_1"];
		}
		else if (arrTiles[pos]->amtMines() == 2) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 2;
			arrTiles[pos]->texture = textures["number_2"];
		}
		else if (arrTiles[pos]->amtMines() == 3) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 3;
			arrTiles[pos]->texture = textures["number_3"];
		}
		else if (arrTiles[pos]->amtMines() == 4) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 4;
			arrTiles[pos]->texture = textures["number_4"];
		}
		else if (arrTiles[pos]->amtMines() == 5) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 5;
			arrTiles[pos]->texture = textures["number_5"];
		}
		else if (arrTiles[pos]->amtMines() == 6) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->texture = textures["number_6"];
		}
		else if (arrTiles[pos]->amtMines() == 7) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 7;
			arrTiles[pos]->texture = textures["number_7"];
		}
		else if (arrTiles[pos]->amtMines() == 8) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 8;
			arrTiles[pos]->texture = textures["number_8"];
		}
	}
	else {
		loser(textures);
	}
	if (didIJustWin()) {
		winner(textures);
	}
}

void Board::updateBoard(int pos, map<string, sf::Texture> textures) {
	/*
	if (faceVal == "face_lose") {
		return;
	}
	*/
	if (arrTiles[pos]->isMine() == false) {
		if (arrTiles[pos]->amtMines() == 0) {
			checkSurroundings(arrTiles[pos], textures);
		}
		else if (arrTiles[pos]->amtMines() == 1) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 1;
			arrTiles[pos]->texture = textures["number_1"];
		}
		else if (arrTiles[pos]->amtMines() == 2) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 2;
			arrTiles[pos]->texture = textures["number_2"];
		}
		else if (arrTiles[pos]->amtMines() == 3) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 3;
			arrTiles[pos]->texture = textures["number_3"];
		}
		else if (arrTiles[pos]->amtMines() == 4) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 4;
			arrTiles[pos]->texture = textures["number_4"];
		}
		else if (arrTiles[pos]->amtMines() == 5) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 5;
			arrTiles[pos]->texture = textures["number_5"];
		}
		else if (arrTiles[pos]->amtMines() == 6) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->texture = textures["number_6"];
		}
		else if (arrTiles[pos]->amtMines() == 7) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 7;
			arrTiles[pos]->texture = textures["number_7"];
		}
		else if (arrTiles[pos]->amtMines() == 8) {
			arrTiles[pos]->textureVal = "tile_revealed";
			arrTiles[pos]->isNumber = true;
			arrTiles[pos]->number = 8;
			arrTiles[pos]->texture = textures["number_8"];
		}
	}
	else {
		arrTiles[pos]->textureVal = "tile_revealed";
		arrTiles[pos]->isNumber = true;
		arrTiles[pos]->texture = textures["mine"];
	}
}