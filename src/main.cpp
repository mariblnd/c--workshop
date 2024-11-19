#include <sil/sil.hpp>
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
        sil::Image image{500, 500};
        rosace(image,15);
        image.save("output/rosace.png");
    }
    
}