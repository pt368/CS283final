// #ifndef HW4_H_// #define HW4_H_#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "openssl/rand.h"
#include "openssl/ssl.h"
#include "openssl/err.h"




//user
char* get_user_info(long user_id,char* access_token);
char* get_selffeed(char* access_token);

char* get_user_recent(long user_id,char* access_token);

char* get_self_liked(char* access_token);

char* search_by_name(char* search_token,char* access_token);

// relationship
char* get_flows(char* user_id,char* access_token);

char* get_flowed_by(char* user_id,char* access_token);

char* get_requested_by(char* access_token);

char* get_relationship(long user_id,char* access_token);

// int modify_relationship(long user_id, char* access_token,char* action);

// media
// char* get_media(long media_id);
// char* get_media(long media_id,char* access_token);

// char* search_media(char* search_token);
// char* search_media(char* search_token,char*access_token);

// char* get_popular_media();
// char* get_popular_media(char*access_token);

// comment 
// char* get_comments(long comment_id);
// char* get_comments(long comment_id,char* access_token);

// bool post_comments(long comment_id);
// bool post_comments(long comment_id,char* access_token);

// bool del_comments(long comment_id);
// bool del_comments(long comment_id,char* access_token);

// likes

// char* get_liked(long media_id);
// char* get_liked(long media_id,char* access_token);

// bool like_media(long media_id);
// bool like_media(long media_id,char* access_token);

// bool unline_media(long media_id);
// bool unline_media(long media_id, char* access_token);


//util

char* form_get_request(char* cmd,char* access_token);
char* form_post_request(char* cmd,char* access_token,char* content,int len_content);
// char* form_del_request(char* cmd,char* access_token);
char* send_request(char* request);
char* get_conntent_response(char* response);
// bool* check_status(char* response);
