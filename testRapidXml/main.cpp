#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
using namespace rapidxml;

class CRapidXml
{
public:
	void CreateXml();
	void ReadAndChangeXml(const char *strPath);
};

void CRapidXml::CreateXml()
{
	xml_document<> doc;
	xml_node<> *root = doc.allocate_node(node_pi,doc.allocate_string("xml version='1.0' encoding='utf-8'"));
	doc.append_node(root);

	xml_node<> *node = doc.allocate_node(node_element,"config",NULL);
	doc.append_node(node);

	xml_node<> *color = doc.allocate_node(node_element,"color",NULL);
	node->append_node(color);

	color->append_node(doc.allocate_node(node_element,"red","0.1"));
	color->append_node(doc.allocate_node(node_element,"green","0.1"));
	color->append_node(doc.allocate_node(node_element,"blue","0.1"));
	color->append_node(doc.allocate_node(node_element,"alpha","1.0"));

	xml_node<> *size = doc.allocate_node(node_element,"size",NULL);
	node->append_node(size);

	size->append_node(doc.allocate_node(node_element,"x","640"));
	size->append_node(doc.allocate_node(node_element,"y","480"));

	xml_node<> *mode = doc.allocate_node(node_element,"mode","screen mode");
	mode->append_attribute(doc.allocate_attribute("fullscreen","false"));
	node->append_node(mode);

	ofstream out("../config/config1.xml");
	out<< doc;
}

void CRapidXml::ReadAndChangeXml(const char *strPath)
{
	file<> fdoc(strPath);
	cout << fdoc.data()<<endl;
	xml_document<> doc;
	doc.parse<0>(fdoc.data());
	cout<< doc.name() << endl;
	//获取根结点
	xml_node<> *root = doc.first_node();
	cout<<root->name()<<endl;

	xml_node<> *node = root->first_node();
	xml_node<> *node1 = node->first_node();


	for(xml_node<> *node = root->first_node();node != NULL;node = node->next_sibling())
	{
		cout<< node->name() << endl;
		if(node1)
		{
			for(;node1 != NULL;node1 = node1->next_sibling())
			{
				cout<< node1->name() << endl;
				cout<< node1->value() << endl;
			}
		}

	}
	
	//xml_node<> *node1 = root->first_node();
	//cout << node1->name() << endl;

	//xml_node<> *node11 = node1->first_node();
	//cout << node11->name() << endl;
	//cout << node11->value() << endl;

	////修改后再保存
	//xml_node<> *size = root->first_node("size");
	//size->append_node(doc.allocate_node(node_element,"w","1"));
	//size->append_node(doc.allocate_node(node_element,"h","1"));
	//string text;
	//print(back_inserter(text),doc,0);
	//cout << text << endl;
	ofstream out(strPath);
	out << doc;
}

void main()
{
	CRapidXml obj;
	//创建XML
//	obj.CreateXml();
	//读取XML
	const char *strPath = "../config/config2.xml";
	obj.ReadAndChangeXml(strPath);
	system("pause");
}