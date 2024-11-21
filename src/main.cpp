#include <sil/sil.hpp>
#include <cmath>
#include <complex>
#include "random.hpp"

void makeItGreen(sil::Image& image){


    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            //R = 0
            image.pixel(x, y).r = 0.f;
            //B=0
            image.pixel(x,y).b = 0.f;
        }
    }


}

void swapColor(sil::Image& image){


    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            //J'échange la valeur de R et B
            std::swap(image.pixel(x,y).r, image.pixel(x,y).b);

        }
    }


}

void blackAndWhite(sil::Image& image){


    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            //Conversion d'une couleur RGB en valeur de gris
            float gray = 0.59*image.pixel(x,y).g
                        +0.3*image.pixel(x,y).r 
                        +0.11*image.pixel(x,y).b;

            image.pixel(x, y) = {gray, gray, gray};

        }
    }

}

void negativeImage(sil::Image& image){


    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x,y) = {1 - image.pixel(x,y).r, 1 - image.pixel(x,y).g, 1 - image.pixel(x,y).b };
        }
    }

}

void makeAGradient(sil::Image& image){

float counter{1.f};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x,y) = {counter, counter, counter};
        }

         counter = counter - 0.005f;
}
}

void mirrorEffect(sil::Image& image) {
    int width = image.width();
    int height = image.height();

    for (int x = 0; x < width / 2; x++) {
        for (int y = 0; y < height; y++) {
            // Lire les pixels à gauche et à droite
            glm::vec3 pixelLeft = image.pixel(x, y);
            glm::vec3 pixelRight = image.pixel(width - x - 1, y);

            // Échanger les pixels après avoir sauvegardé leurs valeurs
            image.pixel(x, y) = pixelRight;
            image.pixel(width - x - 1, y) = pixelLeft;
        }
    }
}

void noisyEffect(sil::Image& image){

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            //Je calcule le coef avec lequel je vais multiplier RGB
            float coef{random_float(0.f, 1.f)};
            //Je définis la couleur du nouveau pixel
            glm::vec3 color = {image.pixel(x,y).r*coef,image.pixel(x,y).g*coef, image.pixel(x,y).b*coef };
            //Je l'assigne au pixel
            image.pixel(x,y)=color;
        }
    }
}

void rotateX(sil::Image& image) {
    int width = image.width();
    int height = image.height();

    sil::Image new_image{height, width};

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            new_image.pixel(y, x) = image.pixel(x, height - y - 1);
        }
    }

    image = new_image;
}

void rgbSplit(sil::Image& image) {
    int width = image.width();
    int height = image.height();

    sil::Image new_image{width, height};

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            new_image.pixel(x,y).g = image.pixel(x,y).g; 
            if(width>x+20){
                new_image.pixel(x,y).b = image.pixel(x+20,y).b;
            } else if(0<x-20){
               new_image.pixel(x,y).b = image.pixel(x-20,y).b; 
            }

        }
    }

    image = new_image;
}

void brightness(sil::Image& image, float coef) {
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            glm::vec3 pixel = image.pixel(x, y);

            //clamp permet de s'assurer que la valeur reste en 0 et 255
            //si pixel.r*1.2>255 alors =255
            pixel.r = glm::clamp(pixel.r * coef, 0.0f, 255.0f);
            pixel.g = glm::clamp(pixel.g * coef, 0.0f, 255.0f);
            pixel.b = glm::clamp(pixel.b * coef, 0.0f, 255.0f);

            image.pixel(x, y) = pixel;
        }
    }
}

void disc(sil::Image& image) {

    int rayon = 50;
    int x_centre = image.width()/2;
    int y_centre = image.height()/2;

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            if((x - x_centre) * (x - x_centre) + (y - y_centre) * (y - y_centre) <= rayon * rayon){
                image.pixel(x,y)={0,0,0};
            } else {
                image.pixel(x,y)={1,1,1};
            }
        }
    }
}

void circle(sil::Image& image, int thickness) {

    int rayon = 50;
    int x_centre = image.width()/2;
    int y_centre = image.height()/2;

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            if((x - x_centre) * (x - x_centre) + (y - y_centre) * (y - y_centre) >= (rayon * rayon)-(thickness*thickness) && (x - x_centre) * (x - x_centre) + (y - y_centre) * (y - y_centre) <= (rayon * rayon) ){
                image.pixel(x,y)={0,0,0};
            } else {
                image.pixel(x,y)={1,1,1};
            }
        }
    }
}

sil::Image animation() {

    sil::Image image {500,500};

    int width = image.width();
    int height = image.height();

    int rayon = 50;

    int x_centre = 0;
    int y_centre = image.height()/2;

    for(int i; i<30 ;i++){ 

        for (int x = 0; x < image.width(); x++) {

            for (int y = 0; y < image.height(); y++) {
                
                if((x - x_centre) * (x - x_centre) + (y - y_centre) * (y - y_centre) <= rayon * rayon){
                    image.pixel(x,y)={0,0,0};
                } else {
                    image.pixel(x,y)={1,1,1};
                }
            }
        }

    x_centre += 50;
    image.save("output/animation/diskframe"+std::to_string(i)+".png");

    }
    return image;
}

void rosace(sil::Image& image, int thickness) {
    int rayon = 100;
    double angle = M_PI / 3; 

    int x_centre = image.width() / 2;
    int y_centre = image.height() / 2;

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            bool condition = (x - x_centre) * (x - x_centre) + (y - y_centre) * (y - y_centre) >= (rayon * rayon)-(thickness*thickness) && (x - x_centre) * (x - x_centre) + (y - y_centre) * (y - y_centre) <= (rayon * rayon);
            if(condition){
                image.pixel(x,y)={1,1,1};
            } else {
                for(int i = 0; i <7; i++){
                    int new_x_centre = x_centre+rayon * std::cos(i * angle) ;
                    int new_y_centre = y_centre+rayon * std::sin(i * angle) ;

                    bool condition = (x - new_x_centre) * (x - new_x_centre) + (y - new_y_centre) * (y - new_y_centre) >= (rayon * rayon) - (thickness * thickness) &&
                                    (x - new_x_centre) * (x - new_x_centre) + (y - new_y_centre) * (y - new_y_centre) <= (rayon * rayon);

                    if(condition){
                       image.pixel(x,y)={1,1,1}; 
                    }

                }
            }
        }
    }
}


void mosaique(sil::Image& image, int coef) {

    sil::Image new_image{image.width(), image.height() };

    //Pour avoir la dimension d'une dimension
    //de la dalle
    int width = image.width() / coef;
    int height = image.height() / coef;


        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                // Index local de la dalle
                int x2 = x % width;
                int y2 = y % height;


                new_image.pixel(x,y) = image.pixel(x2*coef, y2*coef);
            }
        }
    
    
    image=new_image;
}


void mosaiqueMiroir(sil::Image& image, int coef) {
    sil::Image new_image{image.width(), image.height()};

    int width = image.width() / coef;
    int height = image.height() / coef;

    int counterX {0};
    int counterY{0};

    for (int x = 0; x < image.width(); x++) {
        
        int x2 = x % width;

        for (int y = 0; y < image.height(); y++) {

            int y2 = y % height;
            
            int real_x = x2 * coef;
            if (counterX % 2 == 1) {
                real_x = (width - 1 - x2) * coef;
            }

            int real_y = y2 * coef;
            if(counterY % 2 == 1){
                real_y = (height - 1 - y2) * coef;
            }


            new_image.pixel(x, y) = image.pixel(real_x, real_y);

            if (y2 == height - 1) {
                counterY++;
            }

        }
            counterY  = 0;
            if(x2 == width - 1){
            counterX++;
            }
    }

    image = new_image;
}

void glitch(sil::Image& image) {

    int width = image.width();
    int height = image.height();

    for (int i = 0; i < 100; i++)
    {
        //taille du rect
        int widthRect = random_int(10, 30);
        int heightRect = random_int(3, 10);

        //position max de X et Y
        int maxX = width - widthRect;
        int maxY = height - heightRect;

        //def du point de rect1
        int x1 = random_int(0, maxX);
        int y1 = random_int(0, maxY);

        //def du point de rect2
        int x2 = random_int(0, maxX);
        int y2 = random_int(0, maxY); 

        //rectangle 1
        sil::Image rect1 {widthRect,heightRect};
        //remplissage du rect1
        for (int i = 0; i < heightRect; i++)
        {
            for (int j = 0; j < widthRect; j++)
            {
                rect1.pixel(j,i) = image.pixel(x1 + j, y1 + i);
            }
            
        }

        //rectangle 2
        sil::Image rect2 {widthRect,heightRect};
        //remplissage du rect2
        for (int i = 0; i < heightRect; i++)
        {
            for (int j = 0; j < widthRect; j++)
            {
                rect2.pixel(j,i) = image.pixel(x2 + j, y2 + i);
            }
            
        }

        for (int i = 0; i < heightRect; i++)
        {
            for (int j = 0; j < widthRect; j++)
            {
                image.pixel(x1 + j,y1 + i)=rect2.pixel(j,i);
                image.pixel(x2 + j,y2 + i)=rect1.pixel(j,i);
                
            }
            
        }
        
        }

}

struct Lab {float L; float a; float b;};
struct RGB {float r; float g; float b;};

Lab linear_srgb_to_oklab(RGB c) 
{
    float l = 0.4122214708f * c.r + 0.5363325363f * c.g + 0.0514459929f * c.b;
	float m = 0.2119034982f * c.r + 0.6806995451f * c.g + 0.1073969566f * c.b;
	float s = 0.0883024619f * c.r + 0.2817188376f * c.g + 0.6299787005f * c.b;

    float l_ = cbrtf(l);
    float m_ = cbrtf(m);
    float s_ = cbrtf(s);

    return {
        0.2104542553f*l_ + 0.7936177850f*m_ - 0.0040720468f*s_,
        1.9779984951f*l_ - 2.4285922050f*m_ + 0.4505937099f*s_,
        0.0259040371f*l_ + 0.7827717662f*m_ - 0.8086757660f*s_,
    };
}

RGB oklab_to_linear_srgb(Lab c) 
{
    float l_ = c.L + 0.3963377774f * c.a + 0.2158037573f * c.b;
    float m_ = c.L - 0.1055613458f * c.a - 0.0638541728f * c.b;
    float s_ = c.L - 0.0894841775f * c.a - 1.2914855480f * c.b;

    float l = l_*l_*l_;
    float m = m_*m_*m_;
    float s = s_*s_*s_;

    return {
		+4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
		-1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
		-0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    };
}

void colorGradient(sil::Image& image){

RGB color1 = {0.9f, 0.6f, 0.2f};
RGB color2 = {0.2f, 0.5f, 0.5f};

//RGB TO OKLAB
Lab labColor1 = linear_srgb_to_oklab(color1);
Lab labColor2 = linear_srgb_to_oklab(color2);

// float r1 = 0.9f;
// float r2 = 0.2f;

// float g1 = 0.1f;
// float g2 = 0.5f;

// float b1 = 0.2f;
// float b2 = 0.5f;

// glm::vec3 color1 = {r1,g1,b1};
// glm::vec3 color2 = {r2,g2,b2};

//coef
float coef_step = 1.0f / image.width();
float coef = 0.0f;

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            // Mélange dans l'espace Oklab
            Lab mixedLab = {
                labColor1.L + coef * (labColor2.L - labColor1.L),
                labColor1.a + coef * (labColor2.a - labColor1.a),
                labColor1.b + coef * (labColor2.b - labColor1.b),
            };

            // Conversion en sRGB linéaire
            RGB mixedRGB = oklab_to_linear_srgb(mixedLab);

            // Affectation du pixel (assurez-vous que les valeurs sont dans [0, 1])
            image.pixel(x, y) = glm::vec3(
                std::clamp(mixedRGB.r, 0.0f, 1.0f),
                std::clamp(mixedRGB.g, 0.0f, 1.0f),
                std::clamp(mixedRGB.b, 0.0f, 1.0f)
            );
        }

        // Incrémenter le coefficient pour la prochaine colonne
        coef += coef_step;
    }
}

void fractale(sil::Image& image) {

    int width = image.width();
    int height = image.height();

    for (int px = 0; px < width; px++) {
        for (int py = 0; py < height; py++) {
        

        float x = (px / (float)width) * 4.0f - 2.0f;  // Maps to [-2, 2]
        float y = (py / (float)height) * 4.0f - 2.0f;

            std::complex<float> c = {x, y};
            std::complex<float> z = {0, 0};

            int counter = 0;

            while (std::abs(z) <= 2.0f && counter < 1000) {
            z = z * z + c;
            counter++;
}

            float intensity = counter / 10.0f;
            image.pixel(px, py) = {intensity, intensity, intensity};  // Échelle de gris

            }
        }
    }

    void tramage(sil::Image& image) {

        int width = image.width();
        int height = image.height();
        

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                
            }
        }
    }





int main()
{

    {
        sil::Image image{"images/logo.png"};
        makeItGreen(image);
        image.save("output/green.png");
    }

    {
        sil::Image image{"images/logo.png"};
        swapColor(image);
        image.save("output/swapcolor.png");  
    }

    {
        sil::Image image{"images/logo.png"};
        blackAndWhite(image);
        image.save("output/blackandwhite.png");  
    }

    {
        sil::Image image{"images/logo.png"};
        negativeImage(image);
        image.save("output/negative.png");  
    }

    {
        sil::Image image{300, 200};
        makeAGradient(image);
        image.save("output/gradient.png");  
    }

    {
        sil::Image image{"images/logo.png"};
        mirrorEffect(image);
        image.save("output/mirror.png");  
    }

    {
        sil::Image image{"images/logo.png"};
        noisyEffect(image);
        image.save("output/noisy.png");    
    }

    {
        sil::Image image{"images/logo.png"};
        rotateX(image); 
        image.save("output/rotateX.png"); 
    }

    {
        sil::Image image{"images/logo.png"};
        rgbSplit(image); 
        image.save("output/rgbSplit.png"); 
    }

    {
        sil::Image image{"images/photo.jpg"};
        brightness(image, 0.1f);
        image.save("output/brightness.jpg");
    }

    {
        sil::Image image{300, 300};
        disc(image);
        image.save("output/disc.jpg");
    }

    {
        sil::Image image{300, 300};
        circle(image, 15);
        image.save("output/circle.jpg");
    }
    {
        sil::Image image{animation()};
    }
    {
        sil::Image image{"images/logo.png"};
        mosaique(image,4);
        image.save("output/mosaique.png");
    }

    {
        sil::Image image{"images/logo.png"};
        mosaiqueMiroir(image,5);
        image.save("output/mosaiquemiroir.png");
    }

    {
        sil::Image image{"images/logo.png"};
        glitch(image);
        image.save("output/glitch.png");
    }

    {
        sil::Image image{300, 200};
        colorGradient(image);
        image.save("output/colorgradient.png");  
    }

    {
        sil::Image image{500, 500};
        fractale(image);
        image.save("output/fractale.png");  
    }

    {
        sil::Image image{"images/photo.jpg"};
        tramage(image);
        image.save("output/tramage.jpg");  
    }

    
}