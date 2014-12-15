#include <iostream>
#include "Import.h"
#include "Tile.h"

using namespace std;

int main(int argc, char *argv[])
{
	Import import(argv[1]);
	import.write_to_file();
	import.write_to_filep();
	return EXIT_SUCCESS;
}
