#include "instagram_api.h"
#include "inst_connection.c"


#define MAX_REQUEST 1024
#define XHOST_COMMONE_NAME "api.instagram.com"
#define HOST "api.instagram.com"
#define X_TARGET_URL "https://api.instagram.com"

char* get_user_info(long user_id,char* access_token){
	char cmd[1024];
	char* request;
	sprintf(cmd,"/v1/users/%d/?",user_id);
	request = form_get_request(cmd,access_token);
	return get_conntent_response(send_request(request));
}

char* get_selffeed(char* access_token){
	char cmd[1024];
	char* request;
	sprintf(cmd,"/v1/users/self/feed?");
	request = form_get_request(cmd,access_token);
	return get_conntent_response(send_request(request));
}

char* form_get_request(char* cmd,char* access_token){
	char request[MAX_REQUEST];
	sprintf(request,"GET %saccess_token=%s HTTP/1.1\r\nX-HostCommonName:%s\r\nHost:%s\nConnection:Keep-Alive\r\n\r\n",cmd,access_token,XHOST_COMMONE_NAME,HOST,X_TARGET_URL);
	return request;
}

char* send_request(char* request){
	char* response[1024*8];
	connection *c;
	c = sslConnect ();
	sslWrite (c,request);
	
	sprintf(response,"%s",sslRead (c));
	sslDisconnect(c);
	return response;
}

char* get_conntent_response(char* response){
	char* ret;
	ret = strstr(response,"{");	
	return ret;
}