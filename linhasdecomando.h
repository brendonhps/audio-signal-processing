// Brendon Henrique de Paula da Silva 
// Grr 20170203

#ifndef __LINHAS_DE_COMANDO__

#define __LINHAS_DE_COMANDO__

// Funcao especifica para tratar os argumentos do arquivo (wavinfo.c), retorna erros em caso de parametro desconhecido ou retorna o arquivo aberto
soundWAV wavinfoparam(int argc, char **argv, soundWAV header);

// Funcao especifica para abrir os .wav passados por argumento em alguns filtros, retorna erros em caso de falta de parametro ou de entrada nao encontrada
// ou retorna o arquivo ja aberto
soundWAV wavparam (int argc, char **argv , soundWAV header);

// Funcao especifica para abrir o sound dentro do wavmix
soundWAV wavmixparam (int i,char **argv,soundWAV header);

// Devolve a posicao da saida.
int devolve_pos_saida (int argc, char **argv);


// Funcao que retorna a posicao do level caso exista, caso nao exista retorna 0.
int level_param_pos (int argc, char **argv);


// Funcao que retorna a posicao do delay caso exista, nos arquimentos do programa wavecho
int level_eco (int argc, char **argv);




#endif
