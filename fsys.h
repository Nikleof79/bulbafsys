#include <iostream>

namespace filesystem
{
    using namespace std;
    /*
     * @param path its path to target file for reading
     * @return body of file that was in param 'path'
     */
    string readFile(string path)
    {
        // Открываем файл в бинарном режиме для чтения
        FILE *f = fopen(path.c_str(), "rb");
        if (!f)
        {
            throw runtime_error("Could not open file: " + path);
        }

        // Узнаем размер файла
        fseek(f, 0, SEEK_END);    // Перемещаем указатель в конец файла
        long fileSize = ftell(f); // Узнаем текущую позицию — это размер файла
        rewind(f);                // Возвращаем указатель в начало файла

        // Выделяем буфер для хранения данных файла
        string content(fileSize, '\0'); // Строка нужного размера

        // Читаем файл с помощью fread
        size_t bytesRead = fread(&content[0], 1, fileSize, f);
        if (bytesRead != fileSize)
        {
            throw runtime_error("Error reading file: " + path);
        }

        // Закрываем файл
        fclose(f);

        return content;
    }
    
    void writeFile(string path, string content)
    {
        FILE *f = fopen(path.c_str(), "wb");
        if (!f)
        {
            throw runtime_error("Could not open file for writing: " + path);
        }

        // Записываем данные в файл с помощью fwrite
        size_t bytesWritten = fwrite(content.c_str(), 1, content.size(), f);
        if (bytesWritten != content.size())
        {
            throw runtime_error("Error writing to file: " + path);
        }

        // Закрываем файл
        fclose(f);
    }
    void appendToFile(string path, string content)
    {
        writeFile(path,readFile(path) + content);
    }
}
