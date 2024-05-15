#include "include/openai.h"

# define API_KEY "your api key here"

int main()
{
	openai_init(API_KEY, "gpt-3.5-turbo");
	set_content("hello", 50);
	send_request();
	free_openai();
	return 0;
}
