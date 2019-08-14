#ifndef __SOUNDS_H__
#define __SOUNDS_H__

#ifdef __OSDK__
#define __asm__(x)
#endif

#define AY_AChanelL 0
#define AY_AChanelH 1
#define AY_BChanelL 2
#define AY_BChanelH 3
#define AY_CChanelL 4
#define AY_CChanelH 5
#define AY_Noise 6
#define AY_Status 7
#define AY_AmplitudeA 8
#define AY_AmplitudeB 9
#define AY_AmplitudeC 10
#define AY_EnvelopeL 11
#define AY_EnvelopeH 12
#define AY_Envelope 13

void sfxNative(int addr);
void w8912(unsigned char reg, unsigned char val);
void sfx(unsigned int *soundTable);

static unsigned char isSoundDisabled = 0;

unsigned int *currentSFXTable;
unsigned char sfxPlayerStatus = 0;

unsigned char sfxPlayerVolumeReduction = 1; // 1,2,3,4

static unsigned char sfxNativeReset[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
void sfxNative(int addr)
{
    __asm__("ldy #0");
    __asm__("lda (sp),y");
    __asm__("tax");
    __asm__("iny");
    __asm__("lda (sp),y");
    __asm__("tay");
    __asm__("jsr $FA86");
}

void w8912(unsigned char reg, unsigned char val)
{
    __asm__("ldy #0");
    __asm__("lda (sp),y");
    __asm__("tax");
    __asm__("iny");
    __asm__("lda (sp),y");
    __asm__("jsr $F590");
}

void sfx(unsigned int *soundTable)
{
    unsigned char i, stat;

    if (isSoundDisabled)
    {
        return;
    }

    sfxNative((int)&sfxNativeReset);

    w8912(AY_BChanelL, 0);
    w8912(AY_BChanelH, 0);
    w8912(AY_CChanelL, 0);
    w8912(AY_CChanelH, 0);
    w8912(AY_AmplitudeB, 0);
    w8912(AY_AmplitudeC, 0);

    currentSFXTable = soundTable;
    sfxPlayerStatus = 1;

    if (sfxPlayerStatus == 0)
        return;

    while (*currentSFXTable != 0xffff)
    {

        stat = 127;

        //tone
        if (currentSFXTable[0])
        {
            stat &= 255 - 1;
        }

        //noise
        if (currentSFXTable[1])
        {
            stat &= 255 - 8;
        }

        w8912(AY_AChanelL, currentSFXTable[0] % 256);
        w8912(AY_AChanelH, currentSFXTable[0] / 256);

        w8912(AY_Status, stat);
        w8912(AY_AmplitudeA, (currentSFXTable[2] / sfxPlayerVolumeReduction));
        w8912(AY_Noise, currentSFXTable[1]);

        w8912(AY_EnvelopeL, 200);
        w8912(AY_EnvelopeH, 7);
        w8912(AY_Envelope, 0);

        wait(2);

        currentSFXTable += 3;
    }

    w8912(AY_Status, 127);
    return;
}

#endif __SOUNDS_H__
