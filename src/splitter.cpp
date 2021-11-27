#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

void splitFile( std::filesystem::path filePath, long long unsigned int chunkSize){
  // check that the file really exists
  if(!std::filesystem::exists(filePath)){
    throw "The file does not exist. Please check the file path.";
  }
  std::cout << "splitting the file here " << filePath << "\n";
  std::filesystem::path fileStem = filePath.stem();
  std::filesystem::path destFolder = filePath.parent_path()/fileStem;

  if(std::filesystem::exists(destFolder)){
    std::filesystem::remove_all(destFolder);
  }
  std::cout << "creating destination folder...\n";
  std::filesystem::create_directories(destFolder);
  std::cout << "done.\n";
  long long int nbChunkFiles = 0;
  std::fstream sourceFile;
  std::fstream destFile;
  sourceFile.open(filePath, std::ios::in);

  std::string firstLine = "";
  if(sourceFile.is_open()){
    std::string currentLine;
    long long unsigned int currentSize = 0;
    std::string tmpFileName;
    
    std::cout << "starting splitting the files...\n";
    while(std::getline(sourceFile, currentLine)){
      // saving the first line so we can write it in every new files
      if(firstLine == ""){
        firstLine = currentLine+"\n";
      }
      else{
        // if this line would make the file too big, we close the file
        if(currentLine.size()+currentSize > chunkSize){
          destFile.close();
        }

        // if the current destination file is closed, we open a new one and wrie the 
        // first line in it
        if(!destFile.is_open()){
          nbChunkFiles++;
          tmpFileName = fileStem.string() + "_" + std::to_string(nbChunkFiles) + ".csv";
          destFile.open(destFolder/tmpFileName, std::ios::out);
          if(destFile.is_open()){
            destFile << firstLine;
            currentSize = firstLine.size();
          }
          else{
            throw "Error while opening the file "+tmpFileName;
          }
        }

        destFile << currentLine << "\n";
        currentSize+=currentLine.size();
      }


    }
  }

  destFile.close();
  sourceFile.close();
  std::cout << "done.\n";


}