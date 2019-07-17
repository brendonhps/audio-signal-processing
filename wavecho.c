// Brendon Henrique de Paula da Silva 
// Grr 20170203


#include <stdio.h>
#include <stdlib.h>
#include "opensound.h"
#include <string.h>
#include "linhasdecomando.h"


int main (int argc, char **argv)
{
// Variaveis locais utilizadas
soundWAV fileINPUT;
int saidapos,
   delay,
	aux,
	eco_deslocamento;
char *saida;
float aten;
	
// Funcao especifica para abrir os .wav passados por argumento em alguns filtros, retorna erros em caso de falta de parametro ou de entrada nao encontrada
// ou retorna o arquivo ja aberto
fileINPUT = wavparam(argc, argv, fileINPUT);

saidapos = devolve_pos_saida(argc,argv);

	
if (saidapos != 0)
{
	saida = malloc (sizeof (char) * (strlen (argv[saidapos])+ 1));
	strcpy(saida,argv[saidapos]);
	saida[(strlen(argv[saidapos])+1)] = 0;
}	
else
{
	saida = malloc (sizeof(char));
	saida[0] = 0;
}
	
FILE *output;

if (saida[0] != 0)
{
	output = fopen(saida, "w");
		if (!output)
		{
			fprintf(stderr, "%s", "Erro na abertura da saida\n");
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

		if (level_param_pos(argc,argv) == 0) 
			aten = 0.5; // Valor default de aten
		else 
			aten = atof(argv[level_param_pos(argc,argv)]);

		if ((aten < 0.0) || (aten > 1.0))	
		{
			fprintf(stderr, "%s","Atenuacao fora do padrao <Limite permitido : 0.0 ate 1.0>\n" );
			exit(1);
		}

		if (level_eco(argc,argv) == 0)
			delay = 1000; // Valor default de delay
		else 
			delay = atoi(argv[level_eco(argc,argv)]);

			if (delay < 0)	
			{
				fprintf(stderr, "%s","Delay fora do padrao <Limite permitido :Inteiro maior que 0>\n" );
				exit(1);
			}

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

			eco_deslocamento = fileINPUT.sample_rate * (delay / 1000);
		
			for (aux=0;aux<(fileINPUT.data_size/2);aux++)
			{
				fileINPUT.DATA[aux+eco_deslocamento] = fileINPUT.DATA[aux+eco_deslocamento] + (fileINPUT.DATA[aux] * aten);
				fwrite (&fileINPUT.DATA[aux],sizeof(short),1,output);
			}
	}

free (fileINPUT.DATA);
free (saida);
return 0;
}