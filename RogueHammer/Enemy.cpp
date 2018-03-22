#include "Enemy.h"
#include <random>

// Constructor to create enemy with random stats
Enemy::Enemy()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> hp20(10, 30); // random number in range [10, 20] C++ 11
	health = hp20(rng);
	std::uniform_int_distribution<std::mt19937::result_type> att20(7, 18);
	attack = att20(rng);
}

Enemy::~Enemy()
{
}

// Method to create game boss with fixed stats

void Enemy::createBoss(int hp, int att)
{
	health = hp;
	attack = att;
}

int Enemy::getRandomHealth()
{
	int randomHealth;
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> hp30(15, 30); // random number in range [15, 30] C++ 11
	randomHealth = hp30(rng);
	return randomHealth;
}


