#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>

void printProgress(size_t current, size_t total) {
    const int barWidth = 50;
    float progress = float(current) / float(total);

    std::cout << "\r[";
    int pos = progress * barWidth;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "%";
    std::cout.flush();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ezFlash <iso> <output>\n";
        return 1;
    }

    const char* isoPath = argv[1];
    const char* outPath = argv[2];

    struct stat st;
    if (stat(isoPath, &st) != 0) {
        perror("stat");
        return 1;
    }
    size_t totalSize = st.st_size;

    int iso = open(isoPath, O_RDONLY);
    if (iso < 0) {
        perror("open iso");
        return 1;
    }

    int out = open(outPath, O_WRONLY | O_CREAT, 0666);
    if (out < 0) {
        perror("open output");
        close(iso);
        return 1;
    }

    std::vector<char> buffer(1024 * 1024); // 1MB buffer
    ssize_t r;
    size_t written = 0;

    while ((r = read(iso, buffer.data(), buffer.size())) > 0) {
        ssize_t w = write(out, buffer.data(), r);
        if (w != r) {
            perror("write");
            close(iso);
            close(out);
            return 1;
        }

        written += w;
        printProgress(written, totalSize);
    }

    if (r < 0) perror("read");

    std::cout << "\nDone.\n";

    close(iso);
    close(out);
    return 0;
}
