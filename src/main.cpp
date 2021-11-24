#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <filesystem>

std::string splitArgument(std::string argument);
std::string getFilename(std::string filePath);
std::string getFolderPath(std::string filePath);

int main(int argc, char* argv[]){
    int mbSize = 0;
    std::string folderPath = "";
    std::string fileName = "";
    std::string fileNameWoExtension = "";
    std::filesystem::path filePath;
    if(argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")){
        std::string helpText = "\n\n### CSV SPLITTER ###\nThis program helps you split a big csv file into "
        "multiple smaller ones. It is useful to handle sizes too big "
        "to load in Excel.\n\nArguments list:\n\t- size: max size "
        "of an individual chunks, in MB\n\t- path: the path to the file. "
        "You must have writing permission to the containing folder."
        "\n\nex: csv-splitter --size=10 --path=/path/to/file.csv\n\n";
        std::cout << helpText;
    }
    else{
        try{
            // Extracting all the infromation we need to split the file
            for(int argIndex=0; argIndex<argc; argIndex++){
                std::string arg = argv[argIndex];
                
                if(arg.find("--size=") != std::string::npos){
                    std::string sSize = splitArgument(arg);
                    mbSize = stoi(sSize);
                }
                else if(arg.find("--path=") != std::string::npos){
                    filePath = splitArgument(arg);
                    if(filePath.is_relative()){
                        filePath=std::filesystem::canonical( filePath);
                    }

                    
                }
            }
            // at this point all the required options should be known, throwing 
            // an exception if it's not the case
            if(mbSize == 0 || filePath == ""){
                throw "Missing options. Use -h option to list all options.";
            } 

            // Creating the destination folder
            

        }
        catch (const std::invalid_argument& ia) {
            std::cerr << "ERR: " << ia.what() << "\nERR: Invalid option. The size is probably not a number or the file not the right format\n";
            return 1;
        }
        catch(const char* e){
            std::cerr << "ERR: " << e << '\n';
            return 1;
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
            return 1;
        }
        
       

    }


    return 0;
}

std::string splitArgument(std::string argument){
    std::string value = "";
    bool separatorFound = false;
    for(auto c:argument){
        if(separatorFound){
            value += c;
        }
        if (c=='='){
            separatorFound = true;
        }
    }
    return value;
}

std::string getFilename(std::string filePath){
    int sepIndex = filePath.find_last_of("/");
    if((unsigned)sepIndex == std::string::npos){
        sepIndex = filePath.find_last_of("\\");
    }
    if((unsigned)sepIndex == std::string::npos){
        throw "Impossible to extract filename";
    }
    return filePath.substr(sepIndex+1);
}

std::string getFolderPath(std::string filePath){
    int sepIndex = filePath.find_last_of("/");
    if((unsigned)sepIndex == std::string::npos){
        sepIndex = filePath.find_last_of("\\");
    }
    if((unsigned)sepIndex == std::string::npos){
        throw "Impossible to extract filename";
    }
    return filePath.substr(0, sepIndex);
}