// Brendon Henrique de Paula da Silva 
// Grr 20170203

#include <stdio.h>
#include <stdlib.h>
#include "opensound.h"
#include <string.h>
#include "linhasdecomando.h"

int main(int argc, char **argv)
{
    // Variaveis locais utilizadas 
    soundWAV file;
    int samplesperchannel;

    // Funcao espericifica para tratar parametros do arquivo (wavinfo.c)
	file = wavinfoparam(argc, argv, file);

	// Impressao das informacoes do arquivo .wav
    printf("riff tag        : \"%s\" \n", file.riff_tag);
    printf("riff size       : %d \n", file.riff_size);
    printf("wave tag        : \"%s\" \n", file.wave_tag);
    printf("form tag        : \"%s\" \n", file.form_tag);
    printf("fmt_size        : %d \n", file.fmt_size);
    printf("audio_format    : %d \n", file.audio_format);
    printf("num_channels    : %d \n", file.num_channels);
    printf("sample_rate     : %d \n", file.sample_rate);
    printf("byte_rate       : %d \n", file.byte_rate);
    printf("block_align     : %d \n", file.block_align);
    printf("bits_per_sample : %d \n", file.bits_per_sample);
    printf("data tag        : \"%s\" \n", file.data_tag);
    printf("data size       : %d \n", file.data_size);

    // Calculo do numero de samples por canal do arquivo WAV
    samplesperchannel = file.data_size / file.block_align;
    printf("samples/channel : %d \n", samplesperchannel);
    
    // Liberacao de memoria alocada
    free(file.DATA);
    return 0;
}