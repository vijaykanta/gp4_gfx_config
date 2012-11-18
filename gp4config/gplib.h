/**
* @author Vijay Kanta
* @website www.vizcreations.com
* @abstract Simple console configurator for game Grand Prix 4
* @license Free software - No guarantee
* @copyright Not applicable
* @link https://github.com/vijaykanta/gp4_gfx_config.git
*/

#define MAX_PATH 1000
#define MAX_STRUCT 5000
#define MAX_LEN 200
#define MAX_LINE 255
#define MAX_LINES 100
#define MAX_VAL 20

void strip_newline(char *str, int len);

void strip_tab(char *str, int len);

void save_file(CFG *cfg);

void show_file_contents(CFG *cfg);

void get_val_cmt_(CFG *cfg);

void set_val_cmt_(CFG *cfg);

void show_cur_val(CFG *cfg);
