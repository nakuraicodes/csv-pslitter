#include <filesystem>

/**
 * @brief take a csv file and split it in several files of a specific maximum
 * size. This function will create a folder with the same name as the file, in
 * the same path as the file. All the generated files inside will be created inside.
 * If the destination folder cannot be written, it will throw an error.
 * If the new folder already exists, it will delete it and replace its content.
 * 
 * @param size the maximum size of each chunk files in bytes
 * @param filePath the path to the file to be splitted
 *
 */
void splitFile( std::filesystem::path filePath, long long unsigned int chunkSize);