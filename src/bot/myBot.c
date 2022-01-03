#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "discord.h"

#define MESSAGES_FOR_NOT_ASKING 10
#define FIRST_ROAST_INDEX 22

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

    return EXIT_SUCCESS;
}

void on_ready(struct discord *client) {
    const struct discord_user *bot = discord_get_self(client);
    
    log_info("Succesfully connected to Discord as %s#%s!",
        bot->username, bot->discriminator);
}

void on_viktor(struct discord *client, const struct discord_message *msg) {
    if(msg->author->bot) return;
    int msgLength = sizeof(msg->content)/sizeof(char);

    char message[msgLength];
    strcpy(message, msg->content);
    log_info("Message: -- %s --", message);

    for(int i = 0; i < strlen(message); i++) {
        message[i] = tolower(message[i]);
    }

    if(strstr(message, "viktor") != NULL) {
        int randNum = 0, temp = 0;

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
            "viktor is a sniper's dream target",
            "<@352116555464704001> u have more face to wash every morning", /* rasmus roast */
            "viktor ur hairline looks like the mcdonalds logo",
            "<@136912986605355008> if i throw a stick will u leave?"
        };

        srand(time(NULL));
        randNum = rand() % (sizeof(hateComments)/sizeof(hateComments[0]));

        if(newRoast == 0) {
            struct discord_create_message_params params = { .content = hateComments[FIRST_ROAST_INDEX] };
            newRoast = 1;
            discord_create_message(client, msg->channel_id, &params, NULL);
        }
        else {
            /* if rasmus roast is chosen */
            if(randNum == 23){ 
                /* generate a new random number to decrease the odds of getting the rasmus roast */
                temp = rand() % 2;
                if(temp != 0) {
                    on_viktor(client, msg);
                }
            }

            struct discord_create_message_params params = { .content = hateComments[randNum] };
            log_info("Params content: -- %s -- randNum: %d", params.content, randNum);
            discord_create_message(client, msg->channel_id, &params, NULL);
        }
    }
    else if(msg->author->id == 136912986605355008) {
        msgCounter++;

        if(msgCounter >= MESSAGES_FOR_NOT_ASKING) {
            struct discord_create_message_params params = { .content = "<@136912986605355008> did anyone ask?" };
            discord_create_message(client, msg->channel_id, &params, NULL);
            msgCounter = 0;
        }
    }

    /* free(message); */
}

