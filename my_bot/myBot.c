#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>
#include "discord.h"

#define USER_ID_VIKTOR              136912986605355008
#define USER_ID_RASMUS              352116555464704001
#define USER_ID_ALI                 150314037975056384

#define MESSAGES_FOR_NOT_ASKING     10
#define RASMUS_ROAST_ID             23
#define FIRST_ROAST_ID              29
#define HELP_INIT_NUM               26

void on_ready(struct discord *client);
void on_msg_create(struct discord *client, const struct discord_message *msg);

void on_viktor_id(struct discord *client, const struct discord_message *msg);
void on_help(struct discord *client, const struct discord_message *msg);
void on_viktor(struct discord *client, const struct discord_message *msg);

void set_bot_activity(struct discord *client, char *status_message);

bool firstRoast = true;

int msgCounter = 0;
int previousNum = 0;

char statusMsg[] = "Hate Viktor v2.0";

char *hateComments[] = {
    "all my homies hate viktor...",
    "i hate viktor",
    "shut up viktor",
    "victor*",
    "vIkToR",
    "imagine being viktor xddd",
    "imagine being the cringiest person on earth",
    "stop being cringe viktor",
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
    "viktor how long until you shut the fuck up?",
    "viktor is sleeping",
    "viktor stop crying",
    "viktor's forehead so big his dreams are in IMAX",
    "viktor is a sniper's dream target",
    "<@352116555464704001> u have more face to wash every morning",
    "viktor ur hairline looks like the mcdonalds logo",
    "<@136912986605355008> if i throw a stick will u leave?",
    "Write '!help' for more options",
    "Hello, im Dora. Viktor can you help me find where we asked?",
    "viktor how much for advertising on your billboard?",
    "viktor's forehead has become so big he started renting out parking spots",
    "viktor's forehead so big the photo on his driver's license says 'to be continued on the back'",
    "lol",
    "damn viktor you got a big ass forehead"
};

int main(void) {
    sigaction(SIGPIPE, &(struct sigaction){SIG_IGN}, NULL);
    
    srand(time(NULL));

    struct discord *client = discord_config_init("./config.json");
    
    discord_set_on_ready(client, &on_ready);
    discord_set_on_message_create(client, &on_msg_create);

    discord_run(client);
    discord_cleanup(client);

    return 0;
}

/* Callback function for when the client has connected to the bot */
void on_ready(struct discord *client) {
    const struct discord_user *bot = discord_get_self(client);
    
    log_info("Succesfully connected to Discord as %s#%s!", bot->username, bot->discriminator);
    
    /* Set bot status to custom status message */
    set_bot_activity(client, statusMsg);
}

/* This function is called each time the client detects a new message */
void on_msg_create(struct discord *client, const struct discord_message *msg) {
    /* Return if message author is a bot */
    if(msg->author->bot) return;
    
    /* Make a copy of the message text */
    char *message = strdup(msg->content);

    /* Convert message text to lowercase */
    for(int i = 0; i < strlen(message); i++) {
        message[i] = tolower(message[i]);
    }

    if(strstr(message, "viktor") != NULL) {
        on_viktor(client, msg);
    }
    else if(msg->author->id == USER_ID_VIKTOR) {
        on_viktor_id(client, msg);
    }
    
    /* Handle !help comment reply */
    if(strcmp(message, "!help") == 0 && previousNum == HELP_INIT_NUM) {
        on_help(client, msg);
    }

    free(message);
}

/* This function is called whenever a user with id USER_ID_VIKTOR sends a message */
void on_viktor_id(struct discord *client, const struct discord_message *msg) {
    msgCounter++;

    if(msgCounter >= MESSAGES_FOR_NOT_ASKING) {
        struct discord_create_message_params params = { .content = "<@136912986605355008> did anyone ask?" };
        discord_create_message(client, msg->channel_id, &params, NULL);
        msgCounter = 0;
    }
}

/* This function is called whenever the message text consists of '!help' */
void on_help(struct discord *client, const struct discord_message *msg) {
    struct discord_create_message_params params = { .content = "help me drag these nuts across your face xddd got em" };
    discord_create_message(client, msg->channel_id, &params, NULL);

    log_info("Received: %s", msg->content);
    log_info("Sent '!help' reply");

    previousNum = 0;
}

/* This function is called whenever the message text contains 'viktor' in any form */
void on_viktor(struct discord *client, const struct discord_message *msg) {
    int randNum = 0, temp = 0, length = 0;

    if(firstRoast) {
        struct discord_create_message_params params = { .content = hateComments[FIRST_ROAST_ID] };
        discord_create_message(client, msg->channel_id, &params, NULL);

        log_info("Sent first roast");
            
        previousNum = FIRST_ROAST_ID;
        firstRoast = false;
    }
    else {
        length = sizeof(hateComments)/sizeof(hateComments[0]);
        randNum = rand() % length;
        
        log_info("Received: %s", msg->content);
        log_info("length = %d, random number = %d", length, randNum);

        /* If rasmus roast is chosen */
        if(randNum == RASMUS_ROAST_ID) { 
            /* Generate a new random number to decrease the odds of getting the rasmus roast */
            temp = rand() % 2;

            log_info("Got Rasmus roast! Temp = %d, Proceed? %s", temp, temp == 0 ? "True" : "False");

            /* If new number equals 1: reroll, otherwise continue */
            if(temp == 1) {
                on_viktor(client, msg);
            }
        }

        struct discord_create_message_params params = { .content = hateComments[randNum] };
        discord_create_message(client, msg->channel_id, &params, NULL);

        previousNum = randNum;
    }
}

/* This function sets the custom bot activity */
void set_bot_activity(struct discord *client, char *status_message) {
    /* Set bot status to custom status message */
    struct discord_presence_status status = {
        .activities = (struct discord_activity *[]){
            &(struct discord_activity){
                .name = status_message,
                .type = DISCORD_ACTIVITY_GAME,
            },
            NULL // END OF ACTIVITIES LIST
        },
        .status = "online",
        .since = discord_timestamp(client)
    };

    discord_set_presence(client, &status);
}

