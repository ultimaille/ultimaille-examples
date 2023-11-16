#include <iostream>

#ifdef __unix__

#include <unistd.h>

std::string getExecutablePath() {
    char pBuf[256];
    size_t len = sizeof(pBuf);

    // int bytes = MIN(readlink("/proc/self/exe", pBuf, len), len - 1);
    int bytes = readlink("/proc/self/exe", pBuf, len);

    if(bytes >= 0)
        pBuf[bytes] = '\0';
    
    std::string path(pBuf);

    // Split path, get directory name without program name
    int i = path.find_last_of("/");
    return path.substr(0, i);
}

#elif _WIN32

#define NOMINMAX   
#include <Windows.h>
std::string getExecutablePath() {
    char pBuf[256];
    size_t len = sizeof(pBuf);
    int bytes = GetModuleFileName(NULL, pBuf, len);

    std::string path(pBuf);

    // Split path, get directory name without program name
    int i = path.find_last_of("\\");
    return path.substr(0, i);
}

#endif

std::string getAssetPath() {
    std::string path = getExecutablePath();
    #ifdef __unix__
    path += "/assets/";
    #elif _WIN32
    // Considering user will use VS C++ on Windows,
    // it will generate a target directory according to the config (Release, Debug, ...)
    // We get assets on the top directory
    path += "\\..\\assets\\";
    #endif
    return path;
}