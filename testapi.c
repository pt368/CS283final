#include "instagram_api.h"#include "instagram_api.c"
#define DEF_ACCESSTOKEN "30759048.1fb234f.d5aec0874ceb4696a2167f6c89910575"
int main(int argc, char ** argv) {
	printf("%s",get_selffeed(DEF_ACCESSTOKEN));
	return 1;
}