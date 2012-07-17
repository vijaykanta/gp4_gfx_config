#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH 1000
#define MAX_STRUCT 5000
#define MAX_LEN 50
#define MAX_LINE 125
#define MAX_LINES 100

char *buff;
char *value;
char *comment;
int val;
int i;
char sel;
char *token;

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
	cfg->fp = fopen("config.cfg", "w");
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

void get_val_cmt_(CFG *cfg) {
	free(buff);
	free(value);
	free(comment);

	buff = (char *) malloc(sizeof(char) * MAX_LINE);
	value = (char *) malloc(sizeof(char) * 5);
	comment = (char *) malloc(sizeof(char) * MAX_LINE);
	
	strcpy(buff, cfg->all_lines[cfg->cur_sel]);
	token = strtok(buff, ";");
	value[0] = '\0';
	strcpy(value, token);
	strip_tab(value, MAX_LINE);

	token = strtok(NULL, ";");
	comment[0] = '\0';
	strcpy(comment, token);
	strip_newline(comment, MAX_LINE);
}

void set_val_cmt_(CFG *cfg) {
	free(cfg->all_lines[cfg->cur_sel]);
	cfg->all_lines[cfg->cur_sel] = (char *) malloc(sizeof(char) * MAX_LINE);
	cfg->all_lines[cfg->cur_sel][0] = '\0';
	free(value);
	value = (char *) malloc(sizeof(char) * MAX_LEN);
	value[0] = '\0';
	sprintf(value, "%d\t\t", val);
	strcat(cfg->all_lines[cfg->cur_sel], value);
	strcat(cfg->all_lines[cfg->cur_sel], comment);
	strcat(cfg->all_lines[cfg->cur_sel], "\0");
}

void start_(CFG *cfg) {
	printf("\nType 't' to edit Texture Filter Quality\n");
	printf("Type 'm' to edit Track Map\n");
	printf("Type 'v' to edit Environment Map\n");
	printf("Type 'q' to edit Texture Quality\n");
	printf("Type 'a' to edit Anisotropic Filter Quality\n");
	printf("Type 's' to edit Shadow Type\n");
	printf("Type 'c' to generate configuration file from buffer\n\n");

	scanf("%c", &sel);
	if(sel == 't' || sel == 'T') {
		cfg->cur_sel = cfg->tex_fil_qlty_key;
		get_val_cmt_(cfg);

		printf("Enter value for Texture Filter Quality (%s default): ", value);
		scanf("%d", &val);
		cfg->tex_fil_qlty = val;

		strcpy(cfg->tex_fil_qlty_cmt, comment);

		set_val_cmt_(cfg);
		printf("Value edited successfully..\n");
		start_(cfg);
	} else if(sel == 'm' || sel == 'M') {
		cfg->cur_sel = cfg->track_map_key;
		get_val_cmt_(cfg);

		printf("Enter value for Track Map (%d default): ", cfg->track_map);
		scanf("%d", &val);
		cfg->track_map = val;

		strcpy(cfg->track_map_cmt, comment);

		set_val_cmt_(cfg);
		printf("Value edited successfully..\n");
		start_(cfg);
	} else if(sel == 'v' || sel == 'V') {
		printf("Enter value for Environment Map (%d default): ", cfg->env_map);
	} else if(sel == 'q' || sel == 'Q') {
		printf("Enter value for Texture Quality (%d default): ", cfg->tex_qlty);
	} else if(sel == 'a' || sel == 'A') {
		printf("Enter value for Anisotropic Filter Quality (%d default): ", cfg->an_fil_qlty);
	} else if(sel == 's' || sel == 'S') {
		printf("Enter value for Shadow Type (%d default): ", cfg->shdw_type);
	} else if(sel == 'c' || sel == 'C') {
		save_file(cfg);
		start_(cfg);
	}
}

void init_vals(CFG *cfg) {
	cfg->tex_fil_qlty_key = 98;
	cfg->tex_fil_qlty_cmt = "";
	cfg->tex_fil_qlty = 0;
	
	cfg->track_map_key = 52;
	cfg->track_map_cmt = "";
	cfg->track_map = 0;

	cfg->env_map_key = 64;
	cfg->env_map_cmt = "";
	cfg->env_map = 0;

	cfg->tex_qlty_key = 23;
	cfg->tex_qlty_cmt = "";
	cfg->tex_qlty = 0;

	cfg->an_fil_qlty_key = 100;
	cfg->an_fil_qlty_cmt = "";
	cfg->an_fil_qlty = 0;

	cfg->shdw_type_key = 108;
	cfg->shdw_type_cmt = "";
	cfg->shdw_type = 0;
	
	printf("Initialized values from file..\n");
	start_(cfg);
}

void read_file(CFG *cfg) {
	printf("Now reading contents of file..\n");

	cfg->tot_lines = 0;
	free(cfg->all_lines);
	free(cfg->cur_line);
	cfg->all_lines = (char **) malloc(sizeof(char) * MAX_LINE * MAX_LINES);
	cfg->cur_line = (char *) malloc(sizeof(char) * MAX_LINE);

	while(fgets(cfg->cur_line, MAX_LINE, cfg->fp)) {
		strip_newline(cfg->cur_line, MAX_LINE);
		if(strlen(cfg->cur_line) > 0) {
			cfg->all_lines[cfg->tot_lines] = (char *) malloc(sizeof(char) * MAX_LINE);
			//printf("%s", cfg->cur_line);
			strcpy(cfg->all_lines[cfg->tot_lines], cfg->cur_line);
			free(cfg->cur_line);
			cfg->cur_line = (char *) malloc(sizeof(char *) * MAX_LINE);
			++cfg->tot_lines;
		}
	}
	fclose(cfg->fp);
	init_vals(cfg);
}

int main(int argc, char *argv[], char *env[]) {
	CFG cfg;
	printf("\n|+++++++++++++++++++++++++++++|");
	printf("\n| Welcome to GP4 configurator |");
	printf("\n|+++++++++++++++++++++++++++++|\n");

	printf("Specify the path for the configuration file: ");
	memset(cfg.file_name, 0, 256);
	fgets(cfg.file_name, 256, stdin);
	strip_newline(cfg.file_name, 256);
	
	if(strlen(cfg.file_name) > 0) {
		cfg.fp = fopen(cfg.file_name, "r");
		if(cfg.fp) {
			printf("Loading from location: %s\n", cfg.file_name);
			read_file(&cfg);
		} else {
			printf("Error reading file!\n");
		}
	} else {
		strcpy(cfg.file_name, "C:\\Program Files\\Infogrames\\Grand Prix 4\\f1graphics.cfg");
		cfg.fp = fopen(cfg.file_name, "r");
		if(!cfg.fp) {
			strcpy(cfg.file_name, "C:\\Program Files (x86)\\Infogrames\\Grand Prix 4\\f1graphics.cfg");
			cfg.fp = fopen(cfg.file_name, "r");
			if(!cfg.fp) {
				printf("Error reading file!\n");
				return -1;
			}
		}
		printf("Loading from default location: %s\n", cfg.file_name);
		read_file(&cfg);
	}

	free(value);
	free(token);
	free(comment);	
	free(cfg.cur_line);
	free(cfg.all_lines);
	cfg.tot_lines = 0;
	
	return 0;
}
