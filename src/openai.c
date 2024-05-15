# include "../include/openai.h"

t_openai* globalOpenaiAddress;

int openai_init(const char *api_key, const char *model)
{
	t_openai* openai = (t_openai *)malloc(sizeof(t_openai));
	if (!openai)
	{
		write(2, "Error: not enough memory\n", 22);
		return -1;
	}
	openai->apiKey = strdup(api_key);
	openai->model = strdup(model);
	openai->url = "https://api.openai.com/v1/chat/completions";
	
	globalOpenaiAddress = openai;
	return 0;
}

int set_content(const char* content, unsigned int max_tokens)
{
	if (max_tokens < 1)
	{
		write(2, "Error: max_tokens must be greater than 0\n", 41);
		return -1;
	}
	globalOpenaiAddress->data = strdup(content);
	globalOpenaiAddress->max_tokens = max_tokens;
	return 0;
}

int send_request()
{
	const char* data = "{\"model\": \"gpt-3.5-turbo\", \
	\"messages\": [{\"role\": \"user\", \"content\": \"Hello, world!\"}], \
	\"max_tokens\": 50}";

    char command[1024];
    snprintf(command, sizeof(command), 
             "curl -H \"Authorization: Bearer %s\" "
             "-H \"Content-Type: application/json\" "
             "-d '%s' %s", \
			 globalOpenaiAddress->apiKey, \
			 data, \
			 globalOpenaiAddress->url);

    int result = system(command);
    if (result == -1) {
        perror("system");
		write(2, "Error: request failed\n", 22);
        return -1;
    }
	return 0;
}

void	free_openai()
{
	free((void *)globalOpenaiAddress->apiKey);
	globalOpenaiAddress->apiKey = NULL;
	free((void *)globalOpenaiAddress->model);
	globalOpenaiAddress->model = NULL;
	free((void *)globalOpenaiAddress->data);
	globalOpenaiAddress->data = NULL;
	free((void *)globalOpenaiAddress);
	globalOpenaiAddress = NULL;
}