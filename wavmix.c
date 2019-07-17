// Brendon Henrique de Paula da Silva 
// Grr 201702

#include <stdio.h>
#include <stdlib.h>
#include "opensound.h"
#include <string.h>
#include "linhasdecomando.h"
#define PICOMAX 32767


int main (int argc, char ** argv )
{

// Variaveis locais utilizadas
soundWAV fileINPUT;
int i,
	j,
	max,
	saidapos,
	SaveMaiorInput,
	aux,
	maiorvalor;
int *loader;
char *Saida;
float fatordeajuste;


// Laco para verificar qual e o maior arquivo soundWAV dado como entrada
for (i=1 ; i<argc ; i++)
{

	if ((strcmp (argv[i],"-o") != 0) && (strcmp (argv[i-1],"-o") != 0))
	{

		fileINPUT = wavmixparam (i,argv,fileINPUT);
		if (fileINPUT.data_size > max)
		{
			max = fileINPUT.data_size;
			SaveMaiorInput = i;
		}
	}
}

// Alocando memoria para o loader
loader = malloc (sizeof(int ) * max/2);
for (j=0;j<max/2;j++)
	loader[j] = 0;

for (i=1; i<argc ; ++i)
{
	if ((strcmp (argv[i],"-o") != 0) && (strcmp (argv[i-1],"-o") != 0))
	{
		fileINPUT = wavmixparam (i,argv,fileINPUT);
		
		
		// Laco para somar os valores de cada arquivo WAV 
		for (j=0; j<fileINPUT.data_size/2;++j)
		{

			loader[j] = loader[j]+ fileINPUT.DATA[j];
			
		}
	
		
	}
}


// Laco para definir qual e o maior valor de DATA , dentro das minhas amostras somadas
	for(aux=0;aux<(max/2);aux++)
		{
			if (loader[j] > maiorvalor)
				maiorvalor = loader[j];

		}
		
// Com conhecimento da maior amostra podemos definir um fator de ajuste , pare reorganizar no loader as amostras com valor maximo = PICOMAX

		fatordeajuste = (PICOMAX / (maiorvalor * 1.000));
		
		for(aux=0;aux<(max/2);aux++)
		{
			loader[j] = fatordeajuste * loader[j];
			
		}


	// Abrindo novamente o maior arquivo para guardar seu header

	fileINPUT = open_sound (argv[SaveMaiorInput],&fileINPUT);

	saidapos = devolve_pos_saida(argc,argv);

// Caso ache saida "-o", a variavel saidapos vai ser diferente de 0
if (saidapos != 0)
		{
		Saida = malloc (sizeof (char) * (strlen (argv[saidapos])+ 1));
		strcpy(Saida,argv[saidapos]);
		Saida[(strlen(argv[saidapos])+1)] = 0;
		}	
// Caso nao ache o "-o", iremos definir a saida pela saida padrao "stdout"
	else
	{
		Saida = malloc (sizeof(char));
		Saida[0] = 0;
	}

	

 
FILE *output;

// Caso minha posicao 0 no vetor saida seja 0 , usaremos a saida padrao
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
		// Escrevemos o parte do header do maior arquivo na saida definida
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
		// armazenamos o loader no DATA do arquivo saida
		for (aux=0;aux<max/2;aux++)
		{
		fwrite ((void*)&loader[aux],sizeof(short),1,output);
		}
	}
// Liberando memoria
free (loader);
free (fileINPUT.DATA);
free (Saida);

return 0;
}


