#pragma once
//for referencing sounds. These are the internal names of each.
enum SoundsList {
    Jump,Swipe,GoatDeath
};

//for notifying the sound event, basically exists to let us use event system easily.
struct SoundParams {
    SoundsList sound;
    float x;
    float y;
    float z;
};

