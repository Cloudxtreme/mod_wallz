#include "httpd.h"
#include "http_core.h"
#include "http_config.h"
#include "http_log.h"
#include "http_request.h"
module AP_MODULE_DECLARE_DATA   wallz_module =
{ 
    STANDARD20_MODULE_STUFF,
    create_dir_conf,
    merge_dir_conf,
    create_svr_conf,
    merge_svr_conf,
    directives,
    register_hooks
};
LoadModule wallz_module modules/mod_wallz.so
