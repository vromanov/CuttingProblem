#pragma once

#include <string>
#include <map>
#include <vector>

class FileConf
{
public:
	std::map<std::string, std::vector<std::string> > fileConfig;
};

class ConfigReader
{
public:

	static ConfigReader*	GetInstance();
	static void				DeleteInstance();

	void					LoadTestConfig(const char* pName);

	const std::vector<std::string>&	ReadConfig(const char* pName);
	const std::vector<std::string>&	GetTestNames() { return m_TestName; }
	const std::vector<std::string>&	GetTestConfigs() { return m_TestConfig; }
	const size_t					GetTestRepeat() { return atoi(m_Params["TEST_REPEAT"][0].c_str());}

	const std::string&				GetConfigValue(const std::string& name) { return m_Configs[name][0]; }
	const size_t					GetConfigIntValue(const std::string& name) { return atoi(m_Configs[name][0].c_str()); }

	const size_t					GetFileConfigIntValue(const std::string& name) { return atoi(m_FileConfigs[m_CurrentTestFile].fileConfig[name][0].c_str()); }

	void							SetCurrentTestFile(const char* pName) { m_CurrentTestFile = pName; }

private:
	ConfigReader(void);
	~ConfigReader(void);
	
	void					ParseLine( const std::string&  line, std::map< std::string, std::vector<std::string> >& params, bool writeSequense = false);

	void					GenerateTestNames();
	void					GenerateTestConfigs();

	std::map< std::string, std::vector<std::string> > m_Params;
	std::map< std::string, std::vector<std::string> > m_Configs;

	std::map< std::string, FileConf > m_FileConfigs;
	
	std::string					m_CurrentTestFile;
	bool						m_bActivatedTestConf;

	std::vector<std::string>	m_TestQueue;
	std::vector<std::string>	m_TestName;
	std::vector<std::string>	m_TestConfig;

	bool						m_bLoopFound;

	static ConfigReader*		s_pInstance;
};

