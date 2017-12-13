
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include <cstdlib>

#include "IValue.h"
#include "tinyxml.h"
#include "RSIRuntimeModel.h"


class RSIXmlLoader {
public:
	RSIXmlLoader() {}
	RSIXmlLoader(std::string file) : xmlFile(file) {
		if (doc.LoadFile(xmlFile.c_str())) {  	
			// doc.Print();  
			std::cout << "xml file load sucessfully !" << std::endl;
		} else {
			std::cout << "can not parse xml file: " << file << std::endl;
			throw rc_xmlparser_exception(file);
		}
	}

	int parseXml(std::vector<IValue> &addrspace, 
			 std::unordered_map<std::string, int> &dataIndexMap,
			 std::unordered_map<std::string, EntityBase*> &fbMap);

private:
	bool getXmlDeclare(std::string &strVersion, std::string &strStandalone, std::string &strEncoding);
	bool getNodeByName(TiXmlElement* pRootEle, std::string strNodeName, TiXmlElement* &Node);


public:
	std::string xmlFile;
	TiXmlDocument doc; 
};

