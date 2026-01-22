// Garret Clark 1-22-26
// This program generates a mandelbrot html file that you can open in your browser and view. 

#include <iostream>
#include <fstream>

// You can change these colors and add more.
const int PALETTE_SIZE = 5;

int red[PALETTE_SIZE]   = { 54, 250,  90,   10, 5 };
int green[PALETTE_SIZE] = { 243,  70,  10,   100, 25 };
int blue[PALETTE_SIZE]  = { 100, 260, 92, 150, 205 };

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

    // Color the pixels based on iteration count
    // iter is the number of iterations used for this pixel
    // Choose an index into the palette based on iter
    out << "    let index = iter % " << PALETTE_SIZE << ";\n";
    
    // Output pixel color data for all palette indices into JavaScript
    // This creates an array of color objects that will be used to look up colors
    out << "    let palette = [\n";
    for (int i = 0; i < PALETTE_SIZE; i++) {
        out << "      {r: " << red[i] << ", g: " << green[i] << ", b: " << blue[i] << "}";
        if (i < PALETTE_SIZE - 1) out << ",";
        out << "\n";
    }
    out << "    ];\n";
    
    // Get the color from the palette for this pixel's iteration count
    out << "    let color = palette[index];\n";
    // Write the red, green, and blue values to the image data
    out << "    data[i++] = color.r;\n";
    out << "    data[i++] = color.g;\n";
    out << "    data[i++] = color.b;\n";
    out << "    data[i++] = 255;\n"; // Alpha channel is always fully opaque (255)
    // Close the x and y loops
    out << "    }\n";
    out << "  }\n";
    out << "}\n";
    
    out << "ctx.putImageData(img, 0, 0);\n";
    out << "</script>\n</body>\n</html>\n";

    out.close();
    std::cout << "mandelbrot.html generated — open it in your cloud IDE's browser preview.\n";
    return 0;
}
