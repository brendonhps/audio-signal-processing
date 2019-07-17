// Brendon Henrique de Paula da Silva 
// Grr 20170203

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "opensound.h"
#include "linhasdecomando.h"

#define TRUE  1
#define FALSE 0

// Funcao especifica para tratar os argumentos do arquivo (wavinfo.c), retorna erros em caso de parametro desconhecido ou retorna o arquivo aberto
soundWAV wavinfoparam (int argc, char **argv, soundWAV header)
{
	if (argc >= 2) 
	{
		if ((strcmp(argv[1],"-i") == 0) && (strlen(argv[2]) != 0))
		{
			open_sound (argv[2],&header);

		}

		else 
		{	
			fprintf(stderr, "%s", "Parametro desconhecido\n");
			exit(1);
		}
	}
	else
	{
		open_sound ("",&header);
		
	}

return header;

} 

// Funcao especifica para abrir os .wav passados por argumento em alguns filtros, retorna erros em caso de falta de parametro ou de entrada nao encontrada
// ou retorna o arquivo ja aberto
soundWAV wavparam (int argc, char **argv , soundWAV header)
{
	
	int i;
	int aux=FALSE;
	if (argc < 1)
	{
		fprintf(stderr, "%s", "Falta parametros\n");
		exit(1);
	}
	
	 	
		for (i=1;i<argc;i++)
		{
			if (strcmp(argv[i],"-i") == 0) 
			{
				aux = TRUE;
				if (strlen(argv[i+1]) != 0)
				{
					open_sound (argv[i+1],&header);					
					break;
				}
				else
					fprintf(stderr, "%s", "Entrada nao encontrada\n");
					
			}
			
		}
		if (aux == FALSE){
			open_sound ("",&header);
		}
	

	
return header;
}

// Funcao especifica para abrir o sound dentro do wavmix
soundWAV wavmixparam (int i,char **argv,soundWAV header)
{
	open_sound (argv[i],&header);

return header;
}

// Funcao que retorna a posicao da saida , caso nao encontre "-o" retorna 0
int devolve_pos_saida (int argc, char **argv)
{
	int i;
	

	for (i=1;i<argc;i++){
		if (strcmp(argv[i],"-o") == 0)
		{
			
			return (i+1);
		}
	}


return 0; 

}

// Funcao que retorna a posicao do level/atenuacao , caso nao encontre "-l" retorna 0
int level_param_pos (int argc, char **argv)
{	
int i;

	for(i=1; i< argc; i++)
		{	
			if (strcmp(argv[i],"-l") == 0)
			
				return (i+1);

			}
	return 0;

}


// Funcao que retorna o level no arquivo (wavecho) ,caso nao encontre retorna 0
int level_eco (int argc, char **argv)
{

	int i;

	for(i=1; i<argc; i++)
	{
		if (strcmp(argv[i],"-t") == 0)
			return (i+1);
	}

	return 0;

}






