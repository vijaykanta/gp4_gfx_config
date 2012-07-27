/**
* @author Vijay Kanta
* @website www.vizcreations.com
* @abstract Simple console configurator for game Grand Prix 4
* @license Free software - No guarantee
* @copyright Not applicable
* @link https://github.com/vijaykanta/gp4_gfx_config.git
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gplib.h"

void start_(CFG *cfg) {
	printf("\nType 't' to edit Texture Filter Quality\n");
	printf("Type 'm' to edit Track Map\n");
	printf("Type 'v' to edit Environment Map\n");
	printf("Type 'q' to edit Texture Quality\n");
	printf("Type 'a' to edit Anisotropic Filter Quality\n");
	printf("Type 's' to edit Shadow Type\n");
	printf("Type 'c' to generate configuration file from buffer\n");
	printf("Type 'x' to exit\n\n");

	scanf("%c", &sel);
	if(sel == 't' || sel == 'T') {
		cfg->cur_sel = cfg->tex_fil_qlty_key;
		get_val_cmt_(cfg);
		show_cur_val(cfg);

		printf("Enter value for Texture Filter Quality (%s - current): ", value);
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
		show_cur_val(cfg);

		printf("Enter value for Track Map (%s - current): ", value);
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
		show_cur_val(cfg);

		printf("Enter value for Environment Map (%s - current): ", value);
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
		show_cur_val(cfg);

		printf("Enter value for Texture Quality (%s - current): ", value);
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
		show_cur_val(cfg);

		printf("Enter value for Anisotropic Filter Quality (%s - current): ", value);
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
		show_cur_val(cfg);

		printf("Enter value for Shadow Type (%s - current): ", value);
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
	int num;
	FILE *handler;
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

	printf("Now creating backup file..\n");
	handler = fopen("f1graphics.cfg.backup", "w");
	if(handler) {
		for(num=0; num<cfg->tot_lines; num++) {
			fprintf(handler, "%s\n", cfg->all_lines[num]);
		}
		fclose(handler);
		printf("Created backup file successfully..\n");
	}

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

	if(sizeof(buff) > 0) free(buff);
	if(sizeof(value) > 0) free(value);
	if(sizeof(comment) > 0) free(comment);
	
	return 0;
}
