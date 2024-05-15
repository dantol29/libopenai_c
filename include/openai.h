#ifndef OPENAI_H
# define OPENAI_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_openai
{
	const char* apiKey;
	const char* url;
	const char* model;
	const char* data;
	unsigned int max_tokens;
}	t_openai;

int openai_init(const char *api_key, const char *model);
int set_content(const char* content, unsigned int max_tokens);
int send_request();
void free_openai();

#endif
