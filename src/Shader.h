#pragma once

#include <iostream>
#include <unordered_map>

using namespace std;



struct shaderProgramSource {
	string vertexSource;
	string fragmentSource;
};



class Shader {
private:
	string m_FilePath;
	unsigned int m_RendererID;
	unordered_map<string, int> m_UniformLOcationCache;
public:
	Shader(const string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const string& name, int value);
	void SetUniform1f(const string& name, float value);
	void SetUniform4f(const string& name, float v0, float v1, float f2, float f3);
private:
	shaderProgramSource parseShader(const string& filepath);
	unsigned int compileShader(unsigned int type, const string& source);
	unsigned int createShader(const string& vertexShader, const string& fragmentShader);
	int GetUniformLocation(const string& name);
};