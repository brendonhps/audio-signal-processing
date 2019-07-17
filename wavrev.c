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
char *saida;
soundWAV fileINPUT;
int Saidapos,
aux;
	

// Funcao especifica para abrir os .wav passados por argumento em alguns filtros, retorna erros em caso de falta de parametro ou de entrada nao encontrada
// ou retorna o arquivo ja aberto	

fileINPUT = wavparam(argc, argv, fileINPUT);


Saidapos = devolve_pos_saida(argc,argv);

if (Saidapos != 0)
{
	// Copia o nome da saida saida dado no argumento para uma string 
	saida = malloc (sizeof (char) * (strlen (argv[Saidapos])+ 1));
	strcpy(saida,argv[Saidapos]);
	saida[(strlen(argv[Saidapos])+1)] = 0;
}	
else
{
	// Caso nao seja encontrado o "-o" nos argumentos colocamos 0 na unica posicao da nossa string
	saida = malloc (sizeof(char));
	saida[0] = 0;
}

	

 
FILE *output;

if (saida[0] != 0)
{
	// Abrimos a string saida no mode de escrita
	output = fopen(saida, "w");
	if (!output)
	{
		fprintf(stderr, "%s", "Erro na abertura da saida\n");
		exit(1);
	}
}
else	
{
	// Caso a primeira posicao da nossa string seja 0 , usaremos stdout
	output = stdout;
}

if (output == NULL)
{

	fprintf(stderr, "%s", "O output nao pode ser aberto\n");
	exit(1);
}
else
{
	// Escrevemos no arquivo o mesmo cabecalho do arquivo aberto , afinal isso nao se altera 

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
			
	for (aux=(fileINPUT.data_size/2);aux>=0;aux=aux-2)
	{
		// Neste laco vamos da ultima ate a primeira posicao do DATA escrevendo no arquivo de saida de tras pra frente , mantendo a sequencia {E,D,E,D...,E,D}
		fwrite (&fileINPUT.DATA[aux-1],sizeof(short),1,output);
		fwrite (&fileINPUT.DATA[aux],sizeof(short),1,output);
	}
}

// Liberacao de memoria alocada
free (fileINPUT.DATA);
free (saida);
return 0;
}