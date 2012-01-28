#include "ConfigReader.h"

#include <fstream>


ConfigReader::ConfigReader(void)
: m_bLoopFound(false)
, m_bActivatedTestConf(false)
{

}


ConfigReader::~ConfigReader(void)
{

}

ConfigReader* ConfigReader::GetInstance()
{
	if (s_pInstance)
		return s_pInstance;
	s_pInstance = new ConfigReader();
	return s_pInstance;
}

void ConfigReader::DeleteInstance()
{
	if (s_pInstance)
		delete s_pInstance;
}

void ConfigReader::LoadTestConfig( const char* pName )
{
	std::ifstream config(pName);
	std::string line;

	m_bLoopFound = false;
	m_bActivatedTestConf = false;

	if (config.is_open())
	{
		while ( config.good() )
		{
			getline(config, line);
			ParseLine(line, m_Params);
		}
		config.close();

		GenerateTestPath();
		GenerateTestConfigs();
	}
}

void ConfigReader::ParseLine( const std::string& line, std::map< std::string, std::vector<std::string> >& params, bool bWriteSequense )
{
	int comment_pos = line.find('#');
	if (comment_pos != -1) // this is a comment. need to do nothing
		return;

	std::string str_key;
	int equal_pos = line.find('=');
	if (equal_pos == -1) // it is the key without param
	{
		str_key = line;
		
		if (bWriteSequense&&m_bLoopFound)
			m_TestQueue.push_back(str_key);
		if (strcmp("LOOP", str_key.c_str()) == 0)
			m_bLoopFound = true;
	}
	else
	{
		str_key = line.substr(0, equal_pos);

		if (bWriteSequense&&m_bLoopFound)
			m_TestQueue.push_back(str_key);

		std::string str_values = line.substr(equal_pos + 1);
		
		std::vector<std::string> value;
		int value_pos = str_values.find(';');
		if (value_pos == -1)
		{
			value.push_back(str_values);
		}
		else
		{
			int separator_pos = 0, separator_next_pos = 0;
			bool bLoop = true;
			while (bLoop)
			{
				separator_next_pos = str_values.find(';', separator_pos);

				// if end of the line we go out
				if (separator_next_pos == -1)
				{
					std::string str_value = str_values.substr(separator_pos);
					value.push_back(str_value);
					break;
				}

				// get one param
				std::string str_value = str_values.substr(separator_pos, separator_next_pos - separator_pos);
				value.push_back(str_value);

				separator_pos = separator_next_pos + 1;
			}
		}
		
		if (strcmp("CONF", str_key.c_str()) == 0)
		{
			char filePath[128];
			sprintf_s(filePath, "%s\\%s.%s", 
				m_Params["TEST_FILE_DIRECTORY"][0].c_str(), 
				str_values.c_str(),
				m_Params["TEST_FILE_FORMAT"][0].c_str());
			m_CurrentTestFile = filePath;
			m_bActivatedTestConf = true;
		}
		else
		{
			if (!m_bActivatedTestConf)
				params[str_key] = value;
			else
			{
				std::map<std::string, std::vector<std::string> >& fileConf = m_FileConfigs[m_CurrentTestFile].fileConfig;
				fileConf[str_key] = value;
			}
		}
	}
}

void ConfigReader::GenerateTestPath()
{
	char str[128];
	for (size_t i = 0, i_end = m_Params["TEST_FILE_DIRECTORY"].size(); i < i_end; ++i)
	{
		for (size_t j = 0, j_end = m_Params["TEST_FILE_NAME"].size(); j < j_end; ++j)
		{
			for (size_t k = 0, k_end = m_Params["TEST_FILE_FORMAT"].size(); k < k_end; ++k)
			{
				sprintf_s(str, "%s\\%s.%s", 
					m_Params["TEST_FILE_DIRECTORY"][i].c_str(), 
					m_Params["TEST_FILE_NAME"][j].c_str(),
					m_Params["TEST_FILE_FORMAT"][k].c_str());
				m_TestPath.push_back(str);
			}
		}
	}
}

void ConfigReader::GenerateTestConfigs()
{
	char str[128];
	for (size_t i = 0, i_end = m_Params["TEST_CONFIG_DIRECTORY"].size(); i < i_end; ++i)
	{
		for (size_t j = 0, j_end = m_Params["TEST_CONFIG_FORMAT"].size(); j < j_end; ++j)
		{
			for (size_t k = 0, k_end = m_Params["TEST_CONFIG_NAME"].size(); k < k_end; ++k)
			{
				sprintf_s(str, "%s\\%s.%s", 
					m_Params["TEST_CONFIG_DIRECTORY"][i].c_str(), 
					m_Params["TEST_CONFIG_NAME"][k].c_str(),
					m_Params["TEST_CONFIG_FORMAT"][j].c_str()
					);
				m_TestConfig.push_back(str);
			}
		}
	}
}

const std::vector<std::string>&	ConfigReader::ReadConfig( const char* pName )
{
	m_TestQueue.clear();
	std::ifstream config(pName);
	std::string line;

	m_bLoopFound = false;
	m_bActivatedTestConf = false;

	if (config.is_open())
	{
		while ( config.good() )
		{
			getline(config, line);
			ParseLine(line, m_Configs, true);
		}
		config.close();
	}

	return m_TestQueue;
}

ConfigReader* ConfigReader::s_pInstance = 0;