#include "gf2d_file.h"

void openFile(char* filePath) {
	int success = 0;
	Sint64 gData[FILE_MAX_DATA];
	//Open file for reading in binary
	SDL_RWops* file = SDL_RWFromFile("33_file_reading_and_writing/nums.bin", "r+b");

	//File does not exist
	if (file == NULL)
	{
		printf("Warning: Unable to open file! SDL Error: %s\n", SDL_GetError());

		//Create file for writing
		file = SDL_RWFromFile(filePath, "w+b");


		if (file != NULL)
		{
			printf("New file created!\n");

			//Initialize data
			for (int i = 0; i < FILE_MAX_DATA; ++i)
			{
				gData[i] = 0;
				SDL_RWwrite(file, &gData[i], sizeof(Sint32), 1);
			}

			//Close file handler
			SDL_RWclose(file);
		}
		else
		{
			printf("Error: Unable to create file! SDL Error: %s\n", SDL_GetError());
			success = 0;
		}
	}
	//File exists
	else
	{
		//Load data
		printf("Reading file...!\n");
		for (int i = 0; i < FILE_MAX_DATA; ++i)
		{
			SDL_RWread(file, &gData[i], sizeof(Sint32), 1);
		}

		//Close file handler
		SDL_RWclose(file);
	}

}

