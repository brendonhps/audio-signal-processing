// Brendon Henrique de Paula da Silva 
// Grr 20170203
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opensound.h"
#include "linhasdecomando.h"
#define PICOMAX 32767

int main (int argc, char **argv)
{

	// Variaveis locais utilizadas
	soundWAV fileINPUT;
	int Saidapos,
		aux,
		max=0;
	char *Saida;
	float fatordeajuste;
	

	
// Funcao especifica para abrir os .wav passados por argumento em alguns filtros, retorna erros em caso de falta de parametro ou de entrada nao encontrada
// ou retorna o arquivo ja aberto	

fileINPUT = wavparam(argc, argv, fileINPUT);

Saidapos = devolve_pos_saida(argc,argv);

	
if (Saidapos != 0)
{
	Saida = malloc (sizeof (char) * (strlen (argv[Saidapos])+ 1));
	strcpy(Saida,argv[Saidapos]);
	Saida[(strlen(argv[Saidapos])+1)] = 0;
}	
else
{
	Saida = malloc (sizeof(char) * 2);
	Saida[0] = 0;
}

	 
FILE *output;

if (Saida[0] != 0)
{
	output = fopen(Saida, "w");
		if (!output)
		{
			fprintf(stderr, "%s", "Erro na abertura da Saida\n");
			exit(1);
		}
}
else	
{
	output = stdout;
}
	if (output == NULL)
	{
		fprintf(stderr, "%s", "O output nao pode ser aberto\n");
		exit(1);
	}
	else
	{
		// Escrevemos o mesmo header no arquivo de saida 
		fwrite(fileINPUT.riff_tag, sizeof(unsigned char), 4, output);
		fwrite(&fileINPUT.riff_size, sizeof(unsigned int), 1, output);
		fwrite(fileINPUT.wave_tag, sizeof(unsigned char), 4, output);
		fwrite(fileINPUT.form_tag, sizeof(unsigned char), 4, output);
		fwrite(&fileINPUT.fmt_size, sizeof(unsigned int), 1, output);
		fwrite(&fileINPUT.audio_format, sizeof(short unsigned int), 1, output);
		fwrite(&fileINPUT.num_channels, sizeof(short unsigned int), 1, output);
		fwrite(&fileINPUT.sample_rate, sizeof(unsigned int), 1, output);
		fwrite(&fileINPUT.byte_rate, sizeof(unsigned int), 1, output);
		fwrite(&fileINPUT.block_align, sizeof(short unsigned int), 1, output);
		fwrite(&fileINPUT.bits_per_sample, sizeof(short unsigned int), 1, output);
		fwrite(fileINPUT.data_tag, sizeof(unsigned char), 4, output);	
		fwrite(&fileINPUT.data_size, sizeof(unsigned int), 1, output);

		
		for(aux=0;aux<(fileINPUT.data_size/2);aux++)
		{
			// Laco para obter o maior valor dentro das amostras
			if (fileINPUT.DATA[aux] > max)
				max = fileINPUT.DATA[aux];
				
			

		}

		

		// fator de ajuste se trata do valor maximo possivel = PICOMAX dividido pelo maior valor encontrado nas amostras
		fatordeajuste = (PICOMAX / (max * 1.000));
		
		for(aux=0;aux<(fileINPUT.data_size/2);aux++)
		{
			// Neste laco vamos multiplicar da primeira ate a ultima posicao do DATA pelo volume
			fileINPUT.DATA[aux] = fatordeajuste * fileINPUT.DATA[aux];

			if (fileINPUT.DATA[aux] > PICOMAX)
				fileINPUT.DATA[aux] = PICOMAX;

			if (fileINPUT.DATA[aux] < -32768)
				fileINPUT.DATA[aux] = -32767;

		}
	

		// Escrevemos o conteudo ja alterado no arquivo de saida 

		fwrite (fileINPUT.DATA,sizeof(short),fileINPUT.data_size/(fileINPUT.bits_per_sample/8),output);
		
	}
// Liberacao de memoria alocada
free (fileINPUT.DATA);
free (Saida);
return 0;
}
