// Brendon Henrique de Paula da Silva 
// Grr 20170203

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opensound.h"

soundWAV open_sound(char filename[], soundWAV *music)
{
	
	FILE *ptr;

// Abre o arquivo que foi passado por parametro , caso a primeira letra da minha string seja difente de 0
	if (filename[0] != 0) 
	{
		ptr = fopen(filename, "r");

// Verificando se o arquivo foi aberto com sucesso 
		if (!ptr)
		{

			fprintf(stderr, "%s", "Erro na abertura do arquivo\n");
			exit(1);
		}
	}


// Caso o nome do arquivo que foi passado por parametro seja Nulo (caracteres nulos), abriremos o arquivo da entrada padrao 

	else
	{
		ptr = stdin;
	}

	if (ptr == NULL)
	{
		fprintf(stderr, "%s", "O arquivo nao pode ser aberto\n");
		exit(1);
	}
	else
	{

		rewind(ptr);
		fread((*music).riff_tag, sizeof(unsigned char), 4, ptr);	
		fread(&(*music).riff_size, sizeof(unsigned int), 1, ptr);
		fread((*music).wave_tag, sizeof(unsigned char), 4, ptr);
		fread((*music).form_tag, sizeof(unsigned char), 4, ptr);
		fread(&(*music).fmt_size, sizeof(unsigned int), 1, ptr);
		fread(&(*music).audio_format, sizeof(short unsigned int), 1, ptr);
		fread(&(*music).num_channels, sizeof(short unsigned int), 1, ptr);
		fread(&(*music).sample_rate, sizeof(unsigned int), 1, ptr);
		fread(&(*music).byte_rate, sizeof(unsigned int), 1, ptr);
		fread(&(*music).block_align, sizeof(short unsigned int), 1, ptr);
		fread(&(*music).bits_per_sample, sizeof(short unsigned int), 1, ptr);
		fread((*music).data_tag, sizeof(unsigned char), 4, ptr);
		fread(&(*music).data_size, sizeof(unsigned int), 1, ptr);
		// Colocamos 0 na ultima posicao de cada tag para imprimir no arquivo (wavinfo.c) na forma de string
		(*music).riff_tag[4] = 0;
		(*music).wave_tag[4] = 0;
		(*music).form_tag[4] = 0;
		(*music).data_tag[4] = 0;
		(*music).DATA = malloc (((*music).data_size)*((*music).bits_per_sample/8));

		fread((*music).DATA, sizeof(short),(*music).data_size / 2, ptr);
		
		
	}

	fclose(ptr);
	return *music;
}
