#ifndef __FILE_WRITER_H__
#define __FILE_WRITER_H__

#include <fstream>
#include <optional>
#include <string>
#include <utility>

class FileWriter
{
private:
	std::ofstream _stream;
	std::string _file_name;

	FileWriter(std::ofstream &&stream, std::string file_name);

public:
	static std::unique_ptr<FileWriter> create(const std::string &file_name);

	~FileWriter();

	bool write_line(const std::string &data);
	const std::string &file_name();
	bool is_open();
};

#endif /* __FILE_WRITER_H__ */