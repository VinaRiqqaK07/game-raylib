#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "scene_manager.h"

void InitAudioManager();
void UpdateAudioManager();

void PlayMusicByScene(GameScene scene);
void UnloadAudioManager();

void ToggleMute();
void SetVolume(float volume);
float GetVolume();
bool IsMuted();

#endif