// Brendon Henrique de Paula da Silva 
// Grr 20170203
#include <stdio.h>
#include <stdlib.h>
#include "opensound.h"
#include "linhasdecomando.h"
#include <string.h>


int main (int argc, char **argv)
{

// Variaveis locais utilizadas 

soundWAV fileINPUT;
int Diff,
	saidapos,
	levelpos,
	aux;
char *saida;	
float Fator_ampliacao;
	


fileINPUT = wavparam(argc, argv, fileINPUT);
	
saidapos = devolve_pos_saida(argc,argv);
levelpos = level_param_pos(argc,argv);
if (levelpos == 0)
{
	// Caso o fator de ampliacao seja 0 , significa que a funcao level_param_pos nao achou "-l" nos argumentos , logo usaremos o valor default (1.0) 
	Fator_ampliacao = 1.0;
}
else 
{
	Fator_ampliacao = atof (argv[levelpos]);
}

if ((Fator_ampliacao < 0.0) || (Fator_ampliacao > 10.0)){
	fprintf(stderr, "%s","Fator de ampliacao fora do padrao <Limite permitido : 0.0 ate 10.0>\n" );
	exit(1);
}
if (saidapos != 0)
{
	saida = malloc (sizeof (char) * (strlen (argv[saidapos])+ 1));
	strcpy(saida,argv[saidapos]);
	saida[(strlen(argv[saidapos])+1)] = 0;
}	
else
{
	saida = malloc (sizeof(char) * 2);
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


			for (aux=0;aux<((fileINPUT.data_size/2)-1);aux=aux+2)
			{
				// Neste laco fazemos escrevemos nas posicoes referentes ao lado Direito o seu valor anterior somado ao Fator de amplicao multiplicado pela diferenca do lado direito - lado esquerdo 
				// e nas posicoes do lado esquerdo , o seu valor anterior subtraido ao Fator de ampliacao multiplicado pela difrenca do lado direito - lado esquerdo 
				// Para calcular a diferenca do lado direito e lado esquerdo , consideramos subconjuntos , onde {E,D} se trata de um conjunto 
				Diff = fileINPUT.DATA[aux+1] - fileINPUT.DATA[aux];
				fileINPUT.DATA[aux+1] = fileINPUT.DATA[aux+1] + (Fator_ampliacao * Diff);
				fileINPUT.DATA [aux] = fileINPUT.DATA [aux] - (Fator_ampliacao * Diff);
				fwrite (&fileINPUT.DATA[aux],sizeof(short),1,output);
				fwrite (&fileINPUT.DATA[aux+1],sizeof(short),1,output);
			}
	}
//Liberacao de memoria alocada
free (fileINPUT.DATA);
free (saida);
return 0;

}