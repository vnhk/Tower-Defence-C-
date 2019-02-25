#include "HUD.h"

void HUD::draw(sf::RenderWindow &window)
{
	if (active)
	{
		window.draw(hudSprite);
		window.draw(taSprite);
		window.draw(tcSprite);
		window.draw(tgSprite);
		window.draw(tsSprite);
	}
}

HUD::HUD(sf::RenderWindow &window)
{
	active = true;

	hudTexture.loadFromFile("Textures/HUD/HUD.png");
	hudSprite.setPosition(1000, 0);
	hudSprite.setTexture(hudTexture);
	towerok.loadFromFile("Textures/HUD/ok.png");
	taSprite.setTexture(towerok);
	tgSprite.setTexture(towerok);
	tcSprite.setTexture(towerok);
	tsSprite.setTexture(towerok);
	taSprite.setPosition(1150, 50);
	tgSprite.setPosition(1150, 190);
	tcSprite.setPosition(1150, 330);
	tsSprite.setPosition(1150, 470);
}

int HUD::getSelectedTower()
{
	if (selectedTower >= 0 && selectedTower <= 3)
		return selectedTower;
	else
		return -1;
}

void HUD::click(sf::Vector2i mouse, TowerPlace &TP)
{
	if (active)
	{
		if (taSprite.getGlobalBounds().contains(mouse.x, mouse.y))
			selectedTower = 1;
		else if (tgSprite.getGlobalBounds().contains(mouse.x, mouse.y))
			selectedTower = 0;
		else if (tcSprite.getGlobalBounds().contains(mouse.x, mouse.y))
			selectedTower = 2;
		else if (tsSprite.getGlobalBounds().contains(mouse.x, mouse.y))
			selectedTower = 3;
		TP.setTexture(selectedTower);
	}
}