#include "raylib.h"
#include <stddef.h>
#include "game.h"
#include "audio_manager.h"

typedef struct {
    Music intro;
    Music puzzle;
    Music ending;

    Music *currentMusic;

    float volume;
    bool isMuted;

    GameScene lastScene;

} AudioManager;

static AudioManager audio;

void InitAudioManager() {
    InitAudioDevice();

    audio.intro = LoadMusicStream("../assets/music/Intro.mp3");
    audio.puzzle = LoadMusicStream("../assets/music/Game.mp3");
    audio.ending = LoadMusicStream("../assets/music/ending.mp3");

    audio.currentMusic = NULL;
    audio.volume = 1.0f;
    audio.isMuted = false;
    audio.lastScene = -1;
}

void ApplyVolume() {
    if (audio.currentMusic == NULL) return;

    if (audio.isMuted) {
        SetMusicVolume(*audio.currentMusic, 0.0f);
    } else {
        SetMusicVolume(*audio.currentMusic, audio.volume);
    }
}

void PlayMusicByScene(GameScene scene) 
{    
    if (scene == audio.lastScene) return;

    Music *newMusic = NULL;

    switch(scene)
    {
        case SCENE_MENU:
        case SELECT_ROLE:
            newMusic = NULL;
            break;

        case SCENE_INTRO:
            newMusic = &audio.intro;
            break;

        case SCENE_PUZZLE1:
        case SCENE_PUZZLE2:
        case SCENE_PUZZLE3:
        case SCENE_PUZZLE4:
            newMusic = &audio.puzzle;
            break;

        case SCENE_ENDING:
            newMusic = &audio.ending;
            break;
    }

    // stop music lama
    
    if (audio.currentMusic != newMusic && audio.currentMusic != NULL) {
        StopMusicStream(*audio.currentMusic);
    }
    
    audio.currentMusic = newMusic;
    
    // play baru
    if (audio.currentMusic != NULL) {
        PlayMusicStream(*audio.currentMusic);
        ApplyVolume();
    }

    audio.lastScene = scene;
}

void UpdateAudioManager() {
    if (audio.currentMusic != NULL) {
        UpdateMusicStream(*audio.currentMusic);
    }
}

void UnloadAudioManager()
{
    CloseAudioDevice();
}

void ToggleMute() {
    audio.isMuted = !audio.isMuted;
    ApplyVolume();
}

void SetVolume(float volume) {
    audio.volume = volume;
    ApplyVolume();
}

float GetVolume() {
    return audio.volume;
}

bool IsMuted() {
    return audio.isMuted;
}