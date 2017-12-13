#include "RCXml.h"


int RCXmlLoader::parseXml(RC_SymbolTable &symTable) {
	TiXmlElement* rootEle = doc.RootElement(); 
	
	TiXmlElement* decEle;	
	if(getNodeByName(rootEle, "DECLARE", decEle)) {
		
		TiXmlElement* varEle ;
		if(getNodeByName(decEle, "VARIABLES", varEle)) {
			// std::cout << varEle->Value() << std::endl;
			
			TiXmlElement* vEle = varEle->FirstChildElement();
			for(; vEle != NULL; vEle = vEle->NextSiblingElement()) {
				std::string varName;
				std::string varVal("0");
				
				TiXmlAttribute* attr = vEle->FirstAttribute();
				for(; attr != NULL; attr = attr->Next()) {
					
					std::string attrName = attr->Name();
					if(attrName == "NAME") {
						varName = attr->Value();
					} else if(attrName == "INIT"){
						varVal = attr->Value();
					}

				}

				double val = std::stod(varVal);
				int curIndex = symTable.addrspace.size();

				symTable.dataIndexMap.insert(std::pair<std::string, int>(varName, curIndex));
				symTable.addrspace.push_back(RC_IValue(TDOUBLE, val));
			}

		}
	
		TiXmlElement* fbNode ;
		if(getNodeByName(decEle, "FUNBLOCK", fbNode)) {

			TiXmlElement* fbEle = fbNode->FirstChildElement();
			for(; fbEle != NULL; fbEle = fbEle->NextSiblingElement()) {

				/* get fb entity name */
				TiXmlAttribute* attr = fbEle->FirstAttribute(); // NAME property in xml file for fb
				std::string fbName = attr->Value();

				/* get fb entity pointer */
				attr = attr->Next();     		// TYPE property in xml file for fb
				RCEntityBase* entity = RCEntityFactory::getEntity(attr->Value());
				if(entity != NULL) {
					/* config fb entity */
					for(attr = attr->Next(); attr != NULL; attr = attr->Next()) {
						entity->setConfig(attr->Name(), attr->Value());
					}

					symTable.fbMap.insert(std::pair<std::string, RCEntityBase*>(fbName, entity));
				}
			}

		}

	}


	TiXmlElement* commEle;
	if(getNodeByName(rootEle, "COMMUNICATION", commEle)) {
		RCCommEntity* entity = dynamic_cast<RCCommEntity*>(RCEntityFactory::getEntity("RC_COMMUNICATION"));

		TiXmlElement* configEle ;
		if(getNodeByName(commEle, "CONFIG", configEle)) {
			TiXmlElement* cEle = configEle->FirstChildElement();
			for(; cEle != NULL; cEle = cEle->NextSiblingElement()) {
				entity->setConfig(cEle->Value(), cEle->GetText());
			}
		}

		TiXmlElement* sendEle ;
		if(getNodeByName(commEle, "SEND", sendEle)) {
			// std::cout << "SEND" << std::endl;
			TiXmlElement* sEle = sendEle->FirstChildElement()->FirstChildElement();
			for(; sEle != NULL; sEle = sEle->NextSiblingElement()) {
				std::string tagName;
				int varIndex = 0;

				TiXmlAttribute* attr = sEle->FirstAttribute();
				for(; attr != NULL; attr = attr->Next()) {
					std::string attrName = attr->Name();
					if(attrName == "TAG") {
						tagName = attr->Value();
					} else if(attrName == "VAR") {
						varIndex = symTable.dataIndexMap[attr->Value()]; // if varIndex == 0 then var is invalid
						if(varIndex == 0) {
							std::cout << "the var of [" << attr->Value() << "] is not declared" << std::endl; 
						} 
					} else if(attrName == "TYPE") {

					}
				}
				
				entity->setSendDataMap(tagName, varIndex);
			}

		}

		TiXmlElement* recvEle ;
		if(getNodeByName(commEle, "RECEIVE", recvEle)) {
			// std::cout << "RECEIVE" << std::endl;
			TiXmlElement* rEle = recvEle->FirstChildElement()->FirstChildElement();
			for(; rEle != NULL; rEle = rEle->NextSiblingElement()) {
				std::string tagName;
				int varIndex = 0;

				TiXmlAttribute* attr = rEle->FirstAttribute();
				for(; attr != NULL; attr = attr->Next()) {
					std::string attrName = attr->Name();
					if(attrName == "TAG") {
						tagName = attr->Value();
					} else if(attrName == "VAR") {
						varIndex = symTable.dataIndexMap[attr->Value()];	// if varIndex == 0 then var is invalid
						if(varIndex == 0) {
							std::cout << "the var of [" << attr->Value() << "] is not declared" << std::endl; 
						} 
					} else if(attrName == "TYPE") {

					}
				}

				entity->setRecvDataMap(tagName, varIndex);
			}

		}

		symTable.fbMap.insert(std::pair<std::string, RCEntityBase*>("RC_COMMUNICATION", entity));
	}
}