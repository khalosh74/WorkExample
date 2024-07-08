#include <SDL.h>
#include "Label.h"
#include "Session.h"
#include "BoxCollider.h"
#include "Image.h"
#include <string>
#include <iostream>
#include <random>

using namespace gui;
static int count = 0;
static int seconds = 0;
static int enemySpawnTime = 2;
static int moveAmount = 12;
static bool canSpawn = true;
std::vector<Component*> items;
std::vector<Component*> enemies;
Position movement(int x, int y) {
	return Position(x, y);
}

int getRandomNumber(int min, int max) {
	std::random_device rd; // seed the random number generator
	std::mt19937 gen(rd()); // use the Mersenne Twister 19937 generator
	std::uniform_int_distribution<> distr(min, max); // create a distribution object that maps to the range [min, max]
	return distr(gen); // generate a random number from the distribution object
}
void remove(Component* c)
{
	if (c->getName() == "enemy") {
		auto it = std::find(enemies.begin(), enemies.end(), c);
		if (it != enemies.end()) {
			enemies.erase(it);
		}
	}

}

int main(int argc, char** argv) {
	Session ses;

	Label* score = Label::getInstance("0");
	Image* player = Image::getInstance("Color 7_BigBlue.png");
	Image* box = Image::getInstance("Color 1_BigBlue.png");
	Image* box2 = Image::getInstance("Color 1_BigBlue.png");

	BoxCollider* bc = BoxCollider::getInstance();
	BoxCollider* bc2 = BoxCollider::getInstance();
	BoxCollider* bc3 = BoxCollider::getInstance();
	bool moveRight = false;
	bool canMoveRight = true;
	bool moveLeft = false;
	bool canMoveLeft = true;
	Position pos1(100, 550);
	Position pos2(750, 550);
	Position pos3(0, 550);

	std::string enemyName = "enemy";
	std::string playerName = "player";
	std::string ballName = "ball";
	player->setName(playerName);

	bc->add(player);
	bc2->addAll({ box });
	bc3->addAll({ box2 });
	bc->setPosition(pos1);
	bc2->setPosition(pos2);
	bc3->setPosition(pos3);
	ses.add(player);
	ses.add(box);
	ses.add(box2);
	ses.add(score);
	ses.update([&pos1, &bc, &moveRight, &moveLeft, &canMoveRight, &canMoveLeft, &ses, &enemyName, &score] {
		count++;
		if (count % ses.getFPS() == 0) {
			seconds++;
			score->setText(std::to_string(seconds));
		}
		//Player
		if (moveRight && canMoveRight) {
			pos1.x += moveAmount;
			bc->setPosition(pos1);
		}
		else if(moveLeft && canMoveLeft){
			pos1.x -= moveAmount;
			bc->setPosition(pos1);
		}
		//bullets/Balls
		for (Component* item : items) {
			Position posTemp(item->getPosition().x, item->getPosition().y-moveAmount);
			item->setPosition(posTemp);
		}
		//Enemies
		if ((seconds+1) % enemySpawnTime == 0) canSpawn = true;
		if (seconds % enemySpawnTime == 0 && canSpawn) {
			Image* enemy = Image::getInstance("bird.png");
			BoxCollider* ebc = BoxCollider::getInstance();
			ses.add(enemy);
			ebc->add(enemy);
			ebc->setName(enemyName);
			Position posTemp(getRandomNumber(50, 400), 0);
			ebc->setPosition(posTemp);
			enemies.push_back(ebc);
			canSpawn = false;
;		}
		for (Component* enemy : enemies) {
			Position posTemp(enemy->getPosition().x, enemy->getPosition().y + (moveAmount / 3));
			enemy->setPosition(posTemp);
		}
		});

	bc->onCollisionEnter([&pos1, &bc, &canMoveRight, &canMoveLeft, &ses, &enemyName](BoxCollider* other) {
		if (other->getName() == enemyName) ses.quit();
		if (other->getPosition().x > pos1.x){ 
			if(canMoveRight)pos1.x -= moveAmount;
			canMoveRight = false; 
		}
		else if(other->getPosition().x < pos1.x) { 
			if(canMoveLeft)pos1.x += moveAmount;
			canMoveLeft = false; 
		}
		});
	ses.addKeyDownCallback(SDLK_RIGHT, [&moveRight, &canMoveLeft] {moveRight = true; canMoveLeft = true; });
	ses.addKeyUpCallback(SDLK_RIGHT, [&moveRight] {moveRight = false;});
	ses.addKeyDownCallback(SDLK_LEFT, [&moveLeft, &canMoveRight] {moveLeft = true; canMoveRight = true; });
	ses.addKeyUpCallback(SDLK_LEFT, [&moveLeft] {moveLeft = false;});

	ses.addKeyDownCallback(SDLK_SPACE, [&player, &ses, &ballName] {
		Image* ball = Image::getInstance("Button Normal.png");
		BoxCollider* bbc = BoxCollider::getInstance();
		Position pos4(player->getPosition());
		bbc->setPosition(pos4);
		bbc->add(ball);
		bbc->setName(ballName);
		bbc->onCollisionEnter([](BoxCollider* other) {
			if (other->getName() == "enemy") {
				other->clear();
				remove(other);
			}
			});
		ses.add(ball);
		items.push_back(bbc);
		});
	ses.addMouseDownButtonCallback(SDL_BUTTON_LEFT, [](int x, int y) {
		std::cout << "SHOOT!";
		});

	ses.run();
	items.clear();
	enemies.clear();
	return 0;
}