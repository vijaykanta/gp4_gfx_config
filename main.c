#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH 1000
#define MAX_STRUCT 5000
#define MAX_LEN 150
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
		getchar();
		start_(cfg);
	} else if(sel == 'm' || sel == 'M') {
		cfg->cur_sel = cfg->track_map_key;
		get_val_cmt_(cfg);

		printf("Enter value for Track Map (%s default): ", value);
		scanf("%d", &val);
		cfg->track_map = val;

		strcpy(cfg->track_map_cmt, comment);

		set_val_cmt_(cfg);
		printf("Value edited successfully..\n");
		getchar();
		start_(cfg);
	} else if(sel == 'v' || sel == 'V') {
		cfg->cur_sel = cfg->env_map_key;
		get_val_cmt_(cfg);

		printf("Enter value for Environment Map (%s default): ", value);
		scanf("%d", &val);
		cfg->env_map = val;

		strcpy(cfg->env_map_cmt, comment);

		set_val_cmt_(cfg);
		printf("Value edited successfully..\n");
		getchar();
		start_(cfg);
	} else if(sel == 'q' || sel == 'Q') {
		cfg->cur_sel = cfg->tex_qlty_key;
		get_val_cmt_(cfg);

		printf("Enter value for Texture Quality (%s default): ", value);
		scanf("%d", &val);
		cfg->tex_qlty = val;

		strcpy(cfg->tex_qlty_cmt, comment);

		set_val_cmt_(cfg);
		printf("Value edited successfully..\n");
		getchar();
		start_(cfg);
	} else if(sel == 'a' || sel == 'A') {
		cfg->cur_sel = cfg->an_fil_qlty_key;
		get_val_cmt_(cfg);

		printf("Enter value for Anisotropic Filter Quality (%s default): ", value);
		scanf("%d", &val);
		cfg->an_fil_qlty = val;

		strcpy(cfg->an_fil_qlty_cmt, comment);

		set_val_cmt_(cfg);
		printf("Value edited successfully..\n");
		getchar();
		start_(cfg);
	} else if(sel == 's' || sel == 'S') {
		cfg->cur_sel = cfg->shdw_type_key;
		get_val_cmt_(cfg);

		printf("Enter value for Shadow Type (%s default): ", value);
		scanf("%d", &val);
		cfg->shdw_type = val;

		set_val_cmt_(cfg);
		printf("Value edited successfully..\n");
		getchar();
		start_(cfg);
	} else if(sel == 'c' || sel == 'C') {
		save_file(cfg);
		getchar();
		start_(cfg);
	} else if(sel == 'f' || sel == 'F') {
		show_file_contents(cfg);
		getchar();
		start_(cfg);
	}
}

void init_vals(CFG *cfg) {
	cfg->tex_fil_qlty_key = 98;
	cfg->tex_fil_qlty_cmt = (char *) malloc(sizeof(char) * MAX_LEN);
	cfg->tex_fil_qlty = 0;
	
	cfg->track_map_key = 54;
	cfg->track_map_cmt = (char *) malloc(sizeof(char) * MAX_LEN);
	cfg->track_map = 0;

	cfg->env_map_key = 64;
	cfg->env_map_cmt = (char *) malloc(sizeof(char) * MAX_LEN);
	cfg->env_map = 0;

	cfg->tex_qlty_key = 23;
	cfg->tex_qlty_cmt = (char *) malloc(sizeof(char) * MAX_LEN);
	cfg->tex_qlty = 0;

	cfg->an_fil_qlty_key = 100;
	cfg->an_fil_qlty_cmt = (char *) malloc(sizeof(char) * MAX_LEN);
	cfg->an_fil_qlty = 0;

	cfg->shdw_type_key = 108;
	cfg->shdw_type_cmt = (char *) malloc(sizeof(char) * MAX_LEN);
	cfg->shdw_type = 0;
	
	printf("Initialized values from file..\n");
	start_(cfg);
}

void free_vals(CFG *cfg) {
	free(cfg->tex_fil_qlty_cmt);
	free(cfg->track_map_cmt);
	free(cfg->env_map_cmt);
	free(cfg->tex_qlty_cmt);
	free(cfg->an_fil_qlty_cmt);
	free(cfg->shdw_type_cmt);
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
		free_vals(&cfg);
		free(cfg.cur_line);
		free(cfg.all_lines);
		cfg.tot_lines = 0;
	}

	if(sizeof(value) > 0) free(value);
	if(sizeof(comment) > 0) free(comment);
	
	return 0;
}
