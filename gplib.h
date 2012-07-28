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

char *token;
char *buff;
char *value;
char *comment;
int val;
int i;
char sel;
//char *token;

char delimiters[] = " .,;|";

typedef struct Configurator {
	char file_name[256];
	char *cur_line;
	char **all_lines;
	int tot_lines;
	int cur_sel;
	FILE *fp;
	int global;
	int global_key;
	char *global_cmt;
	int res_width;
	int res_width_key;
	char *res_width_cmt;
	int res_height;
	int res_height_key;
	char *res_height_cmt;
	int hw_tnl;
	int hw_tnl_key;
	char *hw_tnl_cmt;
	int wnd_mode;
	int wnd_mode_key;
	char *wnd_mode_cmt;
	int vsync;
	int vsync_key;
	char *vsync_cmt;
	int tex_qlty;
	int tex_qlty_key;
	char *tex_qlty_cmt;
	int bump_map;
	int bump_map_key;
	char *bump_map_cmt;
	int mirrors;
	int mirrors_key;
	char *mirrors_cmt;
	int track_map;
	int track_map_key;
	char *track_map_cmt;
	int env_map;
	int env_map_key;
	char *env_map_cmt;
	int tex_fil_qlty;
	int tex_fil_qlty_key;
	char *tex_fil_qlty_cmt;
	int an_fil_qlty;
	int an_fil_qlty_key;
	char *an_fil_qlty_cmt;
	int shdws;
	int shdws_key;
	char *shdws_cmt;
	int shdw_type;
	int shdw_type_key;
	char *shdw_type_cmt;
	int ext_steer;
	int ext_steer_key;
	char *ext_steer_cmt;
	int heat_haze;
	int heat_haze_key;
	char *heat_haze_cmt;
} CFG;

void strip_newline(char *str, int len) {
	int i = 0;
	for(i=0; i<len; i++) {
		if(str[i] == '\n') {
			str[i] = '\0';
			break;
		}
	}
}

void strip_tab(char *str, int len) {
	int i = 0;
	for(i=0; i<len; i++) {
		if(str[i] == '\t') {
			str[i] = '\0';
			break;
		}
	}
}

void save_file(CFG *cfg) {
	printf("Generating new configuration file from buffer..\n");
	cfg->fp = fopen("f1graphics.cfg", "w");
	if(!cfg->fp) {
		printf("Couldn't write file!\n");
	} else {
		for(i=0; i<cfg->tot_lines; i++) {
			fprintf(cfg->fp, "%s\n", cfg->all_lines[i]);
		}
		fclose(cfg->fp);
		printf("New configuration file created successfully!\n");
	}
}

void show_file_contents(CFG *cfg) {
	char *buff;
	int counter = 0;
	cfg->fp = fopen(cfg->file_name, "r");
	//if(sizeof(buff) > 0) free(buff);
	buff = (char *) malloc(sizeof(char) * MAX_LINE);
	while(fgets(buff, MAX_LINE, cfg->fp)) {
		printf("%d: %s", counter, buff);
		free(buff);
		buff = (char *) malloc(sizeof(char) * MAX_LINE);
		++counter;
	}
	free(buff);
}

void get_val_cmt_(CFG *cfg) {
	if(sizeof(buff) > 0) free(buff);
	if(sizeof(value) > 0) free(value);
	if(sizeof(comment) > 0) free(comment);

	buff = (char *) malloc(sizeof(char) * MAX_LINE);
	value = (char *) malloc(sizeof(char) * MAX_VAL);
	comment = (char *) malloc(sizeof(char) * MAX_LINE);
	
	strcpy(buff, cfg->all_lines[cfg->cur_sel]);
	token = strtok(buff, ";");

	if(token != NULL) {
		//value[0] = '\0';
		strcpy(value, token);
		strip_tab(value, MAX_VAL);
	}

	token = strtok(NULL, ";");

	if(token != NULL) {
		//comment[0] = '\0';
		strcpy(comment, token);
		strip_newline(comment, MAX_LINE);
	}

}

void set_val_cmt_(CFG *cfg) {
	int last;
	free(cfg->all_lines[cfg->cur_sel]);
	cfg->all_lines[cfg->cur_sel] = (char *) malloc(sizeof(char) * MAX_LINE);
	cfg->all_lines[cfg->cur_sel][0] = '\0';

	free(value);
	value = (char *) malloc(sizeof(char) * MAX_VAL);
	//value[0] = '\0';

	sprintf(value, "%d\t\t\t", val);
	strcat(cfg->all_lines[cfg->cur_sel], value);
	strcat(cfg->all_lines[cfg->cur_sel], ";");
	strcat(cfg->all_lines[cfg->cur_sel], comment);

	last = strlen(cfg->all_lines[cfg->cur_sel]) + 1;
	cfg->all_lines[cfg->cur_sel][last] = '\0';
}

void show_cur_val(CFG *cfg) {
	printf("Change settings as below:\n");
	printf("%s\n", comment);
}
