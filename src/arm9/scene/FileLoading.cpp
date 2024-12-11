#include "FileLoading.hpp"
#include "file.hpp"
#include <cstdlib>
#include <nds/arm9/console.h>
#include <nds/arm9/video.h>
#include <nds/system.h>

using namespace nb;

FileLoading::FileLoading()
{
  videoSetMode(MODE_0_3D);
  lcdMainOnTop();
  consoleDemoInit();
}

FileLoading::~FileLoading()
{

}

void FileLoading::Preload()
{
  consoleClear();

  size_t file_size;
  unsigned char* file_buffer = LoadFileData("nitro:/file.txt", file_size);

  printf("\n file: ");
  consoleSetColor(nullptr, ConsoleColor::CONSOLE_LIGHT_YELLOW);
  printf("nitro:/file.txt\n");
  consoleSetColor(nullptr, ConsoleColor::CONSOLE_WHITE);
  printf(" size: ");
  consoleSetColor(nullptr, ConsoleColor::CONSOLE_LIGHT_YELLOW);
  printf("%i bytes\n", file_size);

  consoleSetColor(nullptr, ConsoleColor::CONSOLE_WHITE);
  printf("\n\n content:\n\n");
  consoleSetColor(nullptr, ConsoleColor::CONSOLE_LIGHT_GRAY);
  for (size_t i=0; i<file_size; i++) consolePrintChar(file_buffer[i]);

  free(file_buffer);
}

void FileLoading::Update()
{

}
