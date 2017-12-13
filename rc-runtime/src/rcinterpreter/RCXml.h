
#pragma once


#include "tinyxml.h"
#include "RCRuntimeModel.h"


class RCXmlLoader {
public:
	RCXmlLoader() {}
	RCXmlLoader(std::string file) : xmlFile(file) {
		if (doc.LoadFile(xmlFile.c_str())) {  	
			// doc.Print();  
			std::cout << "RC xml file load sucessfully !" << std::endl;
		} else {
			std::cout << "RC can not parse xml file: " << file << std::endl;
			throw rc_xmlparser_exception(file);
		}
	}

	int parseXml(RC_SymbolTable &symTable) ;

private:
	bool getXmlDeclare(std::string &strVersion, std::string &strStandalone, std::string &strEncoding){
		TiXmlNode* pXmlFirst = doc.FirstChild();     
		if (NULL != pXmlFirst) {    
			TiXmlDeclaration* pXmlDec = pXmlFirst->ToDeclaration();    
			if (NULL != pXmlDec) {    
				strVersion = pXmlDec->Version();  
				strStandalone = pXmlDec->Standalone();  
				strEncoding = pXmlDec->Encoding();  
			}  
		}  
		return true;  
	}
	bool getNodeByName(TiXmlElement* pRootEle, std::string strNodeName, TiXmlElement* &Node) {
		if (strNodeName == pRootEle->Value()) {  
			Node = pRootEle;  
			return true;  
		}  
		TiXmlElement* pEle = pRootEle;    
		for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement()) {    
			if(getNodeByName(pEle, strNodeName, Node)) {
				return true;  
			}
		}    
		return false;  
	}


public:
	std::string xmlFile;
	TiXmlDocument doc; 
};

