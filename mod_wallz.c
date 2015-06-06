#include <stdio.h>
#include <stdlib.h>
#include "apr_hash.h"
#include "ap_config.h"
#include "ap_provider.h"
#include "apr_strings.h"
#include "apr_network_io.h"
#include "apr_dbd.h"
#include <apr_file_info.h>
#include <apr_file_io.h>
#include <apr_tables.h>
#include "httpd.h"
#include "http_core.h"
#include "http_config.h"
#include "http_log.h"
#include "http_protocol.h"
#include "http_request.h"
// Conf Struct
typedef struct{
    int enabled;
} wallz_conf;
static wallz_conf config;
// AP_MODULE_DECLARE_DATA declaration
static int    wallz_handler(request_rec *r);
void          *create_dir_conf(apr_pool_t *pool, char *context);
void          *merge_dir_conf(apr_pool_t *pool, void *BASE, void *ADD);
static void   register_hooks(apr_pool_t *pool);
// Directives declaration
const char    *wallz_set_enabled(cmd_parms *cmd, void *cfg, const char *arg);

static const command_rec    directives[]={
    AP_INIT_TAKE1("wallzEnabled", wallz_set_enabled, NULL, OR_ALL, "Enable or disable wallz."),
	{NULL}
};
module AP_MODULE_DECLARE_DATA    wallz_module = { 
    STANDARD20_MODULE_STUFF,
    create_dir_conf,
    merge_dir_conf,
    NULL,
    NULL,
    directives, // More config coming soon............
    register_hooks
};
static void register_hooks(apr_pool_t *pool){
    ap_hook_handler(wallz_handler, NULL, NULL, APR_HOOK_FIRST);
}
const char *wallz_set_enabled(cmd_parms *cmd, void *cfg, const char *arg){
    wallz_conf    *conf = (wallz_conf *) cfg;
    if(conf){
        if(strcasecmp(arg, "on")||strcasecmp(arg, "true")||strcasecmp(arg, "enabled")){
            conf->enabled = 1;
        }else{
            conf->enabled = 0;
		}
    }
    return NULL;
}
void *create_dir_conf(apr_pool_t *pool, char *context){
    context = context ? context : "Default wallz config generated.";
    wallz_conf    *cfg = apr_pcalloc(pool, sizeof(wallz_conf));
    if(cfg){{
		// Insert default config here
		cfg->enabled = 1;
    }}
    return cfg;
}
void *merge_dir_conf(apr_pool_t *pool, void *BASE, void *ADD){
    wallz_conf    *base = (wallz_conf *) BASE;
    wallz_conf    *add = (wallz_conf *) ADD;
    wallz_conf    *conf = (wallz_conf *) create_dir_conf(pool, "Default wallz config generated.");
	// Insert merged config here
	conf->enabled = (add->enabled == 0) ? base->enabled : add->enabled;
    return conf;
}
static int wallz_handler(request_rec *r){
	// Disable by config not working yet.......
    if(config.enabled == 0){
		ap_set_content_type(r, "text/html");
		ap_rprintf(r, "Wallz handler is not enabled. :(");
		return OK;
	}
	char *fn;
	int ar;
	apr_finfo_t fi;
	fn = apr_pstrdup(r->pool, r->filename);
	ar = apr_stat(&fi, fn, APR_FINFO_MIN, r->pool);
    if (ar == APR_SUCCESS){
		if (fi.filetype != APR_NOFILE){
			// Add warning point.
		}
	}
    ap_set_content_type(r, "text/html");
    ap_rprintf(r, "Wallz handler.");
    return OK;
}
