//#include "Shaders/include/shader.h"
//#include <glm/glm.hpp>
//std::string get_file_contents(const char* filename) {
//	std::ifstream in(filename, std::ios::binary);
//
//	if (in) {
//		std::string contents;
//		in.seekg(0, std::ios::end);
//		contents.resize(in.tellg());
//		in.seekg(0, std::ios::beg);
//		in.read(&contents[0], contents.size());
//		in.close();
//		return(contents);
//	}
//	throw(errno);
//}
//Shader::Shader(const char* vertexFile, const char* fragmentFile) {
//	std::string vertexCode = get_file_contents(vertexFile);
//	std::string fragmentCode = get_file_contents(vertexFile);
//
//	const char* vShaderCode = vertexCode.c_str();
//	const char* fShaderCode = fragmentCode.c_str();
//
//	unsigned int vertexShader, fragmentShader;
//
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
//	glCompileShader(vertexShader);
//	checkCompileErrors(vertexShader, "VERTEX");
//
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
//	glCompileShader(fragmentShader);
//	checkCompileErrors(vertexShader, "FRAGMENT");
//
//	ID = glCreateProgram();
//	glAttachShader(ID, vertexShader);
//	glAttachShader(ID, fragmentShader);
//	glLinkProgram(ID);
//	checkCompileErrors(ID, "PROGRAM");
//}
//
//
//void Shader::useShader() {
//	glUseProgram(ID);
//}
//void Shader::deleteShader() {
//	glDeleteProgram(ID);
//}
//
//
//void Shader::setBool(const std::string& name, bool value) const {
//	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
//}
//
//void Shader::setInt(const std::string& name, int value) const {
//	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
//}
//
//void Shader::setFloat(const std::string& name, float value) const {
//	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
//}
//
//void Shader::setVec2(const std::string& name, const glm::vec2& value) const
//{
//	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//}
//void Shader::setVec2(const std::string& name, float x, float y) const
//{
//	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
//}
//// ------------------------------------------------------------------------
//void Shader::setVec3(const std::string& name, const glm::vec3& value) const
//{
//	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//}
//void Shader::setVec3(const std::string& name, float x, float y, float z) const
//{
//	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
//}
//// ------------------------------------------------------------------------
//void Shader::setVec4(const std::string& name, const glm::vec4& value) const
//{
//	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//}
//void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
//{
//	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
//}
//// ------------------------------------------------------------------------
//void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
//{
//	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//}
//
//void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
//{
//	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//}
//
//void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
//{
//	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//}
//void Shader:: checkCompileErrors(unsigned int shader, std::string type) {
//
//	int success;
//	char infolog[1024];
//
//	if (type != "PROGRAM") {
//		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//		if (!success)
//		{
//			glGetShaderInfoLog(shader, 1024, NULL, infolog);
//			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infolog << "\n -- --------------------------------------------------- -- " << std::endl;
//		}
//
//	}
//	else {
//		glGetProgramiv(ID, GL_LINK_STATUS, &success);
//
//		if (!success) {
//			glGetProgramInfoLog(ID, 1024, NULL, infolog);
//			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infolog << "\n -- --------------------------------------------------- -- " << std::endl;
//		}
//	}
//};