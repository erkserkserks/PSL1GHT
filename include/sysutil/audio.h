#pragma once

#include <psl1ght/types.h>
#include <stdlib.h>

EXTERN_BEGIN

#define AUDIO_OUT_PRIMARY 0
#define AUDIO_OUT_SECONDARY 1

typedef struct {
  uint8_t type;
  uint8_t channel;
  uint8_t fs;
  uint8_t reserved;
  uint32_t layout;
} AudioOutSoundMode;

typedef struct {
  uint8_t port_type;
  uint8_t num_modes;
  uint8_t state;
  uint8_t reserved[3];
  uint16_t latency;
  AudioOutSoundMode modes[16];
} AudioOutDeviceInfo;

typedef struct {
  uint8_t channel;
  uint8_t encoder;
  uint8_t reserved[10];
  uint32_t down_mixer;
} AudioOutConfiguration;

typedef struct {
  uint8_t state;
  uint8_t encoder;
  uint8_t reserved[6];
  uint32_t down_mixer;
  AudioOutSoundMode soundMode;
} AudioOutState;

#define AUDIO_OUT_CODING_TYPE_LPCM        0
#define AUDIO_OUT_CODING_TYPE_AC3         1
#define AUDIO_OUT_CODING_TYPE_MPEG1       2 
#define AUDIO_OUT_CODING_TYPE_MP3         3
#define AUDIO_OUT_CODING_TYPE_MPEG2       4
#define AUDIO_OUT_CODING_TYPE_AAC         5
#define AUDIO_OUT_CODING_TYPE_DTS         6
#define AUDIO_OUT_CODING_TYPE_ATRAC       7
#define AUDIO_OUT_CODING_TYPE_BITSTREAM   255

#define AUDIO_OUT_FS_32KHZ                     0x01
#define AUDIO_OUT_FS_44KHZ                     0x02
#define AUDIO_OUT_FS_48KHZ                     0x04
#define AUDIO_OUT_FS_88KHZ                     0x08
#define AUDIO_OUT_FS_96KHZ                     0x10
#define AUDIO_OUT_FS_176KHZ                    0x20
#define AUDIO_OUT_FS_192KHZ                    0x40

#define AUDIO_OUT_DOWNMIXER_NONE   0
#define AUDIO_OUT_DOWNMIXER_TYPE_A 1   // >2 channels
#define AUDIO_OUT_DOWNMIXER_TYPE_B 2   // >6 channels


int audioOutGetNumberOfDevice(uint32_t out);
int audioOutGetDeviceInfo(uint32_t out, uint32_t index,
			  AudioOutDeviceInfo *info);
int audioOutGetSoundAvailability(uint32_t audioOut, uint32_t type,
				 uint32_t fs, uint32_t option);

int audioOutConfigure(uint32_t out, AudioOutConfiguration *conf,
		      uint32_t *option, uint32_t wait_for_event);
		      
int audioOutGetState(uint32_t out, uint32_t deviceindex, AudioOutState *state);
