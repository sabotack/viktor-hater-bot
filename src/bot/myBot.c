#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "discord.h"

#define MESSAGES_FOR_NOT_ASKING 10

void on_ready(struct discord *client);
void on_viktor(struct discord *client, const struct discord_message *msg);

int msgCounter = 0;
int newRoast = 0;

int main(void) {

    struct discord *client = discord_config_init("./../../../mybot_config.json");
    
    discord_set_on_ready(client, &on_ready);

    discord_set_on_message_create(client, &on_viktor);

    discord_run(client);

    discord_cleanup(client);

    return 0;
}

void on_ready(struct discord *client) {
    const struct discord_user *bot = discord_get_self(client);
    
    log_info("Succesfully connected to Discord as %s#%s!",
        bot->username, bot->discriminator);
}

void on_viktor(struct discord *client, const struct discord_message *msg) {
    if(msg->author->bot) return;
    
    char *message = strdup(msg->content);

    for(int i = 0; i < strlen(message); i++) {
        message[i] = tolower(message[i]);
    }

    struct discord_create_message_params params;

    if(strstr(message, "viktor") != NULL) {
        int randNum = 0;

        char *hateComments[] = {
            "all my homies hate viktor...",
            "i hate viktor",
            "shut up viktor",
            "hey victor",
            "vIkToR",
            "imagine being viktor xddd",
            "viktor is cringe",
            "cringe viktor",
            "stfu viktor",
            "viktor did anyone ask?",
            "ur gae viktor",
            "viktor? xdddd",
            "viktor is so gae",
            "i just hate viktor so much",
	        "get ratioed viktor",
	        "viktor fell off",
	        "the hood hates viktor now",
	        "viktor get ratioed + ur white + u fell off",
            "viktor how many times do i have to tell u to shut the fuck up?",
            "pleeaaseee shut the fuck up viktor",
            "viktor stop crying",
            "viktor's forehead so big his dreams are in IMAX",
            "viktor is a sniper's dream target"
        };

        srand(time(NULL));
        randNum = rand() % (sizeof(hateComments)/sizeof(hateComments[0]));

        if(newRoast == 0) {
            params.content = hateComments[21];
            newRoast = 1;
        }
        else {
            params.content = hateComments[randNum];
        }
        discord_create_message(client, msg->channel_id, &params, NULL);
    }
    else if(msg->author->id == 136912986605355008) {
        msgCounter++;

        if(msgCounter >= MESSAGES_FOR_NOT_ASKING) {
            params.content = "<@136912986605355008> did anyone ask?";
            discord_create_message(client, msg->channel_id, &params, NULL);
            msgCounter = 0;
        }
    }
}

