#include "shader.h"
#include <iostream>


void Shader::checkCompileErrors(unsigned int object, std::string type)
{
	int success;
	char infoLog[512];
	if (type != "PROGRAM")
	{
		// 컴파일 에러 체크
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 512, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		// linking error 체크
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}
	return;
}

Shader& Shader::Use()
{
	glUseProgram(ID);
	return *this;
}

void Shader::Compile(const char* vertexCode, const char* fragmentCode)
{
	// 쉐이더 컴파일
	unsigned int vertexShader, fragmentShader;
	// vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);		// 쉐이더 종류 알려줌
	glShaderSource(vertexShader, 1, &vertexCode, NULL);		// 쉐이더 소스 코드 붙임
	glCompileShader(vertexShader);		// 컴파일
	checkCompileErrors(vertexShader, "VERTEX");
	// fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);		// 컴파일
	checkCompileErrors(fragmentShader, "FRAGMENT");

	// 컴파일한 쉐이더를 shader program에 link
	ID = glCreateProgram();		// id 반환하는 함수
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);		// 링크가 끝난 후에는 shader objects 지워도 됨

	return;
}

void Shader::SetFloat(const char* name, float value, bool useShader = false)
{
	if (useShader)
		Use();
	glUniform1f(glGetUniformLocation(ID, name), value);
	return;
}
void Shader::SetInteger(const char* name, int value, bool useShader = false)
{
	if (useShader)
		Use();
	glUniform1i(glGetUniformLocation(ID, name), value);
	return;
}
void Shader::SetVector2f(const char* name, float x, float y, bool useShader = false)
{
	if (useShader)
		Use();
	glUniform2f(glGetUniformLocation(ID, name), x, y);
	return;
}
void Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader = false)
{
	if (useShader)
		Use();
	glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
	return;
}
void Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader = false)
{
	if (useShader)
		Use();
	glUniform3f(glGetUniformLocation(ID, name), x, y, z);
	return;
}
void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader = false)
{
	if (useShader)
		Use();
	glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
	return;
}
void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false)
{
	if (useShader)
		Use();
	glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
	return;
}
void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader = false)
{
	if (useShader)
		Use();
	glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
	return;
}
void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false)
{
	if (useShader)
		Use();
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, false, glm::value_ptr(matrix));
	return;
}