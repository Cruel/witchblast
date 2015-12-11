/**  This file is part of Witch Blast.
  *
  *  Witch Blast is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  Witch Blast is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with Witch Blast.  If not, see <http://www.gnu.org/licenses/>.
  */

#include "Game.h"

#include "GameEntity.h"
#include "EntityManager.h"

#include <iostream>

Game::Game()
{
}

void Game::create(int screenWidth, int screenHeight, std::string windowsTitle, bool fullScreen, bool vsync)
{
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;

//  if (fullScreen)
//    app = new cpp3ds::RenderWindow(cpp3ds::VideoMode(this->screenWidth, this->screenHeight), windowsTitle, cpp3ds::Style::Fullscreen);
//  else
//    app = new cpp3ds::RenderWindow(cpp3ds::VideoMode(this->screenWidth, this->screenHeight), windowsTitle);
//  if (vsync) app->setVerticalSyncEnabled(true);
//  else app->setFramerateLimit(60);
}

Game::~Game()
{
  printf("Deleting the game...\n");
  delete(app);
}

float Game::getAbsolutTime()
{
  static cpp3ds::Clock clock;
  return clock.getElapsedTime().asSeconds();
}

void Game::startGame()
{
  lastTime = getAbsolutTime();

  // Start game loop
  while (app->isOpen())
  {
    // Process events
    cpp3ds::Event event;

    while (app->pollEvent(event))
    {
      // Close window : exit
      if (event.type == cpp3ds::Event::Closed)
        app->close();

    }

    onUpdate();
    onRender();
  }

  quitGame();
}

void Game::quitGame()
{
}

void Game::onRender()
{
  // clear the view
  app->clear(cpp3ds::Color(32, 32, 32));

  // render the game objects
  EntityManager::getInstance().render(app);

  app->display();
}

void Game::onUpdate()
{
  float delta = getAbsolutTime() - lastTime;
  lastTime = getAbsolutTime();
  EntityManager::getInstance().animate(delta);
}

void Game::update(float delta)
{

}

void Game::processEvent(cpp3ds::Event &event)
{

}

void Game::renderTopScreen(cpp3ds::Window &window)
{
	app = &window;
}

void Game::renderBottomScreen(cpp3ds::Window &window)
{

}
