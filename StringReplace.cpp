/**
*  @函数strReplace
*  实现了高效率的子串检测
*  将主串str中所有符合的子串oldStr替换为输入参数中的newStr
*/
#include<string>


void strReplace(std::string& str,
	const std::string& oldStr,
	const std::string& newStr)
{
	std::string::size_type pos = 0u;
	while ((pos = str.find(oldStr, pos)) != std::string::npos) {
		str.replace(pos, oldStr.length(), newStr);
		pos += newStr.length();
	}
}
