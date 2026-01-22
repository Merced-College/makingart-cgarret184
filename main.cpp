// Garret Clark 1-22-26
// This program generates a mandelbrot html file that you can open in your browser and view. 

#include <iostream>
#include <fstream>

int main() {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const int MAX_ITER = 300;

    std::ofstream out("mandelbrot.html");
    if (!out) {
        std::cerr << "Error opening HTML output file\n";
        return 1;
    }

    out << "<!DOCTYPE html>\n<html>\n<body>\n";
    out << "<canvas id='c' width='" << WIDTH << "' height='" << HEIGHT << "'></canvas>\n";
    out << "<script>\n";
    out << "const canvas = document.getElementById('c');\n";
    out << "const ctx = canvas.getContext('2d');\n";
    out << "const img = ctx.createImageData(" << WIDTH << ", " << HEIGHT << ");\n";

    // Push Mandelbrot data into JS arrays
    out << "let data = img.data;\n";

    out << "let i = 0;\n";
    out << "for (let y = 0; y < " << HEIGHT << "; y++) {\n";
    out << "  for (let x = 0; x < " << WIDTH << "; x++) {\n";
    out << "    let zx = 0, zy = 0;\n";
    out << "    let cX = (x - " << WIDTH / 2 << ") / 150;\n";
    out << "    let cY = (y - " << HEIGHT / 2 << ") / 150;\n";
    out << "    let iter = " << MAX_ITER << ";\n";
    out << "    while (zx*zx + zy*zy < 4 && iter > 0) {\n";
    out << "      let tmp = zx*zx - zy*zy + cX;\n";
    out << "      zy = 2*zx*zy + cY;\n";
    out << "      zx = tmp;\n";
    out << "      iter--;\n";
    out << "    }\n";

    // Color 
    out << "    let color = iter | (iter << 8);\n";
    out << "    data[i++] = (color >> 16) & 255;\n";
    out << "    data[i++] = (color >> 8) & 255;\n";
    out << "    data[i++] = color & 255;\n";
    out << "    data[i++] = 255;\n";   // alpha
    out << "  }\n";
    out << "}\n";

    out << "ctx.putImageData(img, 0, 0);\n";
    out << "</script>\n</body>\n</html>\n";

    out.close();
    std::cout << "mandelbrot.html generated — open it in your cloud IDE's browser preview.\n";
    return 0;
}
