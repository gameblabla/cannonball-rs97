/***************************************************************************
    Binary File Loader. 
    
    Handles loading an individual binary file to memory.
    Supports reading bytes, words and longs from this area of memory.

    Copyright Chris White.
    See license.txt for more details.
***************************************************************************/

#include <iostream>
#include <fstream>
#include <cstddef>       // for std::size_t
#include "stdint.hpp"
#include "romloader.hpp"

RomLoader::RomLoader()
{
    loaded = false;
}

RomLoader::~RomLoader()
{
}

void RomLoader::init(const uint32_t length)
{
    this->length = length;
    rom = new uint8_t[length];
}

void RomLoader::unload(void)
{
    delete[] rom;
}

int RomLoader::load(const char* filename, const int offset, const int length, const int expected_crc, const uint8_t interleave)
{
	char path[256];
	snprintf(path, sizeof(path), "%s/.cannonball/roms/%s", getenv("HOME"), filename);

    // Open rom file
    std::ifstream src(path, std::ios::in | std::ios::binary);
    if (!src)
    {
        std::cout << "cannot open rom: " << filename << std::endl;
        loaded = false;
        return 1; // fail
    }

    // Read file
    char* buffer = new char[length];
    src.read(buffer, length);

    // Interleave file as necessary
    for (int i = 0; i < length; i++)
    {
        rom[(i * interleave) + offset] = buffer[i];
    }

    // Clean Up
    delete[] buffer;
    src.close();
    loaded = true;
    return 0; // success
}

// Load Binary File (LayOut Levels, Tilemap Data etc.)
int RomLoader::load_binary(const char* filename)
{
	char path[256];

	snprintf(path, sizeof(path), "%s/.cannonball/roms/%s", getenv("HOME"), filename);

    // --------------------------------------------------------------------------------------------
    // Read LayOut Data File
    // --------------------------------------------------------------------------------------------
    std::ifstream src(path, std::ios::in | std::ios::binary);
    if (!src)
    {
        std::cout << "cannot open file: " << filename << std::endl;
        loaded = false;
        return 1; // fail
    }

    length = filesize(filename);

    // Read file
    char* buffer = new char[length];
    src.read(buffer, length);
    rom = (uint8_t*) buffer;

    // Clean Up
    src.close();

    loaded = true;
    return 0; // success
}

int RomLoader::filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::in | std::ifstream::binary);
    in.seekg(0, std::ifstream::end);
    int size = (int) in.tellg();
    in.close();
    return size; 
}
