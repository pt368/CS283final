#include "instagram_api.h"#include "instagram_api.c"
#define DEF_ACCESSTOKEN "30759048.1fb234f.d5aec0874ceb4696a2167f6c89910575"
int main(int argc, char ** argv) {
	// printf("%s",get_selffeed(DEF_ACCESSTOKEN));	// char* action ;	// action	= "unfollow";	// int n ;	printf("%s\n",get_user_info(12345,DEF_ACCESSTOKEN));	printf("\r\n");	printf("%s\n",get_relationship(12345,DEF_ACCESSTOKEN));	printf("\r\n");	printf("%s\n",get_user_recent(12345,DEF_ACCESSTOKEN));	printf("\r\n");	return 1;
}