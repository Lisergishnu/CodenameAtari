#include "audio.h"

Mix_Chunk *themeSnd;
Mix_Chunk *hit1Snd;
Mix_Chunk *hit2Snd;
Mix_Chunk *hit3Snd;
Mix_Chunk *hit4Snd;
Mix_Chunk *menuSnd;
Mix_Chunk *scoringSnd;
Mix_Chunk *lossHealthSnd;
Mix_Chunk *climbSnd;
Mix_Chunk *powerupSnd;
Mix_Chunk *breakdownSnd;

  void
initAudio()
{
  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 ) == -1 )
  {
    printf("Error: Couldn't initialize audio...\n");
  }
}

void
loadAudioClips()
{
  /* Load intro sound */
  themeSnd = Mix_LoadWAV("snd/theme.wav");
  ASSERT_AUDIO(themeSnd);

  /* Load different sounds for shield hits */
  hit1Snd = Mix_LoadWAV("snd/hit1.wav");
  ASSERT_AUDIO(hit1Snd);
  hit2Snd = Mix_LoadWAV("snd/hit2.wav");
  ASSERT_AUDIO(hit2Snd);
hit3Snd = Mix_LoadWAV("snd/hit3.wav");
  ASSERT_AUDIO(hit3Snd);
hit4Snd = Mix_LoadWAV("snd/hit4.wav");
  ASSERT_AUDIO(hit4Snd);

  /* Load menu switching sound */
  menuSnd = Mix_LoadWAV("snd/menu.wav");
  ASSERT_AUDIO(menuSnd);

  /* Load scoring clicking sound */
  scoringSnd = Mix_LoadWAV("snd/scoring.wav");
  ASSERT_AUDIO(scoringSnd);

  /* Load loss health sound */
  lossHealthSnd = Mix_LoadWAV("snd/lossHealth.wav");
  ASSERT_AUDIO(lossHealthSnd);

  /* Load climbing sound */
  climbSnd = Mix_LoadWAV("snd/climb.wav");
  ASSERT_AUDIO(climbSnd);

  /* Load powerup sound */
  powerupSnd = Mix_LoadWAV("snd/powerup.wav");
  ASSERT_AUDIO(powerupSnd);

  /* Load lift breakdown sound */
  breakdownSnd = Mix_LoadWAV("snd/breakdown.wav");
  ASSERT_AUDIO(breakdownSnd);
}

void
playSound(AudioClip c)
{
  int ch;
  switch(c)
  {
    case AC_THEME:
        Mix_PlayChannel( -1, themeSnd, 0);
        break;
    case AC_HIT:
        ch = rand() % 4 + 1;
        switch (ch)
        {
          case 1:
            Mix_PlayChannel( -1 , hit1Snd, 0);
            break;
          case 2:
            Mix_PlayChannel( -1 , hit2Snd, 0);
            break;
          case 3:
            Mix_PlayChannel( -1 , hit3Snd, 0);
            break;
          case 4:
            Mix_PlayChannel( -1, hit4Snd, 0);
            break;
        }
        break;
    case AC_MENU:
        Mix_PlayChannel( -1, menuSnd, 0);
        break;
    case AC_SCORING:
        Mix_PlayChannel( -1, scoringSnd, 0);
        break;
    case AC_LOSS_HEALTH:
        Mix_PlayChannel( -1, lossHealthSnd, 0);
        break;
    case AC_CLIMB:
        Mix_PlayChannel( -1, climbSnd, 0);
        break;
    case AC_POWERUP:
        Mix_PlayChannel( -1, powerupSnd, 0);
        break;
    case AC_BREAKDOWN:
        Mix_PlayChannel( -1, breakdownSnd, 0);
        break;
  }
}

  void
cleanupAudio()
{
  Mix_FreeChunk(breakdownSnd);
  Mix_FreeChunk(powerupSnd);
  Mix_FreeChunk(climbSnd);
  Mix_FreeChunk(lossHealthSnd);
  Mix_FreeChunk(scoringSnd);
  Mix_FreeChunk(menuSnd);
  Mix_FreeChunk(hit4Snd);
  Mix_FreeChunk(hit3Snd);
  Mix_FreeChunk(hit2Snd);
  Mix_FreeChunk(hit1Snd);
  Mix_FreeChunk(themeSnd);
  Mix_CloseAudio();
  Mix_Quit();
}
