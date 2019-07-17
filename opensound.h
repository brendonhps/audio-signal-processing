// Brendon Henrique de Paula da Silva 
// Grr 20170203


#ifndef __OPENSOUND__

#define __OPENSOUND__



// Definicao da estrutura de um arquivo WAV
typedef struct
{

    unsigned char riff_tag[5], wave_tag[5], form_tag[5], data_tag[5];

    unsigned int riff_size, fmt_size, sample_rate, byte_rate, data_size, samples_channel;

    short  audio_format, num_channels, block_align, bits_per_sample;

    short  *DATA;

} soundWAV;

// Funcao para ler um arquivo de som , recebendo o nome do arquivo de som como parametro
soundWAV open_sound(char *filename, soundWAV *music);


#endif
