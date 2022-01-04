#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "discord.h"

#define NUM_OF_COMMENTS 14

void on_ready(struct discord *client);
void on_viktor(struct discord *client, const struct discord_message *msg);

int main(void) {
    
    struct discord *client = discord_config_init("./mybot_config.json");

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

    if(strstr(message, "viktor") != NULL) {
        int randNum = 0;

        char *hateComments[50] = {
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
            "i just hate viktor so much"
        };

        srand(time(NULL));
        randNum = rand() % NUM_OF_COMMENTS;

        struct discord_create_message_params params = { .content = hateComments[randNum] };
        discord_create_message(client, msg->channel_id, &params, NULL);
    }
    free(message);
}
