#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <curl/curl.h>

#include <mosquitto.h>
#include <mosquitto_plugin.h>
#include <mosquitto_broker.h>

static char *unpwd_cmd = NULL;
static char *acl_cmd = NULL;

/**
 * Version check.
 */
int mosquitto_auth_plugin_version(void)
{
    return MOSQ_AUTH_PLUGIN_VERSION;
}

/**
 * Init plugin.
 */
int mosquitto_auth_plugin_init(void **user_data, struct mosquitto_opt *opts, int opt_count)
{
    int i = 0;
    for (i = 0; i < opt_count; i++) {
        if(strncmp(opts[i].key, "unpwd_cmd", 9) == 0){
            unpwd_cmd = opts[i].value;
        }
        if(strncmp(opts[i].key, "acl_cmd", 7) == 0){
            acl_cmd = opts[i].value;
        }
    }
    #ifdef MQAP_DEBUG
        mosquitto_log_printf(MOSQ_LOG_INFO, "Auth plugin: unpwd_cmd: \"%s\" acl_cmd: \"%s\"", unpwd_cmd, acl_cmd);
    #endif

    return MOSQ_ERR_SUCCESS;
}

/**
 * Cleanup.
 */
int mosquitto_auth_plugin_cleanup(void *user_data, struct mosquitto_opt *opts, int opt_count)
{
    return MOSQ_ERR_SUCCESS;
}

/**
 * Security init.
 */
int mosquitto_auth_security_init(void *user_data, struct mosquitto_opt *opts, int opt_count, bool reload)
{
    return MOSQ_ERR_SUCCESS;
}

/**
 * Security cleanup.
 */
int mosquitto_auth_security_cleanup(void *user_data, struct mosquitto_opt *opts, int opt_count, bool reload)
{
    return MOSQ_ERR_SUCCESS;
}

/**
 * Username / Password check.
 */
int mosquitto_auth_unpwd_check(void *user_data, struct mosquitto *client, const char *username, const char *password)
{
    if(unpwd_cmd == NULL || username == NULL || password == NULL){
        return MOSQ_ERR_AUTH;
    }

    mosquitto_log_printf(MOSQ_LOG_INFO, "unpwd check: cmd: \"%s\" username: \"%s\", password: \"%s\"", unpwd_cmd, username, password);

    char command[100];
    snprintf(command, sizeof(command), "%s -u %s -p %s", unpwd_cmd, username, password);

    #ifdef MQAP_DEBUG
        mosquitto_log_printf(MOSQ_LOG_INFO, "\e[96mExecuting command: \"%s\"\e[0m", command);
    #endif

    int exitCode = system(command);
    if(exitCode == 0){
        return MOSQ_ERR_SUCCESS;
    }

    return MOSQ_ERR_AUTH;
}


int mosquitto_auth_acl_check(void *user_data, int access, struct mosquitto *client, const struct mosquitto_acl_msg *msg)
{
    if(acl_cmd == NULL){
        return MOSQ_ERR_AUTH;
    }
return MOSQ_ERR_SUCCESS;
   /* char access_name[6];
    get_access_name(&access_name);
      if (access == MOSQ_ACL_READ) {
        sprintf(access_name, "read");
      } else if (access == MOSQ_ACL_WRITE) {
        sprintf(access_name, "write");
      } else {
        sprintf(access_name, "none");
      }

    mosquitto_log_printf(MOSQ_LOG_INFO, "acl check: cmd: \"%s\" username: \"%s\", password: \"%s\"", acl_cmd, username, password);

    char command[100];
    snprintf(command, sizeof(command), "%s -u %s -p %s", unpwd_cmd, username, password);

    #ifdef MQAP_DEBUG
        mosquitto_log_printf(MOSQ_LOG_INFO, "\e[96mExecuting command: \"%s\"\e[0m", command);
    #endif

    int exitCode = system(command);
    if(exitCode == 0){
        return MOSQ_ERR_SUCCESS;
    }

    return MOSQ_ERR_AUTH;*/
}

/*
int mosquitto_auth_psk_key_get(void *user_data, struct mosquitto *client, const char *hint, const char *identity, char *key, int max_key_len) {
  return MOSQ_ERR_PLUGIN_DEFER;
}*/

