#include <exiv2/exiv2.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include <fstream>

using namespace std;
namespace fs = std::filesystem;

void MyCopy(const fs::path &from, const fs::path &to)
{
    std::ifstream fin(from, std::ios::binary | std::ios::in);
    fin.seekg(0, std::ios::end);
    size_t length = static_cast<size_t>(fin.tellg());
    fin.seekg(0, std::ios::beg);
    std::shared_ptr<uint8_t[]> data(new uint8_t[length]);
    fin.read(reinterpret_cast<char*>(data.get()), length);
    fin.close();

    std::ofstream fout(to, std::ios::binary | std::ios::out);
    fout.write(reinterpret_cast<char*>(data.get()), length);
    fout.close();
}

void Deidentify(const fs::path &oldPath, const fs::path &newPath)
{
    // filesystem impl is so lame for gcc
    // fs::copy_file(oldPath, newPath, fs::copy_options::overwrite_existing);
    MyCopy(oldPath, newPath);

    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(newPath.string().c_str());
    image->clearMetadata();
    image->writeMetadata();
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        cout << "Please enter at least one file to deidentify." << endl;
        return 0;
    }

    vector<fs::path> paths;
    for (int i = 1; i < argc; i++)
    {
        paths.push_back(fs::path(argv[i]));
    }

    for (const auto &path : paths)
    {
        fs::path newPath = path.stem().concat("_deidentified").concat(path.extension().string());

        cout << "Deidentifying " << path << "..." << endl;
        Deidentify(path, newPath);
    }

    cout << "Done." << endl;

    return 0;
}
