/**  This file is part of sfmlGame.
  *
  *  FreeTumble is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  FreeTumble is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with FreeTumble.  If not, see <http://www.gnu.org/licenses/>.
  */

#include "SoundManager.h"
#include <iostream>


SoundManager::SoundManager()
{
  mute = false;
  volume = 100;
}

SoundManager::~SoundManager()
{
  std::cout << "Releasing audio memory... ";
  soundArray.clear();
  soundBufferArray.clear();
  std::cout << "OK" << std::endl;
}

SoundManager& SoundManager::getInstance()
{
  static SoundManager singleton;
  return singleton;
}

void SoundManager::addSound(const char* fileName)
{
  cpp3ds::SoundBuffer* newSoundBuffer = new cpp3ds::SoundBuffer;
  newSoundBuffer->loadFromFile(fileName);
  soundBufferArray.push_back(newSoundBuffer);
}

void SoundManager::playSound(int n, bool force)
{
  checkSoundStatus();

  if (mute) return;

  if (!force)
  {
    for (cpp3ds::Sound* s: soundArray)
      if (s->getBuffer() == soundBufferArray[n]) return;
  }

  stopSound(n);

  cpp3ds::Sound* newSound = new cpp3ds::Sound;
  newSound->setBuffer(*soundBufferArray[n]);
  newSound->setVolume(volume);
  soundArray.push_back(newSound);
  newSound->play();
}

void SoundManager::playPitchModSound(int n, bool force)
{
  checkSoundStatus();

  if (mute) return;

  if (!force)
  {
    for (cpp3ds::Sound* s: soundArray)
      if (s->getBuffer() == soundBufferArray[n]) return;
  }

  stopSound(n);

  cpp3ds::Sound* newSound = new cpp3ds::Sound;
  newSound->setBuffer(*soundBufferArray[n]);
  newSound->setVolume(volume);

  newSound->setPitch( (float)(75 +(rand() % 50)) / 100.0f );

  soundArray.push_back(newSound);
  newSound->play();
}

void SoundManager::stopSound(int n)
{
  {
    for (cpp3ds::Sound* s: soundArray)
      if (s->getBuffer() == soundBufferArray[n]) s->stop();
  }
}

void SoundManager::setMute(bool mute)
{
  this->mute = mute;
}

void SoundManager::setVolume(int volume)
{
  this->volume = volume;
  for (cpp3ds::Sound* s: soundArray)
    s->setVolume(volume);
}

void SoundManager::checkSoundStatus()
{
  for (unsigned int i = 0; i < soundArray.size(); i++)
  {
    cpp3ds::Sound* sound = soundArray[i];
    if (sound->getStatus() == cpp3ds::Sound::Stopped)
    {
      delete sound;
      soundArray.erase(soundArray.begin() + i);
      i--;
    }
  }
}
