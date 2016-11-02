//
// Created by Robert JONES on 2016/11/02.
//

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>
#include "../includes/Taskmaster.h"

void initProcecces(string file){
    YAML::Node config = YAML::LoadFile(file);
    for(YAML::const_iterator it=config.begin();it != config.end();++it) {
        /*std::string key = it->first.as<std::string>();       // <- key
        cTypeList.push_back(it->second.as<CharacterType>()); // <- value*/
        cout << *it <<endl;
    }
}
