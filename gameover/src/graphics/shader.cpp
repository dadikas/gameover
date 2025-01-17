#include "gameover/graphics/shader.h"
#include "gameover/log.h"

#include "glad/glad.h"

#include "external/glm/gtc/type_ptr.hpp"

namespace gameover::graphics {
	Shader::Shader(const std::string& vertex, const std::string& fragment) {
		mProgramId = glCreateProgram();

		int status = GL_FALSE;
		char errorLog[512];

		uint32_t vertextShaderId = glCreateShader(GL_VERTEX_SHADER);
		{
			const GLchar* glSource = vertex.c_str();
			glShaderSource(vertextShaderId, 1, &glSource, NULL);
			glCompileShader(vertextShaderId);
			glGetShaderiv(vertextShaderId, GL_COMPILE_STATUS, &status);
			if (status != GL_TRUE) {
				glGetShaderInfoLog(vertextShaderId, sizeof(errorLog), NULL, errorLog);
				GAMEOVER_ERROR("Vertext Shader compilation error: {}", errorLog);
			}
			else {
				glAttachShader(mProgramId, vertextShaderId);
			}
		}

		uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		if(status == GL_TRUE){
			const GLchar* glSource = fragment.c_str();
			glShaderSource(fragmentShaderId, 1, &glSource, NULL);
			glCompileShader(fragmentShaderId);
			glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &status);
			if (status != GL_TRUE) {
				glGetShaderInfoLog(fragmentShaderId, sizeof(errorLog), NULL, errorLog);
				GAMEOVER_ERROR("Fragment Shader compilation error: {}", errorLog);
			}
			else {
				glAttachShader(mProgramId, fragmentShaderId);
			}
		}

		GAMEOVER_ASSERT(status = GL_TRUE, "Error compiling shader");
		if (status == GL_TRUE) {
			glLinkProgram(mProgramId);
			glValidateProgram(mProgramId);
			glGetProgramiv(mProgramId, GL_LINK_STATUS, &status);

			if (status != GL_TRUE) {
				glGetProgramInfoLog(mProgramId, sizeof(errorLog), NULL, errorLog);
				GAMEOVER_ERROR("Shader link error: {}", errorLog);
				glDeleteProgram(mProgramId);
				mProgramId = -1;
			}

		}

		glDeleteShader(vertextShaderId);
		glDeleteShader(fragmentShaderId);

	}

	Shader::~Shader() {
		glUseProgram(0);
		glDeleteProgram(mProgramId);
	}

	void Shader::Bind() {
		glUseProgram(mProgramId);
	}

	void Shader::Unbind() {
		glUseProgram(0);
	}

	void Shader::SetUniformInt(const std::string& name, int val)
	{
		glUseProgram(mProgramId);
		glUniform1i(GetUniformLocation(name), val);
	}


	void Shader::SetUniformFloat1(const std::string& name, float val1)
	{

		glUseProgram(mProgramId);
		glUniform1f(GetUniformLocation(name), val1);
	}

	void Shader::SetUniformFloat2(const std::string& name, float val1, float val2)
	{

		glUseProgram(mProgramId);
		glUniform2f(GetUniformLocation(name), val1, val2);
	}

	void Shader::SetUniformFloat2(const std::string& name, const glm::vec2& val)
	{
		SetUniformFloat2(name, val.x, val.y);
	}

	void Shader::SetUniformFloat3(const std::string& name, float val1, float val2, float val3)
	{

		glUseProgram(mProgramId);
		glUniform3f(GetUniformLocation(name), val1, val2, val3);
	}

	void Shader::SetUniformFloat3(const std::string& name, const glm::vec3& val)
	{
		SetUniformFloat3(name, val.x, val.y, val.z);

	}

	void Shader::SetUniformFloat4(const std::string& name, float val1, float val2, float val3, float val4)
	{

		glUseProgram(mProgramId);
		glUniform4f(GetUniformLocation(name), val1, val2, val3, val4);
	}

	void Shader::SetUniformFloat4(const std::string& name, const glm::vec4& val)
	{
		SetUniformFloat4(name, val.x, val.y, val.z, val.w);
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		auto it = mUniformLocations.find(name);
		if (it == mUniformLocations.end()) {
			mUniformLocations[name] = glGetUniformLocation(mProgramId, name.c_str());
		}

		return mUniformLocations[name];
	}

	void Shader::SetUniformMat3(const std::string& name, const glm::mat3& mat)
	{
		glUseProgram(mProgramId);
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::SetUniformMat4(const std::string& name, const glm::mat4& mat)
	{
		glUseProgram(mProgramId);
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
	}

}