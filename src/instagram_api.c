#include "instagram_api.h"
#include "inst_connection.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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

char* get_user_profile_pic(long user_id,char* access_token){
	char * user_info;
	char* ret;
	char * link_object;
	user_info = get_user_info(user_id,access_token);
	ret = strstr(user_info,"\"profile_picture\":\"");
	link_object = strtok(strdup(ret), ",");	
	link_object = strtok(strdup(link_object), ":");	
	link_object = strtok(NULL, " ");	
	link_object = strtok(link_object, "\"");	
	return link_object;
}

char* get_selffeed(char* access_token){
	char cmd[1024];
	char* request;
	sprintf(cmd,"/v1/users/self/feed?");
	request = form_get_request(cmd,access_token);
	return get_conntent_response(send_request(request));
}

char* get_user_recent(long user_id,char* access_token){
	char cmd[1024];
	char* request;
	sprintf(cmd,"/v1/users/%d/media/recent/?",user_id);
	request = form_get_request(cmd,access_token);
	return get_conntent_response(send_request(request));
}

char* get_self_liked(char* access_token){
	char cmd[1024];
	char* request;
	sprintf(cmd,"/v1/users/self/media/liked?");
	request = form_get_request(cmd,access_token);
	return get_conntent_response(send_request(request));
}
char* search_by_name(char* search_token,char* access_token){
	char cmd[1024];
	char* request;
	sprintf(cmd,"/v1/users/search?q=%s",search_token);
	request = form_get_request(cmd,access_token);
	return get_conntent_response(send_request(request));
}

char* get_flows(char* user_id,char* access_token){
	char cmd[1024];
	char* request;
	sprintf(cmd,"/v1/users/%d/follows?",user_id);
	request = form_get_request(cmd,access_token);
	return get_conntent_response(send_request(request));
}

char* get_flowed_by(char* user_id,char* access_token){
	char cmd[1024];
	char* request;
	sprintf(cmd,"/v1/users/%d/followed-by?",user_id);
	request = form_get_request(cmd,access_token);
	return get_conntent_response(send_request(request));
}
char* get_requested_by(char* access_token){
	char cmd[1024];
	char* request;
	sprintf(cmd,"/v1/users/self/requested-by?");
	request = form_get_request(cmd,access_token);
	return get_conntent_response(send_request(request));
}
char* get_relationship(long user_id,char* access_token){
	char cmd[1024];
	char* request;
	sprintf(cmd,"/v1/users/%d/relationship?",user_id);
	request = form_get_request(cmd,access_token);
	return get_conntent_response(send_request(request));
}

char* get_media(long media_id,char* access_token){
	char cmd[1024];
	char* request;
	sprintf(cmd,"v1/media/%d?",media_id);
	request = form_get_request(cmd,access_token);
	return get_conntent_response(send_request(request));
}

char* get_popular_media(char* access_token){
	char cmd[1024];
	char* request;
	sprintf(cmd,"v1/media/popular?");
	request = form_get_request(cmd,access_token);
	return get_conntent_response(send_request(request));
}

// int modify_relationship(long user_id, char* access_token,char* action){
	// char *cmd;
	// char content[1024];
	// char* request;
	// sprintf(content,"action = %s",action);
	
	// cmd =malloc(sizeof(char) * 1024);
	// sprintf(cmd,"/v1/users/%d/relationship?",user_id);
	// request = form_post_request(cmd,access_token,content,strlen(content));
	// printf("%s\n",send_request(request));
	// return 1;
// }
	
char* form_get_request(char* cmd,char* access_token){
	char request[MAX_REQUEST];
	sprintf(request,"GET %saccess_token=%s HTTP/1.1\r\nX-HostCommonName:%s\r\nHost:%s\r\nX-Target-URI:%s\r\nConnection:Keep-Alive\r\n\r\n",cmd,access_token,XHOST_COMMONE_NAME,HOST,X_TARGET_URL);
	return request;
}

char* form_post_request(char* cmd,char* access_token,char* content,int len_content){
	char request[MAX_REQUEST];
	char* ret;
	sprintf(request,"POST %saccess_token=%s HTTP/1.1\r\nX-HostCommonName: %s\r\nHost: %s\r\nX-Target-URI: %s\r\nContent-Type: text/plain; charset=UTF-8\r\nConnection:Keep-Alive\r\n\r\n%s\r\n\r\n",cmd,access_token,XHOST_COMMONE_NAME,HOST,X_TARGET_URL,content);
	ret = malloc(sizeof(char)*strlen(request));
	strcat(ret,request);
	return ret;
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

int* download(char* link){
	char cmd[1000];
	sprintf(cmd,"wget %s", link);
	system(cmd);
	return 1;
}


char* get_conntent_response(char* response){
	char* ret;
	ret = strstr(response,"{");	
	return ret;
}