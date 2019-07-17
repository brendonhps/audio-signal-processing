// Brendon Henrique de Paula da Silva 
// Grr 201702

#include <stdio.h>
#include <stdlib.h>
#include "opensound.h"
#include <string.h>
#include "linhasdecomando.h"

int main (int argc, char ** argv )
{
soundWAV fileINPUT;
int i,
 	saidapos,
 	SAVE,
 	eh_primeiravez = 0;
char *saida;
unsigned int savedata_size,
			 sample_verif;


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
	output = fopen(saida, "a+");
		if (!output)
		{
			fprintf(stderr, "%s", "Erro na abertura do arquivo destino\n");
			exit(1);
		}
}
else	
{
	output = stdout;
}



for (i=1;i<argc;++i)
	{
		// Abriremos todos os arquivos passados por argumento que sejam diferentes de -o ou que na sejam antecedidos por -o 
		if ((strcmp (argv[i],"-o") != 0) && (strcmp (argv[i-1],"-o") != 0))
		{
			open_sound (argv[i],&fileINPUT);
			// Se o arquivo aberto for nulo vamos ao proximo
			if (fileINPUT.data_size == 0)
				continue;
			else
			{
				if (output == NULL)
				{
					fprintf(stderr, "%s", "O output nao pode ser aberto\n");
					exit(1);
				}
				else
				{
					// Quando abrir o primeiro arquivo teremos uma variavel para marcar isso e somente na primeira vez que um arquivo for aberto vamos escrever no arquivo saida parte de seu header
					if (eh_primeiravez != 1)
					{ 
						eh_primeiravez = 1;
						sample_verif = fileINPUT.sample_rate;
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
						// Vamos salvando o tamanho do data para no final voltarmos a escrever todo o datasize do arquivo final 
						SAVE = fileINPUT.data_size;
						savedata_size = savedata_size + SAVE;
						fseek(output,sizeof(&fileINPUT.data_size),SEEK_CUR);
						fwrite(fileINPUT.DATA,sizeof(short),fileINPUT.data_size/(fileINPUT.bits_per_sample/8),output);
					}
					else
					{		
						// Verificacao do sample rate
						if (sample_verif == fileINPUT.sample_rate) 
						{			
							// Para o segundo arquivo em diante so escrevemos no arquivo final o conteudo do data 
							SAVE = fileINPUT.data_size;
							savedata_size = savedata_size + SAVE;
							fwrite(fileINPUT.DATA,sizeof(short),fileINPUT.data_size/(fileINPUT.bits_per_sample/8),output);	
						}	
						else 
						{
							fprintf(stderr, "%s","Sample rate diferente entre os arquivos");
							exit(1);
						}
					}

				}
			}
		}
		else
			continue;
	}

rewind (output);
// Setamos em datasize do arquivo destino e escrevemos o datasize total dos arquivos escritos
fseek(output,40,SEEK_SET);
fwrite((void*)&savedata_size,sizeof(int),1,output);

//Liberacao de memoria alocada
free(fileINPUT.DATA);
free(saida);
return 0;
}