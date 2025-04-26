#include "file_writer.h"

FileWriter::FileWriter(std::ofstream &&stream, std::string file_name)
    : _stream(std::move(stream)), _file_name(std::move(file_name)) {}

FileWriter::~FileWriter()
{
	if (_stream.is_open())
	{
		_stream.close();
	}
}

std::unique_ptr<FileWriter> FileWriter::create(const std::string &file_name)
{
	std::ofstream stream(file_name);
	if (!stream.is_open())
	{
		return nullptr;
	}

	return std::make_unique<FileWriter>(std::move(stream), file_name);
}

bool FileWriter::write_line(const std::string &data)
{
	if (!is_open())
	{
		return false;
	}
	_stream << data << "\n";
	return _stream.good();
}

const std::string &FileWriter::file_name()
{
	return _file_name;
}

bool FileWriter::is_open()
{
	return _stream.is_open();
}