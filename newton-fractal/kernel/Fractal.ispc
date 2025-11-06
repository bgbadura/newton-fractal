// simple struct that C++ and ISPC can understand
struct ComplexC {
    double re, im
};

inline ComplexC cAdd(ComplexC a, ComplexC b) {
    return {a.re + b.re, a.im + b.im};
}

inline ComplexC cSub(ComplexC a, ComplexC b) {
    return {a.re - b.re, a.im - b.im};
}

inline ComplexC cMul(ComplexC a, ComplexC b) {
    return {a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re};
}

inline ComplexC cPow(ComplexC a, uniform int n) {
    ComplexC result = {1.0, 0.0};
    for (uniform int i = 0; i < n; i++) {
        result = cMul(result, a);
    }
    return result;
}

inline ComplexC cDiv(ComplexC a, ComplexC b) {
    double denom = b.re * b.re + b.im * b.im;

    if (denom == 0.0) return {0.0, 0.0};

    return {a.re * b.re + a.im * b.im) / denom, (a.im * b.re - a.re * b.im) / denom};
}

// no need to calculate square roots
// when both sides of inequalities are over zero (distance < delta)
inline double cAbsSq(ComplexC a) {
    return a.re * a.re + a.im * a.im;
}

struct RGB {
    uint8 r, g, b;
};

struct RGB convertHslToRgb(double h, double s, double v) {
    double r = 0, g = 0, b = 0;
    double c = v * s;
    double hPrim = h / 60.0;

    double x = c * (1 - fabs(fmod(hPrim, 2.0) - 1.0));

    if (hPrim >= 0 && hPrim < 1)      { r = c; g = x; b = 0; }
    else if (hPrim >= 1 && hPrim < 2) { r = x; g = c; b = 0; }
    else if (hPrim >= 2 && hPrim < 3) { r = 0; g = c; b = x; }
    else if (hPrim >= 3 && hPrim < 4) { r = 0; g = x; b = c; }
    else if (hPrim >= 4 && hPrim < 5) { r = x; g = 0; b = c; }
    else if (hPrim >= 5 && hPrim < 6) { r = c; g = 0; b = x; }

    double m = v - c;

    struct RGB finalColor;
    finalColor.r = (uint8)((r + m) * 255);
    finalColor.g = (uint8)((g + m) * 255);
    finalColor.b = (uint8)((b + m) * 255);
    return finalColor;
}

struct RGB findPixelColour(ComplexC zStart,
                           uniform int n,
                           uniform int MAX_ITERATIONS,
                           uniform double DELTA_SQ,
                           uniform const ComplexC roots[])
{
    // Newton's fractal formula:    z_{k+1} = z_k - [ f(z_k) / f'(z_k) ]
    // value at point z:            f(z) = z^n - 1
    // derivative at point z:       f'(z) = n * z^(n-1)

    ComplexC z = zStart;

    for (uniform int i = 0; i < MAX_ITERATIONS; ++i) {
        ComplexC fZ  = cSub(cPow(z, n), {1.0, 0.0});
        ComplexC fPrimZ = cMul({(double)n, 0.0}, cPow(z, n - 1));
        ComplexC zNext = cSub(z, cDiv(fZ, fPrimZ));

        for (uniform int k = 0; k < n; ++k) {
            if (cAbsSq(cSub(zNext, roots[k])) < DELTA_SQ) {
                // "the color of the point is determined by which root is reached (hue),
                // and how many iterations it took (brightness)" - brightness is "value" in HSV

                double shadingConstant = 0.8;
                double v = 1.0 - ((double)i / MAX_ITERATIONS) * shadingConstant;
                double baseHue = ((double)k * 360.0 / n);
                return convertHslToRgb(baseHue, 1.0, v);
            }
        }
        z = zNext;
    }

    return {0, 0, 0};
}

export void generateFractalKernel(
    uniform int width, uniform int height,
    uniform double min_re, uniform double max_re, uniform double min_im, uniform double max_im,
    uniform int n, uniform int MAX_ITERATIONS, uniform double DELTA,
    uniform const ComplexC roots[],
    uniform uint8 output[]
) {

    // delta optimised for the inequality: distance^2 < delta^2
    // will give the same result as: distance < delta, without the need of calculating the square root
    uniform double DELTA_SQ = DELTA * DELTA;

    foreach (y = 0 ... height, x = 0 ... width) {
        // map a pixel (x,y) to a complex number: reZ and imZ
        ComplexC z0 = {
            min_re + ((x / (double)width) * (max_re - min_re)),
            max_im - ((y / (double)height) * (max_im - min_im))
        };

        struct RGB color = findPixelColour(z0, n, MAX_ITERATIONS, DELTA_SQ, roots);

        int index = (y * width + x) * 4; // RGBA

        output[index + 0] = color.r;
        output[index + 1] = color.g;
        output[index + 2] = color.b;
        output[index + 3] = 255;
    }
}